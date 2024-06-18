#ifndef BVECTOR_H
#define BVECTOR_H

#include "bmemory.h"
#include "defines.h"

template<typename T>
class bvector {
public:
    bvector() : data(nullptr), size(0), capacity(0) {}

    bvector(u64 initial_capacity) : data(new T[initial_capacity]), size(0), capacity(initial_capacity) {
        bzero_memory(data, sizeof(T) * initial_capacity);
    }

    ~bvector() { delete[] data; }

    void push_back(T value) {
        if(size >= capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = value;
    }

    void clear() {
        size = 0;
    }

    void reserve(u64 new_capacity) {
        if(new_capacity <= capacity) {
            return;
        }

        T* new_data = new T[new_capacity];
        for(u64 i = 0; i < size; i++) {
            new_data[i] = data[i];
        }

        delete[] data;

        data = new_data;
        capacity = new_capacity;
    }

    T* begin() {
        return data;
    }

    T operator[](u64 index) const {
        return data[index];
    }

    T& operator[](u64 index) {
        return data[index];
    }

    [[nodiscard]] u64 get_size() const { return size; }
    [[nodiscard]] u64 get_capacity() const { return capacity; }
private:
    T* data;
    u64 size;
    u64 capacity;
};



#endif //BVECTOR_H
