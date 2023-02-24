#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void task1(void *params){
    while(1){
        printf("Reading temperature from %s\n", (char*)params);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
void task2(void *params){
    while(1){
        printf("Reading humidity from %s\n", (char*)params);
        vTaskDelay(2000/portTICK_PERIOD_MS);
    }
}
void app_main(void){
    xTaskCreate(&task1, "Temperature reading", 2048, "Task 1", 2, NULL);
    xTaskCreate(&task2, "Humidity reading", 2048, "Task 2", 2, NULL);
}