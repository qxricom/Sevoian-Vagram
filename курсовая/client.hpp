#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "entity.hpp"
#include "entity_vector.hpp" 
#include "wallet.hpp"

class Client : public Entity {
protected:
    string name;
    Entityvector wallets;
public:
    Client(string id, string name);
    virtual ~Client();
    void addWallet(shared_ptr<Wallet> wallet);
    double getTotalBalance() const;
    virtual double calculateCommission(double amount) const = 0;
    virtual double getMaxTransactionLimit() const = 0;
    
    // Этот метод уже существует и возвращает const vector<shared_ptr<Entity>>&
    const vector<shared_ptr<Entity>>& getWallets() const;

    const Entityvector& getWalletsObject() const { return wallets; }

    string getId() const override;
    string getName() const;
};

#endif
