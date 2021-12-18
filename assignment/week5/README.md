## Questions

* What are the hardware registers that cause the LED to turn on and off? (From the processor manual, don’t worry about initialization.) 

In my case, the LED is attached to PC13, So the GPIO port output data register for port C would be used, GPIOC_ODR. This register is at 0x4002 0800 plus offset 0x14, or 0x4002 0814.

`*((volatile uint32_t *)0x40020814) |= (1 << 13);`

Would extinguish the LED, since the gpio is sinking the current from the rail.

`*((volatile uint32_t *)0x40020814) &= ~(1 << 13);`

would be the expression to light the led

* What are the button registers that you read?

The button in my case is the classic momentarily closed connection from PA0 to ground. Thus, if this were a polling implementation, I would read the GPIO port input data register at 0x4002 0000 plus offset 0x10, or 0x40020010, and bit 1 would indicate the button were pressed if 0, or unpressed if 1. The gpio must be configured to have an internal pullup via the GPIO port pull-up/pull-down register (offset 0x0C). 

```
typedef enum {false=0, true} bool;
bool button_pressed;

if *((volatile uint32_t *)0x40020010) & (1 << 0)
   button_pressed = false;
else
   button_pressed = true;

```

In my case, I used an interrupt (rising edge) on the gpio connected to the button to set an event flag in FreeRTOS. This is accomplished by overriding the weak reference for `void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)`. The method checks for `GPIO_PIN0` as an argument passed in, and if that is the case, sets a FreeRTOS event flag via `osEventFlagsSet()`. Another thread looks at this value, changes the LED state if it is set and clears the event flag via osEventFlagsClear(). There is a delay of at least one scheduler tick involved in this process, and can be increased to prevent bouncing as showing up as multiple events. 

* Can you read that memory directly and see the button change in a debugger or by printing out the associated memory?

Having the ISR copy the register value into a variable, which you could put a debugger watch on would probably be the best way.

## Button video

![](button_video.gif)


## Code

Here is the code that does most of the work, although it's only one line, setting the global event flag by overriding the external input interrupt handler. The handler checks to see if it's the button gpio, then sets the global event flag to defer processing out of interrupt context. 

```
//
// Interrupt handler for button press (GPIO_PIN_0)
//
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
   if (GPIO_Pin == GPIO_PIN_0)
   {
      osEventFlagsSet(ioEventsHandle, EVENT_FLAG_BUTTON);
   }
}
```

This decouples the interrupt from a majority of the processing done in non-interrupt context. I didn't do much to debounce the button as the `osDelay(10)` provides delay after the event occurs, allowing for settling time. This is a FreeRTOS task. 

```
  for(;;)
  {
      eventFlags = osEventFlagsGet(ioEventsHandle);
      if (eventFlags & 0x00000001U)
      {
         ledState++;
         if (ledState % 2)
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
         else
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

         osEventFlagsClear(ioEventsHandle, 0x00000001U);
      }

      // time to debounce the button and throttle event rate
      osDelay(10); // always give a time slice to the scheduler 
      
      // ledTaskPoll(NULL);
  }
```
## Easy but important

One thing that I always start out any embedded project with is my command line interface. It's looks trivial and is relatively simple -- I wrote it for an MSP430 application 20 years ago (hard to believe; time flies). But it allows you to register handlers in the different modules that you create and debug/exercise the system at a high level. 

These are the commands when nothing else is registered, but more commands will be added. The echo command switches between human and machine-to-machine communications as the host talked to the micro via the same serial interface. 
```
-> help
help: help [command]
h: h [command]
echo: echo [{0 | n(o) | N(o)} {1 | y(es) | Y(es)}]

-> 
```
