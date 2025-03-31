

#include "warehouse.hpp"

// warehouse.cpp
#include <cmath>
#include <algorithm>

int Warehouse::nextWarehouseCode = 100;

std::ostream& operator<<(std::ostream& os, const WarehouseType& type) {
    switch (type) {
        case WarehouseType::CENTER:
            os << "Центр";
            break;
        case WarehouseType::WEST:
            os << "Запад";
            break;
        case WarehouseType::EAST:
            os << "Восток";
            break;
        default:
            os << "Неизвестно";
            break;
    }
    return os;
}

// Реализация класса Product
Product::Product() : barcode(generateBarcode()), description(""), price(0.0), quantity(0), shipmentLatitude(0.0), shipmentLongitude(0.0) {}

Product::Product(const std::string& description, double price, int quantity, double shipmentLatitude, double shipmentLongitude)
    : barcode(generateBarcode()), description(description.substr(0, 50)), price(price), quantity(quantity), shipmentLatitude(shipmentLatitude), shipmentLongitude(shipmentLongitude) {}

Product::Product(const Product& other) : barcode(other.barcode), description(other.description), price(other.price), quantity(other.quantity), shipmentLatitude(other.shipmentLatitude), shipmentLongitude(other.shipmentLongitude) {}

std::string Product::getBarcode() const {
    return barcode;
}

std::string Product::getDescription() const {
    return description;
}

double Product::getPrice() const {
    return price;
}

int Product::getQuantity() const {
    return quantity;
}

double Product::getShipmentLatitude() const {
    return shipmentLatitude;
}

double Product::getShipmentLongitude() const {
    return shipmentLongitude;
}

void Product::setDescription(const std::string& description) {
    this->description = description.substr(0, 50);
}

void Product::setPrice(double price) {
    this->price = price;
}

void Product::setQuantity(int quantity) {
    this->quantity = quantity;
}

void Product::setShipmentLatitude(double shipmentLatitude) {
    if (shipmentLatitude >= 41.0 && shipmentLatitude <= 82.0) {
        this->shipmentLatitude = shipmentLatitude;
    } else {
        std::cerr << "Ошибка: Некорректная широта транспортировки (" << shipmentLatitude << "). Должна быть в диапазоне [41, 82]." << std::endl;
    }
}

void Product::setShipmentLongitude(double shipmentLongitude) {
    if (shipmentLongitude >= 19.0 && shipmentLongitude <= 169.0) {
        this->shipmentLongitude = shipmentLongitude;
    } else {
        std::cerr << "Ошибка: Некорректная долгота транспортировки (" << shipmentLongitude << "). Должна быть в диапазоне [19, 169]." << std::endl;
    }
}

void Product::print() const {
    std::cout << "  Штрих-код: " << barcode << std::endl;
    std::cout << "  Описание: " << description << std::endl;
    std::cout << "  Цена: " << std::fixed << std::setprecision(2) << price << " руб." << std::endl;
    std::cout << "  Количество: " << quantity << std::endl;
    std::cout << "  Широта отгрузки: " << std::fixed << std::setprecision(6) << shipmentLatitude << std::endl;
    std::cout << "  Долгота отгрузки: " << std::fixed << std::setprecision(6) << shipmentLongitude << std::endl;
}

// Реализация класса Warehouse
Warehouse::Warehouse() : id(generateWarehouseId()), type(WarehouseType::CENTER), latitude(0.0), longitude(0.0), maxCapacity(100), totalStock(0), products() {}

Warehouse::Warehouse(WarehouseType type, double latitude, double longitude, int maxCapacity)
    : id(generateWarehouseId()), type(type), latitude(latitude), longitude(longitude), maxCapacity(maxCapacity), totalStock(0), products() {
    if (latitude < 41.0 || latitude > 82.0 || longitude < 19.0 || longitude > 169.0) {
        std::cerr << "Ошибка: Некорректные координаты склада (" << latitude << ", " << longitude << "). Должны быть в пределах России." << std::endl;
        // Можно выбросить исключение или установить значения по умолчанию
    }
    if (maxCapacity <= 0) {
        std::cerr << "Ошибка: Максимальная вместимость должна быть положительной." << std::endl;
        this->maxCapacity = 100; // Установка значения по умолчанию
    }
}

