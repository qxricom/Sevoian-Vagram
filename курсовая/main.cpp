#include <iostream>
#include <memory>
#include "blockchain.hpp"
#include "gold_client.hpp"
#include "platinum_client.hpp"
#include "standard_client.hpp"
#include "wallet.hpp"

using namespace std;

// Функция для отображения главного меню
void showMenu() {
    cout << "\n===== БЛОКЧЕЙН СИСТЕМА =====" << endl;
    cout << "1. Добавить клиента" << endl;
    cout << "2. Добавить кошелек клиенту" << endl;
    cout << "3. Выполнить транзакцию" << endl;
    cout << "4. Показать всех клиентов" << endl;
    cout << "5. Показать все транзакции" << endl;
    cout << "6. Удалить транзакцию" << endl;
    cout << "7. Сохранить данные в файлы" << endl;
    cout << "8. Выйти" << endl;
    cout << "Выберите действие: ";
}
int main() {
    Blockchain blockchain;
    // Загрузка клиентов и транзакций из файлов при запуске программы
    blockchain.loadClientsFromFile("Clients.txt");
    blockchain.loadTransactionsFromFile("Blockchain_transactions.txt");

    int choice;
    do {
        showMenu();        // Показать меню
        cin >> choice;     // Ввод выбора пользователя

        switch (choice) {
            case 1: {  // Добавить клиента
                string id, name, type;
                cout << "Введите ID клиента: ";
                cin >> id;
                cout << "Введите имя клиента: ";
                cin.ignore(); // Очистка буфера после cin
                getline(cin, name);
                cout << "Тип клиента (gold/platinum/standard): ";
                cin >> type;

                shared_ptr<Client> client;
                if (type == "gold") {
                    client = make_shared<GoldClient>(id, name);
                } else if (type == "platinum") {
                    client = make_shared<PlatinumClient>(id, name);
                } else if (type == "standard") {
                    client = make_shared<StandardClient>(id, name);
                } else {
                    cout << "Неизвестный тип клиента." << endl;
                    break;
                }

                blockchain.addClient(client);
                cout << "Клиент добавлен." << endl;
                break;
            }

            case 2: {  // Добавить кошелек клиенту
                string clientId, walletId;
                double balance;
                cout << "Введите ID клиента: ";
                cin >> clientId;
                cout << "Введите ID кошелька: ";
                cin >> walletId;
                cout << "Введите начальный баланс: ";
                cin >> balance;

                shared_ptr<Client> client = blockchain.findClient(clientId);
                if (!client) {
                    cout << "Клиент не найден." << endl;
                    break;
                }

                shared_ptr<Wallet> wallet = make_shared<Wallet>(walletId, clientId, balance);
                client->addWallet(wallet);
                cout << "Кошелек добавлен." << endl;
                break;
            }

            case 3: {  // Выполнить транзакцию
                string senderClientId, senderWalletId, receiverClientId, receiverWalletId;
                double amount;

                cout << "ID клиента-отправителя: ";
                cin >> senderClientId;
                cout << "ID кошелька отправителя: ";
                cin >> senderWalletId;
                cout << "ID клиента-получателя: ";
                cin >> receiverClientId;
                cout << "ID кошелька получателя: ";
                cin >> receiverWalletId;
                cout << "Сумма транзакции: ";
                cin >> amount;

                blockchain.processTransaction(senderClientId, senderWalletId,
                                              receiverClientId, receiverWalletId, amount);
                break;
            }

            case 4:  // Показать всех клиентов
                blockchain.displayClients();
                break;

            case 5:  // Показать все транзакции
                blockchain.displayTransactions();
                break;

            case 6: { // Удалить транзакцию
                string transactionId;
                cout << "Введите ID транзакции для удаления: ";
                cin >> transactionId;
                blockchain.removeTransaction(transactionId);
                break;
            }

            case 7:  // Сохранить данные в файлы
                blockchain.saveClientsToFile("Clients.txt");
                blockchain.saveTransactionsToFile("Blockchain_transactions.txt");
                cout << "Данные сохранены в файлы." << endl;
                break;

            case 8:  // Выйти из программы
                cout << "Выход..." << endl;
                break;

            default:  // Неверный ввод
                cout << "Неверный выбор. Попробуйте снова." << endl;
        }

    } while (choice != 8);  // Повторять, пока пользователь не выберет "Выйти"

    return 0;
}
