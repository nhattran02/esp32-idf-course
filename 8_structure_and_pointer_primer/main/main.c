#include <stdio.h>
#include <string.h>

typedef struct Person_struct{
    char firstName[20];
    char lastName[20];
    int age;
}Person;

void updatePerson(Person *person){
    strcpy(person->firstName, "Minh");
    strcpy(person->lastName, "Nhat");
    person->age=21;
}
void exclamIt(char *phrase){
    strcat(phrase, "!");
}
void app_main(void){
    Person person;
    char phrase[20]={"Hello World"};
    exclamIt(phrase);
    printf("function output: %s\n", phrase);
    updatePerson(&person);
    printf("person: %s %s is %d years old\n", person.firstName, person.lastName, person.age);
}