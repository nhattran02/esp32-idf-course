#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/timers.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "driver/gpio.h"
#define LED 2 

TimerHandle_t xTimers[2];
void vTimerCallback(TimerHandle_t xTimer);
void vTask1(void *params);
void toggle_pin(gpio_num_t led);

void app_main(void){
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    xTimerStart(xTimers[0], 0);
    xTimerStart(xTimers[1], 0);
    xTimers[0]=xTimerCreate("Timer Blink", pdMS_TO_TICKS(500), pdTRUE, (void*)0, vTimerCallback);
    xTimers[1]=xTimerCreate("Timer Blink", pdMS_TO_TICKS(1000), pdTRUE, (void*)1, vTimerCallback);
    xTaskCreate(vTask1, "Task 1", 1024, NULL, 4, NULL);
}
void vTimerCallback(TimerHandle_t xTimer){
    configASSERT(xTimer);
    uint32_t ulCount = (uint32_t )pvTimerGetTimerID(xTimer);
    if(ulCount == 0){ //timer 0
        toggle_pin(LED);
    }else if(ulCount == 1){ //timer 1
        printf("Hello \n");
    }
}
void vTask1(void *params){
    while(1){
        printf("Task 1 \n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
void toggle_pin(gpio_num_t led){
    int old_level = gpio_get_level(LED);
    gpio_set_level(LED, 1-old_level);
}