#ifndef SYSTEM_H
#define SYSTEM_H
#include <unordered_set>

#include "ecs.h"

class isystem {
public:
    std::unordered_set<entity> entities;
};

#endif //SYSTEM_H
