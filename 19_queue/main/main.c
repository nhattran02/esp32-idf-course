#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOSConfig.h"

void task1(void *pvParameters);
void task2(void *pvParameters);

void app_main(void){
    xTaskCreate(&task1, "Task 1", 4096, (void*)"From task 1", 0, NULL);
    xTaskCreate(&task2, "Task 2", 4096, (void*)"From task 2", 1, NULL);
    //vTaskStartScheduler(); 
    
}
void task1(void *pvParameters){
    TaskHandle_t task1_handle;
    while(1){
        task1_handle=xTaskGetCurrentTaskHandle();
        printf("\n%s is running------", pcTaskGetName(task1_handle));
        //vTaskDelay(5000/portTICK_PERIOD_MS);
    }
}
void task2(void *pvParameters){
    TaskHandle_t task2_handle;
    while(1){
        task2_handle=xTaskGetCurrentTaskHandle();
        printf("\n%s is running------", pcTaskGetName(task2_handle));
        vTaskDelay(100/portTICK_PERIOD_MS);
        
    }
}