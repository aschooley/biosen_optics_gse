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

#include "stdbool.h"

/*extern volatile unsigned char mode;
extern volatile unsigned char S1buttonDebounce;
extern volatile unsigned char S2buttonDebounce;
extern Timer_B_initUpModeParam initUpParam_A0;
extern volatile unsigned char stopWatchRunning;
extern Calendar currentTime;
extern volatile unsigned int counter;
extern volatile int centisecond;*/

static const unsigned char taos_max_well_number=64;
static char const * const taos_well_lookup_table[]=
{"1G ","1R ","1I ","1X ",
"2G ","2R ","2I ","2X ",
"3G ","3R ","3I ","3X ",
"4G ","4R ","4I ","4X ",
"5G ","5R ","5I ","5X ",
"6G ","6R ","6I ","6X ",
"7G ","7R ","7I ","7X ",
"8G ","8R ","8I ","8X ",
"9G ","9R ","9I ","9X ",
"10G","10R","10I","10X",
"11G","11R","11I","11X",
"12G","12R","12I","12X",
"13G","13R","13I","13X",
"14G","14R","14I","14X",
"15G","15R","15I","15X",
"16G","16R","16I","16X"};

void taos_increment_well(void);
void taos_decrement_well(void);
unsigned char taos_get_current_well(void);
bool taos_set_current_well(unsigned char index);
void taos_output_enable(void);
void taos_output_disable(void);
void taos_mode_init(void);
void taos_mode(void);
char *  taos_translate_well_index(unsigned char index);



#endif
