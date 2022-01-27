#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "iterator.hpp"
# include <memory>
# include <cmath>
# include <iostream>
# include <limits>

template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };
/*
   template<typename> struct is_integral_base: std::false_type {};
   template<> struct is_integral_base<bool>: std::true_type {};
   template<> struct is_integral_base<const bool>: std::true_type {};
   template<> struct is_integral_base<int>: std::true_type {};
   template<> struct is_integral_base<const int>: std::true_type {};
   template<> struct is_integral_base<short>: std::true_type {};
   template<> struct is_integral_base<const short>: std::true_type {};
   template<> struct is_integral_base<char>: std::true_type {};
   template<> struct is_integral_base<const char>: std::true_type {};
   template<> struct is_integral_base<char16_t>: std::true_type {};
   template<> struct is_integral_base<const char16_t>: std::true_type {};
   template<> struct is_integral_base<char32_t>: std::true_type {};
   template<> struct is_integral_base<const char32_t>: std::true_type {};
   template<> struct is_integral_base<wchar_t>: std::true_type {};
   template<> struct is_integral_base<const wchar_t>: std::true_type {};
   template<> struct is_integral_base<long>: std::true_type {};
   template<> struct is_integral_base<const long>: std::true_type {};
   template<> struct is_integral_base<long long>: std::true_type {};
   template<> struct is_integral_base<const long long>: std::true_type {};
   template<typename T> struct is_integral: is_integral_base<T> {};
 */


namespace ft {

    template <class T, class Alloc = std::allocator<T> >
    	class vector {

    		public:

        		//      MEMBER TYPE
        		typedef T 											value_type;
        		typedef Alloc 										allocator_type;
        		typedef typename allocator_type::reference			reference;
        		typedef typename allocator_type::const_reference	const_reference;
        		typedef typename allocator_type::pointer			pointer;
        		typedef typename allocator_type::const_pointer		const_pointer;
        		typedef std::ptrdiff_t 								difference_type;
        		typedef size_t										size_type;

