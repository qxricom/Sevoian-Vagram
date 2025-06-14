#ifndef CLIENT_BST_HPP
#define CLIENT_BST_HPP

#include <string>
#include <memory>
#include <vector>
#include "client.hpp"
#include "client_node.hpp"

using namespace std;

class ClientBST {
private:
    ClientNode* root;
    
    void insertHelper(ClientNode*& node, shared_ptr<Client> client);
    ClientNode* findHelper(ClientNode* node, const string& id) const;
    void inOrderHelper(ClientNode* node, vector<shared_ptr<Client>>& result) const;
    void clearHelper(ClientNode* node);
    ClientNode* findMin(ClientNode* node) const;
    ClientNode* removeHelper(ClientNode* node, const string& id);

public:
    ClientBST();
    ~ClientBST();

    void insert(shared_ptr<Client> client);
    bool remove(const string& id);
    void displayInOrder() const;
    vector<shared_ptr<Client>> getAllClients() const;
    shared_ptr<Client> find(const string& id) const;
};

#endif
