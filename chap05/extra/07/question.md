(From Prof. Main’s Web page at http://www.cs.colorado.edu/~main/projectschap09c.html)
Write a recursive function that takes an integer and prints it out as a binary
one. Here is the prototype:

    void binary_print(ostream& outs, unsigned int n);

The function prints the value of n as a BINARY number to the ostream outs. If n is zero,
then a single zero is printed; otherwise no leading zeros are printed in the output. The '\n'
character is NOT printed at the end of the output. Do not use any local variables.
EXAMPLES:
    n=0 Output:0
    n=4 Output:100
    n=27 Output:11011
