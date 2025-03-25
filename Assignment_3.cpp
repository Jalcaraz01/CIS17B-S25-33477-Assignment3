//Justin Alcaraz
//Lesson 3 Assignment
#include <iostream>
#include <memory>
#include <stdexcept>
#include <iomanip>
using namespace std;


// - NegativeDepositException (for negative deposit attempts)
// - OverdrawException (for withdrawing more than the balance)
// - InvalidAccountOperationException (for transactions on a closed account)

//input_validation is a recycled function from one of my previous assignments that checks to make sure that an input is a number
//without whitespace. Returns true if input is valid and false if not.
bool input_validation(string user_input){
    //for loop iterates through the characters of a string, checking for whitespace that would make an input invalid.
    for (int i=0; i < user_input.length(); i++){
        if (isspace(user_input[i])){
            cout << "Invalid input, please enter a number with no spaces." << endl;
            return false;
        }
    }
    //the try-catch block here tries to convert string to a double, if it fails it will give an exception which will be caught.
    try{
        stod(user_input);
    }
    catch(...){
        cout << "Invalid input, please enter a number." << endl;
        return false;
    }
    return true;
}

//The NegativeDepositException class is an exception class that contains a specific error message for negative deposit exceptions
class NegativeDepositException
{
private:
    string Negative_Error;
public:
    NegativeDepositException(){
        Negative_Error = "Cannot deposit a negative amount!";
    }
    
    const string& getError() const{
        return Negative_Error;
    }
    
};

//The NegativeWithdrawException class is an exception class that contains a specific error message for negative withdraw exceptions
class NegativeWithdrawException
{
private:
    string Negative_Error;
public:
    NegativeWithdrawException(){
        Negative_Error = "Cannot withdraw a negative amount!";
    }
    
    const string& getError() const{
        return Negative_Error;
    }
    
};

//The OverdrawException class contains an exception message to output if the user tries to withdraw more than the current balance
class OverdrawException
{
private:
    string Overdraw_Error;
public:
    OverdrawException(){
        Overdraw_Error = "Insufficient funds!";
    }
    
    const string& getError() const{
        return Overdraw_Error;
    }
    
};

//The InvalidAccountOperationException exception class prevents the user from using the account when it is closed
class InvalidAccountOperationException
{
private:
    string Invalid_Account_Error;
public:
    InvalidAccountOperationException(){
        Invalid_Account_Error = "Account is closed for transactions!";
    }
    
    const string& getError() const{
        return Invalid_Account_Error;
    }
    
};

//The BankAccount class contains private information such as accountNumber, balance, and account activity.
//It also contains multiple member functions that are used to add, subtract, display the balance or close the account.
class BankAccount {
private:
    std::string accountNumber;
    double balance;
    bool isActive;

public:
    // Constructor to initialize account number, balance, and active status
    BankAccount(std::string accNum, double initialBalance) : accountNumber(accNum), balance(initialBalance), isActive(true) {}

    // Deposit method
    void deposit(double amount) {
        //The try-catch here first throws an exception if the account is closed, and if not then if the deposit amount is less
        //than zero. If there is no error then the balance is updated with the deposit amount added.
        try{
            if(isActive == false){
                throw InvalidAccountOperationException();
            }
            if (amount < 0){
                throw NegativeDepositException();
            }
            balance += amount;
            cout << "Deposit Successful!" << endl;
        }
        catch(const NegativeDepositException& Exception){
            cerr << "Error: " << Exception.getError() << endl;
        }
    }

    // Withdraw method
    void withdraw(double amount) {
        //The try-catch here is similar to the previous one for deposit, throwing an exception of a different type this time.
        //It will throw different exceptions if the account is closed, if the amount is negative, and if the amount is greater
        //than the current balance. If there is no error, then the amount will be subtracted from the current balance.
        try{
            if(isActive == false){
                throw InvalidAccountOperationException();
            }
            if(amount < 0){
                throw NegativeWithdrawException();
            }
            if(amount > balance){
                throw OverdrawException();
            }
            balance -= amount;
            cout << "Withdraw Successful!" << endl;
        }
        catch(const NegativeWithdrawException& Exception){
            cerr << "Error: " << Exception.getError() << endl;
        }
        catch(const OverdrawException& Exception){
            cerr << "Error: " << Exception.getError() << endl;
        }
    }