				typedef v_iterator<value_type>						iterator;
				typedef v_iterator<const value_type>					const_iterator;
				typedef ft::reverse_iterator<iterator>				reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;


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
					vector (InputIterator first, typename enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type last,
							const allocator_type& alloc = allocator_type()) {
						//vector (InputIterator first, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last,
                    	//  		const allocator_type& alloc = allocator_type()) {
						//            vector (InputIterator first, typename enable_if<std::is_same<InputIterator, ft::iterator>::value, InputIterator(),
						//                    const allocator_type& alloc = allocator_type()) {
						/*                len = &(*last) - &(*first); 
										  std::cout << "&(*last)  = " << &(*last) << std::endl;
										  std::cout << "&(*first) = " << &(*first) << std::endl;
										  std::cout << "len (&(*last) - &(*first) = " << len << std::endl;
                						  siz = len;*/
						InputIterator iter = first;
						len = 0;

						for (; iter != last; iter++)
							len++;
						siz = len;

                		this->alloc = alloc;
                		array = this->alloc.allocate(siz);
                		for (size_type i = 0; i < len; i++) {
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
            			if (siz > 0)
                			alloc.deallocate(array, siz);
        			}
        			vector& operator=(const vector& x) {
            			value_type * tmp = array;
            			array = alloc.allocate(x.siz);
            			for (size_type i = 0; i < x.len; i++)
                			alloc.construct(array + i, x[i]);
            			for (size_type i = 0; i < len; i++)
                			alloc.destroy(tmp + i);
            			if (siz > 0)
                			alloc.deallocate(tmp, siz);
            			len = x.len;
            			siz = x.siz;
            			return *this;
        			}


        			//      ITERATORS


					/*
        			   struct const_iterator {

        			   public:

        			   typedef T value_type;
        			   typedef typename allocator_type::reference reference;
        			   typedef typename allocator_type::pointer pointer;
        			   typedef std::ptrdiff_t difference_type;
        			   typedef std::random_access_iterator_tag iterator_category;

        			   private: 

            		   const_pointer ptr;

        			   public:

            		   const_iterator() {}
            		   const_iterator(pointer ptr) : ptr(ptr) {}
            		   const_iterator(const_pointer ptr) : ptr(ptr) {}
            		   const_iterator(iterator it) { ptr = &(*it); }
            		//const_iterator(const_iterator & cit) { ptr = &(*cit); }
					//const_iterator operator=(const_iterator & cit) { this->ptr = cit.ptr; return (*this); }

            		const_reference operator*() const { return *ptr; }
            		const_pointer operator->() const { return ptr; }

            		const_iterator& operator++() { ptr++; return *this; }
            		const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }

            		const_iterator& operator--() { ptr--; return *this; }
            		const_iterator operator--(int) { const_iterator tmp = *this; --ptr; return tmp; }

            		const_iterator& operator+=(difference_type n) { ptr += n; return *this; }
            		const_iterator& operator-=(difference_type n) { ptr -= n; return *this; }

					difference_type operator+(const const_iterator &rhs) const { return (this->ptr + rhs.ptr); }
					difference_type operator-(const const_iterator &rhs) const { return (this->ptr - rhs.ptr); }

					const_iterator::reference	operator[](difference_type n) const { return (this->ptr[n]); }

            		friend bool operator==(const const_iterator& a, const const_iterator& b) { return a.ptr == b.ptr; }
            		friend bool operator!=(const const_iterator& a, const const_iterator& b) { return a.ptr != b.ptr; }

            		friend const_iterator operator+(const const_iterator& a, const int& b) { return &*a + b; }
            		friend const_iterator operator+(const int& a, const const_iterator& b) { return a + &*b; }
            		friend const_iterator operator-(const const_iterator& a, const int& b) { return &*a - b; }
            		friend const_iterator operator-(const int& a, const const_iterator& b) { return a - &*b; }

            		friend bool operator<(const const_iterator&a, const const_iterator&b ) { return &*a < &*b; }
            		friend bool operator>(const const_iterator&a, const const_iterator&b ) { return &*a > &*b; }
            		friend bool operator<=(const const_iterator&a, const const_iterator&b ) { return &*a <= &*b; }
            		friend bool operator>=(const const_iterator&a, const const_iterator&b ) { return &*a >= &*b; }


        			};

        			struct reverse_iterator {

        			public:

        			typedef T value_type;
        			typedef typename allocator_type::reference reference;
        			typedef typename allocator_type::pointer pointer;
        			typedef std::ptrdiff_t difference_type;
        			typedef std::random_access_iterator_tag iterator_category;


        			private: 

            		pointer ptr;

        				public:

            		reverse_iterator() {}
            		reverse_iterator(pointer ptr) : ptr(ptr) {}
            		reverse_iterator(iterator it) { ptr = &(*it); }
					reverse_iterator(const_iterator cit) { ptr = &(*cit); }
            		reverse_iterator(reverse_iterator const & rit) { ptr = rit.ptr; }
					//reverse_iterator operator=(iterator & it) { this->ptr = it.ptr; return (*this); }
					//reverse_iterator operator=(const_iterator & cit) { this->ptr = cit.ptr; return (*this); }
					//reverse_iterator operator=(reverse_iterator & rit) { this->ptr = rit.ptr; return (*this); }
					//reverse_iterator operator=(reverse_iterator rit) { this->ptr = rit.ptr; return (*this); }
					//reverse_iterator operator=(const_reverse_iterator & crit) { this->ptr = crit.ptr; return (*this); }

					iterator base() const { return iterator(this->ptr); };

            		reference operator*() const { return *ptr; }
            		pointer operator->() const { return ptr; }

            		reverse_iterator& operator++() { ptr--; return *this; }
            		reverse_iterator operator++(int) { reverse_iterator tmp = *this; --ptr; return tmp; }

            		reverse_iterator& operator--() { ptr++; return *this; }
            		reverse_iterator operator--(int) { reverse_iterator tmp = *this; ++(*this); return tmp; }

            		reverse_iterator& operator+=(difference_type n) { ptr -= n; return *this; }
            		reverse_iterator& operator-=(difference_type n) { ptr += n; return *this; }

					difference_type operator+(const reverse_iterator &rhs) const { return (this->ptr - rhs.ptr); }
					difference_type operator-(const reverse_iterator &rhs) const { return (this->ptr + rhs.ptr); }

					reverse_iterator & operator+(difference_type n) {ptr += n; return *this; }
					reverse_iterator & operator-(difference_type n) {ptr -= n; return *this; }

					reverse_iterator::reference	operator[](difference_type n) const { return (this->ptr[n]); }

            		friend bool operator==(const reverse_iterator& a, const reverse_iterator& b) { return a.ptr == b.ptr; }
            		friend bool operator!=(const reverse_iterator& a, const reverse_iterator& b) { return a.ptr != b.ptr; }

            		friend reverse_iterator operator+(const reverse_iterator& a, const difference_type& b) { return &*a + b; }
            		friend reverse_iterator operator+(const difference_type& a, const reverse_iterator& b) { return a + &*b; }
            		friend reverse_iterator operator-(const reverse_iterator& a, const difference_type& b) { return a.operator-(b); }
            		friend reverse_iterator operator-(const difference_type& a, const reverse_iterator& b) { return a - &*b; }

            		friend bool operator<(const reverse_iterator&a, const reverse_iterator&b ) { return &*a < &*b; }
            		friend bool operator>(const reverse_iterator&a, const reverse_iterator&b ) { return &*a > &*b; }
            		friend bool operator<=(const reverse_iterator&a, const reverse_iterator&b ) { return &*a <= &*b; }
            		friend bool operator>=(const reverse_iterator&a, const reverse_iterator&b ) { return &*a >= &*b; }

        			};

        			struct const_reverse_iterator {

						public:

        					typedef T value_type;
        					typedef typename allocator_type::reference reference;
        					typedef typename allocator_type::pointer pointer;
        					typedef std::ptrdiff_t difference_type;
        					typedef std::random_access_iterator_tag iterator_category;

        				private: 

            				const_pointer ptr;

        				public:

            				const_reverse_iterator() {}
            				const_reverse_iterator(const_pointer & ptr) : ptr(ptr) {}
            				const_reverse_iterator(iterator & it) { ptr = &(*it); }
            				const_reverse_iterator(const_iterator & cit) { ptr = &(*cit); }
            				const_reverse_iterator(reverse_iterator & rit) { ptr = &(*rit); }
            				const_reverse_iterator(const_reverse_iterator & rit) { ptr = &(*rit); }
							//const_reverse_iterator operator=(reverse_iterator & crit) { this->ptr = crit.base(); return (*this); }

							const_iterator base() const { return const_iterator(this->ptr); };

            				const_reference operator*() const { return *ptr; }
            				const_pointer operator->() const { return ptr; }

            				const_reverse_iterator& operator++() { ptr--; return *this; }
            				const_reverse_iterator operator++(int) { const_reverse_iterator tmp = *this; --ptr; return tmp; }

            				const_reverse_iterator& operator--() { ptr++; return *this; }
            				const_reverse_iterator operator--(int) { const_reverse_iterator tmp = *this; ++(*this); return tmp; }

            				const_reverse_iterator& operator+=(difference_type n) { ptr -= n; return *this; }
            				const_reverse_iterator& operator-=(difference_type n) { ptr += n; return *this; }

							difference_type operator+(const const_reverse_iterator &rhs) const { return (this->ptr - rhs.ptr); }
							difference_type operator-(const const_reverse_iterator &rhs) const { return (this->ptr + rhs.ptr); }

							const_reverse_iterator::reference	operator[](difference_type n) const { return (this->ptr[n]); }

            				friend bool operator==(const const_reverse_iterator& a, const const_reverse_iterator& b) { return a.ptr == b.ptr; }
            				friend bool operator!=(const const_reverse_iterator& a, const const_reverse_iterator& b) { return a.ptr != b.ptr; }

            				friend const_reverse_iterator operator+(const const_reverse_iterator& a, const int& b) { return &*a + b; }
            				friend const_reverse_iterator operator+(const int& a, const const_reverse_iterator& b) { return a + &*b; }
            				friend const_reverse_iterator operator-(const const_reverse_iterator& a, const int& b) { return &*a - b; }
            				friend const_reverse_iterator operator-(const int& a, const const_reverse_iterator& b) { return a - &*b; }

            				friend bool operator<(const const_reverse_iterator&a, const const_reverse_iterator&b ) { return &*a < &*b; }
            				friend bool operator>(const const_reverse_iterator&a, const const_reverse_iterator&b ) { return &*a > &*b; }
            				friend bool operator<=(const const_reverse_iterator&a, const const_reverse_iterator&b ) { return &*a <= &*b; }
            				friend bool operator>=(const const_reverse_iterator&a, const const_reverse_iterator&b ) { return &*a >= &*b; }
        			};
					*/








        			iterator begin() { return iterator(&array[0]); }
        			iterator end() { return iterator(&array[len]); }

        			const_iterator begin() const { return const_iterator(&array[0]); }
        			const_iterator end() const { return const_iterator(&array[len]); }

        			reverse_iterator rbegin() { return reverse_iterator(&array[len]); }
        			reverse_iterator rend() { return reverse_iterator(&array[0]); }

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
                			if (siz > 0)
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
                			if (siz > 0)
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
            			void    assign (InputIterator first, typename enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type last);
        			void        assign (size_type n, const value_type& val);
        			iterator    insert (iterator position, const value_type& val);
        			iterator	insert (iterator position, size_type n, const value_type& val);
        			template <class InputIterator>
            			void    insert (iterator position, InputIterator first, typename enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type last);
        			iterator    erase (iterator position);
        			iterator    erase (iterator first, iterator last);
        			void        swap (vector& x);
        			void        clear();


    				//      NON MEMBER-FUNCTIONS OVERLOADS

					void				copy_vector(vector &v);
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
        					if (this->siz > 0)
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
        					alloc.destroy(&array[i]);
    					if (siz > 0)
        					alloc.deallocate(array, siz);
    					len = 0;
    					siz = 0;
					}

