// header.h
#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <iomanip>
#include <limits>

// ENUM для типов склада
enum class WarehouseType {
    CENTER,
    WEST,
    EAST
};

std::ostream& operator<<(std::ostream& os, const WarehouseType& type);

class Product {
private:
    std::string barcode;
    std::string description;
    double price;
    int quantity;
    double shipmentLatitude;
    double shipmentLongitude;

public:
    // Конструкторы
    Product();
    Product(const std::string& description, double price, int quantity, double shipmentLatitude, double shipmentLongitude);
    Product(const Product& other);

    // Деструктор
    ~Product() = default;

    // Getters
    std::string getBarcode() const;
    std::string getDescription() const;
    double getPrice() const;
    int getQuantity() const;
    double getShipmentLatitude() const;
    double getShipmentLongitude() const;

    // Setters
    void setDescription(const std::string& description);
    void setPrice(double price);
    void setQuantity(int quantity);
    void setShipmentLatitude(double shipmentLatitude);
    void setShipmentLongitude(double shipmentLongitude);

    // Метод для печати информации о продукте
    void print() const;
};

class Warehouse {
private:
    std::string id;
    WarehouseType type;
    double latitude;
    double longitude;
    int maxCapacity;
    int totalStock;
    std::vector<Product> products;
    

public:
    static int nextWarehouseCode;
    // Конструкторы
    Warehouse();
    Warehouse(WarehouseType type, double latitude, double longitude, int maxCapacity);
    Warehouse(const Warehouse& other);

    // Деструктор
    ~Warehouse();

    // Getters
    std::string getId() const;
    WarehouseType getType() const;
    double getLatitude() const;
    double getLongitude() const;
    int getMaxCapacity() const;
    int getTotalStock() const;
    const std::vector<Product>& getProducts() const;

    // Методы
    void addProduct(const Product& product);
    bool removeProduct(const std::string& description, int quantityToRemove);
    void listProducts() const;
    void searchProduct(const std::string& description) const;
    double calculateManhattanDistance(double productLatitude, double productLongitude) const;
    bool hasSpace(int quantity) const;
    void updateStock();
};

// Генерация случайного числа в заданном диапазоне
int generateRandomInt(int min, int max);
double generateRandomDouble(double min, double max);
std::string generateBarcode();
std::string generateWarehouseId();

#endif // HEADER_H
