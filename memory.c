#include <stdio.h>
#include <stdlib.h>

// function to convert decimal number to 16-bit binary number
void decToBinary(int n){
    int binaryNum[16]; 
    int i = 0; 

    while(n > 0) {
        binaryNum[i] = n % 2; 
        n = n / 2; 
        i++; 
    }

    for(int j = i; j < 16; j++) {
        binaryNum[j] = 0; 
    }

    for(int j = 15; j >= 0; j--) {
            printf("%d", binaryNum[j]); 
        }
    }

int translateAddress(int virtualAddress, int pageSize, int pageTable[], int physicalMemorySize) {
int pageOffset = virtualAddress & pageSize; // extract offset within page 
int pageNumber = virtualAddress / (pageSize + 1); // extract page number (assuming 4Kb pages)

int physicalAddress = pageTable[pageNumber] + pageOffset;

if(physicalAddress < physicalMemorySize) {
    return physicalAddress; 
}
else{
    return -1; // indicate PA is on disk 
}
}

int main() {
int page_size; 

printf("Enter page size (Valid sizes between 4095 for 4Kb and 8191 for 8kb): ");
scanf("%d", &page_size);

//validate page size 
if(page_size != 4095 && page_size != 8191) {
    printf("Invalid page size.\n");
    return 1; 
}
// display page size in binary and hexadecimal 

printf("Page size (Binary): ");
decToBinary(page_size); 
printf("\n"); 
printf("Page size (hex): 0x%X\n", page_size); 

int numEntries = 1024 * 1024 / (page_size + 1); // 1MB virtual address space 
int page_table[numEntries]; 

int physicalAddressSpace = 512 * 1024; // size of physical m40emory
int frameSize = page_size + 1; // size of frame
int nextFrameAddress = 0; 

for(int i = 0; i < numEntries; i++) // populate page_table
{
   page_table[i] = nextFrameAddress;
   nextFrameAddress = (nextFrameAddress + frameSize) % physicalAddressSpace; 
}

//input and translate 10 VA
for(int i = 0; i < 10; i++) {
    int virtualAddress; 
    printf("\nEnter a virtual address (hexadecimal): ");
    scanf("%x", &virtualAddress);

if(virtualAddress < 0 || virtualAddress > 0x000FFFFF) {
    printf("Invalid virtual address.\n");
    return 1; 
}

int physicalAddress = translateAddress(virtualAddress, page_size, page_table, 512 * 1024); 

//display addresses
printf("Virtual Address: 0x%X\n", virtualAddress);
if(physicalAddress != -1) {
    printf("Physical Address: 0x%X\n", physicalAddress); 
}
else {
    printf("Physical Address: Currently on Disk\n");
}
}
return 0; 
}