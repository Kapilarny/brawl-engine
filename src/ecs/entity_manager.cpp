#include "entity_manager.h"

#include "core/logger.h"

entity_manager::entity_manager() {
    for(entity e = 0; e < MAX_ENTITIES; e++) {
        available_entities.push(e);
    }
}

entity entity_manager::create_entity() {
    ASSERT(living_entity_count < MAX_ENTITIES, "Too many entities in existence.");

    entity e = available_entities.front();
    available_entities.pop();
    living_entity_count++;

    return e;
}

void entity_manager::destroy_entity(entity e) {
    ASSERT(e < MAX_ENTITIES, "Entity out of range.");

    signatures[e].reset();

    available_entities.push(e);
    living_entity_count--;
}

void entity_manager::set_signature(entity e, signature sig) {
    ASSERT(e < MAX_ENTITIES, "Entity out of range.");

    signatures[e] = sig;
}

signature entity_manager::get_signature(entity e) {
    ASSERT(e < MAX_ENTITIES, "Entity out of range.");

    return signatures[e];
}
