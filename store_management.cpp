#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Structure to store product information
struct Product {
    int id;
    string name;
    int quantity;
    double price;
};

// Class for managing the department store system
class StoreManagementSystem {
private:
    vector<Product> inventory;

    // Find a product by ID
    int findProductById(int id) {
        for (size_t i = 0; i < inventory.size(); ++i) {
            if (inventory[i].id == id) {
                return i;
            }
        }
        return -1;
    }

public:
    // Add a product to the inventory
    void addProduct(int id, const string& name, int quantity, double price) {
        if (findProductById(id) != -1) {
            cout << "Product ID " << id << " already exists.\n";
            return;
        }
        inventory.push_back({id, name, quantity, price});
        cout << "Product added successfully.\n";
    }

    // Display all products
    void displayProducts() {
        cout << "\n--- Inventory ---\n";
        cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price\n";
        for (const auto& product : inventory) {
            cout << setw(10) << product.id
                 << setw(20) << product.name
                 << setw(10) << product.quantity
                 << setw(10) << product.price << "\n";
        }
        cout << "------------------\n";
    }

    // Sell a product
    void sellProduct(int id, int quantity) {
        int index = findProductById(id);
        if (index == -1) {
            cout << "Product ID " << id << " not found.\n";
            return;
        }
        if (inventory[index].quantity < quantity) {
            cout << "Insufficient stock for product " << inventory[index].name << ".\n";
            return;
        }
        inventory[index].quantity -= quantity;
        double totalPrice = quantity * inventory[index].price;
        cout << "Sold " << quantity << " units of " << inventory[index].name
             << " for $" << fixed << setprecision(2) << totalPrice << ".\n";
    }

    // Restock a product
    void restockProduct(int id, int quantity) {
        int index = findProductById(id);
        if (index == -1) {
            cout << "Product ID " << id << " not found.\n";
            return;
        }
        inventory[index].quantity += quantity;
        cout << "Restocked " << inventory[index].name << " with " << quantity << " units.\n";
    }
};

// Main function
int main() {
    StoreManagementSystem store;

    // Menu-driven system
    int choice;
    do {
        cout << "\n--- Department Store Management ---\n";
        cout << "1. Add Product\n";
        cout << "2. Display Inventory\n";
        cout << "3. Sell Product\n";
        cout << "4. Restock Product\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, quantity;
                string name;
                double price;
                cout << "Enter Product ID: ";
                cin >> id;
                cout << "Enter Product Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Quantity: ";
                cin >> quantity;
                cout << "Enter Price: ";
                cin >> price;
                store.addProduct(id, name, quantity, price);
                break;
            }
            case 2:
                store.displayProducts();
                break;
            case 3: {
                int id, quantity;
                cout << "Enter Product ID: ";
                cin >> id;
                cout << "Enter Quantity to Sell: ";
                cin >> quantity;
                store.sellProduct(id, quantity);
                break;
            }
            case 4: {
                int id, quantity;
                cout << "Enter Product ID: ";
                cin >> id;
                cout << "Enter Quantity to Restock: ";
                cin >> quantity;
                store.restockProduct(id, quantity);
                break;
            }
            case 5:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
