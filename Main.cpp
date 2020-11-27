#include "additionalFunc.h"

void addDish(){

    cls();
    char tempName[100];
    int tempPrice, tempQty;
    while(1){
        int temp = 0;
        getchar();
        printf("Insert the name of the dish [Lowercase letters]: ");
        scanf("%[^\n]", tempName);
        for(int i = 0 ; tempName[i] != '\0' ; i++){
            if(tempName[i] >= 'a' && tempName[i] <= 'z' || tempName[i] == ' '){
                continue;
            }
            else{
                temp = 1;
                break;
            }
        }
        if(temp == 1){
            continue;
        }
        currDish = headDish;
        while(currDish){
            if(strcmp(currDish->name, tempName) == 0){
                temp = 1;
                break;
            }
            currDish = currDish->next;
        }
        if(temp == 1){
            continue;
        }
        break;
    }

    while(1){
        printf("Insert the price of the dish [1000...50000]: ");
        scanf("%d", &tempPrice);
        if(tempPrice >= 1000 && tempPrice <= 50000){
            break;
        }
    }

    while(1){
        printf("Insert the quantity of the dish [1...999]: ");
        scanf("%d", &tempQty);
        getchar();
        if(tempQty >= 1 && tempQty <= 999){
            break;
        }
    }
    pushDish(tempName, tempPrice, tempQty);
    ctrOrder++;
    puts("The dish has been added");
    printf("Press enter to continue...");
    getchar();
    return;
}

void removeDish(){

    int ctr = 1;
    char temp = ' ';
    cls();
    printf("             Bude's Menu\n");
    printf("=====================================\n");
    printf("No.   Name      Quantity     Price\n");
    currDish = headDish;
    while(currDish){
        printf("%d %10s %4c %03d %5c Rp%d\n", ctr++, currDish->name, temp, currDish->qty, temp, currDish->price);
        currDish = currDish->next;
    }

    char tempDish[100];
    while(1){
        printf("Insert dish's name to be deleted: ");
        scanf("%s", tempDish);
        currDish = headDish;
        while(currDish && strcmp(currDish->name, tempDish) != 0){
            currDish = currDish->next;
        }
        if(currDish == NULL){
            continue;
        }
        currDish->prev->next = currDish->next;
        currDish->next->prev = currDish->prev;
        currDish->prev = currDish->next = NULL;
        free(currDish);

    }
    getchar();getchar();
    
}

void addCust(){

    cls();
    char tempName[100];
    while(1){
        int temp = 0;
        getchar();
        printf("Insert the customer's name [Without space]: ");
        scanf("%[^\n]", tempName);
        for(int i = 0 ; tempName[i] != '\0' ; i++){
            if(tempName[i] == ' '){
                temp = 1;
                break;
            }
        }
        if(temp == 0){
            break;
        }
    }

    insert(tempName);

    printf("Customer has been added!\n");
    printf("Press enter to continue...");
    getchar();getchar();

}

void searchCust(){

    cls();
    char tempName[100];
    while(1){
        int temp = 0;
        getchar();
        printf("Insert the customer’s name to be searched: ");
        scanf("%[^\n]", tempName);
        for(int i = 0 ; tempName[i] != '\0' ; i++){
            if(tempName[i] == ' '){
                temp = 1;
                break;
            }
        }
        if(temp == 0){
            break;
        }
    }

    int index = djb2(tempName);
    currCustomer = headCustomer[index];
    while(currCustomer){
        if(strcmp(currCustomer->name, tempName) == 0){
            printf("%s is present.\n", tempName);
            printf("Press enter to continue...");
            getchar(); getchar();
            return;
        }
        currCustomer = currCustomer->next;
    }

    printf("%s is not present.\n", tempName);
    printf("Press enter to continue...");
    getchar(); getchar();

}

void viewWarteg(){

    cls();
    printf("Customer's List\n");
    for(int i = 0 ; i < MAX_ELEMENT ; i++){
        currCustomer = headCustomer[i];
        while(currCustomer){
            if(currCustomer->name != NULL){
                printf("%d. %s\n", i, currCustomer->name);
            }
            currCustomer = currCustomer->next;
        }
    }

    printf("\nPress enter to continue...");
    getchar(); getchar();

}

