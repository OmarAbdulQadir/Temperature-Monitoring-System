/*
 * main.c
 *
 *  Created on: Sep 16, 2023
 *      Author: Omar A.Qadir
 */

// Libraries section
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

// FreeRTOS section
#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"
#include "../FreeRTOS/event_groups.h"

// Tasks section
#include "../INC/TempUpdate.h"
#include "../INC/Alarm.h"
#include "../INC/LCDdisp.h"
#include "../INC/UserInput.h"

// Global variable
EventGroupHandle_t E_Gr;

// Main function
int main( void )
{
	// Setup section
	E_Gr = xEventGroupCreate();

	TempUpdate_init();
	Alarm_init();
	UserInput_init();
	LCDdisp_init();

	vTaskStartScheduler();

	while( 1 )
	{
		

	}
	return 0;
}