				template <class T, class Alloc>
    				template <class InputIterator>
    				void    ft::vector<T, Alloc>::assign (InputIterator first, typename enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type last) {

						InputIterator iter = first;
						size_type n = 0;

						for (; iter != last; iter++)
							n++;

        				if (n <= siz) {
            				for (size_type i = 0; i < n; i++)
                				alloc.construct(array + i, *first++);
            				len = n;
        				}
        				else {
            				value_type *tmp = array;
            				array = alloc.allocate(n);
            				for (size_type i = 0; i < n; i++)
                				alloc.construct(array + i, *first++);
            				for (size_type i = 0; i < len; i++)
                				alloc.destroy(tmp + i);
            				if (siz > 0)
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
        					if (siz > 0)
            					alloc.deallocate(tmp, siz);
        					len = n;
        					siz = n;
    					}
					}


				template <class T, class Alloc> 
					typename ft::vector<T, Alloc>::iterator   ft::vector<T, Alloc>::insert(iterator position, const value_type& val) {

    					return insert(position, 1u, val);;
					}


				template <class T, class Alloc>
					typename ft::vector<T, Alloc>::iterator        ft::vector<T, Alloc>::insert(iterator position, size_type n, const value_type& val) {

						iterator newpos;

    					int i;
    					if (len + n <= siz) {
        					for (i = len - 1; i >= 0 && &array[i] >= &*position; i--)
            					array[i + n] = array[i];
        					i++;
        					for (size_type j = 0; j < n; j++) {
            					alloc.construct(array + i + j, val);
								if (j == 0)
									newpos = (array + i);
							}
        					len += n;
    					}
    					else {
        					value_type * tmp = array;
        					array = alloc.allocate(siz + n - (siz - len));
        					for (size_type i = 0; i < len; i++)
            					array[i] = tmp[i];
        					for (i = len - 1; i >= 0 && &tmp[i] >= &*position; i--)
            					array[i + n] = array[i];
        					i++;
        					for (size_type j = 0; j < n; j++) {
            					alloc.construct(array + i + j , val);
								if (j == 0)
									newpos = (array + i);
							}
        					for (size_type i = 0; i < len; i++)
            					alloc.destroy(tmp + i);
        					if (siz > 0)
            					alloc.deallocate(tmp, siz);
        					siz += n - (siz - len);
        					len += n;
    					}
						return newpos;
					}

