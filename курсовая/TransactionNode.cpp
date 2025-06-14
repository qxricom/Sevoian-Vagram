
#include "TransactionNode.hpp"

TransactionNode::TransactionNode(Transaction* data) : data(data), prev(nullptr), next(nullptr) {}

TransactionNode::~TransactionNode() {
    delete data;// освобождаем память
    data = nullptr;//обнуляем переменную для безопасного деструктора
}
