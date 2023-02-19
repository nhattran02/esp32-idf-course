#include <stdio.h>
#include "getData.h"

void app_main(void){
    struct getDataParams params;
    sprintf(params.url, "http://go-somewhere");
    params.deal_with_data_fp = DealWithData;
    getData(&params);
}
