
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


void taos_increment_well(void){
	g.well_index++;
	g.well_index %= taos_max_well_number;
	return;
}
void taosdecrement_well(void){
	g.well_index--;
	g.well_index %= taos_max_well_number;
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
		success = true;
	}

	return success;

}

void taos_mode_init(void){
	return;
}
void taos_mode(void){

	return;
}

char * taos_translate_well_index(unsigned char index)
{
	return ((char *)taos_well_lookup_table[index]);
}
