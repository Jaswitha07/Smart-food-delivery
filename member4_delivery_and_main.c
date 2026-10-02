#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "food_delivery.h"

static const char *locationNames[LOCATIONS]={"Central Park","City Mall","Railway Station","University","Tech Park","Beach Road","Hospital","Bus Stand","Green Residency","Lake View"};
static int graph[LOCATIONS][LOCATIONS]={
{0,3,7,8,12,10,9,6,8,13},{3,0,4,6,9,8,7,5,6,10},{7,4,0,5,6,7,6,4,5,7},{8,6,5,0,3,5,4,6,4,5},{12,9,6,3,0,4,5,7,3,4},
{10,8,7,5,4,0,3,6,6,5},{9,7,6,4,5,3,0,4,5,4},{6,5,4,6,7,6,4,0,3,6},{8,6,5,4,3,6,5,3,0,4},{13,10,7,5,4,5,4,6,4,0}};

static QueueNode *queueHead=NULL;
static QueueNode *queueTail=NULL;

static int locationFromRestaurant(int restaurantId){ return (restaurantId-1)%LOCATIONS; }

int calculateShortestDistance(int start,int destination){
    int source=locationFromRestaurant(start), dest=destination-1;
    int dist[LOCATIONS], used[LOCATIONS]={0};
    for(int i=0;i<LOCATIONS;i++) dist[i]=INT_MAX;
    dist[source]=0;

    for(int count=0;count<LOCATIONS;count++){
        int u=-1;
        for(int i=0;i<LOCATIONS;i++)
            if(!used[i] && (u==-1 || dist[i]<dist[u])) u=i;
        if(u==-1 || dist[u]==INT_MAX) break;
        used[u]=1;
        for(int v=0;v<LOCATIONS;v++)
            if(graph[u][v]>0 && dist[u]+graph[u][v]<dist[v])
                dist[v]=dist[u]+graph[u][v];
    }
    return dist[dest];
}

void showShortestRoute(int start,int destination){
    int source=locationFromRestaurant(start), dest=destination-1;
    int dist[LOCATIONS], parent[LOCATIONS], used[LOCATIONS]={0};
    int path[LOCATIONS], count=0;

    for(int i=0;i<LOCATIONS;i++){ dist[i]=INT_MAX; parent[i]=-1; }
    dist[source]=0;

    for(int step=0;step<LOCATIONS;step++){
        int u=-1;
        for(int i=0;i<LOCATIONS;i++)
            if(!used[i] && (u==-1 || dist[i]<dist[u])) u=i;
        if(u==-1 || dist[u]==INT_MAX) break;
        used[u]=1;
        for(int v=0;v<LOCATIONS;v++){
            if(graph[u][v]>0 && dist[u]+graph[u][v]<dist[v]){
                dist[v]=dist[u]+graph[u][v];
                parent[v]=u;
            }
        }
    }

    if(dist[dest]==INT_MAX){ printf("No route available.\n"); return; }
    for(int v=dest;v!=-1;v=parent[v]) path[count++]=v;
    printf("Route        : ");
    for(int i=count-1;i>=0;i--){
        printf("%s",locationNames[path[i]]);
        if(i>0) printf(" -> ");
    }
    printf("\nShortest distance: %d km\n",dist[dest]);
}

int calculateETA(int preparationTime,int distance,int deliveryType){
    int travelTime=distance*3;
    int priorityAdjustment=(deliveryType==2)?-5:0;
    int eta=preparationTime+travelTime+priorityAdjustment;
    if(eta<5) eta=5;
    return eta;
}

void enqueueDelivery(int orderId,int deliveryType){
    QueueNode *node=(QueueNode*)malloc(sizeof(QueueNode));
    if(!node){ printf("Queue memory unavailable.\n"); return; }
    node->orderId=orderId;
    node->priority=deliveryType==2?1:2;
    node->next=NULL;

    if(queueHead==NULL || node->priority<queueHead->priority){
        node->next=queueHead;
        queueHead=node;
        if(queueTail==NULL) queueTail=node;
        return;
    }

    QueueNode *cur=queueHead;
    while(cur->next && cur->next->priority<=node->priority) cur=cur->next;
    node->next=cur->next;
    cur->next=node;
    if(node->next==NULL) queueTail=node;
}

int dequeueDelivery(void){
    while(queueHead){
        QueueNode *node=queueHead;
        int id=node->orderId;
        queueHead=node->next;
        if(queueHead==NULL) queueTail=NULL;
        free(node);
        if(id>=1 && id<=orderCount && orders[id-1].status<2) return id;
    }
    return -1;
}

void clearDeliveryQueue(void){
    while(queueHead){
        QueueNode *node=queueHead;
        queueHead=node->next;
        free(node);
    }
    queueTail=NULL;
}

