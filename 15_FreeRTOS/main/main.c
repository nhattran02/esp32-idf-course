// #include <stdio.h>
// #include <stdlib.h>
// #include "driver/gpio.h"
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"

// #define LED1 2
// #define LED2 4 

// typedef struct {
//     int led;
//     int time;
// }LEDParams;

// void setup(){
//     gpio_set_direction(LED1, GPIO_MODE_OUTPUT);
//     gpio_set_direction(LED2, GPIO_MODE_OUTPUT);
// }
// void BlinkTask(void *params){
//     LEDParams *l = (LEDParams*)params;
//     while(1){
//         gpio_set_level(l->led, 1);
//         vTaskDelay(l->time/portTICK_PERIOD_MS);
//         gpio_set_level(l->led, 0);
//         vTaskDelay(l->time/portTICK_PERIOD_MS);
//     }
// }
// void app_main(void){
//     LEDParams ledParams1={
//         .led = LED1,
//         .time = 200
//     };
//     LEDParams ledParams2={
//         .led = LED2,
//         .time = 200
//     };
//     setup();
//     xTaskCreate(&BlinkTask, "Blink LED 1", 1024*2, &ledParams1, 2, NULL);
//     xTaskCreate(&BlinkTask, "Blink LED 2", 1024*2, &ledParams2, 2, NULL);
//     //it never go into while loop :) 
//     while (true)
//     {
//         vTaskDelay(1000/portTICK_PERIOD_MS);
//     }
// }


#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

void vTask1(void *params){
    while(1){
        printf("Task 1\n");
        vTaskDelay(200/portTICK_PERIOD_MS);
    }
}
void vTask2(void *params){
    while(1){
        printf("Task 22\n");
        vTaskDelay(200/portTICK_PERIOD_MS);
    }
}
void vTask3(void *params){
    while(1){
        printf("Task 333\n\n");
        vTaskDelay(200/portTICK_PERIOD_MS);
    }
}
void app_main(void){
    xTaskCreate(&vTask1, "Task 1", 1024*2, NULL, 2, NULL);
    xTaskCreate(&vTask2, "Task 2", 1024*2, NULL, 5, NULL);
    xTaskCreate(&vTask3, "Task 3", 1024*2, NULL, 3, NULL);
}