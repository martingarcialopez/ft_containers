#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include "Node.hpp"
#include "map.hpp"

namespace ft {

	template <class Iter>
		struct iterator_traits {
			typedef typename Iter::value_type			value_type;
			typedef typename Iter::difference_type		difference_type;
			typedef typename Iter::iterator_category	iterator_category;;
			typedef typename Iter::pointer 				pointer;
			typedef typename Iter::reference 			reference;
		};

	template <class S>
		struct iterator_traits<S*> {
			typedef std::random_access_iterator_tag iterator_category;
			typedef S                               value_type;
			typedef S*                              pointer;
			typedef S&                              reference;
			typedef std::ptrdiff_t                  difference_type;
		};

	template <class S>
		struct iterator_traits<const S*> {
			typedef std::random_access_iterator_tag iterator_category;
			typedef S                               value_type;
			typedef S*                              pointer;
			typedef S&                              reference;
			typedef std::ptrdiff_t                  difference_type;
		};



	template <typename T>
		struct v_iterator {

			public:

				typedef T								value_type;
				typedef value_type&						reference;
				typedef value_type*						pointer;
				typedef std::ptrdiff_t					difference_type;
				typedef std::random_access_iterator_tag iterator_category;

			private: 

				pointer _ptr;

			public:

				v_iterator() : _ptr(pointer()) {}
				v_iterator(pointer ptr) : _ptr(ptr) {}
				v_iterator(const T& ref) : _ptr(ref) {}
				operator v_iterator<const T> () const { return (v_iterator<const T>(this->_ptr)); }

				pointer	base() const { return _ptr; }

				reference operator*() const { return *_ptr; }
				pointer operator->() const { return _ptr; }
				reference operator[](size_t n) const { return *(_ptr + n); }


				v_iterator& operator++() { _ptr++; return *this; }
				v_iterator operator++(int) { v_iterator tmp = *this; ++(*this); return tmp; }

				v_iterator& operator--() { _ptr--; return *this; }
				v_iterator operator--(int) { v_iterator tmp = *this; --_ptr; return tmp; }

				v_iterator& operator+=(difference_type n) { _ptr += n; return *this; }
				v_iterator& operator-=(difference_type n) { _ptr -= n; return *this; }

				v_iterator operator+(difference_type n) const { return(this->_ptr + n); }
				v_iterator operator-(difference_type n) const { return (this->_ptr - n); }

		};	








	template <typename T>
		struct m_iterator {

			public:

				typedef T								value_type;
				typedef T&								reference;
				typedef T*								pointer;
				typedef std::ptrdiff_t					difference_type;
				typedef std::random_access_iterator_tag iterator_category;

			private:

				Node<T>*	_current;


			public:

				m_iterator() {}
				m_iterator(Node<T>* ptr) /*: _current(ptr)*/ {_current = ptr; }
//				m_iterator(Node<T>* const ptr) /*: _current(ptr)*/ {_current = ptr; }
//				m_iterator(m_iterator const &it) : _current(it.base()) {}
//				m_iterator(Node<const T>* ptr) : _current(ptr) {}
//				m_iterator(Node<const T>* ptr) : _current(ptr) {}
				//   KK			m_iterator(const T& ref) : _current(ref) {}
				operator m_iterator<const T> () const { return (m_iterator<const T>(_current)); }
				m_iterator& operator=(m_iterator const &rhs) {
					this->_current = rhs._current;
					return (*this);

				}
//				operator m_iterator<const T> () const { return (m_iterator<const T>(this->_current)); } 
				Node<T>*	base() const { return _current; }

				reference operator*() const { return _current->data; }
				pointer operator->() const { return &(_current->data); }

				m_iterator& operator++() { _current = next_node(_current); return *this; }
				m_iterator operator++(int) { m_iterator tmp = *this; ++(*this); return tmp; }

				m_iterator& operator--() { _current = prev_node(_current); return *this; }
				m_iterator operator--(int) { m_iterator tmp = *this; --(*this); return tmp; }


		};




	template <typename T>
		struct const_m_iterator {

			public:

				typedef T								value_type;
				typedef const T&								reference;
				typedef const T*								pointer;
				typedef std::ptrdiff_t					difference_type;
				typedef std::random_access_iterator_tag iterator_category;

			private:

				Node<T>* _current;


			public:

				const_m_iterator() {}
				const_m_iterator(Node<T>* const ptr) /*: _current(ptr)*/ {_current = ptr; }
//				const_m_iterator(Node<T>* const ptr) /*: _current(ptr)*/ {_current = ptr; }
				const_m_iterator(m_iterator<T> const &it) : _current(it.base()) {}
//				const_m_iterator(Node<const T>* ptr) : _current(ptr) {}
//				const_m_iterator(Node<const T>* ptr) : _current(ptr) {}
				//   KK			const_m_iterator(const T& ref) : _current(ref) {}
				operator const_m_iterator<const T> () const { return (const_m_iterator<const T>(_current)); }
				const_m_iterator& operator=(const_m_iterator const &rhs) {
					this->_current = rhs._current;
					return (*this);

				}
//				operator const_m_iterator<const T> () const { return (m_iterator<const T>(this->_current)); } 
				Node<T>*	base() const { return _current; }

