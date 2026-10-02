SMART FOOD DELIVERY ROUTE OPTIMIZATION

C-based DSA project satisfying the required modules:

1. Restaurant management
2. Customer management
3. Order management
4. Delivery locations represented as a weighted graph
5. Dijkstra shortest-path route optimization
6. Delivery queue management
7. Priority queue for Express and Standard deliveries
8. Estimated delivery time calculation
9. Order tracking and delivery processing
10. Modular four-member C project structure

FOUR MEMBERS
Member 1: member1_restaurant.c
Member 2: member2_customer.c
Member 3: member3_order.c
Member 4: member4_delivery_and_main.c
Shared declarations: food_delivery.h

DSA USED
- Graph using adjacency matrix
- Dijkstra shortest-path algorithm
- Linked-list priority queue
- Order queue processing

ETA
The base ETA uses restaurant preparation time, shortest-route distance and delivery type. Express delivery receives a small time adjustment. AI ETA prediction is an optional extension, not required for the core system.

COMPILE
    gcc -Wall -Wextra *.c -o smart_food_delivery

RUN
    ./smart_food_delivery
