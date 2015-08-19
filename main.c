/* --COPYRIGHT--,BSD
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/*******************************************************************************
 *
 * main.c
 *
 * Out of Box Demo for the MSP-EXP430FR6989
 * Main loop, initialization, and interrupt service routines
 *
 * This demo provides 2 application modes: Stopwatch Mode and Temperature Mode
 *
 * The stopwatch mode provides a simple stopwatch application that supports split
 * time, where the display freezes while the stopwatch continues running in the
 * background.
 *
 * The temperature mode provides a simple thermometer application using the
 * on-chip temperature sensor. Display toggles between C/F.
 *
 * February 2015
 * E. Chen
 *
 ******************************************************************************/

#include <driverlib.h>
#include "taos_mode.h"
#include "hal_LCD.h"
#include "stdio.h"
#include "string.h"
#include "stdbool.h"

#define DEFAULT_MODE        0
#define SPRINTF_BUFFER_SIZE  20

typedef struct{
	bool debounce_b1;
	bool debounce_b2;
	unsigned int b1_and_b2_holdCount;
}debounce_t;

typedef struct{
	unsigned int counter;
	int centisecond;
	Calendar time;
}rtc_t;

typedef struct{
	unsigned int overflow;
	unsigned char freq_array_index;
	unsigned int freq_array[10];
}timer_t;

static struct {
	volatile bool running;
	volatile unsigned char mode;
	volatile debounce_t buttons;
	volatile rtc_t current_time;
	volatile rtc_t last_sample_time;
	volatile timer_t timer;
	volatile bool update_display;
}g={false,DEFAULT_MODE,{false,false,0},{0,0,},{0,0,},{0,false,{}},false};


char sprintf_buffer[SPRINTF_BUFFER_SIZE];

// TimerA0 UpMode Configuration Parameter
Timer_A_initUpModeParam initUpParam_A0 =
{
        TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source
        TIMER_A_CLOCKSOURCE_DIVIDER_1,          // SMCLK/4 = 2MHz
        30000,                                  // 15ms debounce period
        TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
		TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE ,    // Enable CCR0 interrupt
        TIMER_A_DO_CLEAR,                       // Clear value
        true                                    // Start Timer
};


// TimerA1 UpMode Configuration Parameter
Timer_A_initContinuousModeParam initContinuousParam_A1 =
{
		TIMER_A_CLOCKSOURCE_SMCLK,
		TIMER_A_CLOCKSOURCE_DIVIDER_1,
		TIMER_A_TAIE_INTERRUPT_ENABLE,
		TIMER_A_SKIP_CLEAR,
		false
};
Timer_A_initCaptureModeParam initCaptureParam_A1_2 =
{
		TIMER_A_CAPTURECOMPARE_REGISTER_2,
		TIMER_A_CAPTUREMODE_RISING_EDGE,
		TIMER_A_CAPTURE_INPUTSELECT_CCIxA,
		TIMER_A_CAPTURE_SYNCHRONOUS,
		TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,
		TIMER_A_OUTPUTMODE_OUTBITVALUE
};

Timer_A_initContinuousModeParam initContinuousParam_A2 =
{
		TIMER_A_CLOCKSOURCE_SMCLK,
		TIMER_A_CLOCKSOURCE_DIVIDER_64,
		TIMER_A_TAIE_INTERRUPT_ENABLE,
		TIMER_A_SKIP_CLEAR,
		true
};

// Initialization calls
void Init_GPIO(void);
void Init_Clock(void);
void Init_Timer(void);
void init_uart(void);

int fputc(int _c, register FILE *_fp);
int fputs(const char *_ptr, register FILE *_fp);

void print_to_lcd( char string[]);

void reset_rtc_timer(void)
{
	//Setup Current Time for Calendar
	g.current_time.time.Seconds = 0x00;
	g.current_time.time.Minutes = 0x00;
	g.current_time.time.Hours = 0x00;
	g.current_time.time.DayOfWeek = 0x04;
	g.current_time.time.DayOfMonth = 0x30;
	g.current_time.time.Month = 0x04;
	g.current_time.time.Year = 0x2015;
	g.current_time.centisecond = 0;

	g.last_sample_time = g.current_time;

	RTC_C_initCounter(RTC_C_BASE, RTC_C_CLOCKSELECT_32KHZ_OSC, RTC_C_COUNTERSIZE_16BIT);
	RTC_C_initCalendar(RTC_C_BASE,
					   &g.current_time.time,
					   RTC_C_FORMAT_BINARY);
}
/*
 * Main routine
 */
