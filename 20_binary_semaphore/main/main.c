#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "freertos/semphr.h"

//xSemaphoreGive() => set to 1
//xSemaphoreTake() => set to 0

void task1(void *pvParameters);
void task2(void *pvParameters);

SemaphoreHandle_t Sem_Handle; 

void app_main(void){
    Sem_Handle = xSemaphoreCreateBinary();
    xTaskCreate(&task1, "Task 1", 2048, NULL, 0, NULL);
    xTaskCreate(&task2, "Task 2", 2048, NULL, 2, NULL);
}

void task1(void *pvParameters){
    TaskHandle_t task1_hdl;
    while (1)
    {
        task1_hdl = xTaskGetCurrentTaskHandle();
        printf("%s give semaphore (SEM=1)\n", pcTaskGetName(task1_hdl));
        xSemaphoreGive(Sem_Handle); //SEM=1
        printf("%s finish giving semaphore \n", pcTaskGetName(task1_hdl));
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    
}
void task2(void *pvParameters){
    TaskHandle_t task2_hdl;
    while (1)
    {
        task2_hdl = xTaskGetCurrentTaskHandle();
        xSemaphoreTake(Sem_Handle, portMAX_DELAY); //SEM=0 
        printf("%s synchronzied\n", pcTaskGetName(task2_hdl));
        //vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

