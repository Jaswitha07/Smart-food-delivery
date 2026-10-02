#include <stdio.h>
#include "food_delivery.h"

Order orders[MAX_ORDERS];
int orderCount=0;

static const char *statusName(int s){return s==0?"Waiting":s==1?"Preparing":s==2?"Out for Delivery":"Delivered";}

void placeOrder(void){
    int customerId,restaurantId,itemId,quantity,deliveryType;
    if(customerCount==0){printf("\nPlease register a customer first.\n");return;}
    viewCustomers(); printf("\nEnter customer ID: "); scanf("%d",&customerId);
    if(customerId<1||customerId>customerCount){printf("Invalid customer ID.\n");return;}
    showRestaurants(); printf("\nEnter restaurant ID: "); scanf("%d",&restaurantId);
    if(restaurantId<1||restaurantId>20){printf("Invalid restaurant ID.\n");return;}
    Restaurant *r=&restaurants[restaurantId-1];
    printf("\n=============== %s MENU ===============\n",r->name);
    for(int i=0;i<5;i++) printf("%d. %-25s Rs. %.2f\n",i+1,r->itemName[i],r->price[i]);
    printf("Preparation time: %d minutes\n",r->preparationTime);
    printf("\nSelect menu item: "); scanf("%d",&itemId);
    if(itemId<1||itemId>5){printf("Invalid menu item.\n");return;}
    printf("Enter quantity: "); scanf("%d",&quantity);
    if(quantity<=0){printf("Invalid quantity.\n");return;}
    printf("Delivery type (1 = Standard, 2 = Express): "); scanf("%d",&deliveryType);
    if(deliveryType!=1&&deliveryType!=2){printf("Invalid delivery type.\n");return;}

    Customer *c=&customers[customerId-1]; Order *o=&orders[orderCount];
    o->id=orderCount+1; o->customerId=customerId; o->restaurantId=restaurantId; o->itemId=itemId;
    o->quantity=quantity; o->amount=r->price[itemId-1]*quantity; o->deliveryType=deliveryType; o->status=0;
    o->distance=calculateShortestDistance(restaurantId,c->location);
    o->eta=calculateETA(r->preparationTime,o->distance,deliveryType);
    orderCount++;
    enqueueDelivery(o->id,deliveryType);
    printf("\nOrder placed successfully!\nOrder ID: %d\nAmount: Rs. %.2f\nEstimated delivery time: %d minutes\n",o->id,o->amount,o->eta);
}
void viewOrders(void){
    if(orderCount==0){printf("\nNo orders placed.\n");return;}
    printf("\n==================== ORDERS ====================\n");
    for(int i=0;i<orderCount;i++){Order *o=&orders[i];Restaurant *r=&restaurants[o->restaurantId-1];Customer *c=&customers[o->customerId-1];
        printf("Order %d | %s | %s | %s x%d | Rs. %.2f | %s | ETA %d min | %s\n",o->id,c->name,r->name,r->itemName[o->itemId-1],o->quantity,o->amount,statusName(o->status),o->eta,o->deliveryType==2?"EXPRESS":"STANDARD");
    }
}
void updateOrderStatus(void){
    int id,status; viewOrders(); if(orderCount==0)return;
    printf("\nEnter order ID: "); scanf("%d",&id);
    if(id<1||id>orderCount){printf("Invalid order ID.\n");return;}
    printf("\n1. Preparing\n2. Out for Delivery\n3. Delivered\nChoose status: "); scanf("%d",&status);
    if(status<1||status>3){printf("Invalid status.\n");return;}
    orders[id-1].status=status; printf("Order %d status updated to %s.\n",id,statusName(status));
}
