## Week 9 Assignment

In Quiz 1, multiple different implementations for bit reversal were given and you were asked to
consider the algorithms with respect to speed, RAM, and code space. (You can see the code at
Godbolt.)

Choose a small algorithm to implement in different ways. Describe when/why you might use
each. You can choose any small algorithm.

Some possible options include:
* How many bits are one in a given 32-bit uint?
* How many leading zeros are in a 32-bit uint?
* Trigonometry functions like sin, cos, tan
* Integer division with remainder
* Find the first 100 prime numbers

## Algorithm

I implemented the leading zeros in a 32-bit uint algorithm. The purely iterative way is simple -- use a bitmask and look at the bits starting with the most significant bit until you find a non-zero bit. This would use native word length on a 32-bit microcontroller and use relatively fast bit-wise operations. 

The second way to implement it is using a lookup table. I made a lookup table for a `uint8_t` and then used a `union` to select each byte, most significant byte first, to send to the lookup method. The lookup operation is very fast (pointer dereference with offset), although selecting the bytes, most significant byte first, probably involves some shifting and definitely non native word length operations. 

I would favor the iterative approach, as it is relatively fast and requires no added storage. That is not to say that the table driven approach is not without merit. If this were an application like video graphics where performance was paramount and the storage tradeoff was not consequential, there is some time spent iteratively shifting through zeroes to be saved when it is done 8 zeroes at a time (i.e. a byte-wise operation). 

### Sample Run
```
Math algorithm homework
0x8000_0000
zeros_lookup = 0
zeros_shift = 0
0x0000_8000
zeros_lookup = 16
zeros_shift = 16
```
### Code
[algo_hw.cpp](./algo_hw/algo_hw.cpp)