				template <class T, class Alloc>
					template <class InputIterator>
					void    ft::vector<T, Alloc>::insert(iterator position, InputIterator first, typename enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type last) {

						InputIterator iter = first;
						size_type n = 0;

						for (; iter != last; iter++)
							n++;
						//    		int n = &*last - &*first;

    					size_type pos = &*position - &array[0];
    					for (size_type i = 0; i < n; i++) {
        					insert(position, 1u, *--last);
        					position = iterator(&array[pos]); 
    					}
					}

				template <class T, class Alloc>
					typename ft::vector<T, Alloc>::iterator     ft::vector<T, Alloc>::erase(iterator position) {

    					size_type i = 0;
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

    					size_type n = &*last - &*first;
    					iterator it = first;
    					for (size_type i = 0; i < n; i++)
        					it = erase(it);
    					return it;

					}

				template <typename T, typename Alloc>
					void	ft::vector<T, Alloc>::copy_vector(vector<T, Alloc> &v) {
						this->array = v.array;
						this->alloc = v.alloc;
						this->len = v.len;
						this->siz= v.siz;
						v.array = NULL;
						v.len = 0;
						v.siz = 0;

					}

				template <class T, class Alloc>
					void        ft::vector<T, Alloc>::swap(vector& x) {

    					vector<T, Alloc> swp;

						swp.copy_vector(x);
    					x.copy_vector(*this);
    					this->copy_vector(swp);
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
