## HW0: Galaxy Explorers

This project deals with porting a Python benchmark to C++ and analyzing the scaling properties of both the Python and the C++ code.

### Part 1
#### a. The following are the number of iterations I picked at different sizes:

1. 2^8: 10000
2. 2^10: 65000
3. 2^12: 15000
4. 2^14: 5000
5. 2^16: 500
6. 2^18: 200
7. 2^20: 60
8. 2^22: 10
9. 2^24: 1

The motivation behind these numbers was based on the time it took the code to finish executing. If the runtime was too long, the trade-off wasn't enough and hence number of iterations was decreased. Furthermore, I monitored the memory pressure using Activity Monitor on my Mac (I have an early 2011 MacBook with 4GB RAM), and if the memory pressure was higher than desired, I decided to reduce the number of iterations to a more suitable number. I also tweaked the number of iterations in order to obtain precision to the 1000th place in the mean time per coordinate.

#### b. Picking one measurement:

For each iteration, I ran the code 10 times and picked a number which was accurate to its 1000th place. The number of iterations was tweaked as desired in order to obtain this precision.

#### c. Below is a plot of the mean time per coordinate as a function of the number of objects.

![Image of Python plot](/plots/py_plot.jpg)
