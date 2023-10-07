/*
 * UserInput.c
 *
 *  Created on: Sep 17, 2023
 *      Author: Omar A.Qadir
 */

// Libraries section
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

// Driver section
#include "../Drivers/MCAL/DIO/DIO_interface.h"
#include "../Drivers/MCAL/UART/UART_interface.h"

// FreeRTOS section
#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"
#include "../FreeRTOS/event_groups.h"

// Task section
#include "../INC/UserInput.h"

// Drivers section
#define	UI_STACK						85
#define	UI_PRIORITY						3
#define UI_INIT_THRESHOLD				100

#define UI_E_CONFIG						0x01
#define UI_E_ALARM						0x02
#define UI_E_IDLE						0x04
#define UI_E_UTHRESHOLD					0x10
#define UI_E_UALARM_STATE				0x40
#define UI_E_USYS_STATE					0x80

#define UI_ENABLE						1
#define UI_DISABLE						0

// Global variables
u8 Global_u8Threshold = UI_INIT_THRESHOLD;
u8 Global_u8AlarmState = UI_ENABLE;
static u8 Local_u8ReciveFlag = UI_DISABLE;
static u8 UI_cmd;
extern EventGroupHandle_t E_Gr;

void UserInput_init( void )
{
	UART_void_init();
	UART_void_transmit_str("Starting ||  || Receiving: ");
	UART_void_set_Rx_callback( UserInput_UART );
	xTaskCreate(UserInput_main, "UI", UI_STACK, NULL, UI_PRIORITY, NULL);
}


void UserInput_main( void* pvParameters )
{
	u8 Local_u8SystemState = 0;
	u8 Local_u8ThresholdInCounter = 0;
	u8 Local_u8ThresholdTemp = 0;
	EventBits_t Local_E_Gr;
	DIO_void_set_pin_dir(DIO_REF_PORTB, B3, OUTPUT);
	DIO_void_set_pin(DIO_REF_PORTB, B3);
	while( 1 )
	{
		DIO_void_toggle_pin(DIO_REF_PORTB, B3);

		if( Local_u8ReciveFlag == UI_ENABLE )
		{
			Local_E_Gr = xEventGroupGetBitsFromISR(E_Gr);
			Local_u8SystemState = Local_E_Gr & 7;
			switch(Local_u8SystemState)
			{
			case UI_E_CONFIG:
				if( (UI_cmd >= '0') && (UI_cmd <= '9') )
				{
					switch(Local_u8ThresholdInCounter)
					{
					case 0:
						Global_u8Threshold = (UI_cmd - '0')*100;
						Local_u8ThresholdInCounter++;
						xEventGroupSetBits(E_Gr, UI_E_UTHRESHOLD);
						break;
					case 1:
						Global_u8Threshold += (UI_cmd - '0')*10;
						Local_u8ThresholdInCounter++;
						xEventGroupSetBits(E_Gr, UI_E_UTHRESHOLD);
						break;
					case 2:
						Global_u8Threshold += UI_cmd - '0';
						Local_u8ThresholdInCounter = 0;
						xEventGroupSetBits(E_Gr, UI_E_UTHRESHOLD);
						break;
					default:
						break;
					}
				}
				else if( UI_cmd == 'O' )
				{
					Local_u8ThresholdTemp = 0;
					Local_u8ThresholdInCounter = 0;
					xEventGroupClearBits(E_Gr, UI_E_CONFIG);
					xEventGroupSetBits(E_Gr, UI_E_IDLE);
					xEventGroupSetBits(E_Gr, UI_E_USYS_STATE);
				}
				else if( UI_cmd == 'C' )
				{
					UserInput_swap(&Local_u8ThresholdTemp, &Global_u8Threshold);
					Local_u8ThresholdTemp = 0;
					Local_u8ThresholdInCounter = 0;
					xEventGroupClearBits(E_Gr, UI_E_CONFIG);
					xEventGroupSetBits(E_Gr, UI_E_IDLE);
					xEventGroupSetBits(E_Gr, UI_E_USYS_STATE);
				}
				else
				{

				}
				break;
			case UI_E_ALARM:
				if(UI_cmd == 'S')
				{
					xEventGroupClearBits(E_Gr, UI_E_ALARM);
					xEventGroupSetBits(E_Gr, UI_E_IDLE);
					Global_u8AlarmState ^= UI_ENABLE;
					xEventGroupSetBits(E_Gr, UI_E_USYS_STATE);
				}
				else
				{

				}
				break;
			case UI_E_IDLE:
				switch(UI_cmd)
				{
				case 'C':
					UserInput_swap(&Local_u8ThresholdTemp, &Global_u8Threshold);
					xEventGroupClearBits(E_Gr, UI_E_IDLE);
					xEventGroupSetBits(E_Gr, UI_E_CONFIG);
					xEventGroupSetBits(E_Gr, UI_E_USYS_STATE);
					break;
				case 'T':
					Global_u8AlarmState ^= UI_ENABLE;
					xEventGroupSetBits(E_Gr, UI_E_UALARM_STATE);
					break;
				default:
					break;
				}
				break;
			}
			Local_u8ReciveFlag = UI_DISABLE;
		}

		// Task delay 50 ms
		DIO_void_toggle_pin(DIO_REF_PORTB, B3);
		vTaskDelay( 50 );
	}
}

void UserInput_UART( u8 copy_u8RecivedByte )
{
	UI_cmd = copy_u8RecivedByte;
	UART_void_transmit_char(copy_u8RecivedByte);
	Local_u8ReciveFlag = UI_ENABLE;
}

void UserInput_swap( u8* ptr_1stNum , u8* ptr2ndNum )
{
	*(ptr_1stNum) += *(ptr2ndNum);
	*(ptr2ndNum) = *(ptr_1stNum) - *(ptr2ndNum);
	*(ptr_1stNum) =  *(ptr_1stNum) - *(ptr2ndNum);
}
