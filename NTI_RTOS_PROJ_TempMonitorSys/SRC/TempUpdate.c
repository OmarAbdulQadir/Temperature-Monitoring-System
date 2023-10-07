/*
 * TempUpdate.c
 *
 *  Created on: Sep 17, 2023
 *      Author: Omar A.Qadir
 */

// Libraries section
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

// Drivers section
#include "../Drivers/MCAL/DIO/DIO_interface.h"
#include "../Drivers/MCAL/ADC/ADC_interface.h"

// FreeRTOS section
#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"
#include "../FreeRTOS/semphr.h"
#include "../FreeRTOS/event_groups.h"

// Task section
#include "../INC/TempUpdate.h"

// Macros section
#define	TAMP_UPDATE_STACK				150
#define	TAMP_UPDATE_PRIORITY			3
#define TEMP_UPDATE_TASK_DELAY			100

#define TEMP_UPDATE_ADC_MUX				0
#define TEMP_UPDATE_ADC_ADPS			ADPS_8
#define TEMP_UPDATE_ADC_ADTE			0
#define TEMP_UPDATE_ADC_ADTS			0
#define TEMP_UPDATE_ADC_ADIE			0

#define TAMP_UPDATE_E_CONFIG			0x01
#define TAMP_UPDATE_E_ALARM				0x02
#define TAMP_UPDATE_E_IDLE				0x04
#define TAMP_UPDATE_E_UCURRENT_TEMP		0x08
#define TAMP_UPDATE_E_USYS_STATE		0x80
#define TAMP_UPDATE_ALL_BITS			0xFF

#define TAMP_UPDATE_ENABLE				1
#define TAMP_UPDATE_DISABLE				0

// Global variables
u8 Global_u8Temp;
extern u8 Global_u8Threshold;
extern u8 Global_u8AlarmState;
extern EventGroupHandle_t E_Gr;

void TempUpdate_init( void )
{
	// initiate temperature driver
	ADC_void_init();
	ADC_config_struct ADC_Config = {TEMP_UPDATE_ADC_MUX,
									TEMP_UPDATE_ADC_ADPS,
									TEMP_UPDATE_ADC_ADTE,
									TEMP_UPDATE_ADC_ADTS,
									TEMP_UPDATE_ADC_ADIE};
	ADC_void_config(&ADC_Config);
	// Clear all bits
	xEventGroupClearBits(E_Gr, TAMP_UPDATE_ALL_BITS);
	// Set the state to Idle
	xEventGroupSetBits(E_Gr, TAMP_UPDATE_E_IDLE);
	// Create update temperature main task
	xTaskCreate(TempUpdate_main, "Update_Temp", TAMP_UPDATE_STACK, NULL, TAMP_UPDATE_PRIORITY, NULL);
}

void TempUpdate_main( void* pvParameters)
{
	// Setup section
	u16 Local_u16ADC;
	u8 Local_u8Temp;
	u8 Local_u8SystemState = 0;
	EventBits_t Local_E_Gr;
	DIO_void_set_pin_dir( DIO_REF_PORTB , B0 , OUTPUT );
	DIO_void_set_pin( DIO_REF_PORTB , B0 );
	while( 1 )
	{
		DIO_void_toggle_pin( DIO_REF_PORTB , B0 );

		ADC_void_read_data(&Local_u16ADC);
		Local_u8Temp = ( Local_u16ADC * (500/1024.0) );

		Local_E_Gr = xEventGroupGetBitsFromISR(E_Gr);
		Local_u8SystemState = Local_E_Gr & 7;
		if(Local_u8SystemState != TAMP_UPDATE_E_CONFIG)
		{
			if( (Local_u8Temp >= Global_u8Threshold) && (Global_u8AlarmState == TAMP_UPDATE_ENABLE) )
			{
				xEventGroupClearBits(E_Gr, TAMP_UPDATE_E_IDLE);
				xEventGroupSetBits(E_Gr, TAMP_UPDATE_E_ALARM);
				Global_u8Temp = Local_u8Temp;
				xEventGroupSetBits(E_Gr, TAMP_UPDATE_E_USYS_STATE);
			}
			else if( Local_u8Temp != Global_u8Temp )
			{
				xEventGroupClearBits(E_Gr, TAMP_UPDATE_E_ALARM);
				xEventGroupSetBits(E_Gr, TAMP_UPDATE_E_IDLE);
				Global_u8Temp = Local_u8Temp;
				xEventGroupSetBits( E_Gr , TAMP_UPDATE_E_UCURRENT_TEMP );
			}
			else
			{

			}
		}

		DIO_void_toggle_pin( DIO_REF_PORTB , B0 );
		vTaskDelay( TEMP_UPDATE_TASK_DELAY );
	}
}