				reference operator*() const { return _current->data; }
				pointer operator->() const { return &(_current->data); }

				const_m_iterator& operator++() { _current = next_node(_current); return *this; }
				const_m_iterator operator++(int) { const_m_iterator tmp = *this; ++(*this); return tmp; }

				const_m_iterator& operator--() { _current = prev_node(_current); return *this; }
				const_m_iterator operator--(int) { const_m_iterator tmp = *this; --(*this); return tmp; }


		};



	template <typename T>
		bool operator==(const const_m_iterator<T>& a, const const_m_iterator<T>& b) {  return a.base() == b.base(); }
	template <typename T, typename S>
		bool operator==(const const_m_iterator<T>& a, const const_m_iterator<S>& b) {  return a.base() == b.base(); }
	template <typename T>
		bool operator!=(const const_m_iterator<T>& a, const const_m_iterator<T>& b) {  return a.base() != b.base(); }
	template <typename T, typename S>
		bool operator!=(const const_m_iterator<T>& a, const const_m_iterator<S>& b) {  return a.base() != b.base(); }




	template <typename T>
		bool operator==(const m_iterator<T>& a, const m_iterator<T>& b) {  return a.base() == b.base(); }
	template <typename T, typename S>
		bool operator==(const m_iterator<T>& a, const m_iterator<S>& b) {  return a.base() == b.base(); }
	template <typename T>
		bool operator!=(const m_iterator<T>& a, const m_iterator<T>& b) {  return a.base() != b.base(); }
	template <typename T, typename S>
		bool operator!=(const m_iterator<T>& a, const m_iterator<S>& b) {  return a.base() != b.base(); }


	template <typename Iter>
		class reverse_iterator {

			public:

				typedef typename iterator_traits<Iter>::value_type			value_type;
				typedef typename iterator_traits<Iter>::difference_type		difference_type;
				typedef typename iterator_traits<Iter>::pointer				pointer;
				typedef typename iterator_traits<Iter>::reference			reference;
				typedef typename iterator_traits<Iter>::iterator_category	iterator_category;

			private:

				Iter _base;

			public:

				reverse_iterator(): _base() {}
				reverse_iterator(Iter it): _base(it) {} 
				reverse_iterator(const reverse_iterator& rit): _base(rit._base) {}
				template <typename Iter2>
					reverse_iterator(const reverse_iterator<Iter2>& it) : _base(it.base()) {}
				template <typename Iter2>
					reverse_iterator& operator=(const reverse_iterator<Iter2>& it) { _base = it.base(); return *this; }

				Iter base() const { return _base; }

				reference	operator*() const { Iter tmp = _base; return *--tmp; }
				pointer		operator->() const { return &(operator*()); }
				reverse_iterator&	operator++()		{ --_base; return *this; }
				reverse_iterator	operator++(int)		{ reverse_iterator tmp(*this); --_base; return tmp; }
				reverse_iterator&	operator--()		{ ++_base; return *this; }
				reverse_iterator	operator--(int)		{ reverse_iterator tmp(*this); ++_base; return tmp; }
				reverse_iterator	operator+ (difference_type n) const { return reverse_iterator (_base - n); }
				reverse_iterator	operator+=(difference_type n) { _base -= n; return *this; }
				reverse_iterator	operator- (difference_type n) const { return reverse_iterator (_base + n); }
				reverse_iterator	operator-=(difference_type n) { _base += n; return *this; }
				reference			operator[](difference_type n) const { return *(*this + n); }


		};

	template <class Ite>
		bool operator==(const reverse_iterator<Ite>& lhs, const reverse_iterator<Ite>& rhs)
		{ return lhs.base() == rhs.base(); }
	template <class Ite, class Ite2>
		bool operator==(const reverse_iterator<Ite>& lhs, const reverse_iterator<Ite2>& rhs)
		{ return lhs.base() == rhs.base(); }

	template <class Ite>
		bool operator!=(const reverse_iterator<Ite>& lhs, const reverse_iterator<Ite>& rhs)
		{ return lhs.base() != rhs.base(); }
	template <class Ite, class Ite2>
		bool operator!=(const reverse_iterator<Ite>& lhs, const reverse_iterator<Ite2>& rhs)
		{ return lhs.base() != rhs.base(); }

