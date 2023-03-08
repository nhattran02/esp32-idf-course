#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "freertos/semphr.h"
#include "freertos/FreeRTOSConfig.h"

//binary - xSemaphoreGive() => set to 1 (sem=1)
//binary - xSemaphoreTake() => set to 0 (sem=0)
//counting - xSemaphoreGive() => increase +1 (sem++)
//counting - xSemaphoreTake() => decrease -1 (sem--)


void task1(void *pvParameters);
void task2(void *pvParameters);
void task3(void *pvParameters);
SemaphoreHandle_t Sem_Handle;


void app_main(void){
    Sem_Handle = xSemaphoreCreateCounting(2, 0); //max = 2, init = 0
    xTaskCreate(&task1, "Task 1", 2048, NULL, 1, NULL);
    xTaskCreate(&task2, "Task 2", 2048, NULL, 1, NULL);
    xTaskCreate(&task3, "Task 3", 2048, NULL, 2, NULL);

}

void task1(void *pvParameters){
    TaskHandle_t task1_hdl;
    while (1)
    {
        task1_hdl = xTaskGetCurrentTaskHandle();
        printf("%s give signal 1\n", pcTaskGetName(task1_hdl));
        xSemaphoreGive(Sem_Handle); //SEM++
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
void task2(void *pvParameters){
    TaskHandle_t task2_hdl;
    while (1)
    {
        task2_hdl = xTaskGetCurrentTaskHandle();
        printf("%s give signal 2\n", pcTaskGetName(task2_hdl));
        xSemaphoreGive(Sem_Handle); //SEM++
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
void task3(void *pvParameters){
    TaskHandle_t task3_hdl;
    while(1){
        task3_hdl = xTaskGetCurrentTaskHandle();
        xSemaphoreTake(Sem_Handle, portMAX_DELAY);
        xSemaphoreTake(Sem_Handle, portMAX_DELAY);
        printf("%s synchronized --- \n \n", pcTaskGetName(task3_hdl));
    }
}

