/*
 * LCDdisp_update.c
 *
 *  Created on: Sep 17, 2023
 *      Author: Omar A.Qadir
 */

// Libraries section
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

// Drivers section
#include "../Drivers/MCAL/DIO/DIO_interface.h"
#include "../Drivers/HAL/LCD/LCD_interface.h"

// FreeRTOS section
#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"
#include "../FreeRTOS/event_groups.h"

// Task section
#include "../INC/LCDdisp.h"
#include "../INC/LCDdisp_private.h"

// Macros section
#define LCD_DISP_IDLE_ST				0
#define LCD_DISP_CONFIG_ST				1
#define LCD_DISP_ALARM_ST				2

#define LCD_DISP_STACK					100
#define	LCD_DISP_PRIORITY				2

#define LCD_DISP_E_CONFIG				0x01
#define LCD_DISP_E_ALARM				0x02
#define LCD_DISP_E_IDLE					0x04
#define LCD_DISP_E_UCURRENT_TMEP		0x08
#define LCD_DISP_E_UTHRESHOLD			0x10
#define LCD_DISP_E_UALARM_STATE			0x40
#define LCD_DISP_E_USYS_STATE			0x80
#define LCD_DISP_ALL_BITS				0xFF

#define LCD_DISP_ENABLE					1
#define LCD_DISP_DISABLE				0

// Global variables
extern u8 Global_u8Temp;
extern u8 Global_u8Threshold;
extern u8 Global_u8AlarmState;
extern EventGroupHandle_t E_Gr;


void LCDdisp_init( void )
{
	// initiate LCD
	LCD_init();
	// write the Idle data to the screen
	LCDdisp_writeScreen( LCDdisp_IDLE_SCREEN );
	// Create the LCD main task
	xTaskCreate(LCDdisp_main, "LCD_disp", LCD_DISP_STACK, NULL, LCD_DISP_PRIORITY, NULL);
}

void LCDdisp_main( void* pvParameters )
{
	// Setup section

	u8 Local_u8Temp = Global_u8Temp;
	u8 Local_u8Threshold = Global_u8Threshold;
	u8 Local_u8AlarmState = Global_u8AlarmState;
	u8 Local_u8SystemState = 0;
	EventBits_t Local_E_Gr;

	DIO_void_set_pin_dir(DIO_REF_PORTB, B1, OUTPUT);
	DIO_void_set_pin(DIO_REF_PORTB, B1);
	while( 1 )
	{
		DIO_void_toggle_pin(DIO_REF_PORTB, B1);

		Local_E_Gr = xEventGroupGetBitsFromISR(E_Gr);
		Local_u8SystemState = Local_E_Gr & 7;
		switch(Local_u8SystemState)
		{
		case LCD_DISP_E_CONFIG:
			LCDdisp_writeScreen(LCDdisp_CONFIG_SCREEN);
			if( Local_u8Threshold != Global_u8Threshold)
			{
				Local_u8Threshold = Global_u8Threshold;
				LCDdisp_writevalue(LCDdisp_THERSHOLD, Local_u8Threshold);
			}
			break;
		case LCD_DISP_E_ALARM:
			LCDdisp_writeScreen(LCDdisp_ALARM_SCREEN);
			break;
		case LCD_DISP_E_IDLE:
			LCDdisp_writeScreen(LCDdisp_IDLE_SCREEN);
			if( Local_u8Temp != Global_u8Temp )
			{
				Local_u8Temp = Global_u8Temp;
				LCDdisp_writevalue(LCDdisp_CURRENT_TEMP, Local_u8Temp);
			}
			else
			{

			}
			if( Local_u8AlarmState != Global_u8AlarmState )
			{
				Local_u8AlarmState = Global_u8AlarmState;
				LCDdisp_writevalue(LCDdisp_ALARM_STATE, Local_u8AlarmState);
			}
			else
			{

			}
			break;
		default:
			xEventGroupClearBits(E_Gr, LCD_DISP_ALL_BITS);
			xEventGroupSetBits(E_Gr, LCD_DISP_E_IDLE);
			LCDdisp_writeScreen(LCDdisp_IDLE_SCREEN);
			break;
		}

		// wait and clear the event bits
		DIO_void_toggle_pin(DIO_REF_PORTB, B1);
		xEventGroupWaitBits(E_Gr,
							(LCD_DISP_E_UCURRENT_TMEP
						   | LCD_DISP_E_UTHRESHOLD
						   | LCD_DISP_E_UALARM_STATE
						   | LCD_DISP_E_USYS_STATE),
							pdTRUE,
							pdFALSE,
							portMAX_DELAY);
	}
}

void LCDdisp_writeScreen( u8 copy_u8ScreenID )
{
	switch( copy_u8ScreenID )
	{
	case LCDdisp_IDLE_SCREEN:
		LCD_set_cursor(LINE1_LOC);
		LCD_write_str((u8*)"C:    T:    AS: ");
		LCD_set_cursor(LINE2_LOC);
		LCD_write_str((u8*)"  TC:C   AST:T  ");
		LCDdisp_writevalue(LCDdisp_CURRENT_TEMP, Global_u8Temp);
		LCDdisp_writevalue(LCDdisp_THERSHOLD, Global_u8Threshold);
		LCDdisp_writevalue(LCDdisp_ALARM_STATE, Global_u8AlarmState);
		break;
	case LCDdisp_CONFIG_SCREEN:
		LCD_set_cursor(LINE1_LOC);
		LCD_write_str((u8*)"      T:        ");
		LCD_set_cursor(LINE2_LOC);
		LCD_write_str((u8*)"  OK:O    CN:C  ");
		LCDdisp_writevalue(LCDdisp_THERSHOLD, Global_u8Threshold);
		break;
	case LCDdisp_ALARM_SCREEN:
		LCD_set_cursor(LINE1_LOC);
		LCD_write_str((u8*)" !!!ALARMING!!! ");
		LCD_set_cursor(LINE2_LOC);
		LCD_write_str((u8*)"      AS:S      ");
		break;
	default:
		break;
	}
}

void LCDdisp_writevalue( u8 copy_u8ValueID, u8 copy_u8Value )
{
	switch( copy_u8ValueID )
	{
	case LCDdisp_CURRENT_TEMP:
		LCD_set_cursor(CURRENT_TEMP_LOC);
		LCD_write_s32_number(copy_u8Value);
		break;
	case LCDdisp_THERSHOLD:
		LCD_set_cursor(THERSHOLD_LOC);
		LCD_write_s32_number(copy_u8Value);
		break;
	case LCDdisp_ALARM_STATE:
		LCD_set_cursor(ALARM_STATE_LOC);
		if(copy_u8Value == LCD_DISP_ENABLE)
			LCD_write_char('E');
		else
			LCD_write_char('D');
		break;
	default:
		break;
	}
}
