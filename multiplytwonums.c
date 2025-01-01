#include <stdio.h>
int main() {
int num1, num2; 
printf("Enter the first number to multiply: ");
scanf("%i", &num1);
printf("Enter the second number to multiply: ");
scanf("%i", &num2);

int product = num1 * num2; 

printf("The product of the two numbers is: %d\n", product);
return 1;
}
