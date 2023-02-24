#include <stdio.h>
#include <stdlib.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED1 2
#define LED2 4 

void task1(void *params){
    while(1){
        printf("LED1 ON\n");
        vTaskDelay(200/portTICK_PERIOD_MS);
        printf("LED1 OFF\n");
        vTaskDelay(200/portTICK_PERIOD_MS);
    }
}
void app_main(void){
    xTaskCreate(&task1, "Task 1", 1024*2, NULL, 2, NULL);
}