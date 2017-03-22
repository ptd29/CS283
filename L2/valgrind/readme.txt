V00:
40bytes were lost, after looking at the code, the integer pointer was never
freed at the end of the program. After freeing the memory, the program no
longer leaks data. Also, the index of 10 is out of the range of the variable. The pointer
array is allocated for 10 elements and the 10th index would be the 11th element. This
could corrupt that unallocated memory if it is being used elsewhere.

V05:
On the intial run and second run the program freed memory ok, however,
upon examining the code I saw that x was defined but never initialized.
This is an issue because there is no way of knowing what the value of x
could be potentially causing undesired results. Setting it to 0 made it
print the statement.

V06:
Valgrind did not find any memory leaking, however, as in v05, the variable y was not
initialized. This means that y's value is unknown and the outcome of the function call
is unpredictable. I fixed it by initializing y.
