
#include <iostream>

int main()
{
    int x = 0;
    _asm {
        MOV EAX, 5
        MOV x, EAX
    }
    printf("%d\n", x);
    return 0;
}

