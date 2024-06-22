//
// Created by Matylda on 20.06.2024.
//

#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H
#include <memory>
#include <unordered_map> // TODO: custom hashmap

#include "component_array.h"
#include "ecs.h"
#include "core/logger.h"

class component_manager {
public:
    template<typename T>
    void register_component() {
        const char *type_name = typeid(T).name();

        ASSERT(component_types.find(type_name) == component_types.end(), "Registering component type more than once.");

        component_types.insert({type_name, next_component_type});
        component_arrays.insert({type_name, std::make_shared<component_array<T> >()});

        next_component_type++;
    }


    template<typename T>
    component_type get_component_type() {
        const char *type_name = typeid(T).name();

        ASSERT(component_types.find(type_name) != component_types.end(), "Component not registered before use.");

        return component_types[type_name];
    }

    template<typename T>
    void add_component(entity e, T component) {
        get_component_array<T>()->insert_data(e, component);
    }

    template<typename T>
    void remove_component(entity e) {
        get_component_array<T>()->remove_data(e);
    }

    template<typename T>
    T& get_component(entity e) {
        return get_component_array<T>()->get_data(e);
    }

    void entity_destroyed(entity e) const {
        for(auto const& pair : component_arrays) {
            auto const& component = pair.second;

            component->entity_destroyed(e);
        }
    }
private:
    std::unordered_map<const char*, component_type> component_types{};
    std::unordered_map<const char*, std::shared_ptr<icomponent_array>> component_arrays{}; // TODO: remove shared_ptr
    component_type next_component_type{};

    template<typename T>
    std::shared_ptr<component_array<T>> get_component_array() {
        const char *type_name = typeid(T).name();

        ASSERT(component_types.find(type_name) != component_types.end(), "Component not registered before use.");

        return std::static_pointer_cast<component_array<T>>(component_arrays[type_name]);
    }
};

#endif //COMPONENT_MANAGER_H
