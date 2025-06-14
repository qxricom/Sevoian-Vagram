#include "transaction.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

// Конструктор транзакции
Transaction::Transaction(string id, string senderWalletId, string receiveWalletId, double amount, Txtype type, double commission)
    : Entity(id), senderWalletId(senderWalletId), receiveWalletId(receiveWalletId), amount(amount), type(type), commission(commission) {}

// Получить ID транзакции
string Transaction::getId() const {
    return id;
}

// Получить подробности транзакции в виде строки
string Transaction::getDetails() const {
    stringstream ss;
    ss << "ID транзакции: " << id
       << ", Отправитель: " << senderWalletId
       << ", Получатель: " << receiveWalletId
       << ", Сумма: " << fixed << setprecision(2) << amount
       << ", Тип: ПЕРЕВОД"
       << ", Комиссия: " << fixed << setprecision(2) << commission;
    return ss.str();
}

// Получить ID кошелька отправителя
string Transaction::getSenderWalletId() const {
    return senderWalletId;
}

// Получить ID кошелька получателя
string Transaction::getReceiveWalletId() const {
    return receiveWalletId;
}

// Получить сумму перевода
double Transaction::getAmount() const {
    return amount;
}

// Получить тип транзакции
Txtype Transaction::getType() const {
    return type;
}

// Получить размер комиссии
double Transaction::getCommission() const {
    return commission;
}
