#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int MenuSize = 8;

string itemNames[MenuSize] = {
    "Burger",
    "Pizza",
    "Sandwich",
    "Fries",
    "Tea",
    "Coffee",
    "Cold Drink",
    "Water Bottle"
};

float itemPrices[MenuSize] = {
    150.0,
    200.0,
    100.0,
    80.0,
    30.0,
    50.0,
    60.0,
    20.0
};

int   dailyQty[MenuSize] = { 0 };
float dailyTotal = 0.0;
int   totalCustomers = 0;

void displayMenu() {
    cout << "\n";
    cout << "      UNIVERSITY CAFETERIA MENU      \n";
    cout << " No.  Item             Price (PKR)   \n";

    for (int i = 0; i < MenuSize; i++) {
        cout << "  " << setw(2) << (i + 1) << ".  "
            << left << setw(16) << itemNames[i]
            << right << setw(6) << fixed << setprecision(0)
            << itemPrices[i] << " PKR      \n";
    }

    cout << setw(2) << 0 << ".  " << left << setw(22) << "Done ordering"
        << "              \n";
}

bool validateChoice(int choice) {
    return (choice >= 0 && choice <= MenuSize);
}

int takeOrder(int orderedQty[]) {

    for (int i = 0; i < MenuSize; i++) 
    orderedQty[i] = 0;
    int itemsOrdered = 0;

    cout << "\n  Enter item number to add (0 = finish order):\n";

    while (true) {
        displayMenu();
        cout << "  Your choice: ";

        int choice;
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "   Invalid input. Please enter a number.\n";
            continue;
        }

        if (!validateChoice(choice)) {
            cout << "   Invalid choice. Please select between 0 and "
                << MenuSize << ".\n";
            continue;
        }

        if (choice == 0) {
            if (itemsOrdered == 0) {
                cout << "   You haven't ordered anything yet!\n";
                continue;
            }
            break;
        }

        int idx = choice - 1;
        orderedQty[idx]++;
        itemsOrdered++;
        cout << "  <3. " << itemNames[idx] << " added to your order.\n";
    }

    return itemsOrdered;
}

float calculateBill(int orderedQty[]) {
    float total = 0.0;
    for (int i = 0; i < MenuSize; i++) {
        total += orderedQty[i] * itemPrices[i];
    }
    return total;
}

void printReceipt(int orderedQty[], int customerNum) {
    float bill = calculateBill(orderedQty);

    cout << "\n";
    cout << "         UNIVERSITY CAFETERIA         \n";
    cout << "              RECEIPT                 \n";
    cout << "  Customer #" << setw(3) << customerNum
        << "                          \n";
    cout << "  Item              Qty    Amount      \n";

    for (int i = 0; i < MenuSize; i++) {
        if (orderedQty[i] > 0) {
            float lineTotal = orderedQty[i] * itemPrices[i];
            cout << "  " << left << setw(16) << itemNames[i]
                << right << setw(3) << orderedQty[i]
                << "   " << setw(7) << fixed << setprecision(0)
                << lineTotal << " PKR  \n";
        }
    }

    cout << "  TOTAL:                  "
        << setw(7) << bill << " PKR  \n";
    cout << "  Thank you! Please come again.\n\n";
}

void updateDailySales(int orderedQty[]) {
    for (int i = 0; i < MenuSize; i++) {
        dailyQty[i] += orderedQty[i];
    }
    dailyTotal += calculateBill(orderedQty);
    totalCustomers++;
}

void dailySummary() {
    cout << "\n";
    cout << "       END-OF-DAY SALES REPORT        \n";
    cout << "  Item              Qty    Revenue     \n";

    for (int i = 0; i < MenuSize; i++) {
        if (dailyQty[i] > 0) {
            float revenue = dailyQty[i] * itemPrices[i];
            cout << "  " << left << setw(16) << itemNames[i]
                << right << setw(3) << dailyQty[i]
                << "   " << setw(7) << fixed << setprecision(0)
                << revenue << " PKR  \n";
        }
    }

    cout << "  Total Customers:        "
        << setw(11) << totalCustomers << "  \n";
    cout << "  Total Revenue:      "
        << setw(7) << dailyTotal << " PKR      \n";
}

int main() {

    cout << "\n---UNIVERSITY CAFETERIA ORDER MANAGEMENT SYSTEM---\n";
    cout << "  Computer Programming  |  SIR. Asad Ullah\n";
    cout << "  BS CS 1A\n";

    char continueServing;

    do {
        int orderedQty[MenuSize] = { 0 };

        cout << "  New Customer #" << (totalCustomers + 1) << "\n";

        takeOrder(orderedQty);

        printReceipt(orderedQty, totalCustomers + 1);

        updateDailySales(orderedQty);

        cout << "  Serve another customer? (y/n): ";
        cin >> continueServing;

    } while (continueServing == 'y' || continueServing == 'Y');

    dailySummary();

    cout << "  System closed. Goodbye!"<<endl;
}