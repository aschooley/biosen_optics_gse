
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
struct
{
	volatile unsigned char update_screen;
	volatile unsigned char well_index;
}g={0,0};

static void update_screen(void);


void increment_well(void){
	g.well_index++;
	g.well_index %= max_well_number;

	g.update_screen=1;

	return;
}
void decrement_well(void){
	g.well_index--;
	g.well_index %= max_well_number;

	g.update_screen=1;

	return;
}

void taos_mode_init(void){
	update_screen();
	return;
}
void taos_mode(void){

	while(mode == TAOS_MODE)
	{
		if(	g.update_screen==1)
		{
			update_screen();
		}

	}
	return;
}

void update_screen(void)
{
	clearLCD();

	showChar(well_lookup_table[g.well_index][0],pos1);
	showChar(well_lookup_table[g.well_index][1],pos2);
	showChar(well_lookup_table[g.well_index][2],pos3);

	puts(well_lookup_table[g.well_index]);

	g.update_screen=0;
}
