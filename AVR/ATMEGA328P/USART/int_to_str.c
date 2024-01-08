#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
uint8_t baud_code=(uint32_t)16000000/(16*(uint32_t)115200);

int main(){
   

    printf("%d\n",baud_code);
    return 0;
}