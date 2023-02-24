#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "freertos/semphr.h"

SemaphoreHandle_t mutexBus;

void writeToBus(char *message){
    printf(message);
}
void task1(void *params){
    while(1){
        printf("Reading temperate \n");
        if(xSemaphoreTake(mutexBus, 1000/portTICK_PERIOD_MS)){
            writeToBus("Temperature is 35c\n");
            xSemaphoreGive(mutexBus);
        }else{
            printf("Writing temperature timed out \n");
        }
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
void task2(void *params){
    while(1){
        printf("Reading humidity \n");
        if(xSemaphoreTake(mutexBus, 1000/portTICK_PERIOD_MS)){
            writeToBus("Humidity is 50 percent\n");
            xSemaphoreGive(mutexBus);
        }else{
            printf("Writing humidity timed out \n");
        }
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void app_main(void){
    mutexBus = xSemaphoreCreateMutex();
    xTaskCreate(&task1, "Temperature reading", 2048, NULL, 2, NULL);
    xTaskCreate(&task2, "Humidity reading", 2048, NULL, 2, NULL);
}


