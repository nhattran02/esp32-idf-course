#include <stdio.h>
#include <esp_log.h>

void app_main(void){
    esp_log_level_set("LOG", ESP_LOG_INFO);
    ESP_LOGE("LOG", "This is an error");
    ESP_LOGW("LOG", "This is an warning");
    ESP_LOGI("LOG", "This is an info");
    ESP_LOGD("LOG", "This is an Debug");
    ESP_LOGV("LOG", "This is an Verbose");
    int number = 0;
    ESP_LOGE("TAG 2", "This is an error %d", number++);
    ESP_LOGW("TAG 2", "This is an warning %d", number++);
    ESP_LOGI("TAG 2", "This is an info %d", number++);
    ESP_LOGD("TAG 2", "This is an Debug %d", number++);
    ESP_LOGV("TAG 2", "This is an Verbose %d", number++);
}