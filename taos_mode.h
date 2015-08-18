/*******************************************************************************
 *
 * taos_mode.h
 *
 * addresses the taos/led stack for biosentinel
 *
 * August 2015
 * A.Schooley
 *
 ******************************************************************************/

#ifndef TAOS_MODE_H_
#define TAOS_MODE_H_

#define TAOS_MODE        3

/*extern volatile unsigned char mode;
extern volatile unsigned char S1buttonDebounce;
extern volatile unsigned char S2buttonDebounce;
extern Timer_B_initUpModeParam initUpParam_A0;
extern volatile unsigned char stopWatchRunning;
extern Calendar currentTime;
extern volatile unsigned int counter;
extern volatile int centisecond;*/

static const unsigned char max_well_number=64;
static const char * const well_lookup_table[]=
{"1R ","1G ","1B ","1X ",
"2R ","2G ","2B ","2X ",
"3R ","3G ","3B ","3X ",
"4R ","4G ","4B ","4X ",
"5R ","5G ","5B ","5X ",
"6R ","6G ","6B ","6X ",
"7R ","7G ","7B ","7X ",
"8R ","8G ","8B ","8X ",
"9R ","9G ","9B ","9X ",
"10R","10G","10B","10X",
"11R","11G","11B","11X",
"12R","12G","12B","12X",
"13R","13G","13B","13X",
"14R","14G","14B","14X",
"15R","15G","15B","15X",
"16R","16G","16B","16X"};

void increment_well(void);
void decrement_well(void);
void taos_mode_init(void);
void taos_mode(void);
char * translate_well_index(unsigned char index);



#endif
