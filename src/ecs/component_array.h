#ifndef COMPONENT_ARRAY_H
#define COMPONENT_ARRAY_H
#include <unordered_map> // TODO: implement our own hash map

#include "ecs.h"
#include "core/logger.h"

class icomponent_array {
public:
    virtual ~icomponent_array() = default;
    virtual void entity_destroyed(entity e) = 0;
};

template <typename T>
class component_array : public icomponent_array {
public:
    void insert_data(entity e, T component) {
        ASSERT(entity_to_index_map.find(e) == entity_to_index_map.end(), "Component added to same entity more than once.");

        u32 new_index = size;
        entity_to_index_map[e] = new_index;
        index_to_entity_map[new_index] = e;
        comp_array[new_index] = component;
        size++;
    }

    void remove_data(entity e) {
        ASSERT(entity_to_index_map.find(e) != entity_to_index_map.end(), "Removing non-existent component.");

        u32 index_of_removed_entity = entity_to_index_map[e];
        u32 index_of_last_element = size - 1;
        comp_array[index_of_removed_entity] = comp_array[index_of_last_element];

        entity entity_of_last_element = index_to_entity_map[index_of_last_element];
        entity_to_index_map[entity_of_last_element] = index_of_removed_entity;
        index_to_entity_map[index_of_removed_entity] = entity_of_last_element;

        entity_to_index_map.erase(e);
        index_to_entity_map.erase(index_of_last_element);

        size--;
    }

    T& get_data(entity e) {
        ASSERT(entity_to_index_map.find(e) != entity_to_index_map.end(), "Retrieving non-existent component.");

        return comp_array[entity_to_index_map[e]];
    }

    void entity_destroyed(entity e) override {
        if(entity_to_index_map.find(e) != entity_to_index_map.end()) {
            remove_data(e);
        }
    }

private:
    T comp_array[MAX_ENTITIES];
    std::unordered_map<entity, u32> entity_to_index_map;
    std::unordered_map<u32, entity> index_to_entity_map;
    u32 size;
};

#endif //COMPONENT_ARRAY_H
