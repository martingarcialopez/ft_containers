#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <cmath>

namespace ft {

    template <class T, class Alloc = std::allocator<T> >
    class vector {

    public:

        //      MEMBER TYPE
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

        typedef size_t size_type;


    private:

        size_type       len;
        size_type       siz;
        value_type *    array;
        allocator_type  alloc;


    public:


        //      MEMBER FUNCTIONS
        vector() { len = 0; siz = 0; }
        vector(size_type n) { array = alloc.allocate(n); len = 0; siz = n; }
        ~vector() { alloc.deallocate(array, siz); }


        //      ITERATORS


        //      CAPACITY
        size_type   size() { return len; }
        size_type   max_size() const { return alloc.max_size(); }
        void        resize (size_type n, value_type val = value_type());
        bool        empty() const { return !len; }
        size_type   capacity() const { return siz; }
        void        reserve(size_type n);
        


        //      ELEMENT ACCESS
        value_type & operator[](size_t idx) { return this->array[idx]; }



        //      MODIFIERS
        void    push_back(const value_type& val);
        void    pop_back();
        void    clear();


    };

    //      NON MEMBER-FUNCTIONS OVERLOADS

}

template <class T, class Alloc>
void    ft::vector<T, Alloc>::push_back(const T & val) {
    if (this->len < this->siz)
        array[this->len++] = val;
    else {
        value_type * tmp = this->array;
        this->array = this->alloc.allocate(this->siz ? this->siz * 2 : 1);
        for (int i = 0; i < this->siz; i++)
            this->array[i] = tmp[i];
        this->alloc.deallocate(tmp, this->siz);
        this->array[this->siz] = val;
        this->siz = this->siz ? this->siz * 2 : 1;
        this->len++;
    }
    //std::cout << "size of vector is " << this->siz << std::endl;
}

template <class T, class Alloc>
void    ft::vector<T, Alloc>::pop_back() {
    this->len--;
}

template <class T, class Alloc>
void    ft::vector<T, Alloc>::clear() {
    this->alloc.deallocate(this->array, this->siz);
    this->len = 0;
    this->siz = 0;
    //for (int i = 0; i < this->len; i++) {
        //this->alloc.destroy();
    //}
}



#endif 
