# Temperature Monitoring System
## Description:
Temperature monitoring systems using FreeRTOS, The system continuously monitors the temperature and fires an alarm if the temperature exceeds the threshold value. It has three states Idle (Temperature is less than the threshold value), Alarm (Temperature is above the threshold value and alarm is active), and Config (To edit the threshold value).

![Alt text](https://github.com/OmarAbdulQadir/Temperature-Monitoring-System/blob/main/NTI_RTOS_PROJ_TempMonitorSys_Designs/State%20Machine.jpg?raw=true)



## Usage:
The System contains three states as described Idle State, Config State, and Alarm state. Each of the three states is different in the functionality and types of inputs. Now we are describing each state alone Starting with the Idle State.
1- Idle State:

![Alt text](https://github.com/OmarAbdulQadir/Temperature-Monitoring-System/blob/main/NTI_RTOS_PROJ_TempMonitorSys_Designs/Idle.JPG?raw=true)

2- Config State:

![Alt text](https://github.com/OmarAbdulQadir/Temperature-Monitoring-System/blob/main/NTI_RTOS_PROJ_TempMonitorSys_Designs/config.JPG?raw=true)

3- Alarm State:

![Alt text](https://github.com/OmarAbdulQadir/Temperature-Monitoring-System/blob/main/NTI_RTOS_PROJ_TempMonitorSys_Designs/alarming.JPG?raw=true)


## Components:
### Hardware
![Alt text](https://github.com/OmarAbdulQadir/Temperature-Monitoring-System/blob/main/NTI_RTOS_PROJ_TempMonitorSys_Designs/Block%20Diagram%20(2).png?raw=true)

|Element | Description |
|--------|-------------|
|MCU |The microcontroller unit (MCU) used in this project is the ATmega32. It features 32 KB of flash memory and 2 KB of SRAM. Additionally, it includes an ADC with 10-bit resolution, 32 I/O lines, and a 16-bit timer that is highly beneficial when working with a real-time operating system (RTOS). |
|LM35 | The LM35 temperature sensor is used to measure temperature within a range of -55 to 150 °C, with a linear scale factor of +10 mV/°C. |
| HC-05 | The Bluetooth HC-05 is used to receive user input (commands) through the UART in order to modify the system's parameters. |
|LCD 16x2 | The LCD is used to display the current temperature, threshold value, and alarm state (enabled or disabled). Additionally, it is used to alert the user when the temperature exceeds the threshold value. In addition to editing the threshold value throughout the configuration state. |
|LEDs and Buzzer | Elements to visually and audibly alert when the temperature exceeds the threshold value. |


### Software
![Alt text](https://github.com/OmarAbdulQadir/Temperature-Monitoring-System/blob/main/NTI_RTOS_PROJ_TempMonitorSys_Designs/Task%20Diagram.jpeg?raw=true)

| Layer Architecture | Component          | Description  |
|--------------------|--------------------|--------------|
| APP: Task 1        | Temperature Update |              |
| APP: Task 2        | LCD Disp           |              |
| APP: Task 3        | User Input         |              |
| APP: Task 4        | Alarm              |              |
| Service |FreeRTOS            | Using a Real-Time Operating System (RTOS) in this type of application is essential, as it can become very complex and there is a high likelihood of encountering unexpected behaviors. Using FreeRTOS enables multitasking and ensures smooth flow. |
| HAL                | LCD                |              |
| MCAL               | DIO                |              |
| MCAL               | ADC                |              |
| MCAL               | UART               |              |



## Credit:
