#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include <cmath>
# include <iostream>

namespace ft {

    template <class T, class Alloc = std::allocator<T> >
    class list {

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

    //private:
    public:

        pointer                 data;
        ft::list<value_type> *  next;
        ft::list<value_type> *  prev;
        allocator_type          alloc;

    public:

        //      MEMBER FUNCTIONS
        
        explicit list (const allocator_type& alloc = allocator_type()) {
            data = NULL;
            next = this;
            prev = this;
        }
/*
        explicit list (size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()) {
            data = NULL;
            next = this;
            prev = this;
            for (size_type i = 0; i < n; i++) {
                
            }
        }

        template <class InputIterator>
            list (InputIterator first, InputIterator last,
                    const allocator_type& alloc = allocator_type());

        list (const list& x);
*/


        /*list&   operator=(const list& x) {
            data = x.data;
            next = x.next;
            prev = x.prev;
            alloc = x.alloc;
        }*/

        //      ITERATORS
   
/*        struct iterator {

        private: 

            pointer ptr;

        public:

            iterator() {}
            iterator(pointer ptr) : ptr(ptr) {}
            //iterator(iterator& it) { ptr = &(*it); }

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

        };*/


        //      CAPACITY
   

        //      ELEMENT ACCESS
        
        reference front() { return *this; }
        const_reference front() const;

        //      MODIFIERS
    
        void push_front (const value_type& val) {

        ft::list<value_type> * new_lst = new ft::list<value_type>;

        //new_lst = alloc.allocate(1);
        
        new_lst->data = new value_type;
        *new_lst->data = val;


        ft::list<value_type> * lst = this;
        while (lst->data != NULL) {
           lst = lst->next; 
        }
        (lst->next)->prev = new_lst;
        new_lst->next = lst->next;
        new_lst->prev = lst;
        lst->next = new_lst;

        //    prev = alloc.allocate(1);
        //
        //    CREATE NEW
        //    
        //    (NULL next) prev = NEW
        //    NEW next = NULL next 
        //    NEW prev = NULL
        //
        //    NULL next = NEW
        //    
        
        }



        //      OPERATIONS


    };
}


#endif
