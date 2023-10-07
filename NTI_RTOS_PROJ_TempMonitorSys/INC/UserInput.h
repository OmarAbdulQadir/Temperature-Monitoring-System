/*
 * UserInput.h
 *
 *  Created on: Sep 17, 2023
 *      Author: Omar A.Qadir
 */

#ifndef INC_USERINPUT_H_
#define INC_USERINPUT_H_

// User input initiation function
void UserInput_init( void );

// User input main function
void UserInput_main( void* );

// Swap two numbers
void UserInput_swap( u8* , u8* );

// User input callback
void UserInput_UART( u8 );

#endif /* INC_USERINPUT_H_ */
