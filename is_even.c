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