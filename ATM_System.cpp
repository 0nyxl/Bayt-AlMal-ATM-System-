#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>
#include <limits>
#include <cstdlib>

using namespace std;

string ClientsDataFile = "/home/voldemort/ATM_PROJECT/Gringotts_Vaults";
void ATMmainMenuScreen();

enum enATMMainMenu
{

    QuickWithdraw = 1,
    NormalWithdraw = 2,
    Deposit = 3,
    CheckBalance = 4,
    Logout = 5,
};

struct sClentData
{
    string AccountNumber = "";
    string PinCode = "";
    string Name = "";
    string Phone = "";
    double AccountBalance = 0.0;
};

sClentData currentClientLoggin;

void ClearScreen()
{
// Check if the compiler is running on a Windows environment
#ifdef _WIN32
    // If Windows (32-bit or 64-bit)
    system("cls");
// Check if the compiler is running on a Linux or macOS (POSIX) environment
#else
    // Assume non-Windows (Linux, macOS, etc.)
    system("clear");
#endif
}
void Pause()
{
    cout << "\nPress ENTER to continue...";

    // Clear the input buffer first, in case there are pending newline characters
    // from a previous 'cin' operation (e.g., after reading an integer).
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Wait for a single character input (like the ENTER key)
    cin.get();
}

vector<string> Split_Function(string line, string delimiter = "#//#")
{
    vector<string> vClientsData;
    size_t pos = 0;
    string word = "";
    while ((pos = line.find(delimiter)) != string::npos)
    {
        word = line.substr(0, pos);
        if (!word.empty())
        {
            vClientsData.push_back(word);
        }
        line.erase(0, pos + delimiter.length());
    }
    if (!line.empty())
    {
        vClientsData.push_back(line);
    }
    return vClientsData;
}
sClentData FillOneClient(string line, string delimiter = "#//#")
{

    sClentData Temp;

    vector<string> vClientData = Split_Function(line, delimiter);

    Temp.AccountNumber = vClientData[0];
    Temp.PinCode = vClientData[1];
    Temp.Name = vClientData[2];
    Temp.Phone = vClientData[3];
    Temp.AccountBalance = stod(vClientData[4]);

    return Temp;
}
vector<sClentData> FillAllClients()
{

    vector<sClentData> vClientsData;
    fstream file;
    string Word;

    file.open(ClientsDataFile, ios::in);

    if (file.is_open())
    {
        sClentData Temp;

        while (getline(file, Word))
        {
            if (Word.empty())
                continue;
            Temp = FillOneClient(Word);
            vClientsData.push_back(Temp);
        }
        file.close();
    }

    return vClientsData;
}

string ConvertClientToLine(const sClentData &C, string delimiter = "#//#")
{
    return C.AccountNumber + delimiter +
           C.PinCode + delimiter +
           C.Name + delimiter +
           C.Phone + delimiter +
           to_string(C.AccountBalance);
}
void SaveAllClientsToFile(const vector<sClentData> &vClients)
{

    fstream file;

    file.open(ClientsDataFile, ios::out);

    if (file.is_open())
    {
        for (const sClentData &c : vClients)
        {
            file << ConvertClientToLine(c) << "\n";
        }
        file.close();
    }
}

// HERE THE WORK

bool WithdrawAmount(sClentData &client, long long amount, vector<sClentData> &all)
{
    if (amount <= 0 || client.AccountBalance < amount || amount % 5 != 0)
    {
        return false;
    }

    client.AccountBalance -= amount;

    for (sClentData &c : all)
        if (c.AccountNumber == client.AccountNumber)
        {
            c = client;
            break;
        }
    SaveAllClientsToFile(all);
    return true;
}

// FIXED FUNCTION:
int NormalWithDraw()
{
    ClearScreen();
    cout << "\n=====================================\n";
    cout << "        NORMAL WITHDRAWAL     \n";
    cout << "=====================================\n";
    cout << "Note: Amounts must be positive whole numbers\n";
    cout << "      and multiples of 5 (e.g., 20, 50, 100).\n";
    cout << "-------------------------------------\n";

    int amount;

    do
    {
        cout << "Enter Amount: $";

        if (!(cin >> amount))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            amount = -1; // Force the loop to continue
        }
        else if (amount <= 0)
        {
            cout << "Invalid: Amount must be greater than zero.\n";
        }
        else if (amount % 5 != 0)
        {
            cout << "Invalid: Amount must be a multiple of 5 (e.g., 20, 50).\n";
        }

    } while (amount <= 0 || amount % 5 != 0);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return amount;
}

