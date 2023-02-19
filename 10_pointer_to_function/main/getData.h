#ifndef _GET_DATA_H_
#define _GET_DATA_H_

struct getDataParams{
    char url[256];
    void (*deal_with_data_fp)(char *data); //fp is stand for function pointer
};
void connectTour1(char *url);
void DealWithData(char *data);
void getData(struct getDataParams *params);

#endif