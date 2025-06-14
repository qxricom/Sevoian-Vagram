#include "transaction_list.hpp"
#include <iostream>
#include <string>

using namespace std;

// Конструктор по умолчанию
TransactionList::TransactionList() : head(nullptr), tail(nullptr), size(0) {}

// Деструктор — очищает весь список транзакций
TransactionList::~TransactionList() {
    TransactionNode* current = head;
    while (current != nullptr) {
        TransactionNode* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

// Добавить транзакцию в конец списка
void TransactionList::addTransaction(Transaction* tx) {
    if (!tx) {
        cerr << "Ошибка: Попытка добавить нулевую транзакцию" << endl;
        return;
    }
    TransactionNode* newNode = new TransactionNode(tx);
    if (!head) {
        head = tail = newNode; // если список пуст, новый узел становится первым и последним
    } else {
        newNode->prev = tail;  // связываем с предыдущим последним узлом
        tail->next = newNode;
        tail = newNode;        // обновляем хвост
    }
    size++;
}

// Удалить транзакцию по ID
bool TransactionList::removeTransaction(const string& id) {
    TransactionNode* current = head;
    while (current != nullptr) {
        if (current->data && current->data->getId() == id) {
            // Обновляем связи соседних узлов
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }
            delete current;
            size--;
            return true;
        }
        current = current->next;
    }
    return false; // транзакция не найдена
}

// Получить транзакцию по ID
Transaction* TransactionList::getTransaction(const string& id) const {
    TransactionNode* current = head;
    while (current != nullptr) {
        if (current->data && current->data->getId() == id) {
            return current->data;
        }
        current = current->next;
    }
    return nullptr;
}

// Отобразить все транзакции
void TransactionList::displayTransaction() const {
    cout << "--- Транзакции ---" << endl;
    TransactionNode* current = head;
    if (!current) {
        cout << "Транзакции отсутствуют." << endl;
    }
    while (current != nullptr) {
        if (current->data) {
            cout << current->data->getDetails() << endl;
        }
        current = current->next;
    }
    cout << "------------------" << endl;
}

// Получить количество транзакций
int TransactionList::getSize() const {
    return size;
}
