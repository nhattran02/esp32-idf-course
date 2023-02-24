#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void task1(void *params);
void task2(void *params);
void app_main(){
    xTaskCreate(&task1, "Temperature Reading", 2048, "Task 1's data", 2, NULL);
    xTaskCreatePinnedToCore(&task2, "Humidity Reading", 2048, "Task 2's data", 2, NULL, 0);

}
void task1(void *params){
    while(1){
        printf("Reading temperature from %s\n", (char*)params);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
void task2(void *params){
    while(1){
        printf("Reading Humidity from %s\n", (char *)params);
        vTaskDelay(2000/portTICK_PERIOD_MS);
    }
}