void mQuickWithdrawMenu()
{
    ClearScreen();
    vector<sClentData> vClientData = FillAllClients();
    cout << "=====================================\n";
    cout << "      Select a Quick Amount     \n";
    cout << "=====================================\n\n";

    cout << " [1] $20   | [2] $50   | [3] $100 \n";
    cout << " [4] $200  | [5] $500  | [6] $1000\n\n";

    cout << "=====================================\n";
    cout << " (Press (M) to return to Main Menu or Press (7) for Custom Amount ): ";
    char choice;
    cin >> choice;

    choice = tolower(choice);

    switch (choice)
    {
    case '1':
    {
        if (WithdrawAmount(currentClientLoggin, 20, vClientData))
        {
            cout << "\nSuccessfully withdrawn $20.\n";
            Pause();
            ATMmainMenuScreen();
        }
        else
        {
            cout << "\nFailed to withdraw $20. Check your balance.\n";
            Pause();
            mQuickWithdrawMenu();
        }
        break;
    }
    case '2':
    {
        if (WithdrawAmount(currentClientLoggin, 50, vClientData))
        {
            cout << "\nSuccessfully withdrawn $50.\n";
            Pause();
            ATMmainMenuScreen();
        }
        else
        {
            cout << "\nFailed to withdraw $50. Check your balance.\n";
            Pause();
            mQuickWithdrawMenu();
        }
        break;
    }
    case '3':
    {
        if (WithdrawAmount(currentClientLoggin, 100, vClientData))
        {
            cout << "\nSuccessfully withdrawn $100.\n";
            Pause();
            ATMmainMenuScreen();
        }
        else
        {
            cout << "\nFailed to withdraw $100. Check your balance.\n";
            Pause();
            mQuickWithdrawMenu();
        }
        break;
    }
    case '4':
    {
        if (WithdrawAmount(currentClientLoggin, 200, vClientData))
        {
            cout << "\nSuccessfully withdrawn $200.\n";
            Pause();
            ATMmainMenuScreen();
        }
        else
        {
            cout << "\nFailed to withdraw $200. Check your balance.\n";
            Pause();
            mQuickWithdrawMenu();
        }
        break;
    }
    case '5':
    {
        if (WithdrawAmount(currentClientLoggin, 500, vClientData))
        {
            cout << "\nSuccessfully withdrawn $500.\n";
            Pause();
            ATMmainMenuScreen();
        }
        else
        {
            cout << "\nFailed to withdraw $500. Check your balance.\n";
            Pause();
            mQuickWithdrawMenu();
        }
        break;
    }
    case '6':
    {
        if (WithdrawAmount(currentClientLoggin, 1000, vClientData))
        {
            cout << "\nSuccessfully withdrawn $1000.\n";
            Pause();
            ATMmainMenuScreen();
        }
        else
        {
            cout << "\nFailed to withdraw $1000. Check your balance.\n";
            Pause();
            mQuickWithdrawMenu();
        }
        break;
    }
    case '7':
    {
        int n = NormalWithDraw();
        if (WithdrawAmount(currentClientLoggin, n, vClientData))
        {
            cout << "\nSuccessfully withdrawn $" << to_string(n) << ".\n";
            Pause();
            ATMmainMenuScreen();
        }
        else
        {
            cout << "\nFailed to withdraw $" << to_string(n) << ". " << "Check your balance.\n";
            Pause();
            ATMmainMenuScreen();
        }
        break;
    }
    case 'm':
    {
        ATMmainMenuScreen();
        break;
    }
    default:
    {
        cout << "Invalid Option. Returning to Quick Withdraw Menu.\n";
        Pause();
        mQuickWithdrawMenu(); // Recurse for invalid non-menu choices
        break;
    }
    }
}
bool DepositAmount(sClentData &client, long long amount, vector<sClentData> &all)
{
    if (amount <= 0)
    {
        return false;
    }

    client.AccountBalance += amount;

    for (sClentData &c : all)
        if (c.AccountNumber == client.AccountNumber)
        {
            c = client;
            break;
        }
    SaveAllClientsToFile(all);
    return true;
}