int main(void) {
    // Stop watchdog timer
    WDT_A_hold(__MSP430_BASEADDRESS_WDT_A__);

    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PMM_unlockLPM5();

    //enable interrupts
    __enable_interrupt();

    // Initializations
    Init_GPIO();
    Init_Clock();
    Init_LCD();
    Init_Timer();
    init_uart();

    RTC_C_initCounter(RTC_C_BASE, RTC_C_CLOCKSELECT_32KHZ_OSC, RTC_C_COUNTERSIZE_16BIT);
                    RTC_C_definePrescaleEvent(RTC_C_BASE, RTC_C_PRESCALE_1, RTC_C_PSEVENTDIVIDER_32);
                    RTC_C_enableInterrupt(RTC_C_BASE, RTC_C_PRESCALE_TIMER1_INTERRUPT);
                    RTC_C_startClock(RTC_C_BASE);


    // Set RTC modulo to 327-1 to trigger interrupt every ~10 ms
	RTC_C_holdClock(RTC_C_BASE);

	// Clear stopwatch
	reset_rtc_timer();

	RTC_C_definePrescaleEvent(RTC_C_BASE, RTC_C_PRESCALE_0, RTC_C_PSEVENTDIVIDER_32);
	RTC_C_enableInterrupt(RTC_C_BASE, RTC_C_PRESCALE_TIMER0_INTERRUPT | RTC_C_CLOCK_READ_READY_INTERRUPT | RTC_C_TIME_EVENT_INTERRUPT);
	RTC_C_startCounterPrescale(RTC_C_BASE, RTC_C_PRESCALE_0);

	 RTC_C_startClock(RTC_C_BASE);








    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN2);

    __enable_interrupt();

    static char const * const welcome_message = "BIOSENTINEL OPTICS GSE V01";
    displayScrollText((char *)welcome_message);
    printf("%s\r\n",welcome_message);

#if 0
    Timer_A_initContinuousMode(TIMER_A2_BASE,&initContinuousParam_A2);
#endif
    
    while(1)
    {

    	if(g.update_display)
    	{
    		if(g.running)
    		{
    			static char const * const run_string = "RUN";
    			print_to_lcd(run_string);
    		}
    		else
    		{
    			static char const * const stop_string = "STOP";
    			print_to_lcd(stop_string);
    		}
    		g.update_display=false;
    	}

    	g.current_time.time = RTC_C_getCalendarTime(RTC_C_BASE);

    	if(g.running==true && g.current_time.time.Seconds > 5)//if(g.update_display)
    	{
    		reset_rtc_timer();
    		 RTC_C_startClock(RTC_C_BASE);

    		printf("time");

    		taos_set_current_well(0);
    		for(; taos_get_current_well()<taos_max_well_number-1; taos_increment_well() )
    		{
    			printf(",%d",taos_get_current_well());

				Timer_A_enableInterrupt(TIMER_A1_BASE);
				Timer_A_enableCaptureCompareInterrupt(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2);
				Timer_A_startCounter(TIMER_A1_BASE,TIMER_A_CONTINUOUS_MODE);

				while(g.timer.freq_array_index<10)
				{
				}

				unsigned long avg = ((g.timer.overflow + g.timer.freq_array[9]) - g.timer.freq_array[1])>>3;

				sprintf(sprintf_buffer,"%f",8000000.0/(double)avg);
				printf(",%s",sprintf_buffer);
				print_to_lcd(&sprintf_buffer);

				g.update_display=false;
				Timer_A_stop(TIMER_A1_BASE);
				Timer_A_disableCaptureCompareInterrupt(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2);
				g.timer.overflow=0;
				g.timer.freq_array_index=0;
    		}
    		printf("\r\n");
    	}
    }
}


/*
 * GPIO Initialization
 */
