#include <iostream>
#include <limits>
#include <string>
#include <cctype>
#include <vector>
#include <iomanip>

void SystemClear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void SystemPause()
{
#ifdef _WIN32
    system("pause");
#else
    std::cin.get();
#endif
}

void ConverttoUpper(std::string &str)
{
    for (char &c : str)
    {
        if (c >= 'a' && c <= 'z')
        {
            c -= ('a' - 'A');
        }
    }
}

bool isValidNumericString(const std::string &input)
{
    bool decimalFound = false;

    for (char c : input)
    {
        if (c == '.')
        {
            if (decimalFound) 
                return false; // multiple decimals found
            decimalFound = true;
        }
        else if (!std::isdigit(c))
        {
            return false; // invalid character found
        }
    }

    return !input.empty();
}

void getValidDoubleAmount(double &amount)
{
    std::string input;
    bool valid = false;

    while (!valid)
    {
        std::cout << "\nEnter amount: ";
        std::cin >> input;

        if (isValidNumericString(input))
        {
            amount = std::stod(input);
            if (amount < 0)
            {
                std::cout << "Invalid input! Amount cannot be negative." << std::endl;
            }
            else
            {
                valid = true;
            }
        }
        else
        {
            std::cout << "Invalid input! Please enter a valid positive numeric amount." << std::endl;
        }
    }
}

// Function to get a valid integer amount
void getValidIntAmount(int &amount)
{
    std::string input;
    bool valid = false;

    while (!valid)
    {
        std::cout << "\nEnter quantity: ";
        std::cin >> input;

        if (isValidNumericString(input))
        {
            amount = std::stoi(input); // Use stoi for integers
            if (amount < 0)
            {
                std::cout << "Invalid input! Quantity cannot be negative." << std::endl;
            }
            else
            {
                valid = true;
            }
        }
        else
        {
            std::cout << "Invalid input! Please enter a valid positive integer quantity." << std::endl;
        }
    }
}

class Item
{
private:
    std::string category;
    std::string itemID;
    std::string name;
    int quantity;
    double price;

public:
    explicit Item(const std::string &c, const std::string &id, const std::string &n, int q, double p)
        : category(c), itemID(id), name(n), quantity(q), price(p) {}

    void setItemID(const std::string &id) { itemID = id; }
    void setName(const std::string &itemName) { name = itemName; }
    void setQuantity(int qty)
    {
        if (qty >= 0)
        {
            quantity = qty;
        }
        else
        {
            std::cout << "Invalid quantity. Must be non-negative.\n";
        }
    }
    void setPrice(double itemPrice)
    {
        if (itemPrice >= 0.0)
        {
            price = itemPrice;
        }
        else
        {
            std::cout << "Invalid price. Must be non-negative.\n";
        }
    }
    void setCategory(const std::string &itemCategory) { category = itemCategory; }

    std::string getItemID() const { return itemID; }
    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
    std::string getCategory() const { return category; }
};

class Inventory
{
protected:
    std::vector<Item> vectorItems;

public:
    virtual void addInventoryItem() = 0;
    virtual void updateInventoryItem() = 0;
    virtual void removeInventoryItem() = 0;
    virtual void displayCategoryItems() = 0;
    virtual void displayAllInventoryItems() = 0;
    virtual void searchInventoryItem() = 0;
    virtual void sortInventoryItems() = 0;
    virtual void displayLowStockInventoryItems() = 0;
};

class InventorySystem : public Inventory
{
public:
    void addInventoryItem() override
    {
        std::string category, itemID, name;
        int quantity;
        double price;

        const std::string validCategories[] = {"CLOTHING", "ELECTRONICS", "ENTERTAINMENT"};

        bool isValidCategory = false;

        while (!isValidCategory)
        {
            std::cout << "Input Category of the item (Clothing, Electronics, Entertainment): ";
            std::cin >> category;
            ConverttoUpper(category);

            for (const std::string &validCategory : validCategories)
            {
                if (category == validCategory)
                {
                    isValidCategory = true;
                    break;
                }
            }

            if (!isValidCategory)
            {
                std::cout << "ERROR: Invalid category. Please enter a valid category.\n";
            }
        }

        std::cin.clear();
        std::cout << "Enter Item ID: ";
        std::cin.ignore();
        std::cin >> itemID;
        ConverttoUpper(itemID);

        std::cout << "Enter Name: ";
        std::cin.ignore();
        getline(std::cin, name);

        getValidIntAmount(quantity);
        getValidDoubleAmount(price);

        Item newItem(category, itemID, name, quantity, price);
        vectorItems.push_back(newItem);

        std::cout << "Item added successfully!\n";
    }

    void updateInventoryItem() override
    {
        std::string itemID;
        bool itemFound = false;

        if (vectorItems.empty())
        {
            std::cout << "No items available in the inventory.\n";
            return;
        }

        std::cout << "Enter the Item ID to update: ";
        std::cin >> itemID;
        ConverttoUpper(itemID);

        for (auto &item : vectorItems)
        {
            if (item.getItemID() == itemID)
            {
                itemFound = true;

                int choice;
                do
                {
                    std::cout << "\nSubmenu:\n";
                    std::cout << "1 - Update Price\n";
                    std::cout << "2 - Update Quantity\n";
                    std::cout << "3 - Exit\n";
                    std::cout << "Choose an option: ";
                    std::cin >> choice;

                    if (choice == 1)
                    {
                        int newPrice;
                        std::cout << "Enter new price: ";
                        getValidIntAmount(newPrice); // Using getValidAmount for price
                        item.setPrice(newPrice);
                        std::cout << "Price updated successfully.\n";
                    }
                    else if (choice == 2)
                    {
                        int newQuantity;
                        std::cout << "Enter new quantity: ";
                        getValidIntAmount(newQuantity); // Using getValidAmount for quantity
                        item.setQuantity(newQuantity);
                        std::cout << "Quantity updated successfully.\n";
                    }
                    else if (choice == 3)
                    {
                        std::cout << "Exiting update menu.\n";
                    }
                    else
                    {
                        std::cout << "Invalid choice. Please try again.\n";
                    }
                } while (choice != 3);

                break;
            }
        }

        if (!itemFound)
        {
            std::cout << "ERROR: Item with ID " << itemID << " not found in the inventory.\n";
        }
    }

    void removeInventoryItem() override
    {
        if (vectorItems.empty())
        {
            std::cout << "No items in the inventory" << std::endl;
            return;
        }

        bool itemExists = false;
        std::string itemID;
        std::cout << "Input product ID that you want to remove: ";
        std::cin >> itemID;
        ConverttoUpper(itemID);

        for (auto it = vectorItems.begin(); it != vectorItems.end();)
        {
            if (it->getItemID() == itemID)
            {
                std::cout << "Item " << it->getName() << " with ID " << it->getItemID() << " has been removed." << std::endl;
                it = vectorItems.erase(it);
                itemExists = true;
            }
            else
            {
                ++it;
            }
        }

        if (!itemExists)
        {
            std::cout << "ID " << itemID << " NOT FOUND" << std::endl;
        }
    }

    void displayAllInventoryItems() override
    {
        if (vectorItems.empty())
        {
            std::cout << "\n\nNo items to display.\n";
            return;
        }
        std::cout << "------------------------------------------------------------\n";
        std::cout << std::left << std::setw(10) << "ID"
                  << std::left << std::setw(40) << "Name"
                  << std::right << std::setw(10) << "Quantity"
                  << std::right << std::setw(10) << "Price"
                  << std::right << std::setw(20) << "Category" << "\n";
        std::cout << "------------------------------------------------------------\n";

        for (const auto &item : vectorItems)
        {
            std::cout << std::left << std::setw(10) << item.getItemID()
                      << std::left << std::setw(40) << item.getName()
                      << std::right << std::setw(10) << item.getQuantity()
                      << std::right << std::setw(10) << item.getPrice()
                      << std::right << std::setw(20) << item.getCategory()
                      << "\n";
        }
        std::cout << "------------------------------------------------------------\n";
    }

    void displayCategoryItems() override
    {
        std::string category;
        std::cout << "Input Category to Display (Clothing, Electronics, Entertainment): ";
        std::cin >> category;
        ConverttoUpper(category);

        bool found = false;
        std::cout << "Items in category " << category << ":\n";

        for (const auto &item : vectorItems)
        {
            if (item.getCategory() == category)
            {
                if (!found)
                {
                    std::cout << "------------------------------------------------------------\n";
                    std::cout << std::left << std::setw(10) << "ID"
                              << std::left << std::setw(40) << "Name"
                              << std::right << std::setw(10) << "Quantity"
                              << std::right << std::setw(10) << "Price" << "\n";
                    std::cout << "------------------------------------------------------------\n";
                    found = true;
                }

                std::cout << std::left << std::setw(10) << item.getItemID()
                          << std::left << std::setw(40) << item.getName()
                          << std::right << std::setw(10) << item.getQuantity()
                          << std::right << std::setw(10) << item.getPrice()
                          << "\n";
            }
        }

        if (!found)
        {
            std::cout << "No items found in the specified category.\n";
        }
        std::cout << "------------------------------------------------------------\n";
    }

    void searchInventoryItem() override
    {
        std::string itemID;
        std::cout << "Enter Item ID to search: ";
        std::cin >> itemID;
        ConverttoUpper(itemID);

        for (const auto &item : vectorItems)
        {
            if (item.getItemID() == itemID)
            {
                std::cout << "Item found:\n";
                std::cout << "Item ID: " << item.getItemID() << "\n";
                std::cout << "Name: " << item.getName() << "\n";
                std::cout << "Quantity: " << item.getQuantity() << "\n";
                std::cout << "Price: " << item.getPrice() << "\n";
                std::cout << "Category: " << item.getCategory() << "\n";
                return;
            }
        }

        std::cout << "ERROR: Item with ID " << itemID << " not found.\n";
    }

    void sortInventoryItems() override
    {
        if (vectorItems.empty())
        {
            std::cout << "No items available to sort.\n";
            return;
        }

        for (size_t i = 0; i < vectorItems.size() - 1; ++i)
        {
            for (size_t j = 0; j < vectorItems.size() - i - 1; ++j)
            {
                if (vectorItems[j].getName() > vectorItems[j + 1].getName())
                {
                    std::swap(vectorItems[j], vectorItems[j + 1]);
                }
            }
        }
        std::cout << "Items sorted alphabetically by name.\n";
    }

    void displayLowStockInventoryItems() override
    {
        const int LOW_STOCK_THRESHOLD = 5;
        bool foundLowStock = false;

        std::cout << "\nLow stock items (Quantity <= " << LOW_STOCK_THRESHOLD << "):\n";

        for (const auto &item : vectorItems)
        {
            if (item.getQuantity() <= LOW_STOCK_THRESHOLD)
            {
                if (!foundLowStock)
                {
                    std::cout << "------------------------------------------------------------\n";
                    std::cout << std::left << std::setw(10) << "ID"
                              << std::left << std::setw(40) << "Name"
                              << std::right << std::setw(10) << "Quantity"
                              << std::right << std::setw(10) << "Price" << "\n";
                    std::cout << "------------------------------------------------------------\n";
                    foundLowStock = true;
                }

                std::cout << std::left << std::setw(10) << item.getItemID()
                          << std::left << std::setw(40) << item.getName()
                          << std::right << std::setw(10) << item.getQuantity()
                          << std::right << std::setw(10) << item.getPrice()
                          << "\n";
            }
        }

        if (!foundLowStock)
        {
            std::cout << "No low stock items found.\n";
        }
        std::cout << "------------------------------------------------------------\n";
    }
};

int main()
{
    InventorySystem inventory;
    std::string option;
    bool running = true;

    while (running)
    {
        SystemClear();
        std::cout << "\nInventory Management System\n";
        std::cout << "----------------------------\n";
        std::cout << "1. Add Item\n";
        std::cout << "2. Update Item\n";
        std::cout << "3. Remove Item\n";
        std::cout << "4. Display All Items\n";
        std::cout << "5. Search for Item\n";
        std::cout << "6. Display Items by Category\n";
        std::cout << "7. Display Low Stock Items\n";
        std::cout << "8. Sort Items by ID\n";
        std::cout << "9. Exit\n";
        std::cout << "Enter option (1-9): ";
        std::cin >> option;

        if (std::cin.fail()) // Check if the input is valid
        {
            std::cin.clear();                                                   // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
            std::cout << "Invalid input! Please enter a number between 1 and 9.\n";
            SystemPause();
            continue; // Restart the loop
        }

        if (option == "1")
        {
            inventory.addInventoryItem();
        }
        else if (option == "2")
        {
            inventory.updateInventoryItem();
        }
        else if (option == "3")
        {
            inventory.removeInventoryItem();
        }
        else if (option == "4")
        {
            inventory.displayAllInventoryItems();
            SystemPause();
        }
        else if (option == "5")
        {
            inventory.searchInventoryItem();
            SystemPause();
        }
        else if (option == "6")
        {
            inventory.displayCategoryItems();
            SystemPause();
        }
        else if (option == "7")
        {
            inventory.displayLowStockInventoryItems();
            SystemPause();
        }
        else if (option == "8")
        {
            inventory.sortInventoryItems();
            SystemPause();
        }
        else if (option == "9")
        {
            std::cout << "Exiting program." << std::endl;
            running = false; // Set running to false to exit the loop
        }
        else
        {
            std::cout << "Invalid option! Please try again.\n";
            SystemPause();
        }
    }

    return 0;
}
