    #include <iostream>
    #include <limits>
    #include <string>
    #include <cctype>
    #include <vector>

    void SystemClear()
    {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    };

    void SystemPause()
    {
    #ifdef _WIN32
        system("pause");
    #else
        std::cin.get();
    #endif
    }

    // Check if input is number, check decimal, if empty
    bool isValidNumericString(const std::string &input)
    {
        bool Decimal = false;

        for (const char ch : input)
        {
            if (ch == '.')
            {
                if (Decimal)
                {
                    return false;
                }
                Decimal = true;
            }
            else if (!isdigit(ch))
            {
                return false;
            }
        }
        return !input.empty();
    }

    // Amount input, checker
    void getValidAmount(double &amount)
    {
        std::string input;
        bool Valid = false;

        while (!Valid)
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
                    Valid = true;
                }
            }
            else
            {
                std::cout << "Invalid input! Please enter a valid positive numeric amount." << std::endl;
            }
        }
    }
    // Class Item
    class Item
    {
    private:
        std::string category;
        std::string itemID;
        std::string name;
        int quantity;
        double price;

    public:
        // Constructor
        explicit Item(const std::string &c, const std::string &id, const std::string &n, int q, double p)
            : category(c), itemID(id), name(n), quantity(q), price(p) {}

        // Setter
        //  Setters
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

        // Getter
        std::string getItemID() const { return itemID; }
        std::string getName() const { return name; }
        int getQuantity() const { return quantity; }
        double getPrice() const { return price; }
        std::string getCategory() const { return category; }
    };

    class Inventory
    {
    protected:
        std::vector<Item> vectoritems;

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
        // category input
        void addInventoryItem() override
        {
        }
        void updateInventoryItem() override
        {
        }
        void removeInventoryItem() override
        {
        }
        void displayCategoryItems() override
        {
        }
        void displayAllInventoryItems() override
        {
        }
        void searchInventoryItem() override
        {
        }
        void sortInventoryItems() override
        {
        }
        void displayLowStockInventoryItems() override
        {
        }
    };
    void DisplayMenu()
    {
        std::string choice;
        bool running = true;

        while (running)
        {
            std::cout << "Menu:\n";
            std::cout << "1 - Add Item\n";
            std::cout << "2 - Update Item\n";
            std::cout << "3 - Remove Item\n";
            std::cout << "4 - Display Items by Category\n";
            std::cout << "5 - Display All Items\n";
            std::cout << "6 - Search Item\n";
            std::cout << "7 - Sort Items\n";
            std::cout << "8 - Display Low Stock Items\n";
            std::cout << "9 - Exit\n";
            std::cout << "Choose an option: ";
            std::cin >> choice;

            if (choice == "1")
            {
                SystemClear();
            }
            else if (choice == "2")
            {
                SystemClear();
            }

            else if (choice == "3")
            {
                SystemClear();
            }
            else if (choice == "4")
            {
                SystemClear();
            }
            else if (choice == "5")
            {
                SystemClear();
            }
            else if (choice == "6")
            {
                SystemClear();
            }
            else if (choice == "7")
            {
                SystemClear();
            }
            else if (choice == "8")
            {
                SystemClear();
            }
            else if (choice == "9")
            {
                SystemClear();
                std::cout << "Exiting program.\n";
                running = false;
            }
            else
            {

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid choice. Please try again." << std::endl;
                SystemPause();
                SystemClear();
            }
        }
    }

    int main()
    {
        InventorySystem inventorySystem;
        DisplayMenu();
        return 0;
    }
