#ifndef FOOD_DELIVERY_H
#define FOOD_DELIVERY_H

#define MAX_RESTAURANTS 20
#define MENU_ITEMS 5
#define MAX_CUSTOMERS 100
#define MAX_ORDERS 200
#define LOCATIONS 10
#define NAME_LEN 50
#define PHONE_LEN 20
#define QUEUE_SIZE MAX_ORDERS

typedef struct {
    int id;
    char name[NAME_LEN];
    char address[NAME_LEN];
    char itemName[MENU_ITEMS][NAME_LEN];
    float price[MENU_ITEMS];
    int preparationTime;
} Restaurant;

typedef struct {
    int id;
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    int location;
} Customer;

typedef struct {
    int id;
    int customerId;
    int restaurantId;
    int itemId;
    int quantity;
    float amount;
    int deliveryType;
    int status;
    int distance;
    int eta;
} Order;

typedef struct QueueNode {
    int orderId;
    int priority;
    struct QueueNode *next;
} QueueNode;

extern Restaurant restaurants[MAX_RESTAURANTS];
extern Customer customers[MAX_CUSTOMERS];
extern Order orders[MAX_ORDERS];
extern int customerCount;
extern int orderCount;

void initializeRestaurants(void);
void showRestaurants(void);
void showRestaurantMenu(void);
void registerCustomer(void);
void viewCustomers(void);
void viewLocations(void);
void placeOrder(void);
void viewOrders(void);
void updateOrderStatus(void);
void viewPendingDeliveries(void);
void trackOrder(void);
void processNextDelivery(void);
void showDeliveryQueue(void);
int calculateShortestDistance(int start, int destination);
void showShortestRoute(int start, int destination);
int calculateETA(int preparationTime, int distance, int deliveryType);
void enqueueDelivery(int orderId, int deliveryType);
int dequeueDelivery(void);
void clearDeliveryQueue(void);

#endif
