#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
#include "entity.hpp"

using namespace std;

enum class Txtype {
    TRANSFER
};

class Transaction : public Entity {
private:
    string senderWalletId;
    string receiveWalletId;
    double amount;
    Txtype type;
    double commission;

public:
    Transaction(string id, string senderWalletId, string receiveWalletId, double amount, Txtype type, double commission);
    string getId() const override;
    string getDetails() const; // Corrected typo from getDetailes
    string getSenderWalletId() const;
    string getReceiveWalletId() const;
    double getAmount() const;
    Txtype getType() const;
    double getCommission() const;
    ~Transaction() override {}
};

#endif
