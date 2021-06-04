#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <cmath>
# include <iostream>

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
        explicit vector(const allocator_type& alloc = allocator_type()) { (void)alloc; len = 0; siz = 0; }
        explicit vector(size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()) { 
            this->alloc = alloc;
            array = this->alloc.allocate(n);
            for (size_type i = 0; i < n; i++)
                this->alloc.construct(array + i, val);
            len = n;
            siz = n;
        }
        template <class InputIterator>
			vector (InputIterator first, typename ft::enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type last,
                      const allocator_type& alloc = allocator_type())
//            vector (InputIterator first, typename std::enable_if<std::is_same<InputIterator, ft::iterator>::value, InputIterator(),
//                    const allocator_type& alloc = allocator_type()) {
                len = &(*last) - &(*first); 
                siz = len;
                this->alloc = alloc;
                array = this->alloc.allocate(siz);
                for (size_type i = 0; i < len; i++) {
                    //array[i] = *first++;
                    this->alloc.construct(array + i, *first++);
                }
            }
        vector (const vector& x) {
            len = x.len;
            siz = x.siz;
            alloc = x.alloc;
            array = alloc.allocate(siz);
            for (size_type i = 0; i < len; i ++) {
           //     array[i] = x[i];
                this->alloc.construct(array + i, x[i]);
            }
        }
        ~vector() { 
            for (size_type i = 0; i < len; i++)
                alloc.destroy(array + i);
            alloc.deallocate(array, siz);
        }
        vector& operator=(const vector& x) {
            value_type * tmp = array;
            array = alloc.allocate(x.siz);
            for (size_type i = 0; i < x.len; i++)
                alloc.construct(array + i, x[i]);
            for (size_type i = 0; i < len; i++)
                alloc.destroy(tmp + i);
            alloc.deallocate(tmp, siz);
            len = x.len;
            siz = x.siz;
            return *this;
        }


        //      ITERATORS
        struct iterator {

        private: 

            pointer ptr;

        public:

            iterator() {}
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

            friend iterator operator+(const iterator& a, const int& b) { return &*a + b; }
            friend iterator operator+(const int& a, const iterator& b) { return a + &*b; }
            friend iterator operator-(const iterator& a, const int& b) { return &*a - b; }
            friend iterator operator-(const int& a, const iterator& b) { return a - &*b; }

            friend bool operator<(const iterator&a, const iterator&b ) { return &*a < &*b; }
            friend bool operator>(const iterator&a, const iterator&b ) { return &*a > &*b; }
            friend bool operator<=(const iterator&a, const iterator&b ) { return &*a <= &*b; }
            friend bool operator>=(const iterator&a, const iterator&b ) { return &*a >= &*b; }

        };

        struct const_iterator {

        private: 

            const_pointer ptr;

        public:

            const_iterator() {}
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

            friend const_iterator operator+(const const_iterator& a, const int& b) { return &*a + b; }
            friend const_iterator operator+(const int& a, const const_iterator& b) { return a + &*b; }
            friend const_iterator operator-(const const_iterator& a, const int& b) { return &*a - b; }
            friend const_iterator operator-(const int& a, const const_iterator& b) { return a - &*b; }

            

        };

        struct reverse_iterator {

        private: 

            pointer ptr;

        public:

            reverse_iterator() {}
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

            friend reverse_iterator operator+(const reverse_iterator& a, const int& b) { return &*a + b; }
            friend reverse_iterator operator+(const int& a, const reverse_iterator& b) { return a + &*b; }
            friend reverse_iterator operator-(const reverse_iterator& a, const int& b) { return &*a - b; }
            friend reverse_iterator operator-(const int& a, const reverse_iterator& b) { return a - &*b; }

        };

        struct const_reverse_iterator {

        private: 

            const_pointer ptr;

        public:

            const_reverse_iterator() {}
            const_reverse_iterator(pointer ptr) : ptr(ptr) {}
            const_reverse_iterator(reverse_iterator rit) { ptr = &(*rit); }

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

            friend const_reverse_iterator operator+(const const_reverse_iterator& a, const int& b) { return &*a + b; }
            friend const_reverse_iterator operator+(const int& a, const const_reverse_iterator& b) { return a + &*b; }
            friend const_reverse_iterator operator-(const const_reverse_iterator& a, const int& b) { return &*a - b; }
            friend const_reverse_iterator operator-(const int& a, const const_reverse_iterator& b) { return a - &*b; }

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
        void        resize (size_type n, value_type val = value_type()) {
            if (n < len) {
                for (size_type i = n; i < len; i++)
                    alloc.destroy(array + i);
                len = n;
            }
            else if (n < siz) {
                for (size_type i = len; i < n; i++)
                    alloc.construct(array + i, val);
                len = n;
            }
            else {
                value_type * tmp = array;
                array = alloc.allocate(n);
                for (size_type i = 0; i < len; i++)
                    array[i] = tmp[i];
                alloc.deallocate(tmp, siz);
                for (size_type i = len; i < n; i++)
                    alloc.construct(array + i, val);
                len = n;
                siz = n;
            }

        }
        size_type   capacity() const { return siz; }
        bool        empty() const { return !len; }
        void        reserve(size_type n) {
            if (n > siz) {
                value_type * tmp = array;
                array = alloc.allocate(n);
                for (size_type i = 0; i < len; i++) {
                    array[i] = tmp[i];
                    alloc.destroy(tmp + i);
                }
                alloc.deallocate(tmp, siz);
                siz = n;
            }
        }
        


        //      ELEMENT ACCESS
        reference operator[](size_type n) { return array[n]; }
        const_reference operator[](size_type n) const { return array[n]; }
        reference at (size_type n) { if (n < 0 || n >= len) throw std::out_of_range("vector"); return array[n]; }
        const_reference at (size_type n) const { if (n < 0 || n >= len) throw std::out_of_range("vector"); return array[n]; }
        reference front() { return array[0]; }
        const_reference front() const { return array[0]; }
        reference back() { return array[len-1]; }
        const_reference back() const { return array[len-1]; }



        //      MODIFIERS
        void        push_back(const value_type& val);
        void        pop_back();
        template    <class InputIterator>
            void    assign (InputIterator first, InputIterator last);
        void        assign (size_type n, const value_type& val);
        iterator    insert (iterator position, const value_type& val);
        void        insert (iterator position, size_type n, const value_type& val);
        template <class InputIterator>
            void    insert (iterator position, InputIterator first, InputIterator last);
        iterator    erase (iterator position);
        iterator    erase (iterator first, iterator last);
        void        swap (vector& x);
        void        clear();


    //      NON MEMBER-FUNCTIONS OVERLOADS
    //
    //
    //
    //

    };
}

