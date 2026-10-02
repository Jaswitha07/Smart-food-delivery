#include <stdio.h>
#include <string.h>
#include "food_delivery.h"

Restaurant restaurants[MAX_RESTAURANTS];

void initializeRestaurants(void) {
    const char *names[20]={"Spice Garden","Urban Bites","Tandoori Hub","Green Leaf","Pizza Point","Burger House","Dosa Corner","Royal Biryani","Cafe Aroma","Food Junction","Chennai Express","Andhra Ruchulu","Healthy Bowl","Chinese Wok","Grill Nation","South Indian Cafe","The Pasta Room","Street Treats","Fresh Feast","Family Kitchen"};
    const char *addresses[20]={"Main Road","City Center","Market Road","Lake View Road","Station Road","College Road","Temple Street","Central Avenue","Park Road","Bus Stand Road","MG Road","Beach Road","Green Park Road","Clock Tower Road","Ring Road","Library Road","Tech Park Road","Gandhi Street","Garden Road","Hospital Road"};
    const char *items[20][5]={
        {"Veg Biryani","Paneer Curry","Naan","Fried Rice","Lassi"},
        {"Veg Burger","French Fries","Sandwich","Cold Coffee","Brownie"},
        {"Chicken Tikka","Paneer Tikka","Butter Naan","Dal Tadka","Lassi"},
        {"Veg Salad","Paneer Wrap","Fruit Bowl","Veg Soup","Fresh Juice"},
        {"Margherita Pizza","Farmhouse Pizza","Garlic Bread","Pasta","Soft Drink"},
        {"Classic Burger","Cheese Burger","Veg Burger","Fries","Milkshake"},
        {"Masala Dosa","Plain Dosa","Idli","Vada","Filter Coffee"},
        {"Chicken Biryani","Mutton Biryani","Veg Biryani","Chicken 65","Raita"},
        {"Cappuccino","Cold Coffee","Veg Sandwich","Muffin","Cheesecake"},
        {"Veg Meals","Chicken Rice","Noodles","Manchurian","Juice"},
        {"Idli","Pongal","Masala Dosa","Curd Rice","Coffee"},
        {"Gongura Rice","Andhra Meals","Chicken Fry","Pappu","Buttermilk"},
        {"Protein Bowl","Veg Bowl","Fruit Bowl","Oats","Smoothie"},
        {"Veg Noodles","Chicken Noodles","Veg Manchurian","Spring Rolls","Fried Rice"},
        {"Chicken Grill","Paneer Grill","Seekh Kebab","French Fries","Lemonade"},
        {"Mini Meals","Poori","Upma","Vada","Filter Coffee"},
        {"Penne Pasta","White Sauce Pasta","Red Sauce Pasta","Garlic Bread","Tiramisu"},
        {"Pani Puri","Pav Bhaji","Samosa","Bhel Puri","Masala Chai"},
        {"Veg Rice Bowl","Chicken Bowl","Paneer Bowl","Soup","Fresh Juice"},
        {"Family Meals","Veg Biryani","Chicken Curry","Roti","Ice Cream"}
    };
    float prices[20][5]={
        {140,160,45,130,60},{120,80,100,90,70},{220,190,55,140,60},{110,150,100,90,80},{180,220,100,150,60},
        {150,180,130,80,110},{80,70,60,65,50},{220,280,150,170,50},{90,100,120,70,140},{160,180,140,150,80},
        {60,80,90,70,50},{150,180,190,80,45},{180,160,130,100,120},{130,170,150,140,110},{240,200,220,90,70},
        {100,80,70,60,50},{180,200,190,100,160},{50,100,35,60,30},{170,190,180,100,90},{320,180,240,60,80}
    };
    int prep[20]={15,12,18,10,15,12,10,20,10,15,10,18,12,15,20,10,18,8,14,22};
    for(int i=0;i<20;i++){
        restaurants[i].id=i+1;
        strcpy(restaurants[i].name,names[i]);
        strcpy(restaurants[i].address,addresses[i]);
        restaurants[i].preparationTime=prep[i];
        for(int j=0;j<5;j++){ strcpy(restaurants[i].itemName[j],items[i][j]); restaurants[i].price[j]=prices[i][j]; }
    }
}
void showRestaurants(void){
    printf("\n=============== RESTAURANTS ===============\n");
    for(int i=0;i<MAX_RESTAURANTS;i++) printf("%2d. %-22s | %s\n",restaurants[i].id,restaurants[i].name,restaurants[i].address);
}
void showRestaurantMenu(void){
    int id; showRestaurants(); printf("\nEnter restaurant ID: "); scanf("%d",&id);
    if(id<1||id>20){printf("Invalid restaurant ID.\n");return;}
    Restaurant *r=&restaurants[id-1];
    printf("\n=============== %s MENU ===============\n",r->name);
    for(int i=0;i<5;i++) printf("%d. %-25s Rs. %.2f\n",i+1,r->itemName[i],r->price[i]);
    printf("Preparation time: %d minutes\n",r->preparationTime);
}
