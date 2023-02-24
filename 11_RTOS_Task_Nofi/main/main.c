#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static TaskHandle_t receiverHandler = NULL; 
void sender(void *params);
void receiver(void * params);

/*------------------------------------------------*/
void app_main(void){
    xTaskCreate(&receiver, "receiver", 2048, NULL, 2, &receiverHandler);
    xTaskCreate(&sender, "sender", 2048, NULL, 2, NULL);
}
/*------------------------------------------------*/

void sender(void *params){
    while(1){
        xTaskNotifyGive(receiverHandler);
        xTaskNotifyGive(receiverHandler);
        xTaskNotifyGive(receiverHandler);
        xTaskNotifyGive(receiverHandler);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        
    }
}
void receiver(void * params){
    while(1){
        int count = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        printf("Received notification %d times \n", count);
    }
}