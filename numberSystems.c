/* Tanner Crane
Program to work with Binary, Decimal, Hexadecimal 
*/
#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h> 

int main(){
    int number = 0;
    bool ok = false; 


    while(!ok) {
        printf("Choose a number between 1 and 1000 "); 
        scanf("%d", &number); 
        if(number < 0 || number > 1000) {
            printf("Not in listed numerical range"); 
        }
        else {
            ok = true; 
        }

    }
    printf("Binary form \n"); 
    for(int i = 31; i >= 0; i--) {
        printf("%d", (number >> i) & 1);
    }

    printf("\n");

printf("Hexadecimal form: 0x%X\n\n", number); 
 
 int result = (number << 10) & 0xFFFFFC00 | 0x3FF; // shift bits of number 10 places to the left, masks out (set to 0) the lower 10 bits, sets lower 10 bits to 1 
printf("Result (Decimal): %d\n", result);
printf("Result (Hexadecimal): 0x%X\n", result); 
printf("Result (Binary): ");
for(int i = 31; i >= 0; i--) {
    printf("%d", (result >> i) & 1); 
}

printf("\n");
return 0;
}    