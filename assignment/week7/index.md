### Week 7 Homework

Start with an interview question you have asked or one that you’ve been asked (or one from the internet). Then write up what an interviewer would look for in an answer. Be specific about how the interviewer might help the interviewee if they get stuck.

I've had a couple of questions involving 'design this', which implied, at least to me, begin with a state diagram. One was to design an elevator, another a vending machine. I'll choose the vending machine here.

To start off, make the simplifying assumption that you can issue the 'vend' command to another controller with it's own state machine that is responsible for dispensing (vending) the product. In that case, there are two sources of input that the state machine must be concerned with: one is the product selector, and the other is the payment acceptor (used to be bill/coin). We will ignore a credit card acceptor for now, but this could be reduced to an input signal similar to what a bill or coin acceptor would produce. 

There are 3 separate state machines, one for each acceptor (bill/coin), and another overall state machine which includes the users product selection. I've drawn out the state machines below. 

I would look for the valid states, and even if some were missed, look for the major ones (i.e. coin/bill not accepted handling). Extra points for documenting the exception situations (money return signaled). 

If a candidate were stuck, then I would give them an idea what the main states were and ask them about what exception conditions could happen. 

As a final question, I'd ask what functions would be needed to implement this, and perhaps guide the interviewee through a state-centric state machine calling the various functions. 


![Vending Machine FSM](./vend_machine_fsm.png)

Other more coding centric questions I've been asked include the infamous palindrome question (write a function to indicate whether a string is a palindrome or not. The key to this problem is using a comparison at each end of the string, and progress toward the pivot point (center) of the string, comparing each character. Be sure to skip white space. A great example I was asked was "A man, a plan, a canal, Panama" which is actually palindromic if you skip the whitespace. The general idea is the following. 

```
#include <string.h>
int is_palindromic(char *str)
{
  char * begin, *end;
  begin = str; end = begin + strlen(str);
  while (begin < end)
  {
    while (is whitespace(begin))
      begin++;
    while (is_whitespace(end))
      end--;
    if (*begin != *end)
      return -1;
    begin++; end--;
  }
  
  return 0;
}
```
