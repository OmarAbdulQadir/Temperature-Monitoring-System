/*
 * LCDdisp_private.h
 *
 *  Created on: Sep 17, 2023
 *      Author: Omar A.Qadir
 */

#ifndef INC_LCDDISP_PRIVATE_H_
#define INC_LCDDISP_PRIVATE_H_

#define LCDdisp_CONFIG_SCREEN			0
#define LCDdisp_ALARM_SCREEN			1
#define LCDdisp_IDLE_SCREEN				2

#define LCDdisp_CURRENT_TEMP			0
#define LCDdisp_THERSHOLD				1
#define LCDdisp_ALARM_STATE				2

#define LINE1_LOC						0, 0
#define LINE2_LOC						1, 0
#define CURRENT_TEMP_LOC				0, 2
#define THERSHOLD_LOC					0, 8
#define ALARM_STATE_LOC					0, 15

void LCDdisp_writeScreen( u8 );

void LCDdisp_writevalue( u8 , u8 );

#endif /* INC_LCDDISP_PRIVATE_H_ */
