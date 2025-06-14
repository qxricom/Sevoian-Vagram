// Подключение необходимых заголовочных файлов и пространств имен
#include "Blockchain.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <memory>

using namespace std;

// Конструктор и деструктор класса Blockchain
Blockchain::Blockchain() {}
Blockchain::~Blockchain() {}

// Добавление клиента в блокчейн
void Blockchain::addClient(shared_ptr<Client> client) {clients.insert(client);}

// Поиск клиента по его ID
shared_ptr<Client> Blockchain::findClient(const string& clientId) const {
    return clients.find(clientId); // из client_bst.hpp
}

// Поиск кошелька по его ID для заданного клиента
shared_ptr<Wallet> Blockchain::findWallet(const string& walletId, const Client* client) const {
    if (client) {
        // Получение объекта EntityVector и извлечение из него сущности-кошелька
        shared_ptr<Entity> walletEntity = client->getWalletsObject().getEntity(walletId);//получение сущности (Entity) с данным ID из кошельков клиента
        return dynamic_pointer_cast<Wallet>(walletEntity);//динамическое приведение walletEntity
    }
    return nullptr;
}

// Обработка транзакции между двумя кошельками
bool Blockchain::processTransaction(const string& senderClientId, const string& senderWalletId,const string& receiverClientId, const string& receiverWalletId,double amount) {
    // Поиск клиентов отправителя и получателя
    shared_ptr<Client> senderClient = findClient(senderClientId);
    shared_ptr<Client> receiverClient = findClient(receiverClientId);

    if (!senderClient || !receiverClient) {
        cout << "Ошибка: Клиент-отправитель или клиент-получатель не найден." << endl;
        return false;
    }

    // Поиск кошельков отправителя и получателя
    shared_ptr<Wallet> senderWallet = findWallet(senderWalletId, senderClient.get());
    shared_ptr<Wallet> receiverWallet = findWallet(receiverWalletId, receiverClient.get());

    if (!senderWallet || !receiverWallet) {
        cout << "Ошибка: Кошелек отправителя или получателя не найден." << endl;
        return false;
    }

    // Проверка баланса отправителя
    if (senderWallet->getBalance() < amount) {
        cout << "Ошибка: Недостаточно средств в кошельке отправителя." << endl;
        return false;
    }

    // Расчет комиссии и проверка остатка после нее
    double commission = senderClient->calculateCommission(amount);
    double totalDeduction = amount + commission;

    if (senderWallet->getBalance() < totalDeduction) {
        cout << "Ошибка: Недостаточно средств для транзакции и комиссии." << endl;
        return false;
    }

    // Проверка лимита транзакции
    if (amount > senderClient->getMaxTransactionLimit()) {
        cout << "Ошибка: Сумма транзакции превышает лимит для отправителя." << endl;
        return false;
    }

    // Создание и регистрация транзакции
    stringstream ss;
    ss << "tx_" << transactions.getSize() + 1;
    Transaction* newTransaction = new Transaction(
        ss.str(), senderWalletId, receiverWalletId, amount, Txtype::TRANSFER, commission);

    // Списание и зачисление средств
    senderWallet->withdraw(totalDeduction);
    receiverWallet->deposit(amount);
    transactions.addTransaction(newTransaction);

    cout << "Транзакция успешно выполнена. ID: " << newTransaction->getId()
         << ", Сумма: " << amount << ", Комиссия: " << commission << endl;
    return true;
}

// Отображение информации о клиентах и их кошельках
void Blockchain::displayClients() const {
    cout << "\n=== Детальная информация о клиентах ===" << endl;
    const vector<shared_ptr<Client>>& allClients = clients.getAllClients();
    
    for (const auto& client : allClients) {
        cout << "\nКлиент ID: " << client->getId()
             << "\nИмя: " << client->getName()
             << "\nОбщий баланс: " << fixed << setprecision(2) << client->getTotalBalance()
             << "\nЛимит транзакций: " << client->getMaxTransactionLimit()
             << "\nКошельки:";

        const vector<shared_ptr<Entity>>& wallets = client->getWallets();
        if (wallets.empty()) {
            cout << "\n  Нет кошельков" << endl;
        } else {
            for (const auto& walletEntity : wallets) {
                shared_ptr<Wallet> wallet = dynamic_pointer_cast<Wallet>(walletEntity);
                if (wallet) {
                    cout << "\n  ID: " << wallet->getId()
                         << ", Баланс: " << fixed << setprecision(2) << wallet->getBalance();
                }	
            }
            cout << endl;
        }
        cout << "-----------------------------------" << endl;
    }
}

