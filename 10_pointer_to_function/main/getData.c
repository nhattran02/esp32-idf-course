#include <stdio.h>
#include "getData.h"

void connectToURL(char *url){
    printf("Connected to %s\n", url);
}
void DealWithData(char *data){
    printf("Got: ");
    printf("%s\n", data);
}
void getData(struct getDataParams *params){
    //connect to internet

    //create client and connect to url 
    connectToURL(params->url);
    //get some data 
    char *data = "HCMUT's data";
    params->deal_with_data_fp(data);
    //expose data
}