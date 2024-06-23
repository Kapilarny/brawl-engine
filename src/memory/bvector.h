#ifndef BVECTOR_H
#define BVECTOR_H

#include <initializer_list>

#include "bmemory.h"
#include "defines.h"

template<typename T>
class bvector {
public:
    bvector() : data_ptr(nullptr), count(0), capacity(0) {}
    bvector(std::initializer_list<T> list) : data_ptr(nullptr), count(0), capacity(0) {
        for(const T& value : list) {
            push_back(value);
        }
    }

    bvector(u64 initial_capacity) {
        capacity = initial_capacity;
        count = initial_capacity;

        data_ptr = new T[capacity * sizeof(T)];
        bzero_memory(data_ptr, capacity * sizeof(T));
    }

    ~bvector() { if(data_ptr) delete[] data_ptr; }

    void push_back(T value) {
        if(count >= capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }

        data_ptr[count++] = value;
    }

    void clear() {
        count = 0;
    }

    void resize(u64 new_capacity) {
        if(capacity >= new_capacity) return;

        T* new_data = new T[new_capacity];
        bcopy_memory(new_data, data_ptr, capacity * sizeof(T));

        delete[] data_ptr;

        data_ptr = new_data;
        capacity = new_capacity;
    }

    T* data() {
        return data_ptr;
    }

    T operator[](u64 index) const {
        return data_ptr[index];
    }

    T& operator[](u64 index) {
        return data_ptr[index];
    }

    [[nodiscard]] u64 size() const { return count; }
    [[nodiscard]] u64 get_capacity() const { return capacity; }
private:
    T* data_ptr;
    u64 count;
    u64 capacity;
};



#endif //BVECTOR_H
