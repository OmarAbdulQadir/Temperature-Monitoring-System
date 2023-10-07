/*
 * Alarm.c
 *
 *  Created on: Sep 17, 2023
 *      Author: Omar A.Qadir
 */

// Libraries section
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

// Drivers section
#include "../Drivers/MCAL/DIO/DIO_interface.h"

// FreeRTOS section
#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"
#include "../FreeRTOS/event_groups.h"

// Task section
#include "../INC/Alarm.h"

// Macros section
#define	ALARM_STACK			85
#define	ALARM_PRIORITY		1
#define ALARM_E_ALARM		0x02
#define ALARM_DIO_PORT		DIO_REF_PORTD
#define ALARM_DIO_PIN		B2


// Global variables
extern EventGroupHandle_t E_Gr;

void Alarm_init( void )
{
	// initiate the output port
	DIO_void_set_pin_dir(ALARM_DIO_PORT, ALARM_DIO_PIN, OUTPUT);
	DIO_void_clear_pin(ALARM_DIO_PORT, ALARM_DIO_PIN);
	// Create update temperature main task
	xTaskCreate(ALarm_main, "Alarm", ALARM_STACK, NULL, ALARM_PRIORITY, NULL);
}

void ALarm_main( void* pvParameters)
{
	// setup section
	DIO_void_set_pin_dir(DIO_REF_PORTB, B2, OUTPUT);
	DIO_void_set_pin(DIO_REF_PORTB, B2);
	while( 1 )
	{
		// Super loop
		// turn on the alarm
		DIO_void_set_pin(ALARM_DIO_PORT, ALARM_DIO_PIN);
		// wait 75 ticks
		vTaskDelay(75);
		// turn off the alarm
		DIO_void_clear_pin(ALARM_DIO_PORT, ALARM_DIO_PIN);
		// check the alarm event flag
		if( (xEventGroupGetBits(E_Gr) & ALARM_E_ALARM) == ALARM_E_ALARM )
		{// if true
			// wait 25 ticks
			vTaskDelay(25);
		}
		else
		{// if false
			// wait till the event flag is raised
			DIO_void_toggle_pin(DIO_REF_PORTB, B2);
			xEventGroupWaitBits(E_Gr, ALARM_E_ALARM, pdFALSE, pdFALSE, portMAX_DELAY);
			DIO_void_toggle_pin(DIO_REF_PORTB, B2);
		}
	}
}
