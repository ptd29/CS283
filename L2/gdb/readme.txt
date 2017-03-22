etox notes:
Through gdb debugging i found that the factorial function had an error. The variable
that containing the return value was intially set to 0 and because it was being multiplied
by itself in each iteration of the loop it would always return a value of zero. Then
in the calling function, the calculation would always be INF as this value was being
used as the denominator of the power function.

g1.c notes:
I found that the program was stuck in an infinite loop. The loop did not prompt for
a new character with each iteration so the value it was checking to end the loop would
never change and therefore would not equal EOF unless that was the first character
entered. This lead to the infinite loop.

After examining the source code, the fget call was in the code, however, the while loop
did not conatain braces to include it in the loop, therefore only the print statement
was executed with each loop iteration.

g2.c notes:
The reason that the segmentation fault occurs is due to the integer value being used
in the allocation of memory for the buffer. The integer has a value range of
-2^31 to 2^31 where the 32 bit is the signed bit. By bit shifting the first bit by 31
the value then becomes -2^31, as this is the sign bit, making it a negative value which made the malloc
fail to work properly. By changing the integer to an unsigned integer, the 32 bit is no
longer the sign bit and therefore the value is then positive and valid to be used with
malloc.