void order(){

    cls();
    char tempName[100];
    while(1){
        while(1){
            int temp = 0;
            getchar();
            printf("Insert the customer’s name: ");
            scanf("%[^\n]", tempName);
            for(int i = 0 ; tempName[i] != '\0' ; i++){
                if(tempName[i] == ' '){
                    temp = 1;
                    break;
                }
            }
            if(temp == 0){
                break;
            }
        }

        int temp = 0;
        int index = djb2(tempName);
        currCustomer = headCustomer[index];
        while(currCustomer){
            if(strcmp(currCustomer->name, tempName) == 0){
                temp = 1;
                break;
            }
            currCustomer = currCustomer->next;
        }

        if(temp == 1){
            break;
        }
    }

    int tempQty;
    while(1){
        printf("Insert the amount of dish: ");
        scanf("%d", &tempQty);
        if(tempQty >= 1 && tempQty <= ctrOrder){
            break;
        }
    }

    char tempOrder[100];
    for(int i = 1 ; i <= tempQty ; i++){
        int temp = 0;
        int index;
        printf("[%d] Insert the dish's name and quantity: ", i);
        getchar();
        scanf("%[^\n]", tempOrder);
        for(int j = 0 ; tempOrder[j] != '\0' ; j++){
            if(tempOrder[j] == 'x' && tempOrder[j+1] >= '0' && tempOrder[j+1] <= '9'){
                temp = 1;
                index = j-2;
                break;
            }
        }

        // makanan x9
        // 0123456789
        // index = 6

        if(temp == 0){
            i--;
            continue;
        }
        
        char tempOrderName[100] = {};
        for(int j = 0 ; j <= index ; j++){
            tempOrderName[j] = tempOrder[j];
        }

        index+=3;
        int tempQtyOrder = 0;
        int pow = 1;
        for(int j = strlen(tempOrder)-1 ; j >= index ; j--){
            tempQtyOrder+=(tempOrder[j] - '0')*pow;
            pow*=10;
        }

        // printf("%s %d\n",tempOrderName, tempQtyOrder);

        currDish = headDish;
        temp = 0;
        int tempOrderPrice;
        while(currDish){
            if(strcmp(currDish->name, tempOrderName) == 0){
                if(tempQtyOrder > currDish->qty){
                    break;
                }
                tempOrderPrice = currDish->price;
                currDish->qty -= tempQtyOrder;
                temp = 1;
                break;
            }
            currDish = currDish->next;
        }
        if(temp == 0){
            i--;
            continue;
        }
        
        int indexing = djb2(tempName);
        // printf("Index %d\n", indexing);
        pushOrder(tempOrderName, tempOrderPrice, tempQtyOrder, indexing);

    }

    printf("Order success!\n");
    getchar(); getchar();

}

void payment(){

    cls();
    int tempIndex;
    while(1){
        printf("Insert the customer's index: ");
        scanf("%d", &tempIndex);
        currCustomer = headCustomer[tempIndex];
        if(currCustomer->name != NULL){
            break;
        }
    }

    if(headOrder[tempIndex] == NULL){
        printf("No order\n");
        printf("Press enter to continue...");
        getchar(); getchar();
        return;
    }

    currOrder = headOrder[tempIndex];
    printf("%s\n", currCustomer->name);
    int tempCtr = 1;
    int totalPrice = 0;
    while(currOrder){
        printf("[%d] %s x%d\n", tempCtr++, currOrder->name, currOrder->qty);
        totalPrice+=currOrder->price*currOrder->qty;
        currOrder = currOrder->next;
    }

    while(1){
        if(headOrder[tempIndex] && headOrder[tempIndex] == tailOrder[tempIndex]){
            headOrder[tempIndex] = tailOrder[tempIndex] = NULL;
            free(headOrder[tempIndex]);
            break;
        }
        else{
            Order *newHead = headOrder[tempIndex]->next;
            headOrder[tempIndex]->next = newHead->prev = NULL;
            free(headOrder[tempIndex]);
            headOrder[tempIndex] = newHead; 
        }
    }
    printf("Total: Rp%d\n", totalPrice);
    printf("Press enter to continue...");
    getchar(); getchar();    

}

void exit(){

    cls();
    printf("Please expand your terminal to full screen!\n");
    printf("Press enter to continue...");
    getchar(); getchar();

    cls();
    FILE *fp = fopen("splash-screen.txt", "r");
    char temp[100];
    while(fscanf(fp, "%[^\n]\n", temp) == 1){
        printf("%s\n", temp);
    }
    fclose(fp);
    return;


}

int main(){

    int i = 0;
    while(1){
        cls();

        printf("System: %s\n", detectOS());
        puts("1. Add Dish");
        puts("2. Remove Dish");
        puts("3. Add Customer");
        puts("4. Search Customer");
        puts("5. View Warteg");
        puts("6. Order");
        puts("7. Payment");
        puts("8. Exit Warteg");
        printf(">> ");
        int choose;
        scanf("%d", &choose);
        if(choose == 1){
            addDish();
        }
        if(choose == 2){
            removeDish();
        }
        if(choose == 3){
            addCust();
        }
        if(choose == 4){
            searchCust();
        }
        if(choose == 5){
            viewWarteg();
        }
        if(choose == 6){
            order();
        }
        if(choose == 7){
            payment();
        }
        if(choose == 8){
            exit();
            break;
        }
    }

    return 0;
}