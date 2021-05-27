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
        typedef ptrdiff_t difference_type;
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
        struct iterator {

        private: 

            pointer ptr;

        public:

            iterator(pointer ptr) : ptr(ptr) {}

            reference operator*() const { return *ptr; }
            pointer operator->() const { return ptr; }

            iterator& operator++() { ptr++; return *this; }
            iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

            iterator& operator--() { ptr--; return *this; }
            iterator operator--(int) { iterator tmp = *this; --ptr; return tmp; }

            iterator& operator+=(difference_type n) { ptr += n; return *this; }
            iterator& operator-=(difference_type n) { ptr -= n; return *this; }

            friend bool operator==(const iterator& a, const iterator& b) { return a.ptr == b.ptr; }
            friend bool operator!=(const iterator& a, const iterator& b) { return a.ptr != b.ptr; }

        };

        struct const_iterator {

        private: 

            const_pointer ptr;

        public:

            const_iterator(pointer ptr) : ptr(ptr) {}

            const_reference operator*() const { return *ptr; }
            const_pointer operator->() const { return ptr; }

            const_iterator& operator++() { ptr++; return *this; }
            const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }

            const_iterator& operator--() { ptr--; return *this; }
            const_iterator operator--(int) { const_iterator tmp = *this; --ptr; return tmp; }

            const_iterator& operator+=(difference_type n) { ptr += n; return *this; }
            const_iterator& operator-=(difference_type n) { ptr -= n; return *this; }

            friend bool operator==(const const_iterator& a, const const_iterator& b) { return a.ptr == b.ptr; }
            friend bool operator!=(const const_iterator& a, const const_iterator& b) { return a.ptr != b.ptr; }

        };

        struct reverse_iterator {

        private: 

            pointer ptr;

        public:

            reverse_iterator(pointer ptr) : ptr(ptr) {}

            reference operator*() const { return *ptr; }
            pointer operator->() const { return ptr; }

            reverse_iterator& operator++() { ptr--; return *this; }
            reverse_iterator operator++(int) { reverse_iterator tmp = *this; --ptr; return tmp; }

            reverse_iterator& operator--() { ptr++; return *this; }
            reverse_iterator operator--(int) { reverse_iterator tmp = *this; ++(*this); return tmp; }

            reverse_iterator& operator+=(difference_type n) { ptr -= n; return *this; }
            reverse_iterator& operator-=(difference_type n) { ptr += n; return *this; }

            friend bool operator==(const reverse_iterator& a, const reverse_iterator& b) { return a.ptr == b.ptr; }
            friend bool operator!=(const reverse_iterator& a, const reverse_iterator& b) { return a.ptr != b.ptr; }

        };

        struct const_reverse_iterator {

        private: 

            const_pointer ptr;

        public:

            const_reverse_iterator(pointer ptr) : ptr(ptr) {}
            const_reverse_iterator(reverse_iterator rit) { ptr = rit->ptr; }

            const_reference operator*() const { return *ptr; }
            const_pointer operator->() const { return ptr; }

            const_reverse_iterator& operator++() { ptr--; return *this; }
            const_reverse_iterator operator++(int) { const_reverse_iterator tmp = *this; --ptr; return tmp; }

            const_reverse_iterator& operator--() { ptr++; return *this; }
            const_reverse_iterator operator--(int) { const_reverse_iterator tmp = *this; ++(*this); return tmp; }

            const_reverse_iterator& operator+=(difference_type n) { ptr -= n; return *this; }
            const_reverse_iterator& operator-=(difference_type n) { ptr += n; return *this; }

            friend bool operator==(const const_reverse_iterator& a, const const_reverse_iterator& b) { return a.ptr == b.ptr; }
            friend bool operator!=(const const_reverse_iterator& a, const const_reverse_iterator& b) { return a.ptr != b.ptr; }

        };

        iterator begin() { return iterator(&array[0]); }
        iterator end() { return iterator(&array[len]); }

        const_iterator begin() const { return const_iterator(&array[0]); }
        const_iterator end() const { return const_iterator(&array[len]); }

        reverse_iterator rbegin() { return reverse_iterator(&array[len-1]); }
        reverse_iterator rend() { return reverse_iterator(&array[0] - 1); }

        const_reverse_iterator rbegin() const { return const_reverse_iterator(&array[len-1]); }
        const_reverse_iterator rend() const { return const_reverse_iterator(&array[0] - 1); }



        //      CAPACITY
        size_type   size() const { return len; }
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
        //this->alloc.construct(this->array + this->siz, val);
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
