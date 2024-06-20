#ifndef ECS_MANAGER_H
#define ECS_MANAGER_H

#include "ecs.h"

#include "entity_manager.h"
#include "system_manager.h"
#include "component_manager.h"

class ecs_manager {
public:
    ecs_manager();
    ~ecs_manager();

    entity create_entity() const;
    void destroy_entity(entity e) const;

    template<typename T>
    void register_component() const {
        component_mgr->register_component<T>();
    }

    template<typename T>
    void add_component(const entity e, T component) const {
        component_mgr->add_component<T>(e, component);

        auto signature = entity_mgr->get_signature(e);
        signature.set(component_mgr->get_component_type<T>(), true);
        entity_mgr->set_signature(e, signature);

        system_mgr->entity_signature_changed(e, signature);
    }

    template<typename T>
    void remove_component(const entity e) const {
        component_mgr->remove_component<T>(e);

        auto signature = entity_mgr->get_signature(e);
        signature.set(component_mgr->get_component_type<T>(), false);
        entity_mgr->set_signature(e, signature);

        system_mgr->entity_signature_changed(e, signature);
    }

    template<typename T>
    T& get_component(const entity e) const {
        return component_mgr->get_component<T>(e);
    }

    template<typename T>
    component_type get_component_type() const {
        return component_mgr->get_component_type<T>();
    }

    template<typename T>
    std::shared_ptr<T> register_system() const {
        return system_mgr->register_system<T>();
    }

    template<typename T>
    void set_system_signature(const signature sig) const {
        system_mgr->set_signature<T>(sig);
    }
private:
    component_manager* component_mgr;
    entity_manager* entity_mgr;
    system_manager* system_mgr;
};

#endif //ECS_MANAGER_H
