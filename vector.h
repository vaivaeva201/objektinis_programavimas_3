#include <iostream>

template <typename T>
class Vector {
    private:
        size_t size_;
        size_t capacity_;
        T* data_;

    public:
        using size_type = std::size_t;

        Vector() : size_(0), capacity_(0) data_(new T[capacity_]) { }

        ~Vector(){
            delete[] data_;
        }

        void push_back(const T& value)
        {

            data_[size_] = value;
            size_++;
        }

        bool emty()
        {
            return size_ == 0;
        }

        size_type size() const
        {
            return size_;
        }

        size_type capacity() const
        {
            return capacity_;
        }

        void clear(){
            size_ = 0;
            capacity_ = 0;
            delete[] data_;
            data_ = nullptr;
    }

};
