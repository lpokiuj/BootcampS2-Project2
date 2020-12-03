#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>

int ctrDish = 0;

const int MAX_ELEMENT = 26;

unsigned long djb2(char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
    hash = ((hash << 5) + hash) + c;
    return hash % MAX_ELEMENT;
}

struct Dish{
    char name[255];
    int price;
    int qty;
    Dish *next, *prev;
}*headDish, *tailDish, *currDish, *newDish, *delDish;

Dish *createDish(char name[], int price, int qty){
    Dish *temp = (Dish*)malloc(sizeof(Dish));
    strcpy(temp->name, name);
    temp->price = price;
    temp->qty = qty;
    temp->next = temp->prev = NULL;
    return temp;
}

void pushDish(char name[], int price, int qty){
    Dish *temp = createDish(name, price, qty);
    if(!headDish){
        headDish = tailDish = temp;
    }
    else{
        tailDish->next = temp;
        tailDish = temp;
    }
}

struct Customer {
    char name[255];
    Customer *prev, *next;    
}*headCustomer[MAX_ELEMENT], *tailCustomer[MAX_ELEMENT], *currCustomer, *newCustomer, *delCustomer;

Customer *createCustomer(char name[]){
    Customer *temp = (Customer*)malloc(sizeof(Customer));
    strcpy(temp->name, name);
    temp->next = temp->prev = NULL;
    return temp;
}

void insert(char str[]){
    int index = djb2(str);

    if(headCustomer[index]){
        Customer *temp = createCustomer(str);
        tailCustomer[index]->next = temp;
        tailCustomer[index] = temp;
    }
    else{
        headCustomer[index] = tailCustomer[index] = createCustomer(str);
    }
}

struct Order{
    char name[100];
    int qty, price;
    Order *next, *prev;
}*headOrder[MAX_ELEMENT], *tailOrder[MAX_ELEMENT], *currOrder;

Order *createOrder(char name[], int price, int qty){
    Order *temp = (Order*)malloc(sizeof(Order));
    strcpy(temp->name, name);
    temp->price = price;
    temp->qty = qty;
    temp->next = temp->prev = NULL;
    return temp;
}

void pushOrder(char str[], int price, int qty, int index){
    if(headOrder[index]){
        Order *temp = createOrder(str, price, qty);
        tailOrder[index]->next = temp;
        tailOrder[index] = temp;
    }
    else{
        headOrder[index] = tailOrder[index] = createOrder(str, price, qty);
    }
}