template <class T, class Alloc>
void    ft::vector<T, Alloc>::push_back(const T & val) {
    if (this->len < this->siz) {
    //    this->array[this->len++] = val;
        this->alloc.construct(this->array + this->len++, val);
    }
    else {
        value_type * tmp = this->array;
        this->array = this->alloc.allocate(this->siz ? this->siz * 2 : 1);
        for (size_type i = 0; i < this->len; i++)
            this->array[i] = tmp[i];
        this->alloc.deallocate(tmp, this->siz);
        //this->array[this->siz] = val;
        this->alloc.construct(this->array + this->len++, val);
        this->siz = this->siz ? this->siz * 2 : 1;
        //this->len++;
    }
    //std::cout << "size of vector is " << this->siz << std::endl;
}

template <class T, class Alloc>
void    ft::vector<T, Alloc>::pop_back() {
    this->len--;
}

template <class T, class Alloc>
void    ft::vector<T, Alloc>::clear() {
    for (size_type i = 0; i < len; i++)
        alloc.destroy(array[i]);
    alloc.deallocate(array, siz);
    len = 0;
    siz = 0;
}

template <class T, class Alloc>
    template <class InputIterator>
    void    ft::vector<T, Alloc>::assign (InputIterator first, InputIterator last) {

        int n = &(*last) - &(*first); 
        if (n <= siz) {
            for (int i = 0; i < n; i++)
                alloc.construct(array + i, *first++);
            len = n;
        }
        else {
            value_type * tmp = array;
            array = alloc.allocate(n);
            for (int i = 0; i < n; i++)
                alloc.construct(array + i, *first++);
            for (size_type i = 0; i < len; i++)
                alloc.destroy(tmp + i);
            alloc.deallocate(tmp, siz);
            len = n;
            siz = n;
        }
    }