int DepositMenu()
{
    ClearScreen();
    cout << "\n=====================================\n";
    cout << "            DEPOSIT FUNDS        \n";
    cout << "=====================================\n";
    cout << "Note: Please enter the amount you wish to deposit.\n";
    cout << "      Amounts must be positive whole numbers.\n"; // Assuming whole dollar deposits
    cout << "-------------------------------------\n";

    int depositAmount;

    cout << "Enter Amount to Deposit: $";
    while (!(cin >> depositAmount) || depositAmount <= 0)
    {
        if (cin.fail())
        {
            cin.clear();
            cout << "Invalid input. Please enter a number.\n";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (depositAmount <= 0)
        {
            cout << "Invalid: Deposit amount must be greater than zero.\n";
        }
        cout << "Please Re-enter Amount: $";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return depositAmount;
}

void CheckBalanceMenu(const sClentData &client)
{
    ClearScreen();
    cout << "\n=====================================\n";
    cout << "          ACCOUNT BALANCE         \n";
    cout << "=====================================\n";

    cout << "Account Holder: " << client.Name << "\n";
    cout << "Account Number: " << client.AccountNumber << "\n";
    cout << "-------------------------------------\n";
    cout << "CURRENT BALANCE:\n";
    cout << fixed << setprecision(2) << "$ " << client.AccountBalance << "\n";

    cout << "=====================================\n";
    cout << "(Press any key to return to Main Menu)\n";

    Pause();
}

sClentData FindClientByCredentials(const string &AccountNumber, const string &PinCode, const vector<sClentData> &allClients)
{

    for (const sClentData &client : allClients)
    {
        if (client.AccountNumber == AccountNumber && client.PinCode == PinCode)
        {
            return client;
        }
    }
    return sClentData();
}

void LoginScreen()
{
    bool LoginFailed = true;
    string AccountNumber, PinCode;

    while (LoginFailed)
    {
        ClearScreen();
        cout << "\n=====================================\n";
        cout << "           ATM LOGIN SCREEN          \n";
        cout << "=====================================\n";
        cout << "Enter Account Number: ";
        cin >> AccountNumber;

        cout << "Enter PIN Code: ";
        cin >> PinCode;

        vector<sClentData> vClients = FillAllClients();
        sClentData FoundClient = FindClientByCredentials(AccountNumber, PinCode, vClients);

        if (FoundClient.AccountNumber != "")
        {
            // Success! Set the global variable and break the loop.
            currentClientLoggin = FoundClient;
            LoginFailed = false;
            cout << "\nLogin successful! Welcome, " << currentClientLoggin.Name << ".\n";
            Pause();
            ClearScreen();
        }
        else
        {
            cout << "\nERROR! Invalid Account Number or PIN.\n";
            cout << "Please check your credentials and try again.\n";
            Pause();
            ClearScreen();
        }
    }
}

void ATMmainMenuScreen()
{
    ClearScreen();
    vector<sClentData> vClientData = FillAllClients();
    cout << string(50, '=') << "\n";
    cout << "\t\tWelcome To Bayt AlMal ATM System\n";
    cout << string(50, '=') << "\n";
    cout << "[1] Quick Withdraw\n[2] Normal Withdraw\n[3] Deposit\n[4] Check Balance\n[5] Logout\n";
    cout << string(50, '=') << "\n";
    short choice;
    cout << "Enter From [1-5]: ";
    cin >> choice;
    while (cin.fail() || choice < 1 || choice > 5)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid. Make Sure You Select From [1] to [5]: ";
        cin >> choice;
    }

    enATMMainMenu selectedOption = static_cast<enATMMainMenu>(choice);

    switch (selectedOption)
    {
    case QuickWithdraw:
    {
        mQuickWithdrawMenu();
        break;
    }
    case NormalWithdraw:
    {

        int n = NormalWithDraw();
        vector<sClentData> vClientsForWithdraw = FillAllClients();
        if (WithdrawAmount(currentClientLoggin, n, vClientsForWithdraw))
        {
            cout << "\nSuccessfully withdrawn $" << to_string(n) << ".\n";
            Pause();
            ATMmainMenuScreen();
        }
        else
        {
            cout << "\nFailed to withdraw $" << to_string(n) << ". " << "Check your balance.\n";
            Pause();
            ATMmainMenuScreen();
        }
        break;
    }
    case Deposit:
    {
        int D = DepositMenu();
        vector<sClentData> vClientsForDeposit = FillAllClients(); // Renamed to vClientsForDeposit

        if (DepositAmount(currentClientLoggin, D, vClientsForDeposit))
        {
            cout << "\nSuccessfully deposited $" << to_string(D) << ".\n";
        }
        else
        {
            cout << "\nFailed to deposit $" << to_string(D) << ". Amount must be positive.\n";
        }
        Pause();
        ATMmainMenuScreen();
        break;
    }
    case CheckBalance:
    {
        vector<sClentData> vClients = FillAllClients();
        currentClientLoggin = FindClientByCredentials(currentClientLoggin.AccountNumber, currentClientLoggin.PinCode, vClients);

        CheckBalanceMenu(currentClientLoggin);
        ATMmainMenuScreen();
        break;
    }
    case Logout:
    {
        ClearScreen();
        cout << "\nGoodbye, " << currentClientLoggin.Name << "!\n";
        Pause();
        LoginScreen();
        ATMmainMenuScreen();
        break;
    }
    default:
    {
        cout << "Invalid option\n";
        break;
    }
    }
}

int main()
{

    LoginScreen();
    ATMmainMenuScreen();

    return 0;
}