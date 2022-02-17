#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <cmath>
# include <iostream>
# include <limits>
# include "iterator.hpp"
# include "template_utils.hpp"

namespace ft {

	template <class T, class Alloc = std::allocator<T> >
		class vector {

			public:

				//      MEMBER TYPES
				typedef T 											value_type;
				typedef Alloc 										allocator_type;
				typedef typename allocator_type::reference			reference;
				typedef typename allocator_type::const_reference	const_reference;
				typedef typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_pointer;
				typedef std::ptrdiff_t 								difference_type;
				typedef size_t										size_type;

				typedef v_iterator<value_type>						iterator;
				typedef v_iterator<const value_type>				const_iterator;
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
					vector (InputIterator first, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last, const allocator_type& alloc = allocator_type()) {
						InputIterator iter = first;
						len = 0;
						siz = 0;

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
					if (x.siz)
						array = alloc.allocate(siz);
					for (size_type i = 0; i < len; i ++) {
						this->alloc.construct(array + i, x[i]);
					}
				}
				~vector() { 
					clear();
				}
				vector& operator=(const vector& x) {

					value_type * tmp = array;
					if (x.siz)
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
					void   		assign (typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last);
				void        assign (size_type n, const value_type& val);
				iterator    insert (iterator position, const value_type& val);
				iterator	insert (iterator position, size_type n, const value_type& val);
				template <class InputIterator>
					void		insert (iterator position, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last);
				iterator    erase (iterator position);
				iterator    erase (iterator first, iterator last);
				void        swap (vector& x);
				void        clear();


			private:

				void				copy_vector(vector &v);
		};


	template <class T, class Alloc>
		bool operator== (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
			return lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin());
		}

	template <class T, class Alloc>
		bool operator!= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
			return !(lhs == rhs);
		}

	template <class T, class Alloc>
		bool operator<  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
			return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

	template <class T, class Alloc>
		bool operator<= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
			return lhs < rhs || lhs == rhs;
		}

	template <class T, class Alloc>
		bool operator>  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
			return !(lhs < rhs) && !(lhs == rhs);
		}

	template <class T, class Alloc>
		bool operator>= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
			return lhs > rhs || lhs == rhs;
		}


}

template <class T, class Alloc>
void    ft::vector<T, Alloc>::push_back(const T & val) {
	if (this->len < this->siz) {
		this->alloc.construct(this->array + this->len++, val);
	}
	else {
		value_type * tmp = this->array;
		this->array = this->alloc.allocate(this->siz ? this->siz * 2 : 1);
		for (size_type i = 0; i < this->len; i++)
			this->array[i] = tmp[i];
		if (this->siz > 0)
			this->alloc.deallocate(tmp, this->siz);
		this->alloc.construct(this->array + this->len++, val);
		this->siz = this->siz ? this->siz * 2 : 1;
	}
}

template <class T, class Alloc>
void    ft::vector<T, Alloc>::pop_back() {
	alloc.destroy(&array[--len]);
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
void    ft::vector<T, Alloc>::assign (typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) {

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
void    ft::vector<T, Alloc>::insert(iterator position, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) {

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


#endif 
