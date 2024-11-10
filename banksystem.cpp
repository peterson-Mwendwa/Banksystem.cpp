#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <string>
#include <ctime>

// Bank Account Class
class BankAccount {
private:
    std::string accountHolder;
    double balance;
    std::vector<std::string> transactionHistory;

    // Function to get the current timestamp
    std::string getCurrentTime() {
        time_t now = time(0);
        char* dt = ctime(&now);
        return std::string(dt);
    }

public:
    BankAccount(std::string name, double initialBalance) {
        accountHolder = name;
        balance = initialBalance;
        transactionHistory.push_back("Account created with an initial balance of $ " + std::to_string(initialBalance) + " at " + getCurrentTime());
    }

    // Deposit Method
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            transactionHistory.push_back("Deposited $ " + std::to_string(amount) + " at " + getCurrentTime());
            std::cout << "Deposit successful! 💰\n";
        } else {
            std::cout << "Amount must be greater than 0. 🚫\n";
        }
    }

    // Withdraw Method
    void withdraw(double amount) {
        if (amount <= balance && amount > 0) {
            balance -= amount;
            transactionHistory.push_back("Withdrew $ " + std::to_string(amount) + " at " + getCurrentTime());
            std::cout << "Withdrawal successful! 💸\n";
        } else if (amount > balance) {
            std::cout << "Insufficient balance. 🚫\n";
        } else {
            std::cout << "Amount must be greater than 0. 🚫\n";
        }
    }

    // Check Balance Method
    void checkBalance() {
        std::cout << "Your current balance is: $ " << balance << " 💵\n";
    }

    // Display Transaction History
    void displayTransactions() {
        std::cout << "\n📝 Transaction History:\n";
        for (const auto& transaction : transactionHistory) {
            std::cout << transaction << "\n";
        }
    }
};

// Login and Registration System Class
class LoginSystem {
private:
    std::unordered_map<std::string, std::string> users; // To store username and password

    // Load users from file
    void loadUsers() {
        std::ifstream file("users.txt");
        std::string username, password;
        while (file >> username >> password) {
            users[username] = password;
        }
        file.close();
    }

    // Save users to file
    void saveUser(const std::string& username, const std::string& password) {
        std::ofstream file("users.txt", std::ios::app);
        file << username << " " << password << "\n";
        file.close();
    }

public:
    LoginSystem() {
        loadUsers(); // Load users when the system starts
    }

    // Register a new user
    void registerUser() {
        std::string username, password;
        std::cout << "Enter a username for registration: ";
        std::cin >> username;

        if (users.find(username) != users.end()) {
            std::cout << "Username already exists. Try a different one. ❌\n";
            return;
        }

        std::cout << "Enter a password: ";
        std::cin >> password;
        users[username] = password;
        saveUser(username, password);
        std::cout << "Registration successful! 🎉 You can now log in.\n";
    }

    // Login existing user
    bool login() {
        std::string username, password;
        std::cout << "Welcome to the Bank System! 🏦\n";
        std::cout << "Please enter your username: ";
        std::cin >> username;
        std::cout << "Please enter your password: ";
        std::cin >> password;

        if (users.find(username) != users.end() && users[username] == password) {
            std::cout << "Login successful! ✅\n";
            return true;
        } else {
            std::cout << "Invalid username or password. Please try again. ❌\n";
            return false;
        }
    }
};

int main() {
    LoginSystem loginSystem;
    int option;

    // Main menu for login or registration
    while (true) {
        std::cout << "\n--- Main Menu ---\n";
        std::cout << "1. Register 📝\n";
        std::cout << "2. Login 🔑\n";
        std::cout << "3. Exit 🚪\n";
        std::cout << "Please select an option (1-3): ";
        std::cin >> option;

        if (option == 1) {
            loginSystem.registerUser();
        } else if (option == 2) {
            if (loginSystem.login()) {
                break; // Exit the loop if login is successful
            }
        } else if (option == 3) {
            std::cout << "Goodbye! 👋\n";
            return 0;
        } else {
            std::cout << "Invalid option. Please select a valid option (1-3). 🚫\n";
        }
    }

    // Get account holder's name and initialize the bank account
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;
    BankAccount account(name, 1000.0); // Initial balance is $1000

    bool running = true;
    while (running) {
        std::cout << "\n--- Bank System Menu ---\n";
        std::cout << "1. Deposit 💰\n";
        std::cout << "2. Withdraw 💸\n";
        std::cout << "3. Check Balance 💵\n";
        std::cout << "4. Transaction History 📝\n";
        std::cout << "5. Exit 🚪\n";
        std::cout << "Please select an option (1-5): ";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                double amount;
                std::cout << "Enter the amount to deposit: $ ";
                std::cin >> amount;
                account.deposit(amount);
                break;
            }
            case 2: {
                double amount;
                std::cout << "Enter the amount to withdraw: $ ";
                std::cin >> amount;
                account.withdraw(amount);
                break;
            }
            case 3:
                account.checkBalance();
                break;
            case 4:
                account.displayTransactions();
                break;
            case 5:
                std::cout << "Thank you for using our services! 👋\n";
                running = false;
                break;
            default:
                std::cout << "Invalid option. Please select a valid option (1-5). 🚫\n";
        }
    }

    return 0;
}
4
