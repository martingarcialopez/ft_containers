#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>

template <class T, class Alloc = std::allocator<T> >
class vector {

private:

    size_t  len;
    T *     array;

public:

    vector() { this->len = 0; }
    //vector() {   };
    ~vector() { destroy(this->array); }

    T & operator[](size_t idx) {
        return this->array[idx];
    }


};




#endif 
