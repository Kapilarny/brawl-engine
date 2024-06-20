#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H
#include <memory>
#include <unordered_map>

#include "ecs.h"
#include "isystem.h"
#include "core/logger.h"

class system_manager {
public:
    template <typename T>
    std::shared_ptr<T> register_system() {
        const char* type_name = typeid(T).name();

        ASSERT(systems.find(type_name) == systems.end(), "Registering system more than once.");

        auto system = std::make_shared<T>();
        systems.insert({type_name, system});

        return system;
    }

    template <typename T>
    void set_signature(signature sig) {
        const char* type_name = typeid(T).name();

        ASSERT(systems.find(type_name) != systems.end(), "System used before registered.");

        signatures.insert({type_name, sig});
    }

    void entity_destroyed(const entity e) const {
        for (const auto&[type, system] : systems) {
            system->entities.erase(e);
        }
    }

    void entity_signature_changed(const entity e, const signature entity_signature) {
        for (const auto&[type, system] : systems) {
            const auto& system_signature = signatures[type];

            if ((entity_signature & system_signature) == system_signature) {
                system->entities.insert(e);
            } else {
                system->entities.erase(e);
            }
        }
    }
private:
    std::unordered_map<const char*, signature> signatures{};
    std::unordered_map<const char*, std::shared_ptr<isystem>> systems{}; // TODO: remove shared_ptr
};

#endif //SYSTEM_MANAGER_H