	template <class Ite>
		bool operator<(const reverse_iterator<Ite>& lhs, const reverse_iterator<Ite>& rhs)
		{ return lhs.base() > rhs.base(); }
	template <class Ite, class Ite2>
		bool operator<(const reverse_iterator<Ite>& lhs, const reverse_iterator<Ite2>& rhs)
		{ return lhs.base() > rhs.base(); }

	template <class Ite>
		bool operator<=(const reverse_iterator<Ite>& lhs, const reverse_iterator<Ite>& rhs)
		{ return lhs.base() >= rhs.base(); }
	template <class Ite, class Ite2>
		bool operator<=(const reverse_iterator<Ite>& lhs, const reverse_iterator<Ite2>& rhs)
		{ return lhs.base() >= rhs.base(); }

	template <class Ite>
		bool operator>(const reverse_iterator<Ite>& lhs, const reverse_iterator<Ite>& rhs)
		{ return lhs.base() < rhs.base(); }
	template <class Ite, class Ite2>
		bool operator>(const reverse_iterator<Ite>& lhs, const reverse_iterator<Ite2>& rhs)
		{ return lhs.base() < rhs.base(); }

	template <class Ite>
		bool operator>=(const reverse_iterator<Ite>& lhs, const reverse_iterator<Ite>& rhs)
		{ return lhs.base() <= rhs.base(); }
	template <class Ite, class Ite2>
		bool operator>=(const reverse_iterator<Ite>& lhs, const reverse_iterator<Ite2>& rhs)
		{ return lhs.base() <= rhs.base(); }

	template <class Ite>
		reverse_iterator<Ite> operator+(typename reverse_iterator<Ite>::difference_type n, const reverse_iterator<Ite>& it)
		{ return reverse_iterator<Ite>(it.base() - n); }
	template <class Ite, class Ite2>
		reverse_iterator<Ite> operator+(typename reverse_iterator<Ite>::difference_type n, const reverse_iterator<Ite2>& it)
		{ return reverse_iterator<Ite>(it.base() - n); }

	template <class Ite>
		typename reverse_iterator<Ite>::difference_type operator-(const reverse_iterator<Ite>& it, const reverse_iterator<Ite>& it2)
		{ return (it2.base() - it.base()); }
	template <class Ite, class Ite2>
		typename reverse_iterator<Ite>::difference_type operator-(const reverse_iterator<Ite>& it, const reverse_iterator<Ite2>& it2)
		{ return (it2.base() - it.base()); }








	template <typename T>
		bool operator==(const v_iterator<T>& a, const v_iterator<T>& b) { return &*a == &*b; }
	template <typename T, typename S>
		bool operator==(const v_iterator<T>& a, const v_iterator<S>& b) { return &*a == &*b; }

	template <typename T>
		bool operator!=(const v_iterator<T>& a, const v_iterator<T>& b) { return &*a != &*b; }
	template <typename T, typename S>
		bool operator!=(const v_iterator<T>& a, const v_iterator<S>& b) { return &*a != &*b; }

	template <typename T>
		bool operator<(const v_iterator<T>&a, const v_iterator<T>&b ) { return &*a < &*b; }
	template <typename T, typename S>
		bool operator<(const v_iterator<T>&a, const v_iterator<S>&b ) { return &*a < &*b; }

	template <typename T>
		bool operator>(const v_iterator<T>&a, const v_iterator<T>&b ) { return &*a > &*b; }
	template <typename T, typename S>
		bool operator>(const v_iterator<T>&a, const v_iterator<S>&b ) { return &*a > &*b; }

	template <typename T>
		bool operator<=(const v_iterator<T>&a, const v_iterator<T>&b ) { return &*a <= &*b; }
	template <typename T, typename S>
		bool operator<=(const v_iterator<T>&a, const v_iterator<S>&b ) { return &*a <= &*b; }

	template <typename T>
		bool operator>=(const v_iterator<T>&a, const v_iterator<T>&b ) { return &*a >= &*b; }
	template <typename T, typename S>
		bool operator>=(const v_iterator<T>&a, const v_iterator<S>&b ) { return &*a >= &*b; }

	template <typename T>
		typename v_iterator<T>::difference_type operator-(const v_iterator<T>& it, const v_iterator<T>& it2)
		{ return (&*it - &*it2); }
	template <typename T, typename S>
		typename v_iterator<T>::difference_type operator-(const v_iterator<T>& it, const v_iterator<S>& it2)
		{ return (&*it - &*it2); }

	template <typename T>
		v_iterator<T> 					operator+(typename v_iterator<T>::difference_type n, v_iterator<T>& it)
		{ return (it.base() + n); }
	/*	template <typename T, typename S>
		typename v_iterator<T>::difference_type operator+(const v_iterator<T>& it, const v_iterator<S>& it2)
		{ return (&*it + &*it2); }*/



}


#endif
