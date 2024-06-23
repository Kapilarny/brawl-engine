#ifndef PTR_WRAP_H
#define PTR_WRAP_H

#include <memory> // TODO: Remove this

#include "core/logger.h"

template <typename T>
class ptr_wrap {
public:
    ptr_wrap() = default;
    ptr_wrap(T* ptr) : ptr(ptr) {}
    ~ptr_wrap() {
        if(ptr) {
            BINFO("Deleting ptr!");
            delete ptr;
        }
    }

    T* get() const { return ptr; }
    T* operator->() const { return ptr; }
    T& operator*() const { return *ptr; }

    void reset(T* new_ptr) {
        delete ptr;
        ptr = new_ptr;
    }

    void release() {
        ptr = nullptr;
    }

    explicit operator bool() const { return ptr != nullptr; }
private:
    T *ptr = nullptr;
};

template<typename T>
using ref = std::shared_ptr<T>;

template<typename T, typename ... args>
constexpr ref<T> CreateRef(args&& ... arg)
{
    return std::make_shared<T>(std::forward<args>(arg)...);
}

#endif //PTR_WRAP_H
