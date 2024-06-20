#include "ecs_manager.h"

ecs_manager::ecs_manager() {
    component_mgr = new component_manager();
    system_mgr = new system_manager();
    entity_mgr = new entity_manager();
}

ecs_manager::~ecs_manager() {
    delete component_mgr;
    delete system_mgr;
    delete entity_mgr;
}

entity ecs_manager::create_entity() const {
    return entity_mgr->create_entity();
}

void ecs_manager::destroy_entity(entity e) const {
    entity_mgr->destroy_entity(e);
}