template <class T, class Alloc>
void    ft::vector<T, Alloc>::assign (size_type n, const value_type& val) {
    if (n <= siz) {
        for (size_type i = 0; i < n; i++)
            alloc.construct(array + i, val);
        len = n;
    }
    else {
        value_type * tmp = array;
        array = alloc.allocate(n);
        for (size_type i = 0; i < n; i++)
            alloc.construct(array + i, val); 
        for (size_type i = 0; i < len; i++)
            alloc.destroy(tmp + i);
        alloc.deallocate(tmp, siz);
        len = n;
        siz = n;
    }
}


template <class T, class Alloc> 
typename ft::vector<T, Alloc>::iterator   ft::vector<T, Alloc>::insert(iterator position, const value_type& val) {

    insert(position, 1u, val);
    return position;

}


template <class T, class Alloc>
void        ft::vector<T, Alloc>::insert(iterator position, size_type n, const value_type& val) {

    int i;
    if (len + n <= siz) {
        for (i = len - 1; i >= 0 && &array[i] >= &*position; i--)
            array[i + n] = array[i];
        i++;
        for (size_type j = 0; j < n; j++)
            alloc.construct(array + i + j, val);
        len += n;
    }
    else {
        value_type * tmp = array;
        array = alloc.allocate(siz + n - (siz - len));
        for (int i = 0; i < len; i++)
            array[i] = tmp[i];
        for (i = len - 1; i >= 0 && &tmp[i] >= &*position; i--)
            array[i + n] = array[i];
        i++;
        for (int j = 0; j < n; j++)
            alloc.construct(array + i + j , val);
        for (int i = 0; i < len; i++)
            alloc.destroy(tmp + i);
        alloc.deallocate(tmp, siz);
        siz += n - (siz - len);
        len += n;
    }
}

template <class T, class Alloc>
template <class InputIterator>
void    ft::vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last) {
        
    int n = &*last - &*first;
    int pos = &*position - &array[0];
    for (int i = 0; i < n; i++) {
        insert(position, 1u, *--last);
        position = iterator(&array[pos]); 
    }
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator     ft::vector<T, Alloc>::erase(iterator position) {

    int i = 0;
    while (i < len && &array[i] != &*position)
        i++;
    iterator it = iterator(&array[i]);
    for (; i + 1 < len; i++)
        array[i] = array[i + 1];
    len--;
    return it;
}

template <class T, class Alloc>
typename ft::vector<T, Alloc>::iterator     ft::vector<T, Alloc>::erase(iterator first, iterator last) {

    int n = &*last - &*first;
    iterator it = first;
    for (size_type i = 0; i < n; i++)
        it = erase(it);
    return it;

}

template <class T, class Alloc>
void        ft::vector<T, Alloc>::swap(vector& x) {

    vector<T, Alloc> swp = *this;

    *this = x;
    x = swp;
}

template <class T, class Alloc>
bool operator== (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
    if (lhs.size() != rhs.size())
        return false;
    for (size_t i = 0; i < lhs.size(); i++)
        if (lhs[i] != rhs[i])
            return false;
    return true;
}

template <class T, class Alloc>
bool operator!= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
    return !(lhs == rhs);
}

template <class T, class Alloc>
bool operator<  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
    typename ft::vector<T,Alloc>::const_iterator first1 = lhs.begin();
    typename ft::vector<T,Alloc>::const_iterator last1 = lhs.end();
    typename ft::vector<T,Alloc>::const_iterator first2 = rhs.begin();
    typename ft::vector<T,Alloc>::const_iterator last2= rhs.end();

    while (first1!=last1)
    {
        if (first2==last2 || *first2<*first1) return false;
        else if (*first1<*first2) return true;
        ++first1; ++first2;
    }
    return (first2!=last2);

}

template <class T, class Alloc>
bool operator<= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
    if (lhs == rhs)
        return true;
    return lhs < rhs;
}

template <class T, class Alloc>
bool operator>  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
    return !(lhs < rhs) && !(lhs == rhs);
}

template <class T, class Alloc>
bool operator>= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
    if (lhs == rhs)
        return true;
    return lhs > rhs;
}


#endif 
