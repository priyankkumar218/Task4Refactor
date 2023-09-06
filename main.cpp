#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

class Item {
private:
    std::string name;
    int quantity;
    float price;

public:
    Item(const std::string& name, int quantity, float price)
        : name(name), quantity(quantity), price(price) {}

    const std::string& get_name() const {
        return name;
    }

    int get_quantity() const {
        return quantity;
    }

    void set_quantity(int new_quantity) {
        quantity = new_quantity;
    }

    float get_price() const {
        return price;
    }

    bool is_match(const std::string& other) const {
        return name == other;
    }

    void display_data() const {
        std::cout << "\nItem name: " << name
                  << "\nQuantity: " << quantity
                  << "\nPrice: " << price << "\n";
    }
};

class Inventory {
private:
    std::vector<Item> items;
    float total_money;

public:
    Inventory() : total_money(0) {}

    void add_item() {
        std::string name;
        int quantity;
        float price;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nEnter item name: ";
        std::getline(std::cin, name);
        std::cout << "Enter quantity: ";
        std::cin >> quantity;
        std::cout << "Enter price: ";
        std::cin >> price;

        items.emplace_back(name, quantity, price);
    }

    void sell_item() {
        std::string item_to_check;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nEnter item name: ";
        std::getline(std::cin, item_to_check);

        auto item = std::find_if(items.begin(), items.end(),
            [&item_to_check](const Item& i) { return i.is_match(item_to_check); });

        if (item != items.end()) {
            remove_item(item);
        } else {
            std::cout << "\nThis item is not in your Inventory";
        }
    }

    void remove_item(const std::vector<Item>::iterator& item) {
        int input_quantity;
        std::cout << "\nEnter number of items to sell: ";
        std::cin >> input_quantity;

        int quantity = item->get_quantity();
        if (input_quantity <= quantity) {
            float price = item->get_price();
            float money_earned = price * input_quantity;
            item->set_quantity(quantity - input_quantity);
            std::cout << "\nItems sold";
            std::cout << "\nMoney received: " << money_earned;
            total_money += money_earned;

            if (item->get_quantity() == 0) {
                items.erase(item);
            }
        } else {
            std::cout << "\nCannot sell more items than you have.";
        }
    }

    void list_items() const {
        if (items.empty()) {
            std::cout << "\nInventory empty.";
        } else {
            for (const Item& item : items) {
                item.display_data();
            }
        }
    }
};

int main() {
    int choice;
    Inventory inventory_system;
    std::cout << "Welcome to the inventory!";

    while (true) {
        std::cout << "\n\nMENU\n"
                  << "1. Add new item\n"
                  << "2. Sell item\n"
                  << "3. List items\n"
                  << "4. Exit\n\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                inventory_system.add_item();
                break;

            case 2:
                inventory_system.sell_item();
                break;

            case 3:
                inventory_system.list_items();
                break;

            case 4:
                return 0;

            default:
                std::cout << "\nInvalid choice entered";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
        }
    }
}
