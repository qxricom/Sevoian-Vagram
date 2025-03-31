// main.cpp
#include "warehouse.hpp"
#include <iostream>
#include <limits>
#include <vector> // Include for std::vector

// Функция для создания нового продукта
Product createNewProduct() {
    std::string description;
    double price;
    int quantity;
    double shipmentLatitude;
    double shipmentLongitude;

    std::cout << "Введите описание продукта (не более 50 символов): ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, description);

    std::cout << "Введите цену продукта (в рублях): ";
    while (!(std::cin >> price)) {
        std::cout << "Ошибка: Введите числовое значение для цены: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Введите количество продукта: ";
    while (!(std::cin >> quantity)) {
        std::cout << "Ошибка: Введите целое число для количества: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Введите широту отгрузки (41-82): ";
    while (!(std::cin >> shipmentLatitude) || shipmentLatitude < 41.0 || shipmentLatitude > 82.0) {
        std::cout << "Ошибка: Введите числовое значение для широты в диапазоне [41, 82]: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Введите долготу отгрузки (19-169): ";
    while (!(std::cin >> shipmentLongitude) || shipmentLongitude < 19.0 || shipmentLongitude > 169.0) {
        std::cout << "Ошибка: Введите числовое значение для долготы в диапазоне [19, 169]: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return Product(description, price, quantity, shipmentLatitude, shipmentLongitude);
}

// Функция для выбора склада с минимальным манхэттенским расстоянием
Warehouse* findNearestWarehouse(const std::vector<Warehouse>& warehouses, double productLatitude, double productLongitude) {
    if (warehouses.empty()) {
        return nullptr;
    }

    Warehouse* nearestWarehouse = const_cast<Warehouse*>(&warehouses[0]);
    double minDistance = nearestWarehouse->calculateManhattanDistance(productLatitude, productLongitude);

    for (size_t i = 1; i < warehouses.size(); ++i) {
        double distance = warehouses[i].calculateManhattanDistance(productLatitude, productLongitude);
        if (distance < minDistance) {
            minDistance = distance;
            nearestWarehouse = const_cast<Warehouse*>(&warehouses[i]);
        }
    }
    return nearestWarehouse;
}

void warehouseMenu(Warehouse& warehouse) {
    int choice;
    do {
        std::cout << "\nМеню склада " << warehouse.getId() << " (" << warehouse.getType() << "):" << std::endl;
        std::cout << "1. Вставить продукт" << std::endl;
        std::cout << "2. Список продуктов" << std::endl;
        std::cout << "3. Поиск продукта по описанию" << std::endl;
        std::cout << "4. Удалить продукт" << std::endl;
        std::cout << "0. Назад в главное меню" << std::endl;
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                Product newProduct = createNewProduct();
                warehouse.addProduct(newProduct);
                break;
            }
            case 2:
                warehouse.listProducts();
                break;
            case 3: {
                std::string description;
                std::cout << "Введите описание для поиска: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, description);
                warehouse.searchProduct(description);
                break;
            }
            case 4: {
                std::string descriptionToRemove;
                int quantityToRemove;
                std::cout << "Введите описание продукта для удаления: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, descriptionToRemove);
                std::cout << "Введите количество для удаления: ";
                std::cin >> quantityToRemove;
                warehouse.removeProduct(descriptionToRemove, quantityToRemove);
                break;
            }
            case 0:
                std::cout << "Возврат в главное меню." << std::endl;
                break;
            default:
                std::cout << "Некорректный выбор. Попробуйте снова." << std::endl;
        }
    } while (choice != 0);
}

int main() {
    // Пример использования:
    Warehouse centralWarehouse(WarehouseType::CENTER, 55.75, 37.61, 1000);
    Warehouse westWarehouse(WarehouseType::WEST, 55.75, 30.00, 800);
    Warehouse eastWarehouse(WarehouseType::EAST, 55.75, 45.00, 900);

    std::vector<Warehouse> warehouses = {centralWarehouse, westWarehouse, eastWarehouse};

    int mainChoice;
    do {
        std::cout << "\nГлавное меню:" << std::endl;
        std::cout << "1. Управление центральным складом" << std::endl;
        std::cout << "2. Управление западным складом" << std::endl;
        std::cout << "3. Управление восточным складом" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Выберите склад для управления: ";
        std::cin >> mainChoice;

        switch (mainChoice) {
            case 1:
                warehouseMenu(centralWarehouse);
                break;
            case 2:
                warehouseMenu(westWarehouse);
                break;
            case 3:
                warehouseMenu(eastWarehouse);
                break;
            case 0:
                std::cout << "Выход из программы." << std::endl;
                break;
            default:
                std::cout << "Некорректный выбор. Попробуйте снова." << std::endl;
        }
    } while (mainChoice != 0);

    return 0;
}