// Отображение всех транзакций
void Blockchain::displayTransactions() const {
    transactions.displayTransaction();
}

// Сохранение клиентов и их кошельков в файл
void Blockchain::saveClientsToFile(const string& filename) const {
    ofstream file(filename);
    if (!file) {
        cerr << "Ошибка записи в файл: " << filename << endl;
        return;
    }

    vector<shared_ptr<Client>> allClients = clients.getAllClients();
    for (const auto& client : allClients) {
        file << client->getId() << endl;
        file << client->getName() << endl;
    }

    file.close();
}

// Загрузка клиентов и их кошельков из файла
void Blockchain::loadClientsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return;
    }

    clients = ClientBST(); // Очистка дерева клиентов

    string id, name, type;
    while (file >> id) {
        file.ignore(); // Пропустить пробел или символ переноса
        getline(file, name); // Имя может содержать пробелы
        file >> type;

        shared_ptr<Client> client;
        if (type == "gold") {
            client = make_shared<GoldClient>(id, name);
        } else if (type == "platinum") {
            client = make_shared<PlatinumClient>(id, name);
        } else if (type == "standard") {
            client = make_shared<StandardClient>(id, name);
        }

        if (client) {
            clients.insert(client);
        }

        file.ignore(numeric_limits<streamsize>::max(), '\n'); // Пропустить лишнее
    }

    file.close();
}


// Загрузка транзакций из файла
void Blockchain::loadTransactionsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка открытия файла транзакций: " << filename << endl;
        return;
    }

    // Очистить текущие транзакции
    transactions = TransactionList();

    string id, senderId, receiverId;
    double amount, commission;
    int typeInt;

    while (getline(file, id)) {
        getline(file, senderId);
        getline(file, receiverId);
        file >> amount;
        file >> typeInt;
        file >> commission;
        file.ignore(); // Пропустить символ новой строки после числа

        Transaction* tx = new Transaction(id, senderId, receiverId, amount, static_cast<Txtype>(typeInt), commission);
        transactions.addTransaction(tx);
    }

    file.close();
}


// Сохранение транзакций в файл
void Blockchain::saveTransactionsToFile(const string& filename) const {
    ofstream file(filename);
    if (!file) {
        cerr << "Ошибка записи в файл транзакций: " << filename << endl;
        return;
    }

    TransactionNode* current = transactions.getHead(); // Предположим, доступ к head открыт через геттер
    while (current) {
        Transaction* tx = current->data;
        if (tx) {
            file << tx->getId() << endl;
            file << tx->getSenderWalletId() << endl;
            file << tx->getReceiveWalletId() << endl;
            file << tx->getAmount() << endl;
            file << static_cast<int>(tx->getType()) << endl;
            file << tx->getCommission() << endl;
        }
        current = current->next;
    }

    file.close();
}


// Удаление транзакции и откат её последствий
bool Blockchain::removeTransaction(const string& transactionId) {
    Transaction* tx = transactions.getTransaction(transactionId);
    if (!tx) {
        cout << "Транзакция с ID " << transactionId << " не найдена." << endl;
        return false;
    }

    // Найти отправителя и получателя по их кошелькам
    shared_ptr<Client> senderClient = findClientByWalletId(tx->getSenderWalletId());
    shared_ptr<Client> receiverClient = findClientByWalletId(tx->getReceiveWalletId());

    // Возврат средств
    if (senderClient && receiverClient) {
        shared_ptr<Wallet> senderWallet = findWallet(tx->getSenderWalletId(), senderClient.get());
        shared_ptr<Wallet> receiverWallet = findWallet(tx->getReceiveWalletId(), receiverClient.get());

        if (senderWallet && receiverWallet) {
            senderWallet->deposit(tx->getAmount() + tx->getCommission());
            if (!receiverWallet->withdraw(tx->getAmount())) {
                cout << "Ошибка: Недостаточно средств у получателя для отмены транзакции." << endl;
                return false;
            }
        }
    }

    // Удаление транзакции из истории
    bool success = transactions.removeTransaction(transactionId);
    if (success) {
        cout << "Транзакция " << transactionId << " успешно удалена и отменена." << endl;
    }
    return success;
}

// Поиск клиента по ID кошелька
shared_ptr<Client> Blockchain::findClientByWalletId(const string& walletId) const {
    const vector<shared_ptr<Client>>& allClients = clients.getAllClients();
    for (const auto& client : allClients) {
        const vector<shared_ptr<Entity>>& wallets = client->getWallets();
        for (const auto& wallet : wallets) {
            if (wallet->getId() == walletId) {
                return client;
            }
        }
    }
    return nullptr;
}
