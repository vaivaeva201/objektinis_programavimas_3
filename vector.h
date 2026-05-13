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
            delete[] data_;
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

        size_type capacity() const
        {
            return capacity_;
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
