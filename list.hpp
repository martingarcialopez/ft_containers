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

    private:

        value_type      data;
        pointer         next;
        pointer         prev;
        allocator_type  alloc;

    public:

        //      MEMBER FUNCTIONS
        
        explicit list (const allocator_type& alloc = allocator_type());
        explicit list (size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type());
        template <class InputIterator>
            list (InputIterator first, InputIterator last,
                    const allocator_type& alloc = allocator_type());
        list (const list& x);

        //      ITERATORS
   

        //      CAPACITY
   

        //      ELEMENT ACCESS
        
        reference front() { return *this; }
        const_reference front() const;

        //      MODIFIERS
    
        void push_front (const value_type& val);



        //      OPERATIONS


    };
}


#endif
