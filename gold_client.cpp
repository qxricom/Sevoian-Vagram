#include "gold_client.hpp"
#include <string>

using namespace std;

GoldClient::GoldClient(string id, string name) : Client(id, name) {}

double GoldClient::calculateCommission(double amount) const {
    return amount * 0.01; // 1% commission
}

double GoldClient::getMaxTransactionLimit() const {
    return 10000.0;
}

string GoldClient::getBenefits() const {
    return "Приоритетная обработка, низкие комиссии";
}
