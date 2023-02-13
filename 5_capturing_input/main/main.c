#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void){
    char c=0;
    char str[100];
    memset(str, 0, sizeof(str));
    printf("Size of string str is %d\n", sizeof(str));
    printf("Enter character: \n");
    while (c!='\n')
    {   
        c=getchar();
        if(c!=0xff){
            str[strlen(str)]=c;
            printf("Length of string str is %d\n", strlen(str));
            printf("%c", c);
        }
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
    printf("You typed: %s\n", str);
}