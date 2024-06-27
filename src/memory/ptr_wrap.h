#ifndef PTR_WRAP_H
#define PTR_WRAP_H

template <typename T>
class ptr_wrap {
public:
    ptr_wrap() = default;
    ptr_wrap(T* ptr) : ptr(ptr) {} // NOLINT(*-explicit-constructor)
    ~ptr_wrap() { delete ptr; }

    T* get() const { return ptr; }
    T* operator->() const { return ptr; }
    T& operator*() const { return *ptr; }

    // = operator
    ptr_wrap& operator=(T* new_ptr) {
        delete ptr;
        ptr = new_ptr;
        return *this;
    }

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

#endif //PTR_WRAP_H
