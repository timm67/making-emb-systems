### Questions

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

### Button video

![](button_video.gif) 