void showDeliveryQueue(void){
    QueueNode *cur=queueHead;
    int found=0;
    printf("\n============= DELIVERY PRIORITY QUEUE =============\n");
    while(cur){
        if(cur->orderId>=1 && cur->orderId<=orderCount && orders[cur->orderId-1].status<2){
            Order *o=&orders[cur->orderId-1];
            printf("Order %d | %s | %s\n",o->id,o->deliveryType==2?"EXPRESS":"STANDARD",o->status==0?"Waiting":"Preparing");
            found=1;
        }
        cur=cur->next;
    }
    if(!found) printf("No orders in the delivery queue.\n");
}

void viewPendingDeliveries(void){
    int found=0;
    printf("\n============= PENDING DELIVERIES =============\n");
    for(int i=0;i<orderCount;i++){
        if(orders[i].status<3){
            printf("Order %d | %s | %s | Status: %s\n",orders[i].id,restaurants[orders[i].restaurantId-1].name,orders[i].deliveryType==2?"EXPRESS":"STANDARD",orders[i].status==0?"Waiting":orders[i].status==1?"Preparing":"Out for Delivery");
            found=1;
        }
    }
    if(!found) printf("No pending deliveries.\n");
}

void trackOrder(void){
    int id;
    viewOrders();
    if(orderCount==0) return;
    printf("\nEnter order ID to track: "); scanf("%d",&id);
    if(id<1||id>orderCount){ printf("Invalid order ID.\n"); return; }
    Order *o=&orders[id-1];
    Restaurant *r=&restaurants[o->restaurantId-1];
    Customer *c=&customers[o->customerId-1];
    int source=locationFromRestaurant(o->restaurantId);
    printf("\n=============== ORDER TRACKING ===============\n");
    printf("Order ID      : %d\nRestaurant    : %s\nCustomer      : %s\nDestination   : %s\n",o->id,r->name,c->name,locationNames[c->location-1]);
    printf("Status        : %s\n",o->status==0?"Waiting":o->status==1?"Preparing":o->status==2?"Out for Delivery":"Delivered");
    printf("Route starts  : %s\n",locationNames[source]);
    showShortestRoute(o->restaurantId,c->location);
    printf("Estimated time: %d minutes\n",o->eta);
}

void processNextDelivery(void){
    int id=dequeueDelivery();
    if(id==-1){ printf("\nNo delivery is ready to process.\n"); return; }
    orders[id-1].status=2;
    printf("\nProcessing Order %d\nRestaurant: %s\nCustomer: %s\nPriority: %s\nOrder %d is now Out for Delivery.\n",id,restaurants[orders[id-1].restaurantId-1].name,customers[orders[id-1].customerId-1].name,orders[id-1].deliveryType==2?"EXPRESS":"STANDARD",id);
}

static void restaurantMenu(void){
    int ch;
    do{
        printf("\n----------- RESTAURANTS -----------\n1. View Restaurants\n2. View Menu\n0. Back\nEnter choice: ");
        scanf("%d",&ch);
        if(ch==1) showRestaurants();
        else if(ch==2) showRestaurantMenu();
    }while(ch!=0);
}

static void customerMenu(void){
    int ch;
    do{
        printf("\n----------- CUSTOMERS -----------\n1. Register Customer\n2. View Customers\n3. View Delivery Locations\n0. Back\nEnter choice: ");
        scanf("%d",&ch);
        if(ch==1) registerCustomer();
        else if(ch==2) viewCustomers();
        else if(ch==3) viewLocations();
    }while(ch!=0);
}

static void orderMenu(void){
    int ch;
    do{
        printf("\n----------- ORDERS -----------\n1. Place Order\n2. View Orders\n3. Update Order Status\n0. Back\nEnter choice: ");
        scanf("%d",&ch);
        if(ch==1) placeOrder();
        else if(ch==2) viewOrders();
        else if(ch==3) updateOrderStatus();
    }while(ch!=0);
}

static void deliveryMenu(void){
    int ch;
    do{
        printf("\n----------- DELIVERY -----------\n1. View Pending Deliveries\n2. View Delivery Queue\n3. Track an Order\n4. Process Next Delivery\n0. Back\nEnter choice: ");
        scanf("%d",&ch);
        if(ch==1) viewPendingDeliveries();
        else if(ch==2) showDeliveryQueue();
        else if(ch==3) trackOrder();
        else if(ch==4) processNextDelivery();
    }while(ch!=0);
}

int main(void){
    int choice;
    initializeRestaurants();
    printf("\nWelcome to Smart Food Delivery System!\n");
    do{
        printf("\n====================================================\n          SMART FOOD DELIVERY SYSTEM\n====================================================\n1. Restaurants\n2. Customers\n3. Orders\n4. Delivery\n0. Exit\n====================================================\nEnter your choice: ");
        scanf("%d",&choice);
        if(choice==1) restaurantMenu();
        else if(choice==2) customerMenu();
        else if(choice==3) orderMenu();
        else if(choice==4) deliveryMenu();
        else if(choice!=0) printf("Invalid choice.\n");
    }while(choice!=0);
    clearDeliveryQueue();
    printf("\nThank you for using Smart Food Delivery System!\n");
    return 0;
}
