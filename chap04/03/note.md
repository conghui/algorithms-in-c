I am not sure if I understand the current exercise correctly. I don't think we 
can both typedef _int_ and _char *_ as Item in the same source file. What's 
more, we can't define two marco, as the compiler will complain.

So we have to typedef and #define them separately, and use two *printf* 
separately. This time, I only use *typedef int Item* and not for _char *_.
