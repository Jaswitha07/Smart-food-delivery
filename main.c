#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FOOD 10
#define MAX_RESTAURANTS 6

typedef struct food
{
    int id;
    char name[50];
    char category[30];
    float price;
} Food;

typedef struct restaurant
{
    int id;
    char name[60];
    char location[50];
    float rating;
    int delivery_time;
    Food menu[MAX_FOOD];
    int food_count;
    struct restaurant *next;
} Restaurant;

typedef struct customer
{
    int id;
    char name[60];
    char phone[20];
    char address[100];
    struct customer *next;
} Customer;

typedef struct order
{
    int order_id;
    int customer_id;
    char customer_name[60];
    char restaurant[60];
    float amount;
    int priority;
    char status[30];
    struct order *next;
} Order;

typedef struct order_queue
{
    Order *front;
    Order *rear;
} OrderQueue;

Restaurant *restaurant_head = NULL;
Customer *customer_head = NULL;

OrderQueue pending_orders = {NULL, NULL};

int customer_count = 0;
int order_count = 1000;


/* ---------- Utility Functions ---------- */

void line()
{
    printf("------------------------------------------------------------\n");
}

void header(char title[])
{
    printf("\n");
    line();
    printf("                 %s\n", title);
    line();
}


/* ---------- Restaurant Data ---------- */

void add_food(Restaurant *r, int id, char name[],
              char category[], float price)
{
    if (r->food_count >= MAX_FOOD)
        return;

    r->menu[r->food_count].id = id;

    strcpy(r->menu[r->food_count].name, name);
    strcpy(r->menu[r->food_count].category, category);

    r->menu[r->food_count].price = price;

    r->food_count++;
}

