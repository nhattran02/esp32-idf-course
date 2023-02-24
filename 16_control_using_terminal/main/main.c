#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "driver/gpio.h"

static const char *TAG = "uart_events";
#define LED 2 
#define EX_UART_NUM UART_NUM_0
#define PATTERN_CHR_NUM    (3)         /*!< Set the number of consecutive and identical characters received by receiver which defines a UART pattern*/
#define BUF_SIZE (1024)
#define RD_BUF_SIZE (BUF_SIZE)
static QueueHandle_t uart0_queue;
TaskHandle_t TaskHandler_uart;

static void uart_event_task(void *pvParameters);
static void config(void);
bool isEqualString(char *str1, char *str2);

void app_main(void)
{
    config();
    //Create a task to handler UART event from ISR
    xTaskCreate(&uart_event_task, "uart_event_task", 1024*2, NULL, 12, &TaskHandler_uart);
}

static void uart_event_task(void *pvParameters)
{
    uart_event_t event;
    size_t buffered_size;
    char* dtmp = (char*) malloc(RD_BUF_SIZE);
    while(1) {
        //Waiting for UART event.
        printf("\n----------CONTROLL LED VIA TERMINAL----------\n");
        printf("1. Turn on LED:     !ONLED! \n");
        printf("2. Turn off LED:    !OFFLED! \n");
        printf("3. Binkly LED:      !BLED! \n");

        if(xQueueReceive(uart0_queue, (void * )&event, (TickType_t)portMAX_DELAY)) {
            bzero(dtmp, RD_BUF_SIZE);
            //if(event.data)
            switch(event.type) {
                //Event of UART receving data
                /*We'd better handler data event fast, there would be much more data events than
                other types of events. If we take too much time on data event, the queue might
                be full.*/
                case UART_DATA:
                    uart_read_bytes(EX_UART_NUM, dtmp, event.size, portMAX_DELAY);
                    printf("%s", dtmp);
                    if(isEqualString(dtmp, "!ONLED!")){
                        gpio_set_level(LED, 1);
                        //vTaskDelete(TaskHandler_blink);

                    }else if(isEqualString(dtmp, "!OFFLED!")){
                        gpio_set_level(LED, 0);
                        //vTaskDelete(TaskHandler_blink);

                    }else if(isEqualString(dtmp, "!BLED!")){
                        for(int i=0;i<5;i++){
                            gpio_set_level(LED, 1);
                            vTaskDelay(500/portTICK_PERIOD_MS);
                            gpio_set_level(LED, 0);
                            vTaskDelay(500/portTICK_PERIOD_MS);
                        }
                    }
                    //ESP_LOGI(TAG, "hw fifo overflow");
                    //uart_write_bytes(EX_UART_NUM, (const char*) dtmp, event.size);
                    break;
                default:
                    ESP_LOGI(TAG, "uart event type: %d", event.type);
                    break;
            }
        }
    }
    free(dtmp);
    dtmp = NULL;
    vTaskDelete(NULL);
}

static void config(void){
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    esp_log_level_set(TAG, ESP_LOG_INFO);
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    //Install UART driver, and get the queue.
    uart_driver_install(EX_UART_NUM, BUF_SIZE * 2, BUF_SIZE * 2, 20, &uart0_queue, 0);
    uart_param_config(EX_UART_NUM, &uart_config);
    //Set UART pins (using UART0 default pins ie no changes.)
    uart_set_pin(EX_UART_NUM, 1, 3, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}

bool isEqualString(char *str1, char *str2){
    bool check=true;
    for(int i=0;i<strlen(str2);i++){
        if(str1[i]!=str2[i]){
            check=false;
            break;
        }
    }
    return check;
}