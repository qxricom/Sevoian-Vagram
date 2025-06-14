#include "client.hpp"
#include "wallet.hpp"
#include <iostream>
#include <memory>

using namespace std;

// Конструктор класса Client
// Инициализирует идентификатор через базовый класс Entity и задает имя клиента
Client::Client(string id, string name) : Entity(id), name(name) {}

// Деструктор класса Client
Client::~Client() {}

// Метод добавления кошелька клиенту
// Если передан недопустимый указатель, выводит ошибку
void Client::addWallet(shared_ptr<Wallet> wallet) {
    if (!wallet) {
        cerr << "Попытка добавить nullptr кошелек\n";
        return;
    }
    // Добавляет кошелек в коллекцию wallets (EntityVector)
    wallets.addEntity(wallet);
}

// Возвращает ссылку на вектор указателей всех кошельков клиента
const vector<shared_ptr<Entity>>& Client::getWallets() const {
    return wallets.getAllEntities();
}

// Вычисляет и возвращает общий баланс всех кошельков клиента
double Client::getTotalBalance() const {
    double totalBalance = 0.0;
    const vector<shared_ptr<Entity>>& allWallets = wallets.getAllEntities();//Получаем все сущности из wallets — контейнера, который хранит shared_ptr<Entity>.
    for (const auto& walletEntity : allWallets) {
        // Преобразует Entity в Wallet и суммирует баланс, если успешно
        shared_ptr<Wallet> wallet = dynamic_pointer_cast<Wallet>(walletEntity);
        if (wallet) {
            totalBalance += wallet->getBalance();
        }
    }
    return totalBalance;
}

// Геттер для ID клиента
string Client::getId() const { return id; }

// Геттер для имени клиента
string Client::getName() const { return name; }
