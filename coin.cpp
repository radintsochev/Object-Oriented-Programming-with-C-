#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#pragma warning(disable : 4996)
using std::cout;
using std::cin;
using std::endl;

const char* USERS_FILE = "users.dat";
const char* BLOCKS_FILE = "blocks.dat";


unsigned computeHash(const unsigned char* memory, int length) {
    unsigned hash = 0xbeaf;

    for (int c = 0; c < length; c++) {
        hash += memory[c];
        hash += hash << 10;
        hash ^= hash >> 6;
    }

    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

struct User {
    unsigned id;
    char name[128];
};

struct Transaction {
    unsigned sender;
    unsigned receiver;
    double coins;
    long long time;
};

struct TransactionBlock {
    unsigned id;
    unsigned prevBlockId;
    unsigned prevBlockHash;
    int validTransactions = 0;
    Transaction transactions[16];
};

struct Users {
    unsigned numberOfUsers = 0;
    unsigned currMax = 1;
    User* user = nullptr;
    Users()
    {
        user = new User[currMax];
    }
};

struct TransactionBlocks {
    unsigned numberOfTransactionBlocks = 0;
    unsigned currMax = 1;
    TransactionBlock* transactionBlock = nullptr;
    TransactionBlocks()
    {
        transactionBlock = new TransactionBlock[currMax];
    }
};

unsigned myCeil(const double floatNumber)
{
    if (floatNumber - unsigned(floatNumber) * 1.0 != 0)
    {
        return unsigned(floatNumber) + 1;
    }
    else
    {
        return unsigned(floatNumber);
    }
}

unsigned fileSize(std::ifstream& file)
{
    unsigned start = file.tellg();
    file.seekg(0, std::ios::end);
    unsigned size = file.tellg();
    file.seekg(start, std::ios::beg);

    return size;
}

void freeUsers(Users& users)
{
    delete[] users.user;
    users.numberOfUsers = 0;
    users.currMax = 0;
}

void freeTransactionBlocks(TransactionBlocks& transactionBlocks)
{
    delete[] transactionBlocks.transactionBlock;
    transactionBlocks.numberOfTransactionBlocks = 0;
    transactionBlocks.currMax = 0;
}

unsigned maxIdUsers(const Users& users)
{
    unsigned maxId = users.user[0].id;
    for (size_t i = 0; i < users.numberOfUsers; i++)
    {
        if (maxId < users.user[i].id)
        {
            maxId = users.user[i].id;
        }

    }
    return maxId;
}

/*unsigned maxIdBlocks(const Blocks& blocks)
{
    unsigned maxId = blocks.block[0].id;
    for (size_t i = 0; i < blocks.numberOfBlocks; i++)
    {
        if (maxId < blocks.block[i].id)
        {
            maxId = blocks.block[i].id;
        }

    }
    return maxId;
}*/

unsigned generateIdUser(const Users& users)
{
    if (users.numberOfUsers == 0)
    {
        return 1;
    }
    else
    {
        return maxIdUsers(users) + 1;
    }
}

/*unsigned generateIdBlock(const Blocks& blocks)
{
    if (blocks.numberOfBlocks == 0)
    {
        return 1;
    }
    else
    {
        return maxIdBlocks(blocks) + 1;
    }
}*/

void initUser(const char userName[128], Users& users)
{
    if (users.numberOfUsers == users.currMax - 1)
    {
        User* temp = new User[users.currMax * 2];
        for (size_t i = 0; i < users.numberOfUsers; i++)
        {
            temp[i] = users.user[i];
        }
        delete[] users.user;
        users.user = temp;
        users.currMax = users.currMax * 2;
    }

    users.user[users.numberOfUsers].id = generateIdUser(users);
    strcpy(users.user[users.numberOfUsers].name, userName);
    users.numberOfUsers += 1;
}

bool writeUsers(const Users& users)
{
    std::ofstream file(USERS_FILE, std::ios::trunc | std::ios::out | std::ios::binary);
    if (!file.is_open())
    {
        cout << "Error: The users file did not open for writing." << endl;
        return false;
    }
    for (size_t i = 0; i < users.numberOfUsers; i++)
    {
        file.write((const char*)&users.user[i], sizeof(users.user[i]));
        if (file.fail())
        {
            cout << "Error: A write/read operation has failed." << endl;
            return false;
        }
    }
    file.close();
    return true;
}

bool createFile(const char* fileName)
{
    std::fstream file(fileName, std::ios::out);
    if (!file.is_open())
    {
        cout << "Error: The file did not create." << endl;
        return false;
    }
    file.close();
    return true;
}

bool readUsers(Users& users)
{
    std::ifstream file(USERS_FILE, std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        cout << "Error: The users file did not open for reading." << endl;
        return false;
    }
    users.numberOfUsers = fileSize(file) / sizeof(User);
    users.currMax = fileSize(file) / sizeof(User) * 2;
    users.user = new User[users.currMax];
    for (size_t i = 0; i < users.numberOfUsers; i++)
    {
        file.read((char*)&users.user[i], sizeof(users.user[i]));
        if (file.fail())
        {
            cout << "Error: A write/read operation has failed." << endl;
            return false;
        }
    }
    file.close();
    return true;
}

bool deleteUser(const char userName[128], Users& users)
{
    for (size_t i = 0; i < users.numberOfUsers; i++)
    {
        if (strcmp(users.user[i].name, userName) == 0)
        {
            users.user[i].id = users.user[users.numberOfUsers - 1].id;
            strcpy(users.user[i].name, users.user[users.numberOfUsers - 1].name);
            users.numberOfUsers -= 1;

            return true;
        }
    }
    return false;

}

void printUsers(const Users& users)
{
    cout << users.numberOfUsers << endl;
    cout << users.currMax << endl;
    for (size_t i = 0; i < users.numberOfUsers; i++)
    {
        cout << users.user[i].id << " " << users.user[i].name << endl;
    }

}

bool writeTransactionBlocks(const TransactionBlocks& transactionBlocks)
{
    std::ofstream file(BLOCKS_FILE, std::ios::trunc | std::ios::out | std::ios::binary);
    if (!file.is_open())
    {
        cout << "Error: The blocks file did not open for writing." << endl;
        return false;
    }
    for (size_t i = 0; i < transactionBlocks.numberOfTransactionBlocks; i++)
    {
        file.write((const char*)&transactionBlocks.transactionBlock[i], sizeof(transactionBlocks.transactionBlock[i]));
        if (file.fail())
        {
            cout << "Error: A write/read operation has failed." << endl;
            return false;
        }
    }
    file.close();
    return true;
}

bool readTransactionBlocks(TransactionBlocks& transactionBlocks)
{
    std::ifstream file(BLOCKS_FILE, std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        cout << "Error: The blocks file did not open for reading." << endl;
        return false;
    }
    transactionBlocks.numberOfTransactionBlocks = fileSize(file) / sizeof(TransactionBlock);
    transactionBlocks.currMax = (fileSize(file) / sizeof(TransactionBlock)) * 2;
    transactionBlocks.transactionBlock = new TransactionBlock[transactionBlocks.currMax];
    for (size_t i = 0; i < transactionBlocks.numberOfTransactionBlocks; i++)
    {
        file.read((char*)&transactionBlocks.transactionBlock[i], sizeof(transactionBlocks.transactionBlock[i]));
        if (file.fail())
        {
            cout << "Error: A write/read operation has failed." << endl;
            return false;
        }
    }
    file.close();
    return true;
}

void initTransactionBlock(const unsigned senderId, const unsigned recieverId, const double coins, TransactionBlocks& transactionBlocks)
{
    if (transactionBlocks.numberOfTransactionBlocks == transactionBlocks.currMax - 1)
    {
        TransactionBlock* temp = new TransactionBlock[transactionBlocks.currMax * 2];
        for (size_t i = 0; i < transactionBlocks.numberOfTransactionBlocks; i++)
        {
            temp[i] = transactionBlocks.transactionBlock[i];
        }
        delete[] transactionBlocks.transactionBlock;
        transactionBlocks.transactionBlock = temp;
        transactionBlocks.currMax = transactionBlocks.currMax * 2;
    }
    if (transactionBlocks.numberOfTransactionBlocks == 0)
    {
        transactionBlocks.numberOfTransactionBlocks += 1;
        transactionBlocks.transactionBlock[transactionBlocks.numberOfTransactionBlocks - 1].id = 1;
        transactionBlocks.transactionBlock[transactionBlocks.numberOfTransactionBlocks - 1].prevBlockId = 1;
    }
    else if (transactionBlocks.transactionBlock[transactionBlocks.numberOfTransactionBlocks - 1].validTransactions == 0)
    {
        cout << "here" << endl;
        transactionBlocks.transactionBlock[transactionBlocks.numberOfTransactionBlocks - 1].id = transactionBlocks.numberOfTransactionBlocks;
        transactionBlocks.transactionBlock[transactionBlocks.numberOfTransactionBlocks - 1].prevBlockId = transactionBlocks.transactionBlock[transactionBlocks.numberOfTransactionBlocks - 2].id;
        transactionBlocks.transactionBlock[transactionBlocks.numberOfTransactionBlocks - 1].prevBlockHash = computeHash((const unsigned char*)&transactionBlocks.transactionBlock[transactionBlocks.numberOfTransactionBlocks - 2], sizeof(transactionBlocks.transactionBlock[transactionBlocks.numberOfTransactionBlocks - 2]));
    }
    transactionBlocks.transactionBlock[transactionBlocks.numberOfTransactionBlocks - 1].transactions[transactionBlocks.transactionBlock[transactionBlocks.numberOfTransactionBlocks - 1].validTransactions].sender = senderId;
    transactionBlocks.transactionBlock[transactionBlocks.numberOfTransactionBlocks - 1].transactions[transactionBlocks.transactionBlock[transactionBlocks.numberOfTransactionBlocks - 1].validTransactions].receiver = recieverId;
    transactionBlocks.transactionBlock[transactionBlocks.numberOfTransactionBlocks - 1].transactions[transactionBlocks.transactionBlock[transactionBlocks.numberOfTransactionBlocks - 1].validTransactions].coins = coins;
    transactionBlocks.transactionBlock[transactionBlocks.numberOfTransactionBlocks - 1].transactions[transactionBlocks.transactionBlock[transactionBlocks.numberOfTransactionBlocks - 1].validTransactions].time = std::time(nullptr);
    transactionBlocks.transactionBlock[transactionBlocks.numberOfTransactionBlocks - 1].validTransactions += 1;
    if (transactionBlocks.transactionBlock[transactionBlocks.numberOfTransactionBlocks - 1].validTransactions == 16)
    {
        transactionBlocks.numberOfTransactionBlocks += 1;
    }
}

void systemTransactionBlockIn(const Users& users, TransactionBlocks& transansactions, const double coins)
{
    initTransactionBlock(0, users.user[users.numberOfUsers - 1].id, coins * 420, transansactions);
}

bool nameExist(const Users& users, const char name[128])
{
    for (size_t i = 0; i < users.numberOfUsers; i++)
    {
        if (strlen(name) == strlen(users.user[i].name))
        {
            if (strcmp(name, users.user[i].name) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

bool idExist(const Users& users, const unsigned id)
{
    for (size_t i = 0; i < users.numberOfUsers; i++)
    {
        if (users.user[i].id == id)
        {
            return true;
        }

    }
    return false;
}

double coinsName(const char name[128], const Users& users, const TransactionBlocks& transactionBlocks)
{
    double totalCoins = 0;
    unsigned deletedId;
    for (size_t i = 0; i < users.numberOfUsers; i++)
    {
        if (strcmp(name, users.user[i].name) == 0)
        {
            deletedId = users.user[i].id;
            break;
        }
    }
    for (size_t i = 0; i < transactionBlocks.numberOfTransactionBlocks; i++)
    {
        for (size_t j = 0; j < transactionBlocks.transactionBlock[i].validTransactions; j++)
        {
            if (deletedId == transactionBlocks.transactionBlock[i].transactions[j].sender)
            {
                totalCoins -= transactionBlocks.transactionBlock[i].transactions[j].coins;
            }
            else if (deletedId == transactionBlocks.transactionBlock[i].transactions[j].receiver)
            {
                totalCoins += transactionBlocks.transactionBlock[i].transactions[j].coins;
            }
        }
    }
    return totalCoins;
}

double coinsId(const unsigned id, const Users& users, const TransactionBlocks& transactionBlocks)
{
    double totalCoins = 0;
    for (size_t i = 0; i < transactionBlocks.numberOfTransactionBlocks; i++)
    {
        for (size_t j = 0; j < transactionBlocks.transactionBlock[i].validTransactions; j++)
        {
            if (id == transactionBlocks.transactionBlock[i].transactions[j].sender)
            {
                totalCoins -= transactionBlocks.transactionBlock[i].transactions[j].coins;
            }
            else if (id == transactionBlocks.transactionBlock[i].transactions[j].receiver)
            {
                totalCoins += transactionBlocks.transactionBlock[i].transactions[j].coins;
            }
        }
    }
    return totalCoins;
}

void systemTransactionBlockOut(const Users& users, TransactionBlocks& transactionBlocks, const double coins, const char name[128])
{
    unsigned deletedId;
    for (size_t i = 0; i < users.numberOfUsers; i++)
    {
        if (strcmp(name, users.user[i].name) == 0)
        {
            deletedId = users.user[i].id;
            break;
        }
    }
    initTransactionBlock(deletedId, 0, coins, transactionBlocks);
}

void printTransactionBlocks(const TransactionBlocks& transactionBlocks)
{
    cout << transactionBlocks.numberOfTransactionBlocks << endl;
    cout << transactionBlocks.currMax << endl;
    for (size_t i = 0; i < transactionBlocks.numberOfTransactionBlocks; i++)
    {
        cout << transactionBlocks.transactionBlock[i].id << " " << transactionBlocks.transactionBlock[i].prevBlockHash << " " << transactionBlocks.transactionBlock[i].prevBlockId << " " << transactionBlocks.transactionBlock[i].validTransactions << endl;
        for (size_t j = 0; j < transactionBlocks.transactionBlock[i].validTransactions; j++)
        {
            cout << transactionBlocks.transactionBlock[i].transactions[j].sender << " -> " << transactionBlocks.transactionBlock[i].transactions[j].receiver << " " << transactionBlocks.transactionBlock[i].transactions[j].coins << " coins at " << transactionBlocks.transactionBlock[i].transactions[j].time << endl;
        }

    }

}



bool wealthiestUsers(Users& users, const TransactionBlocks& transactions, const unsigned numberOfUsers)
{
    const int COMMAND_NAME_LENGTH = 16;
    const int FILE_EXTENSION_LENGTH = 4;

    time_t currTime = std::time(nullptr);
    int currTimeDigits = 1;
    time_t temp = currTime;
    while (temp > 9) {
        ++currTimeDigits
;
        temp /= 10;
    }

    char* currTimeAsString = new char[currTimeDigits + 1];
    currTimeAsString[currTimeDigits] = '\0';
    for (int i = currTimeDigits - 1; i >= 0; --i) {
        currTimeAsString[i] = (char)((currTime % 10) + '0');
        currTime /= 10;
    }

    char* fileName = new char[COMMAND_NAME_LENGTH + currTimeDigits + FILE_EXTENSION_LENGTH + 1];
    std::strcpy(fileName, "wealthiest-users");
    std::strcat(fileName, currTimeAsString);
    std::strcat(fileName, ".txt");
    delete[] currTimeAsString;
    Users sortedUsers;
    sortedUsers.currMax = users.currMax;
    sortedUsers.numberOfUsers = users.numberOfUsers;
    for (size_t i = 0; i < sortedUsers.numberOfUsers; i++)
    {
        sortedUsers.user[i].id = users.user[i].id;
        strcpy(sortedUsers.user[i].name, users.user[i].name);
    }
    for (size_t i = 0; i < users.numberOfUsers - 1; i++)
    {
        for (size_t j = 0; j < users.numberOfUsers - i - 1; j++)
        {
            if (coinsId(sortedUsers.user[j].id, users, transactions) < coinsId(sortedUsers.user[j + 1].id, users, transactions))
            {
                User temp;
                temp.id = sortedUsers.user[j].id;
                strcpy(temp.name, sortedUsers.user[j].name);
                sortedUsers.user[j].id = sortedUsers.user[j + 1].id;
                strcpy(sortedUsers.user[j].name, sortedUsers.user[j + 1].name);
                sortedUsers.user[j + 1].id = temp.id;
                strcpy(sortedUsers.user[j + 1].name, temp.name);
            }
        }
    }

    std::ofstream file(fileName);
    if (!file)
    {
        cout << "Error: The file did not open. errno=" << errno << endl;
        return false;
    }
    for (size_t i = 0; i < numberOfUsers; i++)
    {
        file << "hello" << endl;
    }
    file.close();
    return true;
}

void commandInterface(Users& users, TransactionBlocks& transactionBlocks)
{
    char command[20];
    do {
        cout << "Enter a valid command: ";
        cin >> command;
        if (strcmp(command, "create-user") == 0)
        {
            User user;
            char name[128];
            do
            {
                cout << "Name: ";
                cin >> name;
                if (nameExist(users, name))
                {
                    cout << "This username is already taken. Please try again." << endl;
                }
                else
                {
                    break;
                }
            } while (true);
            double sum;
            while (true)
            {
                cout << "Sum: ";
                if (!(cin >> sum))
                {
                    cin.clear();
                    cin.ignore(2147483647, '\n');
                    cout << "Please enter a numeric value!" << endl;
                }
                else if (sum < 0)
                {
                    cout << "Please enter a positive numeric value!" << endl;
                }
                else
                {
                    break;
                }
            }
            cin.clear();
            initUser(name, users);
            systemTransactionBlockIn(users, transactionBlocks, sum);
            cout << "The user has been created successfully." << endl;

        }
        else if (strcmp(command, "remove-user") == 0)
        {
            char name[128];
            do
            {
                cout << "Name: ";
                cin >> name;
                if (!nameExist(users, name))
                {
                    cout << "There is no user with that name." << endl;
                }
                else
                {
                    break;
                }
            } while (true);
            systemTransactionBlockOut(users, transactionBlocks, coinsName(name, users, transactionBlocks), name);
            deleteUser(name, users);
            cout << "The user has been deleted successfully." << endl;
        }
        else if (strcmp(command, "wealthiest-users") == 0)
        {
            unsigned numberOfUsers;
            while (true)
            {
                cout << "Number of users: ";
                if (!(cin >> numberOfUsers))
                {
                    cin.clear();
                    cin.ignore(2147483647, '\n');
                    cout << "Please enter a numeric value!" << endl;
                }
                else if (numberOfUsers < 0)
                {
                    cout << "Please enter a positive numeric value!" << endl;
                }
                else if (users.numberOfUsers < numberOfUsers)
                {
                    cout << "There are less than " << numberOfUsers << " users in the system. Please enter a numeric value smaller than " << users.numberOfUsers << "." << endl;
                }
                else
                {
                    break;
                }
            }
            wealthiestUsers(users, transactionBlocks, numberOfUsers);

        }
        else if (strcmp(command, "send-coins") == 0)
        {
            unsigned senderId;
            unsigned receiverId;
            do
            {
                cout << "Sender ID: ";
                if (!(cin >> senderId))
                {
                    cin.clear();
                    cin.ignore(2147483647, '\n');
                    cout << "Please enter a numeric value!" << endl;
                }
                cout << "Receiver ID: ";
                if (!(cin >> receiverId))
                {
                    cin.clear();
                    cin.ignore(2147483647, '\n');
                    cout << "Please enter a numeric value!" << endl;
                }
                if (senderId == receiverId)
                {
                    cout << "Users can not send coins to themselves. Please try again." << endl;
                }
                else if (!idExist(users, senderId) || !idExist(users, receiverId))
                {
                    cout << "The IDs you entered do not match any of the existing users IDs. Please try again." << endl;
                }
                else
                {
                    break;
                }
            } while (true);
            double coins;
            do
            {
                while (true)
                {
                    cout << "Amount: ";
                    if (!(cin >> coins))
                    {
                        cin.clear();
                        cin.ignore(2147483647, '\n');
                        cout << "Please enter a numeric value!" << endl;
                    }
                    else if (coins < 0)
                    {
                        cout << "Please enter a positive numeric value!" << endl;
                    }
                    else
                    {
                        break;
                    }
                }
                if (coinsId(senderId, users, transactionBlocks) < coins)
                {
                    cout << "The sender does not have enoug coins. Please try again." << endl;
                }
                else
                {
                    cout << "The transaction was successful." << endl;
                    break;
                }
            } while (true);

            initTransactionBlock(senderId, receiverId, coins, transactionBlocks);
        }
    } while (strcmp(command, "exit") != 0);
}

void verifyTransactions(const TransactionBlocks& transactions)
{
    for (size_t i = transactions.numberOfTransactionBlocks - 1; i >= 0; i--)
    {
        if (transactions.transactionBlock[i].prevBlockHash != computeHash((const unsigned char*)&transactions.transactionBlock[transactions.transactionBlock[i].prevBlockId], sizeof(transactions.transactionBlock[transactions.transactionBlock[i].prevBlockId])))
        {
            cout << "Block number " << transactions.transactionBlock[i].prevBlockId << " is out of the chain" << endl;
        }
    }

}

int main()
{
    Users systemUsers;
    TransactionBlocks transactions;
    std::ifstream fileUsers;
    fileUsers.open(USERS_FILE);
    if (!fileUsers)
    {
        createFile(USERS_FILE);
    }
    else
    {
        readUsers(systemUsers);
    }

    std::ifstream fileBlocks;
    fileBlocks.open(BLOCKS_FILE);
    if (!fileBlocks)
    {
        createFile(BLOCKS_FILE);
    }
    else
    {
        readTransactionBlocks(transactions);
    }
    commandInterface(systemUsers, transactions);

    writeUsers(systemUsers);
    writeTransactionBlocks(transactions);

    printUsers(systemUsers);
    printTransactionBlocks(transactions);

    freeUsers(systemUsers);
    freeTransactionBlocks(transactions);
}