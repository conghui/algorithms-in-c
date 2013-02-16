
    void letters(ostream& outs, char c)
      // Precondition: c is one of the characters 'A' through 'Z'.
      // Postcondition: The function has printed a pattern of letters to the
      // ostream out, as follows:
      // 1. If the parameter c is 'A', then the output is 'A'.
      // 2. For other values of c, the output consists of three parts:
      //    -- the output for the previous letter (c-1);
      //    -- followed by the letter c itself;
      //    -- followed by a second copy of the output for the previous letter.
      // There is no '\n' printed at the end of the output.
      /* Example output:
         letters(cout, 'D') will print this to cout:
         ABACABADABACABA
      */
