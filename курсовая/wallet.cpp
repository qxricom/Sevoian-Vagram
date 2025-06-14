#include <iostream>
#include "wallet.hpp"
#include <string>

using namespace std;

// Конструктор кошелька: принимает ID кошелька, ID владельца и начальный баланс
Wallet::Wallet(string id, string ownerId, double balance)
    : Entity(id), balance(balance), ownerId(ownerId) {}

// Метод пополнения баланса
void Wallet::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    } else {
        cerr << "Предупреждение: Попытка внести неположительную сумму." << endl;
    }
}

// Метод снятия средств с баланса
bool Wallet::withdraw(double amount) {
    if (amount > 0 && balance >= amount) {
        balance -= amount;
        return true;
    } else {
        cerr << "Ошибка: Невозможно снять " << amount << ". Текущий баланс: " << balance << endl;
    }
    return false;
}

// Получить текущий баланс кошелька
double Wallet::getBalance() const {
    return balance;
}

// Получить ID кошелька
string Wallet::getId() const {
    return id;
}

// Получить ID владельца кошелька
string Wallet::getOwnerId() const {
    return ownerId;
}
