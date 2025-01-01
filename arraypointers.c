#include <stdio.h>

int main() {

int myarr[5];
int *ptr = myarr;

int s = 3;
    for(; ptr < &myarr[5]; ptr++) {
        *ptr = s;
        s = s * 2; 
} 

for(int i = 0; i < 5; i++) {
    printf("%d ", myarr[i]);
}

}