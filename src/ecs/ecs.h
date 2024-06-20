#ifndef ECS_H
#define ECS_H

#include <bitset>

#include "defines.h"

// Credits to Austin Morlan for the ECS implementation
// https://austinmorlan.com/posts/entity_component_system/

typedef u32 entity;
constexpr entity MAX_ENTITIES = 5000;

typedef u8 component_type;
constexpr component_type MAX_COMPONENTS = 32;

typedef std::bitset<MAX_COMPONENTS> signature;

#endif //ECS_H
