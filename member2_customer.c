#include <stdio.h>
#include <string.h>
#include "food_delivery.h"

Customer customers[MAX_CUSTOMERS];
int customerCount=0;
static const char *locationNames[LOCATIONS]={"Central Park","City Mall","Railway Station","University","Tech Park","Beach Road","Hospital","Bus Stand","Green Residency","Lake View"};

void viewLocations(void){
    printf("\n=========== DELIVERY LOCATIONS ===========\n");
    for(int i=0;i<LOCATIONS;i++) printf("%2d. %s\n",i+1,locationNames[i]);
}
void registerCustomer(void){
    if(customerCount>=MAX_CUSTOMERS){printf("Customer limit reached.\n");return;}
    Customer *c=&customers[customerCount]; c->id=customerCount+1;
    printf("\nEnter customer name: "); scanf(" %49[^\n]",c->name);
    printf("Enter phone number: "); scanf("%19s",c->phone);
    viewLocations(); printf("\nSelect delivery location (1-10): "); scanf("%d",&c->location);
    if(c->location<1||c->location>10){printf("Invalid location.\n");return;}
    customerCount++;
    printf("\nCustomer registered successfully! Customer ID: %d\n",c->id);
}
void viewCustomers(void){
    if(customerCount==0){printf("\nNo customers registered.\n");return;}
    printf("\n================ CUSTOMERS ================\n");
    printf("%-4s %-20s %-15s %s\n","ID","Name","Phone","Location");
    for(int i=0;i<customerCount;i++) printf("%-4d %-20s %-15s %s\n",customers[i].id,customers[i].name,customers[i].phone,locationNames[customers[i].location-1]);
}