void Init_GPIO()
{
    // Set all GPIO pins to output low to prevent floating input and reduce power consumption
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P7, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P9, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);

    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P7, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P9, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6|GPIO_PIN7);

    GPIO_setAsInputPin(GPIO_PORT_P3, GPIO_PIN5);
    GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN3);//AJS
    GPIO_setAsPeripheralModuleFunctionInputPin(
    		GPIO_PORT_P1,
			GPIO_PIN3,
			GPIO_PRIMARY_MODULE_FUNCTION
			);

    // Configure button S1 (P1.1) interrupt
    GPIO_selectInterruptEdge(GPIO_PORT_P1, GPIO_PIN1, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);

    // Configure button S2 (P1.2) interrupt
    GPIO_selectInterruptEdge(GPIO_PORT_P1, GPIO_PIN2, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN2);
    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN2);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN2);

    // Set P4.1 and P4.2 as Secondary Module Function Input, LFXT.
    GPIO_setAsPeripheralModuleFunctionInputPin(
           GPIO_PORT_PJ,
           GPIO_PIN4 + GPIO_PIN5,
           GPIO_PRIMARY_MODULE_FUNCTION
           );

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PMM_unlockLPM5();
}

/*
 * Clock System Initialization
 */
void Init_Clock()
{
    // Set DCO frequency to default 8MHz
    CS_setDCOFreq(CS_DCORSEL_0, CS_DCOFSEL_6);

    // Configure MCLK and SMCLK to 8MHz
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    // Intializes the XT1 crystal oscillator
    CS_turnOnLFXT(CS_LFXT_DRIVE_3);
}

/*
 * Timer Initialization
 */
void Init_Timer(void)
{
	Timer_A_initCaptureMode(TIMER_A1_BASE,&initCaptureParam_A1_2);
	Timer_A_initContinuousMode(TIMER_A1_BASE,&initContinuousParam_A1);
	//Timer_A_enableCaptureCompareInterrupt(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2);
	//Timer_A_startCounter(TIMER_A1_BASE,TIMER_A_CONTINUOUS_MODE);
	
}

/*
 * UART Initialization
 */
void init_uart(void)
{
	EUSCI_A_UART_initParam uart_a1_param={
			EUSCI_A_UART_CLOCKSOURCE_ACLK,
			3,
			0,
			146,
			EUSCI_A_UART_NO_PARITY,
			EUSCI_A_UART_LSB_FIRST,
			EUSCI_A_UART_ONE_STOP_BIT,
			EUSCI_A_UART_MODE,
			EUSCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION
	};

	GPIO_setAsInputPin(GPIO_PORT_P3, GPIO_PIN5);//AJS
	GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN4);
	GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN4);

	GPIO_setAsPeripheralModuleFunctionInputPin(
			GPIO_PORT_P3,
			GPIO_PIN5,
			GPIO_PRIMARY_MODULE_FUNCTION
			);
	GPIO_setAsPeripheralModuleFunctionOutputPin(
			GPIO_PORT_P3,
			GPIO_PIN4,
			GPIO_PRIMARY_MODULE_FUNCTION
			);

	EUSCI_A_UART_init(EUSCI_A1_BASE,&uart_a1_param);
	EUSCI_A_UART_enable(EUSCI_A1_BASE);
}

int fputc(int _c, register FILE *_fp)
{
	// Wait for peripherial to be available
	while (!EUSCI_A_UART_getInterruptStatus(EUSCI_A1_BASE,EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG));//while(!(UCA1IFG&UCTXIFG));
	// Stuff byte into tx reg
	EUSCI_A_UART_transmitData(EUSCI_A1_BASE,_c);//UCA1TXBUF = (unsigned char) _c;
	// Return tx'd byte, for giggles I suppose
	return((unsigned char)_c);
}

int fputs(const char *_ptr, register FILE *_fp)
{
	// Vars to iterate over the string
	uint16_t i, len;

	// Get the length of the string
	len = strlen(_ptr);

	// Loop over each byte of the string
	for(i=0 ; i<len ; i++)
	{
		// Wait for the peripherial to be available
		while (!EUSCI_A_UART_getInterruptStatus(EUSCI_A1_BASE,EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG));//while(!(UCA1IFG&UCTXIFG));
		// Stuff byte into the tx reg
		EUSCI_A_UART_transmitData(EUSCI_A1_BASE,_ptr[i]);//UCA1TXBUF = (unsigned char) _ptr[i];
	}

	// Return the number of bytes sent
	return len;
}

void print_to_lcd(char string[])
{
	int i;
	int j=0;
	int pos_map[]={pos1,pos2,pos3,pos4,pos5,pos6};
	clearLCD();
	for(i=0;i<6 && string[i]!=0;i++)
	{
		if(string[j]=='.')
		{
			LCDMEM[pos_map[i-1]+1] |= 0x01;
			j++;
		}
		showChar(string[j],pos_map[i]);
		j++;
	}
}

/*
 * RTC Interrupt Service Routine
 * Wakes up every ~10 milliseconds to update stowatch
 */
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=RTC_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(RTC_VECTOR)))
#endif
void RTC_ISR(void)
{
    switch(__even_in_range(RTCIV, 16))
    {
    case RTCIV_NONE: break;      //No interrupts
    case RTCIV_RTCOFIFG: break;      //RTCOFIFG
    case RTCIV_RTCRDYIFG:             //RTCRDYIFG
        g.current_time.counter = RTCPS;
        g.current_time.centisecond = 0;
        __bic_SR_register_on_exit(LPM3_bits);
        break;
    case RTCIV_RTCTEVIFG:             //RTCEVIFG
        //Interrupts every minute
        __no_operation();
        break;
    case RTCIV_RTCAIFG:             //RTCAIFG
        __no_operation();
        break;
    case RTCIV_RT0PSIFG:
        g.current_time.centisecond = RTCPS - g.current_time.counter;
        __bic_SR_register_on_exit(LPM3_bits);
        break;     //RT0PSIFG
    case RTCIV_RT1PSIFG:
        __bic_SR_register_on_exit(LPM3_bits);
        break;     //RT1PSIFG

    default: break;
    }
}

/*
 * PORT1 Interrupt Service Routine
 * Handles S1 and S2 button press interrupts
 */
#pragma vector = PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{
    switch(__even_in_range(P1IV, P1IV_P1IFG7))
    {
        case P1IV_NONE : break;
        case P1IV_P1IFG0 : break;
        case P1IV_P1IFG1 :    // Button S1 pressed
            P1OUT |= BIT0;    // Turn LED1 On
            if ( g.buttons.debounce_b1 == false)
            {
                // Set debounce flag on first high to low transition
            	g.buttons.debounce_b1 = true;
                g.buttons.b1_and_b2_holdCount = 0;
                switch (g.mode)
                {
                	case DEFAULT_MODE:
						g.running = true;
						g.update_display=true;
						break;
                }

                // Start debounce timer
                Timer_A_initUpMode(TIMER_A0_BASE, &initUpParam_A0);
            }
            break;
        case P1IV_P1IFG2 :    // Button S2 pressed
            P9OUT |= BIT7;    // Turn LED2 On
            if (g.buttons.debounce_b2 == false)
            {
                // Set debounce flag on first high to low transition
            	g.buttons.debounce_b2 = true;
            	g.buttons.b1_and_b2_holdCount = 0;
                switch (g.mode)
                {
                	case DEFAULT_MODE:
						g.running = false;
						g.update_display=true;
                		break;
                }

                // Start debounce timer
                Timer_A_initUpMode(TIMER_A0_BASE, &initUpParam_A0);
            }
            break;
        case P1IV_P1IFG3 : break;
        case P1IV_P1IFG4 : break;
        case P1IV_P1IFG5 : break;
        case P1IV_P1IFG6 : break;
        case P1IV_P1IFG7 : break;
    }
}

/*
 * Timer A0 Interrupt Service Routine
 * Used as button debounce timer
 */
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR (void)
{
    // Both button S1 & S2 held down
    if (!(P1IN & BIT1) && !(P1IN & BIT2))
    {
    	g.buttons.b1_and_b2_holdCount++;
        if (g.buttons.b1_and_b2_holdCount == 40)
        {
            // Stop Timer A0
            Timer_A_stop(TIMER_A0_BASE);

            // Change mode

            __bic_SR_register_on_exit(LPM3_bits);                // exit LPM3
        }
    }

    // Button S1 released
    if (P1IN & BIT1)
    {
    	g.buttons.debounce_b1 = false;                                   // Clear button debounce
        P1OUT &= ~BIT0;
    }

    // Button S2 released
    if (P1IN & BIT2)
    {
    	g.buttons.debounce_b2 = false;                                   // Clear button debounce
        P9OUT &= ~BIT7;
    }

    // Both button S1 & S2 released
    if ((P1IN & BIT1) && (P1IN & BIT2))
    {
        // Stop timer A0
        Timer_A_stop(TIMER_A0_BASE);
    }

    if (g.mode == DEFAULT_MODE)
        __bic_SR_register_on_exit(LPM3_bits);            // exit LPM3
}

/*
 * ADC 12 Interrupt Service Routine
 * Wake up from LPM3 to display temperature
 */
#pragma vector=ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
    switch(__even_in_range(ADC12IV,12))
    {
    case  0: break;                         // Vector  0:  No interrupt
    case  2: break;                         // Vector  2:  ADC12BMEMx Overflow
    case  4: break;                         // Vector  4:  Conversion time overflow
    case  6: break;                         // Vector  6:  ADC12BHI
    case  8: break;                         // Vector  8:  ADC12BLO
    case 10: break;                         // Vector 10:  ADC12BIN
    case 12:                                // Vector 12:  ADC12BMEM0 Interrupt
        ADC12_B_clearInterrupt(ADC12_B_BASE, 0, ADC12_B_IFG0);
        __bic_SR_register_on_exit(LPM3_bits);   // Exit active CPU
        break;                              // Clear CPUOFF bit from 0(SR)
    case 14: break;                         // Vector 14:  ADC12BMEM1
    case 16: break;                         // Vector 16:  ADC12BMEM2
    case 18: break;                         // Vector 18:  ADC12BMEM3
    case 20: break;                         // Vector 20:  ADC12BMEM4
    case 22: break;                         // Vector 22:  ADC12BMEM5
    case 24: break;                         // Vector 24:  ADC12BMEM6
    case 26: break;                         // Vector 26:  ADC12BMEM7
    case 28: break;                         // Vector 28:  ADC12BMEM8
    case 30: break;                         // Vector 30:  ADC12BMEM9
    case 32: break;                         // Vector 32:  ADC12BMEM10
    case 34: break;                         // Vector 34:  ADC12BMEM11
    case 36: break;                         // Vector 36:  ADC12BMEM12
    case 38: break;                         // Vector 38:  ADC12BMEM13
    case 40: break;                         // Vector 40:  ADC12BMEM14
    case 42: break;                         // Vector 42:  ADC12BMEM15
    case 44: break;                         // Vector 44:  ADC12BMEM16
    case 46: break;                         // Vector 46:  ADC12BMEM17
    case 48: break;                         // Vector 48:  ADC12BMEM18
    case 50: break;                         // Vector 50:  ADC12BMEM19
    case 52: break;                         // Vector 52:  ADC12BMEM20
    case 54: break;                         // Vector 54:  ADC12BMEM21
    case 56: break;                         // Vector 56:  ADC12BMEM22
    case 58: break;                         // Vector 58:  ADC12BMEM23
    case 60: break;                         // Vector 60:  ADC12BMEM24
    case 62: break;                         // Vector 62:  ADC12BMEM25
    case 64: break;                         // Vector 64:  ADC12BMEM26
    case 66: break;                         // Vector 66:  ADC12BMEM27
    case 68: break;                         // Vector 68:  ADC12BMEM28
    case 70: break;                         // Vector 70:  ADC12BMEM29
    case 72: break;                         // Vector 72:  ADC12BMEM30
    case 74: break;                         // Vector 74:  ADC12BMEM31
    case 76: break;                         // Vector 76:  ADC12BRDY
    default: break;
    }
}

// Timer capture interrupt
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TACCR1_ISR(void)
{

}

// Timer_A3 Interrupt Vector (TA0IV) handler
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TA0IV_ISR(void)
{
	unsigned char TA1IV_save = TA1IV;

	if(TA1IV_save == 0x04)
	{

		g.timer.freq_array[g.timer.freq_array_index]=TA1CCR2;
		g.timer.freq_array_index++;
		if (g.timer.freq_array_index==10)
		{
			Timer_A_stop(TIMER_A1_BASE);
			Timer_A_disableCaptureCompareInterrupt(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2);
			Timer_A_disableInterrupt(TIMER_A1_BASE);
			Timer_A_clear(TIMER_A1_BASE);
		}
	}

	// after the counter overflow increment the counter with 65536
	//if(Timer_A_getCaptureCompareInterruptStatus(TIMER_A1_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2,TIMER_A_CAPTURE_OVERFLOW))
	if(TA1IV_save == 0x0E)
	{
		if(g.timer.freq_array_index>1){
			g.timer.overflow += 0x10000;
		}
	}
}

#if 0
#pragma vector=TIMER2_A1_VECTOR
__interrupt void TIMER2_A0_ISR (void)
{
	if(TA2IV== 0x0E)
	{
		g.update_display=true;
	}
}
#endif

