// Entity_vector.cpp — реализация контейнера для хранения сущностей (Entity)

#include "entity_vector.hpp"
#include "entity.hpp"
#include <iostream>
#include <algorithm> // для std::remove_if

using namespace std;

// Метод добавления сущности в контейнер
void Entityvector::addEntity(shared_ptr<Entity> entity) {
    if (!entity) {
        cerr << "Попытка добавить пустой (nullptr) указатель shared_ptr<Entity>\n";
        return;
    }
    cout << "Добавление сущности: " << entity->getId() << endl;
    entities.push_back(entity);
    cout << "Текущее количество сущностей: " << entities.size() << endl;
}

// Метод удаления сущности по её ID
bool Entityvector::removeEntity(const string& id) {
    auto initial_size = entities.size();

    // Удаляем все сущности, ID которых совпадает с заданным
    entities.erase(remove_if(entities.begin(), entities.end(),
        [&](const shared_ptr<Entity>& entity) {
            return entity && entity->getId() == id;
        }),
        entities.end());

    // Возвращает true, если хотя бы одна сущность была удалена
    return entities.size() < initial_size;
}

// Метод получения сущности по ID
shared_ptr<Entity> Entityvector::getEntity(const string& id) const {
    for (const auto& entity : entities) {
        if (entity && entity->getId() == id) {
            return entity;
        }
    }
    return nullptr; // Если не найдено
}

// Метод получения всех сущностей
const vector<shared_ptr<Entity>>& Entityvector::getAllEntities() const {
    return entities;
}
