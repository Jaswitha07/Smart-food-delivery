#include <stdio.h>
#include <string.h>

#define MAX 100

struct Customer
{
    int id;
    char name[50];
    char phone[15];
    char address[100];
    int location;
};

struct Customer customers[MAX];

int customerCount = 0;

void addCustomer()
{
    int id;
    int i;

    if (customerCount >= MAX)
    {
        printf("Customer list is full\n");
        return;
    }

    printf("Enter customer ID: ");
    scanf("%d", &id);

    if (id <= 0)
    {
        printf("Invalid ID\n");
        return;
    }

    for (i = 0; i < customerCount; i++)
    {
        if (customers[i].id == id)
        {
            printf("Customer ID already exists\n");
            return;
        }
    }

    customers[customerCount].id = id;

    printf("Enter customer name: ");
    scanf(" %[^\n]", customers[customerCount].name);

    printf("Enter phone: ");
    scanf("%s", customers[customerCount].phone);

    printf("Enter address: ");
    scanf(" %[^\n]", customers[customerCount].address);

    printf("Enter location ID: ");
    scanf("%d", &customers[customerCount].location);

    if (customers[customerCount].location <= 0)
    {
        printf("Invalid location\n");
        return;
    }

    customerCount++;

    printf("Customer added successfully\n");
}

void viewCustomers()
{
    int i;

    if (customerCount == 0)
    {
        printf("No customers available\n");
        return;
    }

    for (i = 0; i < customerCount; i++)
    {
        printf("\nCustomer ID: %d\n", customers[i].id);
        printf("Name: %s\n", customers[i].name);
        printf("Phone: %s\n", customers[i].phone);
        printf("Address: %s\n", customers[i].address);
        printf("Location: %d\n", customers[i].location);
    }
}

void searchCustomer()
{
    int choice;
    int id;
    int location;
    char name[50];
    char phone[15];
    int i;
    int found = 0;

    printf("\nSearch Customer\n");
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("3. Search by Phone\n");
    printf("4. Search by Location\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Enter customer ID: ");
        scanf("%d", &id);

        for (i = 0; i < customerCount; i++)
        {
            if (customers[i].id == id)
            {
                printf("\nCustomer found\n");
                printf("ID: %d\n", customers[i].id);
                printf("Name: %s\n", customers[i].name);
                printf("Phone: %s\n", customers[i].phone);
                printf("Address: %s\n", customers[i].address);
                printf("Location: %d\n", customers[i].location);
                found = 1;
            }
        }
    }
    else if (choice == 2)
    {
        printf("Enter customer name: ");
        scanf(" %[^\n]", name);

        for (i = 0; i < customerCount; i++)
        {
            if (strcmp(customers[i].name, name) == 0)
            {
                printf("\nCustomer found\n");
                printf("ID: %d\n", customers[i].id);
                printf("Name: %s\n", customers[i].name);
                printf("Phone: %s\n", customers[i].phone);
                printf("Address: %s\n", customers[i].address);
                printf("Location: %d\n", customers[i].location);
                found = 1;
            }
        }
    }
    else if (choice == 3)
    {
        printf("Enter customer phone: ");
        scanf("%s", phone);

        for (i = 0; i < customerCount; i++)
        {
            if (strcmp(customers[i].phone, phone) == 0)
            {
                printf("\nCustomer found\n");
                printf("ID: %d\n", customers[i].id);
                printf("Name: %s\n", customers[i].name);
                printf("Phone: %s\n", customers[i].phone);
                printf("Address: %s\n", customers[i].address);
                printf("Location: %d\n", customers[i].location);
                found = 1;
            }
        }
    }
    else if (choice == 4)
    {
        printf("Enter location ID: ");
        scanf("%d", &location);

        for (i = 0; i < customerCount; i++)
        {
            if (customers[i].location == location)
            {
                printf("\nCustomer found\n");
                printf("ID: %d\n", customers[i].id);
                printf("Name: %s\n", customers[i].name);
                printf("Phone: %s\n", customers[i].phone);
                printf("Address: %s\n", customers[i].address);
                printf("Location: %d\n", customers[i].location);
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
        printf("Customer not found\n");
    }
}

void updateCustomer()
{
    int id;
    int i;

    printf("Enter customer ID: ");
    scanf("%d", &id);

    for (i = 0; i < customerCount; i++)
    {
        if (customers[i].id == id)
        {
            printf("Enter new name: ");
            scanf(" %[^\n]", customers[i].name);

            printf("Enter new phone: ");
            scanf("%s", customers[i].phone);

            printf("Enter new address: ");
            scanf(" %[^\n]", customers[i].address);

            printf("Enter new location ID: ");
            scanf("%d", &customers[i].location);

            if (customers[i].location <= 0)
            {
                printf("Invalid location\n");
                return;
            }

            printf("Customer updated\n");
            return;
        }
    }

    printf("Customer not found\n");
}

void deleteCustomer()
{
    int id;
    int i;
    int j;

    printf("Enter customer ID: ");
    scanf("%d", &id);

    for (i = 0; i < customerCount; i++)
    {
        if (customers[i].id == id)
        {
            for (j = i; j < customerCount - 1; j++)
            {
                customers[j] = customers[j + 1];
            }

            customerCount--;

            printf("Customer deleted\n");
            return;
        }
    }

    printf("Customer not found\n");
}
