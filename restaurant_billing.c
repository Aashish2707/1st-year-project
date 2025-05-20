#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MENU_ITEMS 10
#define MAX_ITEM_NAME_LENGTH 50

typedef struct {
    char name[MAX_ITEM_NAME_LENGTH];
    float price;
} MenuItem;

typedef struct {
    char customerName[MAX_ITEM_NAME_LENGTH];
    int itemCount;
    MenuItem items[MAX_MENU_ITEMS];
    float total;
} Bill;

void initializeBill(Bill *bill) {
    printf("Enter customer name: ");
    fgets(bill->customerName, sizeof(bill->customerName), stdin);
    bill->customerName[strcspn(bill->customerName, "\n")] = '\0';  // Remove trailing newline

    bill->itemCount = 0;
    bill->total = 0.0;
}

void addItem(Bill *bill, const char *name, float price) {
    if (bill->itemCount >= MAX_MENU_ITEMS) {
        printf("Maximum item count reached.\n");
        return;
    }

    MenuItem item;
    strncpy(item.name, name, sizeof(item.name) - 1);
    item.name[sizeof(item.name) - 1] = '\0';  // Ensure null-terminated string
    item.price = price;

    bill->items[bill->itemCount++] = item;
    bill->total += price;
}

void printBill(const Bill *bill) {
    int i;
    printf("\nCustomer: %s\n", bill->customerName);
    printf("----------------------------\n");

    for (i = 0; i < bill->itemCount; i++) {
        printf("%-30s $%.2f\n", bill->items[i].name, bill->items[i].price);
    }

    printf("----------------------------\n");
    printf("Total:                       $%.2f\n", bill->total);
}

int main() {
    Bill bill;
    initializeBill(&bill);

    printf("\nMENU:\n");
    printf("1. Burger            $4.99\n");
    printf("2. Pizza             $8.99\n");
    printf("3. Salad             $6.49\n");
    printf("4. Pasta             $9.99\n");
    printf("5. Ice Cream         $3.49\n");

    int choice;
    do {
        printf("\nEnter item number (0 to exit): ");
        scanf("%d", &choice);
        getchar();  // Consume the newline character

        switch (choice) {
            case 1:
                addItem(&bill, "Burger", 4.99);
                break;
            case 2:
                addItem(&bill, "Pizza", 8.99);
                break;
            case 3:
                addItem(&bill, "Salad", 6.49);
                break;
            case 4:
                addItem(&bill, "Pasta", 9.99);
                break;
            case 5:
                addItem(&bill, "Ice Cream", 3.49);
                break;
            case 0:
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);

    printBill(&bill);

    return 0;
}

