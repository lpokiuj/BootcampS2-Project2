#include "LinkedList.h"

const char* detectOS() {
  #ifdef _WIN32
  return "Windows 32-bit";
  #elif _WIN64
  return "Windows 64-bit";
  #elif __APPLE__ || __MACH__
  return "Mac OSX";
  #elif __linux__
  return "Linux";
  #elif __FreeBSD__
  return "FreeBSD";
  #elif __unix || __unix__
  return "Unix";
  #else
  return "Other";
  #endif
}

void cls(){

    for(int i = 0 ; i < 60 ; i++){
        puts("");
    }

}

void printLinkedList(){

    cls();
    if(!headDish){
        return;
    }
    else{
        currDish = headDish;
        while(currDish){
            printf("Name: %s\n", currDish->name);
            printf("Price: %d\n", currDish->price);
            printf("Quantity: %d\n", currDish->qty);
            currDish = currDish->next;
        }
        getchar();getchar();
    }
}

