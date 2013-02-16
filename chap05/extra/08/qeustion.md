Examine this pattern of asterisks and blanks, and write a recursive function that can generate patterns such as this:

    *
    * *
      *
    * * * *
        *
        * *
          *
    * * * * * * * *
            *
            * *
              *
            * * * *
                *
                * *
                  *
With recursive thinking, the function needs only seven or eight lines of code (including two recursive calls). Your prototype should look like this:

      void pattern(ostream& outs, unsigned int n, unsigned int i);
  // Precondition: longest is a power of 2 greater than zero.
  // Postcondition: A pattern based on the above example has been
  // printed to the ostream outs. The longest line of the pattern has
  // n stars beginning in column i of the output. For example,
  // The above pattern is produced by the call pattern(cout, 8, 0).
Hints: You do not need to check the precondition. Think about how the pattern is a fractal. Can you find two smaller versions of the pattern within the large pattern? Here is some code that may be useful within your function:

      // A loop to print exactly i spaces:
      for (k = 0; k < i; k++) outs << ' ';
      // A loop to print n asterisks, each one followed by a space:
      for (k = 0; k < n; k++) outs << "* ";
