#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person_struct{
    char firstName[20];
    char lastName[20];
    int age;
    void (*DoWork)(char *dataRetrieved)
}Person;
void updatePerson(Person *person, char *dataRetrieved){
    strcpy(person->firstName, "data from dataRetrieved");
    strcpy(person->lastName, "data from dataRetrieved");
    person->age = 22;
}
void connectAndGetInfo(char *url, void(*DoWork)(char *dataRetrieved)){
    char *dataRetrieved = (char*)malloc(1024);
    DoWork(dataRetrieved);
    free((void*)dataRetrieved);
}
void DoWorkForPerson(char *dataRetrieved){
    Person person;
    updatePerson(&person, dataRetrieved);
    printf("person: %s %s is %d years old\n", person.firstName, person.lastName, person.age);
}
void app_main(void){
    connectAndGetInfo("http://getperson.com", DoWorkForPerson);
}