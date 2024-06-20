#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <queue>

#include "ecs.h"

class entity_manager {
public:
    entity_manager();

    entity create_entity();
    void destroy_entity(entity e);

    void set_signature(entity e, signature sig);
    signature get_signature(entity e);
private:
    // Queue of unused entity IDs
    std::queue<entity> available_entities{};

    signature signatures[MAX_ENTITIES];
    u32 living_entity_count{};
};

#endif //ENTITY_MANAGER_H
