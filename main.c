#include <stdio.h>

int main(int argc, char **args)
{
    char *name = "ludwig";
    printf("hi %s\n", name);

    return 0;
}

void testBuilInTypes()
{
    char c;             //byte, usually 8 bits
    short s;            //word, usually 16 bits
    int i;              //double word, usually 32 bit
    long l;             //quad word, usually 64 bits
    float f;            //single precision
    double d;           //double precision
    long long ll;       //unofficial 64 bits
    long double ld;     //80,96 or 128 bits
}