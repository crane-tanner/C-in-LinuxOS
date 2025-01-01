#include <stdio.h>
#include <stdlib.h>

int square(int x) {
    return x*x;
}

int main() {
    int num;
    printf("Enter a number to square\n"); 
    scanf("%d", &num);
    num = square(num);
    printf("The square is: %d\n", num);


}