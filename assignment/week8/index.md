## Week 8 Assignment

Compile your project code so it prints out the heap pointer and the stack pointer. Print out a global variable address. If you can find it, modify your linker file to swap your uninitialized variables and initialized variables. Verify it is as expected in the memory map. See how that changes your code output. 

For this assignment, I chose to use a separate STM32 nano board, [Nucleo-G031K8](https://www.st.com/en/evaluation-tools/nucleo-g031k8.html), because the assignment was mainly about reading map/linker files and understanding how the stack and heap gets setup for a baremetal programming environment. I am using FreeRTOS for my project and FreeRTOS has it's own heap manager (a selectable algorithm), and has separate stacks for each thread. The stack pointer for each of these stacks is stored in the TCB (task control block) for each task. In addition, FreeRTOS has highwater marking available for the heap through an optional config define. 

I looked in the startup file for the [STM32G031K8](https://www.st.com/en/microcontrollers-microprocessors/stm32g031k8.html) , and the linker symbols being used by the startup code and newlib nano to establish the heap and stack are `_end` and `_estack` respectively. I printed those and also used inline arm assembly to grab the current stack pointer (r13) and print it out as well. The heap pointer is maintained within newlib. 

```
Heap origin:  [20000140]

Stack origin: [20002000]

Stack current: [20001fa0]
```

Note that the current value of the stack is actually `20001f98` because I pushed two registers onto the stack to get the sp value. 

Here is the code that I used to get the values above. 

``` cpp

static uint32_t cur_sp;

int main(void)
{
  /* USER CODE BEGIN 1 */
  extern uint8_t _estack; /* Origin of stack (growing down)*/
  extern uint8_t _end; /* Origin of heap (growing up) */
  char line[64] = {0};
  char * cp;
  uint16_t len;

  /* USER CODE END 1 */
  ...

  /* USER CODE BEGIN 2 */

  #define HAL_MAX_DELAY      0xFFFFFFFFU

  sprintf(line, "\r\nHeap origin:  [%08x]\r\n", (uint32_t)(&_end));
  len = 1;
  for(cp = (char *)line; *cp != '\0'; cp++)
	  HAL_UART_Transmit(&huart2, cp, len, HAL_MAX_DELAY);

  sprintf(line, "\r\nStack origin: [%08x]\r\n", (uint32_t)(&_estack));
  len = 1;
  for(cp = (char *)line; *cp != '\0'; cp++)
	  HAL_UART_Transmit(&huart2, cp, len, HAL_MAX_DELAY);

  asm volatile ("push {r0, r1}");
  asm volatile ("ldr r0, =cur_sp");
  asm volatile ("mov r1, r13");
  asm volatile ("str r1, [r0]");
  asm volatile ("pop {r0, r1}");

  sprintf(line, "\r\nStack current: [%08x]\r\n", cur_sp);
  len = 1;
  for(cp = (char *)line; *cp != '\0'; cp++)
	  HAL_UART_Transmit(&huart2, cp, len, HAL_MAX_DELAY);

  /* USER CODE END 2 */
```