    // Method to get current balance
    double getBalance() const {
        //throws an exception if the account's activity is set to false.
        //returns the current balance
        if(isActive == false){
            throw InvalidAccountOperationException();
        }
        return balance;
        
    }

    // Method to close the account
    void closeAccount() {
        //throws an exception if the account's activity is set to false.
        //sets the account's activity to false, preventing any further transactions.
        if(isActive == false){
            throw InvalidAccountOperationException();
        }
        isActive = false;
        cout << "Account has been closed." << endl;
    }
};

int main() {
    try {
        //Starter Code Comments:
        // Example: std::cout << "Enter initial balance: ";
        //          std::cin >> initialBalance;
        //          auto account = std::make_unique<BankAccount>("123456", initialBalance);
        string initial_deposit;
        
        //An initial deposit is entered by the user here and verified by the input_validation() function.
        cout << "Welcome to your Bank Account!" << endl;
        cout << "To begin, please enter an initial deposit: ";
        getline(cin, initial_deposit);
        while(input_validation(initial_deposit) == false || stod(initial_deposit) < 0){
            cout << "Enter initial deposit: ";
            getline(cin, initial_deposit);
        }
        
        //account object is initialized here, with an account number and an initial deposit as the starting balance
        auto account = std::make_unique<BankAccount>("123456", stod(initial_deposit));
        
        
        cout << endl;
        std::cout << "Bank Account Created: #" << "123456" << std::endl;
        string userChoice = "";
        //Option menu loops until the user selects to exit
        while (userChoice != "6"){
            cout << endl;
            cout << "1. Deposit Money" << endl << "2. Withdraw Money" << endl << "3. Check Balance" << endl << "4. Close Account" << endl << "5. Demonstrate Exception Handling" << endl << "6. Exit" << endl << endl;
            cout << "Enter your choice: ";
            getline(cin, userChoice);
            
            if (input_validation(userChoice) == false){
                continue;
            }
            //This switch statement switches between different options depending on what the user input is.
            switch(stoi(userChoice)){
                case 1:
                {
                    //Deposit:
                    string deposit_amount;
                    cout << "Please enter an amount to deposit: ";
                    getline(cin, deposit_amount);
                    while(input_validation(deposit_amount) == false){
                        cout << "Please enter an amount to deposit: ";
                        getline(cin, deposit_amount);
                    }
                    cout << "Depositing $" << deposit_amount << "..." << endl;
                    account->deposit(stod(deposit_amount));
                    break;
                }
                case 2:
                {
                    //Withdraw:
                     string withdraw_amount;
                     cout << "Please enter an amount to withdraw: ";
                     getline(cin, withdraw_amount);
                    while(input_validation(withdraw_amount) == false){
                        cout << "Please enter an amount to withdraw: ";
                        getline(cin, withdraw_amount);
                    }
                     cout << "Withdrawing $" << withdraw_amount << "..." << endl;
                     account->withdraw(stod(withdraw_amount));
                     break;
                }
                case 3:
                {
                    //Display Balance:
                    //NOTE: account->getBalance() is called without cout during some cases to raise an exception in
                    //the case that the account has been already closed.
                    account->getBalance();
                    cout << "Current Balance: $" << fixed << setprecision(2) << account->getBalance() << endl;
                    break;
                }
                case 4:
                {
                    //Close Account:
                    account->getBalance();
                    cout << "Closing account..." << endl;
                    account->closeAccount();
                    break;
                }
                case 5:
                {
                    //Demonstrate Exception Handling:
                    //This case outputs various transactions in order to display the functionality of the programs error management
                    cout << endl;
                    account->getBalance();
                    cout << "Now demonstrating Exception Handling ..." << endl;
                    cout << "Current Balance is $" << fixed << setprecision(2) << account->getBalance() << endl;
                    cout << "Attempting to withdraw $" << (account->getBalance() + 1.00) <<  "..." << endl;
                    account->withdraw((account->getBalance() + 1));
                    cout << "Attempting to deposit -$1.00..." << endl;
                    account->deposit(-1);
                    cout << "Closing account..." << endl;
                    account->closeAccount();
                    cout << "Attempting to deposit into a closed account..." << endl;
                    account->deposit(100);
                    break;
                }
            }
            
        }
    }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    //Catch for Invalid Account Exceptions, if the account is closed, an error will display and the program will end.
        catch(const InvalidAccountOperationException& Exception){
            cerr << "Error: " << Exception.getError() << endl;
    }
        return 0;
    }