Warehouse::Warehouse(const Warehouse& other)
    : id(other.id), type(other.type), latitude(other.latitude), longitude(other.longitude), maxCapacity(other.maxCapacity), totalStock(other.totalStock), products(other.products) {}

Warehouse::~Warehouse() {}

std::string Warehouse::getId() const {
    return id;
}

WarehouseType Warehouse::getType() const {
    return type;
}

double Warehouse::getLatitude() const {
    return latitude;
}

double Warehouse::getLongitude() const {
    return longitude;
}

int Warehouse::getMaxCapacity() const {
    return maxCapacity;
}

int Warehouse::getTotalStock() const {
    return totalStock;
}

const std::vector<Product>& Warehouse::getProducts() const {
    return products;
}

double Warehouse::calculateManhattanDistance(double productLatitude, double productLongitude) const {
    return std::abs(latitude - productLatitude) + std::abs(longitude - productLongitude);
}

bool Warehouse::hasSpace(int quantity) const {
    return (totalStock + quantity) <= maxCapacity;
}

void Warehouse::addProduct(const Product& product) {
    if (hasSpace(product.getQuantity())) {
        products.push_back(product);
        totalStock += product.getQuantity();
        std::cout << "Продукт \"" << product.getDescription() << "\" добавлен на склад " << id << " (" << type << ")." << std::endl;
    } else {
        std::cout << "Ошибка: Недостаточно места на складе " << id << " (" << type << ") для " << product.getQuantity() << " единиц товара \"" << product.getDescription() << "\"." << std::endl;
    }
}

bool Warehouse::removeProduct(const std::string& description, int quantityToRemove) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if (it->getDescription() == description) {
            if (it->getQuantity() >= quantityToRemove) {
                it->setQuantity(it->getQuantity() - quantityToRemove);
                totalStock -= quantityToRemove;
                std::cout << quantityToRemove << " единиц продукта \"" << description << "\" удалено со склада " << id << " (" << type << ")." << std::endl;
                if (it->getQuantity() == 0) {
                    products.erase(it);
                }
                return true;
            } else {
                std::cout << "Ошибка: На складе " << id << " (" << type << ") недостаточно товара \"" << description << "\". Доступно: " << it->getQuantity() << ", запрошено: " << quantityToRemove << "." << std::endl;
                return false;
            }
        }
    }
    std::cout << "Ошибка: Продукт \"" << description << "\" не найден на складе " << id << " (" << type << ")." << std::endl;
    return false;
}

void Warehouse::listProducts() const {
    if (products.empty()) {
        std::cout << "Склад " << id << " (" << type << ") пуст." << std::endl;
        return;
    }
    std::cout << "Список товаров на складе " << id << " (" << type << "):" << std::endl;
    for (const auto& product : products) {
        product.print();
        std::cout << "----------" << std::endl;
    }
    std::cout << "Общий запас: " << totalStock << "/" << maxCapacity << std::endl;
}

void Warehouse::searchProduct(const std::string& description) const {
    bool found = false;
    std::cout << "Результаты поиска для \"" << description << "\" на складе " << id << " (" << type << "):" << std::endl;
    for (const auto& product : products) {
        if (product.getDescription().find(description) != std::string::npos) {
            product.print();
            std::cout << "----------" << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "Продукты с описанием, содержащим \"" << description << "\", не найдены на складе " << id << " (" << type << ")." << std::endl;
    }
}

void Warehouse::updateStock() {
    totalStock = 0;
    for (const auto& product : products) {
        totalStock += product.getQuantity();
    }
}

// Вспомогательные функции
int generateRandomInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

double generateRandomDouble(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib(min, max);
    return distrib(gen);
}

std::string generateBarcode() {
    std::string barcode = "460";
    int middlePartOptions[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000};
    barcode += std::to_string(middlePartOptions[generateRandomInt(0, 8)]);
    for (int i = 0; i < 6; ++i) {
        barcode += std::to_string(generateRandomInt(0, 9));
    }
    return barcode;
}

std::string generateWarehouseId() {
    std::string id = "W";
    std::string code = std::to_string(Warehouse::nextWarehouseCode++);
    while (code.length() < 3) {
        code = "0" + code;
    }
    id += code;
    return id;
}
