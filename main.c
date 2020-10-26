#include <stdio.h>
#include <stdarg.h>

//prototype functions, normally always needed
void specialLocalStuff();


//only visible to file level
static const int FILE_CONSTANT = 42;
//imported from somewhere
extern int value;

//use this to navigate
int main(int argc, char **args)
{
    char *name = "ludwig";
    printf("hi %s\n", name);

    //0 = false, all other = true
    if(builInTypes())
    {
        printf("this is never called!\n");
    }

    specialLocalStuff();
    operators();
    arrays();
    strings();
    enums();
    structs();
    unions();
    typedefines();
    functions(2,5,3);
    defines();
    printfParams();
    pointers();
    assembly();

    return 0;
}

int builInTypes()
{
    char c;             //byte, usually 8 bits
    short s;            //word, usually 16 bits
    int i;              //double word, usually 32 bit
    long l;             //quad word, usually 64 bits
    float f;            //single precision
    double d;           //double precision
    long long ll;       //unofficial 64 bits
    long double ld;     //80,96 or 128 bits

    //we can use all types signed or unsigned:
    signed int si;      //same as int si
    unsigned int ui;    
    //floating point types are always signed

    return 0;
}

void specialLocalStuff()
{
    static int notOnStack = 1;          //not on stack, but on heap, not destroyed after function exits
    register int tryPutIntoRegister;    //hint to compiler to use register 
    volatile int doNotPutToRegister;    //hint to compiler not to use register

    //combinable with static
    static volatile int svi;    
}

void operators()
{
    int a;
    a = a << 1; //left shift by 1 
    a >>= 2;    //right shift by 2

    a = ~a;         //bitwise not
    a = a & 1234;   //bitwise and
    a = a | 0;      //bitwise or
    a = 1 ^ a;      //bitwise xor

    //rest as usual like >=, &&, ==, etc
}

void arrays()
{
    int arr1[5];                //int array of size 5
    int arr2[3][4];             //3x4 int array
    int arr3[] = {1,2,3,4,5,6}; //array with initializer

    //arrays ar just blocks of memories -> no range check, size must be specified
    //return arr3   <- not possible, array gets destroyed on the stack
    //arr1[-1]      <- possible but probably wrong
    //int arr4[];   <- not possible, needs size
}

void strings()
{
    //strings are simply an array of characters including the nul character
    char name[] = {'l','u','d','w','i','g','\0'};
    //nul is automatically added, length does not need to be specified
    char name2[] = "ludwig";
}

void enums()
{
    //constants from 0 to 6
    enum days {mon, tue, wed, thur, frid, sat, sun};
    enum days today;
    today = wed;
    printf("today is %i\n", today);

    //enum with values
    enum food {pizza = 42, pasta = 12};
}

void structs()
{
    //struct definition, p1 p2 optional
    struct person
    {
        int age;
        char* name;
    } p1, p2;

    //assign values with . operator
    p1.age = 2;
    p1.age = 20;

    //no immediate definition of variables
    struct person another;
    another.age = 40;

    //arrays are also possible
    struct person familiy[5];
    familiy[0].age = 32;
    familiy[1].age = 29;   
}

void unions()
{
    //all variables use the same memory; when created, enough space for the largest variable is allocated; all other share the same memory
    //64 bits, no 96
    union Union
    {
        int val1;
        double val2;
    } u;

    u.val1 = 2;
    u.val2 = 6.4;

    printf("val1 is %i\n", u.val1);
    printf("val2 is %f\n", u.val2);    
}

void typedefines()
{
    //"renames" char to byte
    typedef char byte;
    byte b = 123;

    struct Person
    {
        int age;
    };
    //defines the Person struct to a new type
    typedef struct Person person;
    person p;
}

//see https://www.tutorialspoint.com/cprogramming/c_variable_arguments.htm
void functions(int num, ...)
{
    //this functions has a variable amount of parameters. use stdarg to access
   va_list valist;
   double sum = 0.0;
   int i;

   /* initialize valist for num number of arguments */
   va_start(valist, num);

   /* access all the arguments assigned to valist */
   for (i = 0; i < num; i++) {
      sum += va_arg(valist, int);
   }
	
   /* clean memory reserved for valist */
   va_end(valist);

   printf("average is %f\n", (sum / num));
}

void defines()
{
//constant
#define DEBUG 0
//makro
#define MAX(A,B) (A < B ? B : A)

#ifdef DEBUG
    printf("running in debug mode\n");
#elif
    printf("running in production mode")
#endif

    int i = MAX(3,4);
    printf("max of 3 and 4 is %i\n", i);
}

void printfParams()
{
    //signed integers
    printf("2+3=%d\n", 5);
    printf("2+3=%i\n", 5);
    //unsigned int
    printf("2+3=%u\n", 5);
    //hex output; use x for lower case
    printf("10 in hex is %X\n", 10);
    //character
    printf("first letter of 'sepp' is %c\n", 's');
    //string
    char str[] = "world";
    printf("hello %s\n", str);
    //double and floa
    printf("pi is approx. %f\n", 3.1415926536);
    //print %
    printf("10%% of 100 is 10\n");
}

void pointers()
{
    //sizeof returns the size of a type in bytes
    printf("int is %lu bytes\n", sizeof(int));

    //declare a pointer
    int *ptr = NULL;

    int j = 1;
    //copy address to pointer
    int *address = &j;

    printf("value of j is %d\n", j);
    printf("address of j is %p\n", address);

    //dereferences value at address
    int val = *address;
    printf("value of address is %d\n", val);

    //array and pointer are the same
    int array[] = {1,2,3,4,5};
    int *array_address = &array[0];

    printf("value on 0 is %d\n", array_address[0]);
    printf("value on 0 is %d\n", *array_address);
    printf("value on 0 is %d\n", *array);
    printf("value on 1 is %d\n", *array_address + 1);
}

//implemented by assembly code
int addVariables(int a, int b);
int countTo(int times);
int sumTo(int times);
float halfOf(int number);
double thirdOf(int number);
void addArray(int *arr1, int *arr2);

void assembly()
{
    int r = addVariables(2,3);
    printf("2+3=%d\n", r);

    printf("counted to %d\n", countTo(5));
    
    //does not terminate!
    //printf("counted to %d\n", countTo(0));
    printf("sum from 1 to %d is %d\n", 5, sumTo(5));
    printf("half of 5 is %f\n", halfOf(5));
    printf("third of 1 is %f\n", thirdOf(1));

    int arr1[] = {1,2,3};
    int arr2[] = {4,5,6};
    //we add these fixed size arrays with a single(!) instruction
    addArray(arr1, arr2);

    for (int i = 0; i < 3; i++)
    {
        printf("val is %d\n", arr1[i]);
    }   
}