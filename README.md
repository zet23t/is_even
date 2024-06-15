# Is even or odd - an implementation using recursive includes

The recent weeks (months!?), I've encountered a huge number of silly tweets mocking dumb implementations to figure out if a number is even or odd. I have to fight my urge responding to those, which is exactly what this is about in most cases: Engagement baiting. 

But I also saw code generators that produce humongous amounts of code to solve this simple problem and pushing the compiler to its limits, which I found more entertaining than most of the takes, as this is a fun exercise in itself.

However, none of the cases have had any practical value for me so far. But when solving a different problem and tinkering with macros, I wondered one couldn't implement a solution that uses recursive includes to solve this "problem". There is still only little practical value in this exercise, but there is at least some value in learning how to use recursive includes in C/C++!

Got curious? Here's the idea: We include a file recursively until a certain condition is met, producing code in the process. The solution I came up with can be tried by running the following command:

```bash
$ make run
gcc -fmax-include-depth=2000 is_even.c -o is_even
./is_even
0 is even
1 is odd
2 is even
3 is odd
4 is even
743 is odd
```

The code is simple and consists of two files: `is_even.c` and `is_even.h`. The `is_even.c` file includes the `is_even.h` file, which includes itself until a certain condition is met. This condition handling was the tricky part: You can't really have mutable variables in macros. However, there are defines in C that can be used for the purpose of counting the number of includes and using this to produce a switch case block that will return if the input number is even or odd. The define I used here is `__INCLUDE_LEVEL__`, which is a predefined macro that holds the current include level. One could also try to use the `__COUNTER__` macro, but the include level fits this problem nicely, so I went with that.

The mischievous file `is_even.h` is shown below:

```c
#if __INCLUDE_LEVEL__ < 1024
#if __INCLUDE_LEVEL__ % 2 == 0
case __INCLUDE_LEVEL__: return 1;
#else
case __INCLUDE_LEVEL__: return 0;
#endif
#include "is_even.h"
#endif
```

By including the `is_even.h` file, it automatically includes itself until the include level reaches 1024. The default include limit is 200, but it can be increased to make this work. The `is_even.c` file is shown below:

```c
int is_even(int n) {
    switch (n) {
        #include "is_even.h"
    }
    return 1;
}

#include <stdio.h>
int main() {
    for (int i=0;i<5;i++)
    {
        printf("%d is %s\n", i, is_even(i) ? "even" : "odd");
    }
    printf("743 is %s\n", is_even(743) ? "even" : "odd");
    return 0;
}
```

If you wonder how this code looks like, you can run the `make code` command, which will produce the following output in a file called `is_even.i`. I'm only showing the first 20 lines here, but you'll get the point:

```c	
# 0 "is_even.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "is_even.c"
int is_even(int n) {
    switch (n) {
# 1 "is_even.h" 1




case 1: return 0;

# 1 "is_even.h" 1


case 2: return 1;



# 1 "is_even.h" 1
```

(this goes on for a total of ~9200 lines)

I am quite sure I am not the first one to come up with this idea, but I haven't seen it before. Let me know who did it first in case you know - or, if you know another solution that uses other macro tricks, I'd like to hear about that too! 

I hope you enjoyed this little exercise and learned something new about C/C++!