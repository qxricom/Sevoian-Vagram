#include "client_bst.hpp"
#include <iostream>

// Конструктор — инициализирует корень дерева как пустой
ClientBST::ClientBST() : root(nullptr) {}

// Деструктор — освобождает всю память дерева
ClientBST::~ClientBST() {
    clearHelper(root);
}

// Рекурсивная функция удаления всех узлов дерева
void ClientBST::clearHelper(ClientNode* node) {
    if (node) {
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
    }
}

// Вставка клиента в дерево
void ClientBST::insert(shared_ptr<Client> client) {
    if (!client) return;
    insertHelper(root, client);
}

// Рекурсивная вставка в дерево поиска по ID клиента
void ClientBST::insertHelper(ClientNode*& node, shared_ptr<Client> client) {
    if (!node) {
        node = new ClientNode(client);  // Создаем новый узел
    } else if (client->getId() < node->data->getId()) {
        insertHelper(node->left, client);  // Идем влево
    } else if (client->getId() > node->data->getId()) {
        insertHelper(node->right, client);  // Идем вправо
    }
    // Если ID уже есть — ничего не делаем (можно было бы обновлять данные)
}

// Поиск клиента по ID
shared_ptr<Client> ClientBST::find(const string& id) const {
    ClientNode* found = findHelper(root, id);
    return found ? found->data : nullptr;
}

// Рекурсивный поиск узла по ID
ClientNode* ClientBST::findHelper(ClientNode* node, const string& id) const {
    if (!node) return nullptr;
    if (id == node->data->getId()) return node;
    if (id < node->data->getId()) return findHelper(node->left, id);
    return findHelper(node->right, id);
}

// Получение всех клиентов в отсортированном порядке (по ID)
vector<shared_ptr<Client>> ClientBST::getAllClients() const {
    vector<shared_ptr<Client>> result;
    inOrderHelper(root, result);
    return result;
}

// Обход дерева in-order (слева — корень — справа)
void ClientBST::inOrderHelper(ClientNode* node, vector<shared_ptr<Client>>& result) const {
    if (node) {
        inOrderHelper(node->left, result);
        result.push_back(node->data);
        inOrderHelper(node->right, result);
    }
}

// Отображение клиентов по возрастанию ID
void ClientBST::displayInOrder() const {
    cout << "--- Клиенты (отсортировано по ID) ---" << endl;
    vector<shared_ptr<Client>> clients = getAllClients();
    for (const auto& client : clients) {
        cout << "ID: " << client->getId()
             << ", Имя: " << client->getName()
             << ", Баланс: " << client->getTotalBalance() << endl;
    }
    cout << "-------------------------------------" << endl;
}

// Поиск минимального узла в поддереве (используется при удалении)
ClientNode* ClientBST::findMin(ClientNode* node) const {
    while (node && node->left) {//пока узел существует и у него есть левый потомок, идём влево.

        node = node->left;//двигаемся к левому потомку.
    }
    return node;
}

// Удаление клиента по ID
bool ClientBST::remove(const string& id) {
    if (!findHelper(root, id)) {
        return false;  // Клиент не найден
    }
    root = removeHelper(root, id);//фактическое удаление узла с заданным id.
    // новый корень дерева
    return true;
}

// Рекурсивное удаление узла
ClientNode* ClientBST::removeHelper(ClientNode* node, const string& id) {
    if (!node) return nullptr;
//Если id меньше текущего node->data->getId() — идём в левое поддерево.
    if (id < node->data->getId()) {
        node->left = removeHelper(node->left, id);  // Идем влево
    } else if (id > node->data->getId()) {
        node->right = removeHelper(node->right, id);  // Идем вправо
    } else {
        // Найден узел, который нужно удалить

        // Случай: один потомок или ни одного
        if (!node->left) {
            ClientNode* temp = node->right;
            delete node;
            return temp;
        } else if (!node->right) {
            ClientNode* temp = node->left;
            delete node;
            return temp;
        }

        // Случай: два потомка
        ClientNode* temp = findMin(node->right);  // Минимум из правого поддерева
        node->data = temp->data;  // Копируем данные
        node->right = removeHelper(node->right, temp->data->getId());  // Удаляем дубль
    }
    return node;
}
//ClientNode* — это указатель на узел.
//Функция removeHelper удаляет узел с заданным ID из дерева клиентов.
