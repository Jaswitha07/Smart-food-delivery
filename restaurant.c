#include <stdio.h>
#include <string.h>

#define MAX 100

struct Restaurant
{
    int id;
    char name[50];
    int location;
    char cuisine[30];
    float rating;
    char phone[15];
};

struct Restaurant restaurants[MAX];

int restaurantCount = 0;

void addRestaurant()
{
    int id;
    int i;

    if (restaurantCount >= MAX)
    {
        printf("Restaurant list is full\n");
        return;
    }

    printf("Enter restaurant ID: ");
    scanf("%d", &id);

    if (id <= 0)
    {
        printf("Invalid ID\n");
        return;
    }

    for (i = 0; i < restaurantCount; i++)
    {
        if (restaurants[i].id == id)
        {
            printf("Restaurant ID already exists\n");
            return;
        }
    }

    restaurants[restaurantCount].id = id;

    printf("Enter restaurant name: ");
    scanf(" %[^\n]", restaurants[restaurantCount].name);

    printf("Enter location ID: ");
    scanf("%d", &restaurants[restaurantCount].location);

    if (restaurants[restaurantCount].location <= 0)
    {
        printf("Invalid location\n");
        return;
    }

    printf("Enter cuisine: ");
    scanf(" %[^\n]", restaurants[restaurantCount].cuisine);

    printf("Enter rating: ");
    scanf("%f", &restaurants[restaurantCount].rating);

    if (restaurants[restaurantCount].rating < 0 ||
        restaurants[restaurantCount].rating > 5)
    {
        printf("Rating should be between 0 and 5\n");
        return;
    }

    printf("Enter phone: ");
    scanf("%s", restaurants[restaurantCount].phone);

    restaurantCount++;

    printf("Restaurant added successfully\n");
}

void viewRestaurants()
{
    int i;

    if (restaurantCount == 0)
    {
        printf("No restaurants available\n");
        return;
    }

    for (i = 0; i < restaurantCount; i++)
    {
        printf("\nRestaurant ID: %d\n", restaurants[i].id);
        printf("Name: %s\n", restaurants[i].name);
        printf("Location: %d\n", restaurants[i].location);
        printf("Cuisine: %s\n", restaurants[i].cuisine);
        printf("Rating: %.1f\n", restaurants[i].rating);
        printf("Phone: %s\n", restaurants[i].phone);
    }
}

void searchRestaurant()
{
    int choice;
    int id;
    int location;
    char name[50];
    char cuisine[30];
    int i;
    int found = 0;

    printf("\nSearch Restaurant\n");
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("3. Search by Cuisine\n");
    printf("4. Search by Location\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Enter restaurant ID: ");
        scanf("%d", &id);

        for (i = 0; i < restaurantCount; i++)
        {
            if (restaurants[i].id == id)
            {
                printf("\nRestaurant found\n");
                printf("ID: %d\n", restaurants[i].id);
                printf("Name: %s\n", restaurants[i].name);
                printf("Location: %d\n", restaurants[i].location);
                printf("Cuisine: %s\n", restaurants[i].cuisine);
                printf("Rating: %.1f\n", restaurants[i].rating);
                printf("Phone: %s\n", restaurants[i].phone);
                found = 1;
            }
        }
    }
    else if (choice == 2)
    {
        printf("Enter restaurant name: ");
        scanf(" %[^\n]", name);

        for (i = 0; i < restaurantCount; i++)
        {
            if (strcmp(restaurants[i].name, name) == 0)
            {
                printf("\nRestaurant found\n");
                printf("ID: %d\n", restaurants[i].id);
                printf("Name: %s\n", restaurants[i].name);
                printf("Location: %d\n", restaurants[i].location);
                printf("Cuisine: %s\n", restaurants[i].cuisine);
                printf("Rating: %.1f\n", restaurants[i].rating);
                printf("Phone: %s\n", restaurants[i].phone);
                found = 1;
            }
        }
    }
    else if (choice == 3)
    {
        printf("Enter cuisine: ");
        scanf(" %[^\n]", cuisine);

        for (i = 0; i < restaurantCount; i++)
        {
            if (strcmp(restaurants[i].cuisine, cuisine) == 0)
            {
                printf("\nRestaurant found\n");
                printf("ID: %d\n", restaurants[i].id);
                printf("Name: %s\n", restaurants[i].name);
                printf("Location: %d\n", restaurants[i].location);
                printf("Cuisine: %s\n", restaurants[i].cuisine);
                printf("Rating: %.1f\n", restaurants[i].rating);
                printf("Phone: %s\n", restaurants[i].phone);
                found = 1;
            }
        }
    }
    else if (choice == 4)
    {
        printf("Enter location ID: ");
        scanf("%d", &location);

        for (i = 0; i < restaurantCount; i++)
        {
            if (restaurants[i].location == location)
            {
                printf("\nRestaurant found\n");
                printf("ID: %d\n", restaurants[i].id);
                printf("Name: %s\n", restaurants[i].name);
                printf("Location: %d\n", restaurants[i].location);
                printf("Cuisine: %s\n", restaurants[i].cuisine);
                printf("Rating: %.1f\n", restaurants[i].rating);
                printf("Phone: %s\n", restaurants[i].phone);
                found = 1;
            }
        }
    }
    else
    {
        printf("Wrong choice\n");
        return;
    }

    if (found == 0)
    {
        printf("Restaurant not found\n");
    }
}

void updateRestaurant()
{
    int id;
    int i;

    printf("Enter restaurant ID: ");
    scanf("%d", &id);

    for (i = 0; i < restaurantCount; i++)
    {
        if (restaurants[i].id == id)
        {
            printf("Enter new name: ");
            scanf(" %[^\n]", restaurants[i].name);

            printf("Enter new location ID: ");
            scanf("%d", &restaurants[i].location);

            printf("Enter new cuisine: ");
            scanf(" %[^\n]", restaurants[i].cuisine);

            printf("Enter new rating: ");
            scanf("%f", &restaurants[i].rating);

            if (restaurants[i].rating < 0 ||
                restaurants[i].rating > 5)
            {
                printf("Invalid rating\n");
                return;
            }

            printf("Enter new phone: ");
            scanf("%s", restaurants[i].phone);

            printf("Restaurant updated\n");
            return;
        }
    }

    printf("Restaurant not found\n");
}

void deleteRestaurant()
{
    int id;
    int i;
    int j;

    printf("Enter restaurant ID: ");
    scanf("%d", &id);

    for (i = 0; i < restaurantCount; i++)
    {
        if (restaurants[i].id == id)
        {
            for (j = i; j < restaurantCount - 1; j++)
            {
                restaurants[j] = restaurants[j + 1];
            }

            restaurantCount--;

            printf("Restaurant deleted\n");
            return;
        }
    }

    printf("Restaurant not found\n");
}