void create_restaurant(int id, char name[],
                       char location[], float rating,
                       int delivery_time)
{
    Restaurant *r;

    r = (Restaurant *)malloc(sizeof(Restaurant));

    if (r == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    r->id = id;

    strcpy(r->name, name);
    strcpy(r->location, location);

    r->rating = rating;
    r->delivery_time = delivery_time;
    r->food_count = 0;

    r->next = restaurant_head;
    restaurant_head = r;
}


/* ---------- Initial Restaurant Menu ---------- */

void load_restaurants()
{
    Restaurant *r;

    create_restaurant(1, "Spice Route",
                      "MVP Colony", 4.7, 25);

    create_restaurant(2, "Pizza Craft",
                      "Dwaraka Nagar", 4.5, 30);

    create_restaurant(3, "Burger Yard",
                      "Siripuram", 4.3, 22);

    create_restaurant(4, "Green Bowl",
                      "Madhurawada", 4.6, 28);

    create_restaurant(5, "Coastal Kitchen",
                      "Beach Road", 4.8, 35);

    create_restaurant(6, "Dosa Corner",
                      "Gajuwaka", 4.4, 24);


    r = restaurant_head;

    while (r != NULL)
    {
        if (r->id == 6)
        {
            add_food(r, 601, "Masala Dosa",
                     "South Indian", 89);

            add_food(r, 602, "Paneer Dosa",
                     "South Indian", 129);

            add_food(r, 603, "Idli Vada",
                     "Breakfast", 79);
        }

        if (r->id == 5)
        {
            add_food(r, 501, "Fish Fry",
                     "Seafood", 279);

            add_food(r, 502, "Prawn Curry",
                     "Seafood", 299);

            add_food(r, 503, "Andhra Meals",
                     "Indian", 179);
        }

        if (r->id == 4)
        {
            add_food(r, 401, "Veg Rice Bowl",
                     "Healthy", 179);

            add_food(r, 402, "Paneer Wrap",
                     "Healthy", 159);

            add_food(r, 403, "Fruit Bowl",
                     "Healthy", 139);
        }

        if (r->id == 3)
        {
            add_food(r, 301, "Classic Burger",
                     "Burger", 149);

            add_food(r, 302, "Chicken Burger",
                     "Burger", 189);

            add_food(r, 303, "French Fries",
                     "Sides", 99);
        }

        if (r->id == 2)
        {
            add_food(r, 201, "Farmhouse Pizza",
                     "Pizza", 249);

            add_food(r, 202, "Cheese Pizza",
                     "Pizza", 299);

            add_food(r, 203, "Garlic Bread",
                     "Sides", 109);
        }

        if (r->id == 1)
        {
            add_food(r, 101, "Paneer Biryani",
                     "Indian", 189);

            add_food(r, 102, "Chicken Biryani",
                     "Indian", 239);

            add_food(r, 103, "Garlic Naan",
                     "Indian", 79);
        }

        r = r->next;
    }
}


/* ---------- Customer Registration ---------- */

void register_customer()
{
    Customer *c;

    c = (Customer *)malloc(sizeof(Customer));

    if (c == NULL)
    {
        printf("Unable to allocate memory.\n");
        return;
    }

    c->id = ++customer_count;

    printf("\nEnter customer name: ");
    scanf(" %[^\n]", c->name);

    printf("Enter phone number: ");
    scanf(" %[^\n]", c->phone);

    printf("Enter delivery address: ");
    scanf(" %[^\n]", c->address);

    c->next = customer_head;
    customer_head = c;

    printf("\nCustomer registered successfully.\n");
    printf("Customer ID: %d\n", c->id);
}


/* ---------- Display Customers ---------- */

void display_customers()
{
    Customer *c;

    header("CUSTOMER LIST");

    c = customer_head;

    if (c == NULL)
    {
        printf("No customers registered.\n");
        return;
    }

    printf("%-8s %-20s %-15s %-25s\n",
           "ID", "Name", "Phone", "Address");

    line();

    while (c != NULL)
    {
        printf("%-8d %-20s %-15s %-25s\n",
               c->id,
               c->name,
               c->phone,
               c->address);

        c = c->next;
    }
}


/* ---------- Restaurant Display ---------- */

void display_restaurants()
{
    Restaurant *r;

    header("AVAILABLE RESTAURANTS");

    r = restaurant_head;

    printf("%-5s %-22s %-18s %-8s %-10s\n",
           "ID", "Restaurant", "Location",
           "Rating", "Time");

    line();

    while (r != NULL)
    {
        printf("%-5d %-22s %-18s %-8.1f %-10d\n",
               r->id,
               r->name,
               r->location,
               r->rating,
               r->delivery_time);

        r = r->next;
    }
}


/* ---------- Search Restaurant ---------- */

Restaurant *find_restaurant(int id)
{
    Restaurant *r;

    r = restaurant_head;

    while (r != NULL)
    {
        if (r->id == id)
            return r;

        r = r->next;
    }

    return NULL;
}


/* ---------- Display Food Menu ---------- */

void display_menu(Restaurant *r)
{
    int i;

    header(r->name);

    printf("Location       : %s\n", r->location);
    printf("Rating         : %.1f\n", r->rating);
    printf("Delivery Time  : %d minutes\n", r->delivery_time);

    printf("\n");

    printf("%-6s %-25s %-18s %-10s\n",
           "ID", "Food", "Category", "Price");

    line();

    for (i = 0; i < r->food_count; i++)
    {
        printf("%-6d %-25s %-18s ₹%-9.2f\n",
               r->menu[i].id,
               r->menu[i].name,
               r->menu[i].category,
               r->menu[i].price);
    }
}


/* ---------- Find Food ---------- */

Food *find_food(Restaurant *r, int food_id)
{
    int i;

    for (i = 0; i < r->food_count; i++)
    {
        if (r->menu[i].id == food_id)
            return &r->menu[i];
    }

    return NULL;
}


/* ---------- Place Order ---------- */

void place_order()
{
    int customer_id;
    int restaurant_id;
    int food_id;
    int quantity;
    int priority;

    float total;

    Customer *customer;
    Restaurant *restaurant;
    Food *food;

    Order *new_order;

    header("PLACE FOOD ORDER");

    if (customer_head == NULL)
    {
        printf("Please register a customer first.\n");
        return;
    }

    display_customers();

    printf("\nEnter customer ID: ");
    scanf("%d", &customer_id);

    customer = customer_head;

    while (customer != NULL &&
           customer->id != customer_id)
    {
        customer = customer->next;
    }

    if (customer == NULL)
    {
        printf("Customer not found.\n");
        return;
    }

    display_restaurants();

    printf("\nEnter restaurant ID: ");
    scanf("%d", &restaurant_id);

    restaurant = find_restaurant(restaurant_id);

    if (restaurant == NULL)
    {
        printf("Restaurant not found.\n");
        return;
    }

    display_menu(restaurant);

    printf("\nEnter food ID: ");
    scanf("%d", &food_id);

    food = find_food(restaurant, food_id);

    if (food == NULL)
    {
        printf("Food item not found.\n");
        return;
    }

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    if (quantity <= 0)
    {
        printf("Invalid quantity.\n");
        return;
    }

    total = food->price * quantity;

    printf("\nDelivery Priority\n");
    printf("1. Normal\n");
    printf("2. Express\n");
    printf("Enter choice: ");
    scanf("%d", &priority);

    if (priority != 2)
        priority = 1;

    new_order = (Order *)malloc(sizeof(Order));

    if (new_order == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    new_order->order_id = ++order_count;
    new_order->customer_id = customer->id;

    strcpy(new_order->customer_name,
           customer->name);

    strcpy(new_order->restaurant,
           restaurant->name);

    new_order->amount = total;
    new_order->priority = priority;

    if (priority == 2)
        strcpy(new_order->status, "Express");
    else
        strcpy(new_order->status, "Normal");

    new_order->next = NULL;


    if (pending_orders.rear == NULL)
    {
        pending_orders.front = new_order;
        pending_orders.rear = new_order;
    }
    else
    {
        pending_orders.rear->next = new_order;
        pending_orders.rear = new_order;
    }

    printf("\n");
    line();
    printf("                 ORDER CONFIRMED\n");
    line();

    printf("Order ID       : %d\n",
           new_order->order_id);

    printf("Customer       : %s\n",
           new_order->customer_name);

    printf("Restaurant     : %s\n",
           new_order->restaurant);

    printf("Food           : %s\n",
           food->name);

    printf("Quantity       : %d\n",
           quantity);

    printf("Amount         : ₹%.2f\n",
           total);

    printf("Priority       : %s\n",
           priority == 2 ? "EXPRESS" : "NORMAL");

    printf("Status         : Confirmed\n");

    line();
}


/* ---------- Display Pending Orders ---------- */

void display_orders()
{
    Order *p;

    header("ORDER QUEUE");

    if (pending_orders.front == NULL)
    {
        printf("No pending orders.\n");
        return;
    }

    printf("%-8s %-18s %-20s %-12s %-10s\n",
           "OrderID",
           "Customer",
           "Restaurant",
           "Amount",
           "Priority");

    line();

    p = pending_orders.front;

    while (p != NULL)
    {
        printf("%-8d %-18s %-20s ₹%-10.2f %-10s\n",
               p->order_id,
               p->customer_name,
               p->restaurant,
               p->amount,
               p->priority == 2 ?
               "EXPRESS" : "NORMAL");

        p = p->next;
    }
}


/* ---------- Process Next Order ---------- */

void process_order()
{
    Order *p;

    header("PROCESS DELIVERY");

    if (pending_orders.front == NULL)
    {
        printf("No orders waiting for delivery.\n");
        return;
    }

    p = pending_orders.front;

    printf("Order ID     : %d\n", p->order_id);
    printf("Customer     : %s\n", p->customer_name);
    printf("Restaurant   : %s\n", p->restaurant);
    printf("Amount       : ₹%.2f\n", p->amount);

    if (p->priority == 2)
        printf("Priority     : EXPRESS\n");
    else
        printf("Priority     : NORMAL\n");

    printf("\nDelivery Status\n");
    printf("-----------------------------\n");
    printf("1. Order Received\n");
    printf("2. Food Preparing\n");
    printf("3. Out for Delivery\n");
    printf("4. Delivered\n");

    printf("\nOrder #%d delivered successfully.\n",
           p->order_id);

    pending_orders.front = p->next;

    if (pending_orders.front == NULL)
        pending_orders.rear = NULL;

    free(p);
}


/* ---------- Cancel Order ---------- */

void cancel_order()
{
    int id;
    Order *current;
    Order *previous;

    header("CANCEL ORDER");

    if (pending_orders.front == NULL)
    {
        printf("There are no pending orders.\n");
        return;
    }

    printf("Enter Order ID: ");
    scanf("%d", &id);

    current = pending_orders.front;
    previous = NULL;

    while (current != NULL &&
           current->order_id != id)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("Order not found.\n");
        return;
    }

    if (previous == NULL)
    {
        pending_orders.front = current->next;
    }
    else
    {
        previous->next = current->next;
    }

    if (current == pending_orders.rear)
        pending_orders.rear = previous;

    printf("\nOrder #%d cancelled successfully.\n",
           current->order_id);

    printf("Refund Amount: ₹%.2f\n",
           current->amount);

    free(current);
}


/* ---------- Search Food ---------- */

void search_food()
{
    char search[50];
    Restaurant *r;
    int i;
    int found = 0;

    header("FOOD SEARCH");

    printf("Enter food name: ");
    scanf(" %[^\n]", search);

    r = restaurant_head;

    while (r != NULL)
    {
        for (i = 0; i < r->food_count; i++)
        {
            if (strstr(r->menu[i].name,
                       search) != NULL)
            {
                printf("\nFood       : %s",
                       r->menu[i].name);

                printf("\nRestaurant : %s",
                       r->name);

                printf("\nCategory   : %s",
                       r->menu[i].category);

                printf("\nPrice      : ₹%.2f\n",
                       r->menu[i].price);

                found = 1;
            }
        }

        r = r->next;
    }

    if (!found)
        printf("\nNo matching food found.\n");
}


/* ---------- Sort Restaurants ---------- */

void sort_restaurants()
{
    Restaurant *a;
    Restaurant *b;

    int id;
    char name[60];
    char location[50];
    float rating;
    int delivery_time;

    a = restaurant_head;

    while (a != NULL)
    {
        b = a->next;

        while (b != NULL)
        {
            if (a->rating < b->rating)
            {
                id = a->id;
                a->id = b->id;
                b->id = id;

                strcpy(name, a->name);
                strcpy(a->name, b->name);
                strcpy(b->name, name);

                strcpy(location, a->location);
                strcpy(a->location, b->location);
                strcpy(b->location, location);

                rating = a->rating;
                a->rating = b->rating;
                b->rating = rating;

                delivery_time = a->delivery_time;
                a->delivery_time = b->delivery_time;
                b->delivery_time = delivery_time;
            }

            b = b->next;
        }

        a = a->next;
    }

    printf("\nRestaurants sorted by rating.\n");

    display_restaurants();
}


/* ---------- Customer Details ---------- */

void customer_details()
{
    int id;
    Customer *c;

    header("CUSTOMER DETAILS");

    printf("Enter customer ID: ");
    scanf("%d", &id);

    c = customer_head;

    while (c != NULL)
    {
        if (c->id == id)
        {
            printf("Customer ID : %d\n", c->id);
            printf("Name        : %s\n", c->name);
            printf("Phone       : %s\n", c->phone);
            printf("Address     : %s\n", c->address);

            return;
        }

        c = c->next;
    }

    printf("Customer not found.\n");
}


/* ---------- Main Menu ---------- */

void main_menu()
{
    int choice;

    while (1)
    {
        header("FOOD DELIVERY MANAGEMENT SYSTEM");

        printf("1. Register Customer\n");
        printf("2. Display Customers\n");
        printf("3. Display Restaurants\n");
        printf("4. Search Food\n");
        printf("5. Place Food Order\n");
        printf("6. View Order Queue\n");
        printf("7. Process Delivery\n");
        printf("8. Cancel Order\n");
        printf("9. Sort Restaurants by Rating\n");
        printf("10. Customer Details\n");
        printf("0. Exit\n");

        line();

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                register_customer();
                break;

            case 2:
                display_customers();
                break;

            case 3:
                display_restaurants();
                break;

            case 4:
                search_food();
                break;

            case 5:
                place_order();
                break;

            case 6:
                display_orders();
                break;

            case 7:
                process_order();
                break;

            case 8:
                cancel_order();
                break;

            case 9:
                sort_restaurants();
                break;

            case 10:
                customer_details();
                break;

            case 0:
                printf("\nThank you for using Food Delivery System.\n");
                return;

            default:
                printf("\nInvalid choice. Try again.\n");
        }

        printf("\n");
        printf("Press ENTER to continue...");

        getchar();
        getchar();
    }
}


/* ---------- Memory Cleanup ---------- */

void free_memory()
{
    Restaurant *r;
    Restaurant *r_next;

    Customer *c;
    Customer *c_next;

    Order *o;
    Order *o_next;

    r = restaurant_head;

    while (r != NULL)
    {
        r_next = r->next;
        free(r);
        r = r_next;
    }

    c = customer_head;

    while (c != NULL)
    {
        c_next = c->next;
        free(c);
        c = c_next;
    }

    o = pending_orders.front;

    while (o != NULL)
    {
        o_next = o->next;
        free(o);
        o = o_next;
    }
}


/* ---------- Main ---------- */

int main()
{
    load_restaurants();

    printf("\n");
    line();
    printf("             FOOD DELIVERY SYSTEM\n");
    printf("          C DATA STRUCTURES PROJECT\n");
    line();

    main_menu();

    free_memory();

    return 0;
}
