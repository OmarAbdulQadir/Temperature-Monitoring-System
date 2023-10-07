# Temperature Monitoring System

## Description:
Temperature monitoring systems using FreeRTOS, The system continuously monitors the temperature and fires an alarm if the temperature exceeds the threshold value. It has three states Idle (Temperature is less than the threshold value), Alarm (Temperature is above the threshold value and alarm is active), and Config (To edit the threshold value).

## Usage:

## Hardware Components:
|Element | Description |
|--------|-------------|
|MCU |The microcontroller unit (MCU) used in this project is the ATmega32. It features 32 KB of flash memory and 2 KB of SRAM. Additionally, it includes an ADC with 10-bit resolution, 32 I/O lines, and a 16-bit timer that is highly beneficial when working with a real-time operating system (RTOS). |
|LM35 | The LM35 temperature sensor is used to measure temperature within a range of -55 to 150 °C, with a linear scale factor of +10 mV/°C. |
|LCD 16x2 | The LCD is used to display the current temperature, threshold value, and alarm state (enabled or disabled). Additionally, it is used to alert the user when the temperature exceeds the threshold value. In addition to editing the threshold value throughout the configuration state. |
|LEDs and Buzzer | Elements to visually and audibly alert when the temperature exceeds the threshold value. |


### Software Components:
| Layer   | Component          | Description  |
|---------|--------------------|--------------|
| Task 1  | Temperature Update |              |
| Task 2  | LCD Disp           |              |
| Task 3  | User Input         |              |
| Task 4  | Alarm              |              |
| Service |FreeRTOS            | Using a Real-Time Operating System (RTOS) in this type of application is essential, as it can become very complex and there is a high likelihood of encountering unexpected behaviors. Using FreeRTOS enables multitasking and ensures smooth flow. |
| HAL     | LCD                |              |
| MCAL    | DIO                |              |
| MCAL    | ADC                |              |
| MCAL    | UART               |              |

## Credit:
