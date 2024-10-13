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

void getValidDoubleAmount(double &amount)
{
    std::string input;
    bool valid = false;

    while (!valid)
    {
        std::cout << "Enter Price: ";
        std::cin >> input; 

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

       
        bool decimalFound = false;
        bool isNumeric = true;

        for (char c : input)
        {
            if (c == '.')
            {
                if (decimalFound)
                {
                    isNumeric = false; 
                    break;
                }
                decimalFound = true;
            }
            else if (!std::isdigit(c))
            {
                isNumeric = false; 
                break;
            }
        }

        if (isNumeric && !input.empty())
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

void getValidIntAmount(int &amount)
{
    std::string input;
    bool valid = false;

    while (!valid)
    {
        std::cout << "Enter Quantity: ";
        std::cin >> input; 

      
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        
        bool isNumeric = true;

        for (char c : input)
        {
            if (!std::isdigit(c))
            {
                isNumeric = false;
                break;
            }
        }

        if (isNumeric && !input.empty())
        {
            amount = std::stoi(input);
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
            std::cout << "Invalid input! Please enter a valid positive integer amount." << std::endl;
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
    explicit Item(std::string &c, std::string &id, std::string &n, int q, double p)
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

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        bool IDExist = true;
        while (IDExist)
        {
            std::cout << "Enter ID: ";
            std::getline(std::cin, itemID);
            ConverttoUpper(itemID);

            IDExist = false;
            for (const auto &item : vectorItems)
            {
                if (item.getItemID() == itemID)
                {
                    IDExist = true;
                    std::cout << "ID already exists." << std::endl;
                    break;
                }
            }
        }

       
        std::cout << "Enter Name: ";
        std::getline(std::cin, name);

       
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
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Enter the Item ID to update: ";
        std::getline(std::cin, itemID);
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
                        double newPrice;
                        getValidDoubleAmount(newPrice);
                        item.setPrice(newPrice);
                        std::cout << "Price updated successfully.\n";
                    }
                    else if (choice == 2)
                    {
                        int newQuantity;
                        getValidIntAmount(newQuantity);
                        ; 
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
            std::cout << "No items available in the inventory.\n";
            return;
        }
        std::cin.clear();
        std::cin.ignore();
        bool itemExists = false;
        std::string itemID;
        std::cout << "Input product ID that you want to remove: ";
        std::getline(std::cin, itemID);
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
            std::cout << "No items to display.\n";
            return;
        }
        std::cout << "---------------------------------------------------------------------------------------------\n";
        std::cout << std::left << std::setw(10) << "ID"
                  << std::left << std::setw(40) << "Name"
                  << std::right << std::setw(10) << "Quantity"
                  << std::right << std::setw(10) << "Price"
                  << std::right << std::setw(20) << "Category" << "\n";
        std::cout << "---------------------------------------------------------------------------------------------\n";

        for (const auto &item : vectorItems)
        {
            std::cout << std::left << std::setw(10) << item.getItemID()
                      << std::left << std::setw(40) << item.getName()
                      << std::right << std::setw(10) << item.getQuantity()
                      << std::right << std::setw(10) << item.getPrice()
                      << std::right << std::setw(20) << item.getCategory()
                      << "\n";
        }
        std::cout << "---------------------------------------------------------------------------------------------\n";
    }

    void displayCategoryItems() override
    {
        if (vectorItems.empty())
        {
            std::cout << "No items available in the inventory.\n";
            return;
        }
        std::string category;
        std::cout << "Input Category to Display (Clothing, Electronics, Entertainment): ";
        std::cin >> category;
        ConverttoUpper(category);

        bool found = false;
        bool categoryExists = false; 

        
        for (const auto &item : vectorItems)
        {
            if (item.getCategory() == category)
            {
                categoryExists = true; 
                break;
            }
        }

        
        if (!categoryExists)
        {
            std::cout << "Category " << category << " does not exist!\n";
            return;
        }
        std::cout << "Items in category " << category << ":\n";

        for (const auto &item : vectorItems)
        {
            if (item.getCategory() == category)
            {
                if (!found)
                {
                    std::cout << "---------------------------------------------------------------------------------------------\n";
                    std::cout << std::left << std::setw(10) << "ID"
                              << std::left << std::setw(40) << "Name"
                              << std::right << std::setw(10) << "Quantity"
                              << std::right << std::setw(10) << "Price" << "\n";
                    std::cout << "---------------------------------------------------------------------------------------------\n";
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
        std::cout << "---------------------------------------------------------------------------------------------\n";
    }

    void searchInventoryItem() override
    {
        if (vectorItems.empty())
        {
            std::cout << "No items available in the inventory.\n";
            return;
        }
        std::cin.clear();
        std::cin.ignore();
        std::string itemID;
        std::cout << "Enter Item ID to search: ";
        std::getline(std::cin, itemID);
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

        std::string sortOption;
        std::string orderOption;

        
        while (true)
        {

            std::cout << "Sort By: (1 - Quantity, 2 - Price)";
            std::cin >> sortOption;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input! Please enter 1 or 2.\n";
                SystemPause();
                continue;
            }

            // Ask for sort order
            std::cout << "Enter '1' for ascending or '2' for descending: ";
            std::cin >> orderOption;

            if (sortOption == "1" || sortOption == "2")
            {

                for (size_t i = 0; i < vectorItems.size() - 1; ++i)
                {
                    bool swapped = false;
                    for (size_t j = 1; j < vectorItems.size() - i; ++j)
                    {
                        bool shouldSwap = false;

                        if (sortOption == "1") // Sort by Quantity
                        {
                            if ((orderOption == "1" && vectorItems[j].getQuantity() < vectorItems[j - 1].getQuantity()) ||
                                (orderOption == "2" && vectorItems[j].getQuantity() > vectorItems[j - 1].getQuantity()))
                            {
                                shouldSwap = true;
                            }
                        }
                        else if (sortOption == "2") // Sort by Price
                        {
                            if ((orderOption == "1" && vectorItems[j].getPrice() < vectorItems[j - 1].getPrice()) ||
                                (orderOption == "2" && vectorItems[j].getPrice() > vectorItems[j - 1].getPrice()))
                            {
                                shouldSwap = true;
                            }
                        }

                        // Swap items if needed
                        if (shouldSwap)
                        {
                            Item temp = vectorItems[j];
                            vectorItems[j] = vectorItems[j - 1];
                            vectorItems[j - 1] = temp;
                            swapped = true;
                        }
                    }

                    if (!swapped)
                    {
                        break;
                    }
                }
                std::cout << "Items sorted successfully.\n";
                displayAllInventoryItems();
                break;
            }
            else
            {
                std::cout << "Invalid sort option. Please choose 1 for Quantity or 2 for Price.\n";
            }
        }
    }
    void displayLowStockInventoryItems() override
    {
        if (vectorItems.empty())
        {
            std::cout << "No items available in the inventory.\n";
            return;
        }
        const int LOW_STOCK_THRESHOLD = 5;
        bool foundLowStock = false;

        std::cout << "\nLow stock items (Quantity <= " << LOW_STOCK_THRESHOLD << "):\n";

        for (const auto &item : vectorItems)
        {
            if (item.getQuantity() <= LOW_STOCK_THRESHOLD)
            {
                if (!foundLowStock)
                {
                    std::cout << "---------------------------------------------------------------------------------------------\n";
                    std::cout << std::left << std::setw(10) << "ID"
                              << std::left << std::setw(40) << "Name"
                              << std::right << std::setw(10) << "Quantity"
                              << std::right << std::setw(10) << "Price" << "\n";
                    std::cout << "---------------------------------------------------------------------------------------------\n";
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
        std::cout << "---------------------------------------------------------------------------------------------\n";
    }
};

int main()
{
    InventorySystem inventory;
    std::string option;
    bool running = true;

    while (running)
    {
        std::cout << "\nInventory Management System\n";
        std::cout << "----------------------------\n";
        std::cout << "1. Add Item\n";
        std::cout << "2. Update Item\n";
        std::cout << "3. Remove Item\n";
        std::cout << "4. Display Items by Category\n";
        std::cout << "5. Display All Items\n";
        std::cout << "6. Search Item\n";
        std::cout << "7. Sort Items\n";
        std::cout << "8. Display Low Stock Items\n";
        std::cout << "9. Exit\n";
        std::cout << "Enter option (1-9): ";
        std::cin >> option;

        if (std::cin.fail())
        {
            std::cin.clear();                                                 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Invalid input! Please enter a number between 1 and 9.\n";
            SystemPause();
            continue;
        }

        if (option == "1")
        {
            SystemClear();
            inventory.addInventoryItem();
        }
        else if (option == "2")
        {
            SystemClear();
            inventory.updateInventoryItem();
        }
        else if (option == "3")
        {
            SystemClear();
            inventory.removeInventoryItem();
        }
        else if (option == "4")
        {
            SystemClear();
            inventory.displayCategoryItems();
        }
        else if (option == "5")
        {
            SystemClear();
            inventory.displayAllInventoryItems();
        }
        else if (option == "6")
        {
            SystemClear();
            inventory.searchInventoryItem();
        }
        else if (option == "7")
        {
            SystemClear();
            inventory.sortInventoryItems();
        }
        else if (option == "8")
        {
            SystemClear();
            inventory.displayLowStockInventoryItems();
        }
        else if (option == "9")
        {
            std::cout << "Exiting program." << std::endl;
            running = false; 
        }
        else
        {
            std::cout << "Invalid option! Please try again.\n";
            SystemPause();
        }
    }

    return 0;
}
