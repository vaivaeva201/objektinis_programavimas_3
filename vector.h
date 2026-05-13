#include <iostream>

template <typename T>
class Vector {
    private:
        size_t size_;
        size_t capacity_;
        T* data_;

    public:
        using size_type = std::size_t;

        //default construktor
        Vector() : size_(0), capacity_(1) {data_ = new T[capacity_];}
        
        //copy construcotr
        Vector(const Vector& rhs) : size_(rhs.size_), capacity_(rhs.capacity_) 
        {
            data_ = new T[capacity_];
            for (int i = 0; i < rhs.size(); i++)
            {
                data_[i] = rhs.data_[i];
            }
        }    

        //copy assignment operator
        Vector& operator=(const Vector& rhs)
        {
            if(this == &rhs) return *this;

            size_ = rhs.size_;
            capacity_ = rhs.capacity_;
            data_ = new T[capacity_];
            for(size_t i = 0; i < size_; ++i) {
                data_[i] = rhs.data_[i];
            }

            return *this;
        }

        //move constructor
        Vector(Vector&& rhs) noexcept 
        : data_(rhs.data_), size_(rhs.size_), capacity_(rhs.capacity_)
        {
            rhs.data_ = nullptr; 
            rhs.size_ = 0;
            rhs.capacity_ = 0;
        }

         //move assignment operator
        Vector& operator=(Vector&& rhs) noexcept
        {
            if(this == &rhs) return *this;
            delete[] data_;
            data_ = rhs.data_;
            size_ = rhs.size_;
            capacity_ = rhs.capacity_;

            rhs.data_ = nullptr;
            rhs.size_ = 0;
            rhs.capacity_ = 0;

            return *this;
        }

        //???
        Vector(int elements, int value = 0) : size_(elements), capacity_(elements)
        {
            data_ = new T[capacity_];
            for(int i = 0; i < size_; i++)
            {
                data_[i] = value;
            }
        }

        //list construktor
        Vector(std::initializer_list<T>& list) : size_(0), capacity_(list.size())
        {
            data_ = new T[capacity_];

            size_t i = 0;
            for (const T& value : list) 
                {
                    data_[i] = value;
                    i++;
                }
        }

        //destructor
        ~Vector(){
            clear();
        }

        //dytis, talpa
        bool emty() const
        {
            return size_ == 0;
        }


        size_type size() const
        {
            return size_;
        }

        size_type max_size() const
        {
            return std::numeric_limits<size_type>::max() / sizeof(T);
        }

        size_type capacity() const
        {
            return capacity_;
        }

        void reserve(size_type new_cap) 
        {
            if (new_cap > capacity_) 
            {
                T* newdata = new T[new_cap];
                for (size_t i = 0; i < size_; i++) 
                    newdata[i] = std::move(data_[i]);
                delete[] data_;
                data_ = newdata;
                capacity_ = new_cap;
            }
        }

        void shrink_to_fit()
        {
            if (capacity_ > size_) 
            {
                T* newdata_ = new T[size_];
                for (size_type i = 0; i < size_; ++i) {
                    newdata_[i] = std::move(data_[i]);
                }
                delete[] data_;
                data_ = newdata_;
                capacity_ = size_;
            }
        }

        void resize()
        {
            capacity_ *= 2;
            T* newdata_ = new T[capacity_];
            for(size_t i=0; i<size_; i++)
            {
                newdata_[i] = data_[i];
            }
            delete[] data_;
            data_ = newdata_;
        }

        void resize(size_t newSize) 
        {
        
            if (newSize > capacity_) 
            {
        
                size_t newCapacity = std::max(newSize, capacity_ * 2);
                
        
                T* newdata_ = new T[newCapacity];
                
            
                for (size_t i = 0; i < size_; i++) 
                {
                    newdata_[i] = data_[i];
                }
                
                for (size_t i = size_; i < newSize; i++) 
                {
                    newdata_[i] = T(); 
                }
                
                delete[] data_;
                data_ = newdata_;
                capacity_ = newCapacity;
            }
        
            else if (newSize > size_) 
            {
                for (size_t i = size_; i < newSize; i++) 
                {
                    data_[i] = T(); 
                }
            }
            size_ = newSize;
        }

        //prieiga prie elementu
        T& operator[](size_t index)
        {
            return data_[index];
        }

        T& at(int index)
        {
            if((index < 0 ) || (index >= size_))
            {
                throw std::out_of_range("Index out of range");
            }
            return data_[index];
        }

        T& front()
        {
            return at(0);
        }

        T& back()
        {
            return at(size_-1);
        }

         T* data() 
        {
            return data_;
        }

        //elementu pridejimas, salinimas
        void clear(){
            size_ = 0;
            capacity_ = 0;
            delete[] data_;
            data_ = nullptr;
        }

        void push_back(const T& value)
        {
            if(size_ < capacity_)
            {
                data_[size_] = value;
                size_++;
            }
            else
            {
                capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
                T *newdata_ = new T[capacity_];
                for (size_t i = 0; i < size_; i++)
                {
                    newdata_[i] = data_[i];
                }
                newdata_[size_] = value;
                size_++;
                delete[] data_;
                data_ = newdata_;
            }

        }

        void pop_back()
        {
            if(size_ > 0)
            {
                --size_;
            }
        }

        void insert(size_t index, const T& value) 
        {
            if (index > size_) 
                throw std::out_of_range("Insert index out of range");
            if (size_ == capacity_) 
                reserve(capacity_ == 0 ? 1 : capacity_ * 2);
            
            for (size_t i = size_; i > index; --i) 
            {
                data_[i] = std::move(data_[i - 1]);
            }
            data_[index] = value;
            size_++;
        }

        void erase(size_t index) 
        {
            if (index >= size_) 
                throw std::out_of_range("Erase index out of range");
            for (size_t i = index; i < size_ - 1; i++) 
            {
                data_[i] = std::move(data_[i + 1]);
            }
            size_--;
        }

        //operators
        bool operator==(const Vector& rhs) const
        {
            if(size() != rhs.size())
            {
                return false;
            }

            for (int i = 0; i < size(); i++)
            {
                if(data_[i] != rhs.data_[i])
                {
                    return false;
                }
            }
            
            return true;
        }

        bool operator!=(const Vector& rhs) const
        {
            return !(*this == rhs);
        }

        friend std:: ostream& operator<<(std::ostream& out, const Vector& rhs)
        {
            for (int i = 0; i < rhs.size_; i++)
            {
                out << rhs.data_[i] << " ";
            }
            out << " || ";

            for (int i = rhs.size_; i < rhs.capacity_; i++)
            {
                out << rhs.data_[i] << " ";
            }
            out << std::endl;
            return out;
        }
};
