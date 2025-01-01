#include <stdio.h>

int main() {

int a = 4; 
printf("The number is %d\n", a);
int *ptr = &a;

printf("The address of a is %x\n", ptr);
printf("Number is %d\n", *ptr); // dereferenced pointer

}
