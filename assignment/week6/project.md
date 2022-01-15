## Application description 

This application is a low throughput biometrics application. I am using an SpO2/heart rate sensor from Maxim and possibly a non-contact Infrared thermometer. One idea I had was to use a sophisticated algorithm to determine heart rate variability and coach breathing to optimize this value. Another idea is to have a straightforward combination of the two sensors to indicate parameters for screening for illnesses that may affect SpO2 and temperature. I will probably due the latter due to time limitation and the specialized nature of HRV algorithms. 

## Hardware description 

For a processor/platform, I chose a breadboard friendly module with an STM32F411CEU6 processor on it. This processor is a Cortex M4F capable of running up to 100MHz and has a floating point unit. This will be useful if I extend the project with a more sophisticated algorithm in the future. I am running it at 25 MHz and performance is fine. The processor has 128KB of SRAM, which will come in handy when using FreeRTOS as it statically allocates a lot of structures. 

In addition to the sensors mentioned above, I plan to add an I2C OLED display if there is time. This would allow for more sophisticated user interaction. If I am not able to integrate this, I will use Neopixel, or some other addressable LED to give user feedback (i.e. finger is moving too much to get an accurate SpO2/heart rate reading). 

In keeping with the requirements of the class, a push button causing an interrupt will signal to the system that a measurement should begin. User feedback will be provided by the above means. 

Two I2C busses are accessible on the module which allows the I2C OLED display to be on a separate bus from the sensors. This is good not only from a mutual exclusion point of view, but to reserve bus bandwidth for the display. 

The IR non-contact temperature sensor can use either I2C or output a PWM signal whose duty cycle correlates with the detected object temperature. My plan is to use the PWM interface with appropriate discrete components (Low pass filter) to allow the signal to be fed to an ADC. This will fulfill another requirement for the final project. 

## Software description 

The software for this system will include the standard STM32 HAL for peripheral interfacing and setup, as well as FreeRTOS for task management and inter-task communications. Modules will be implemented in the context of a FreeRTOS task with an initialization method and a "while(1)" task element. 

### Describe the code in general 

The code will include a state machine driven module for managing the SpO2/heart rate sensor. In addition to the I2C bus, there are two GPIO lines which must be managed in order to operate the module. Measurement bandwidth can vary, but I will probably use a relatively low bandwidth of 100 Hz or so. Status must be continually monitored for exception conditions such as removal/movement of finger preventing measurement. This condition must be indicated to the user immediately, so that they can adjust and allow the sensor to properly obtain a reading. I am working on the state machine for this sensor right now and it will be included in a future version of this document. 

For the User Interface, I plan to use either a text display or Neopixels to inform the user of progress of measurement, measurement results, and any events which the user must respond to (i.e. the SpO2 sensor events described above). There will certainly be another state machine around the color and brightness of the Neopixel if I use that, or what should be displayed on the display if it is utilized. 

For the display, I have found an open source graphics library called u8g2 

https://github.com/olikraus/u8g2

https://github.com/olikraus/u8g2/wiki

### Describe the parts you wrote in some detail (maybe 3-5 sentences per module)



### Describe code you re-used from other sources, including the licenses for those 

STM32 HAL Device Driver framework, FreeRTOS, and the display graphics library are open source components that I plan to employ in this project. For FreeRTOS, I am using the CMSIS v2 API, which is documented well here: https://www.keil.com/pack/doc/CMSIS/RTOS2/html/index.html

### Diagram(s) of the architecture 

## Build instructions 

### How to build the system (including the toolchain(s)) 

### Hardware 

### Software 

### How you debugged and tested the system 

## Future 

### What would be needed to get this project ready for production? 

### How would you extend this project to do something more? Are there other features you’d like? How would you go about adding them? 

## Grading 

### Self assessment of the project: for each criteria, choose a score (1, 2, 3) and explain your reason for the score in 1-2 sentences. 

| Criteria                     | Self Assessment                         | Notes                       |
| Project meets minimum goals  | blah blah blah                          |                             |
| Completeness of deliverables | blah blah blah                          |                             |
| Clear intent / working code  | blah blah blah                          |                             |
| Reusing Code                 | blah blah blah                          |                             |
| Originality / scope of goals | blah blah blah                          |                             |
| Bonus Topics                 | blah blah blah                          |                             |
| Bonus: version control used  | blah blah blah                          |                             |



### Have you gone beyond the base requirements? How so? 
