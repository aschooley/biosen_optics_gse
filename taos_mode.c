
/*******************************************************************************
 *
 * taos_mode.c
 *
 * addresses the taos/led stack for biosentinel
 *
 * August 2015
 * A.Schooley
 *
 ******************************************************************************/

#include <driverlib.h>
#include "taos_mode.h"
#include "hal_LCD.h"
#include "stdbool.h"

static struct
{
	volatile unsigned char well_index;
}g={0,0};

static void update_screen(void);

void set_address_lines(void)
{
	uint16_t p9out_save = P9OUT;
	p9out_save &= ~0x3F;
	p9out_save |= g.well_index;
	P9OUT = p9out_save;
}
void taos_increment_well(void){
	g.well_index++;
	g.well_index %= taos_max_well_number;

	set_address_lines();

	return;
}
void taos_decrement_well(void){
	g.well_index--;
	g.well_index %= taos_max_well_number;

	set_address_lines();

	return;
}


unsigned char taos_get_current_well(void)
{
	return g.well_index;
}

bool taos_set_current_well(unsigned char index)
{
	bool success = false;

	if(0 <= index && taos_max_well_number > index)
	{
		g.well_index = index;

		set_address_lines();
		success = true;
	}

	return success;

}
void taos_output_enable(void){
	GPIO_setOutputHighOnPin(GPIO_PORT_P9, GPIO_PIN6);
}
void taos_output_disable(void){
	GPIO_setOutputLowOnPin(GPIO_PORT_P9, GPIO_PIN6);
}

void taos_mode_init(void){
	GPIO_setOutputLowOnPin(GPIO_PORT_P9, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6);
	GPIO_setAsOutputPin(GPIO_PORT_P9, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5|GPIO_PIN6);
}
void taos_mode(void){

	return;
}

char * taos_translate_well_index(unsigned char index)
{
	return ((char *)taos_well_lookup_table[index]);
}
