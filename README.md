# Temperature Monitoring System
## Description:
Temperature monitoring systems using FreeRTOS, The system continuously monitors the temperature and fires an alarm if the temperature exceeds the threshold value. It has three states Idle (Temperature is less than the threshold value), Alarm (Temperature is above the threshold value and alarm is active), and Config (To edit the threshold value).

![Alt text](https://github.com/OmarAbdulQadir/Temperature-Monitoring-System/blob/main/NTI_RTOS_PROJ_TempMonitorSys_Designs/State%20Machine.jpg?raw=true)



## Usage:
The system contains three states: Idle State, Config State, and Alarm State. Each of the three states differs in functionality and types of inputs. Now we will describe each state individually, starting with the Idle State.

1- Idle State:

In this state, the system monitors the temperature by taking a sample every 100 ms. For each sample, the system compares the temperature to the preset threshold value. If it exceeds the threshold value and the alarm is enabled (can be toggled by sending 'T'). The system will transition to the alarm state. Otherwise, no transition occurs. Also, if the user requests to configure the threshold value (by sending 'C') that triggers the system to enter the configuration state.

![Alt text](https://github.com/OmarAbdulQadir/Temperature-Monitoring-System/blob/main/NTI_RTOS_PROJ_TempMonitorSys_Designs/Idle.JPG?raw=true)

2- Config State:

In this state, the system waits for the user to input three numbers within the range of 0 - 255 as the new threshold value. In this case, the user is obligated to send either the new three numbers and/or send 'O' to approve the new threshold value or 'C' to cancel the configuration session and return to the idle state. Note that it is not recommended to stay in this state for an extended period of time, as the system will not sound an alarm if the temperature increases.

![Alt text](https://github.com/OmarAbdulQadir/Temperature-Monitoring-System/blob/main/NTI_RTOS_PROJ_TempMonitorSys_Designs/config.JPG?raw=true)

3- Alarm State:

In this state, the system will activate the alarm LEDs and buzzer to indicate that the temperature exceeds the threshold value. Exiting this state can be achieved by either turning off the alarm (by sending 'S') or reducing the temperature below the threshold.

![Alt text](https://github.com/OmarAbdulQadir/Temperature-Monitoring-System/blob/main/NTI_RTOS_PROJ_TempMonitorSys_Designs/alarming.JPG?raw=true)


## Components:
### Hardware
![Alt text](https://github.com/OmarAbdulQadir/Temperature-Monitoring-System/blob/main/NTI_RTOS_PROJ_TempMonitorSys_Designs/Block%20Diagram%20(2).png?raw=true)

| Element         | Description |
|-----------------|-------------|
| MCU             | The microcontroller unit (MCU) used in this project is the ATmega32. It features 32 KB of flash memory and 2 KB of SRAM. Additionally, it includes an ADC with 10-bit resolution, 32 I/O lines, and a 16-bit timer that is highly beneficial when working with a real-time operating system (RTOS). |
| LM35            | The LM35 temperature sensor is used to measure temperature within a range of -55 to 150 °C, with a linear scale factor of +10 mV/°C. | 
| HC-05           | The Bluetooth HC-05 is used to receive user input (commands) through the UART in order to modify the system's parameters. |
| LCD 16x2        | The LCD is used to display the current temperature, threshold value, and alarm state (enabled or disabled). Additionally, it is used to alert the user when the temperature exceeds the threshold value. In addition to editing the threshold value throughout the configuration state. |
| LEDs and Buzzer | Elements to visually and audibly alert when the temperature exceeds the threshold value. |


### Software
![Alt text](https://github.com/OmarAbdulQadir/Temperature-Monitoring-System/blob/main/NTI_RTOS_PROJ_TempMonitorSys_Designs/Task%20Diagram.jpeg?raw=true)

| Layer Architecture | Component          | Description  |
|--------------------|--------------------|--------------|
| APP: Task 1        | Temperature Update | This task is responsible for measuring the temperature and raising the alarm flag if the temperature exceeds the threshold value. Otherwise, it will update the new temperature value on the screen. |
| APP: Task 2        | LCD Disp           | This task is responsible for updating the values on the screen if any update flag is raised. Otherwise, nothing will happen. |
| APP: Task 3        | User Input         | This task is responsible for receiving and validating user input data. It then calls the appropriate task to take action based on the validity of the received data. |
| APP: Task 4        | Alarm              | This task is responsible for turning the LEDs and buzzers on and off if the system is in an alarm state. |
| Service            | FreeRTOS           | Using a Real-Time Operating System (RTOS) in this type of application is essential, as it can become very complex and there is a high likelihood of encountering unexpected behaviors. Using FreeRTOS enables multitasking and ensures smooth flow. |
| HAL                | LCD                | This module is responsible for communicating with the LCD display. |
| MCAL               | DIO                | This module is responsible for configuring all the I/O pins of the microcontroller. |
| MCAL               | ADC                | This module is responsible for configuring the ADC peripheral and managing all the conversion processes. |
| MCAL               | UART               | This module is responsible for configuring the UART peripheral and managing all the transmission and receiving processes through the UART. |



## Credit:
All thanks go to the [National Technology Institute](https://www.linkedin.com/school/nti-eg/mycompany/) for giving me the opportunity to advance my career in embedded systems. And special thanks to [Dr. Mahmoud Hussein](https://www.linkedin.com/in/mahmoudhusseinnti/) for his guidance during the course on RTOS.
