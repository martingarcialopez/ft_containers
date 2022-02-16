#ifndef TEMPLATE_UTILS_HPP
# define TEMPLATE_UTILS_HPP


namespace ft {

	template<bool B, class T = void>
		struct enable_if {};

	template<class T>
		struct enable_if<true, T> { typedef T type; };

	template <class T, T v>
		struct integral_constant {
			static const T	value = v;
			typedef T			value_type;
			typedef integral_constant<T,v> type;
		};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	template<typename> struct is_integral_base: false_type {};
	template<> struct is_integral_base<bool>: true_type {};
	template<> struct is_integral_base<const bool>: true_type {};
	template<> struct is_integral_base<int>: true_type {};
	template<> struct is_integral_base<const int>: true_type {};
	template<> struct is_integral_base<short>: true_type {};
	template<> struct is_integral_base<const short>: true_type {};
	template<> struct is_integral_base<char>: true_type {};
	template<> struct is_integral_base<const char>: true_type {};
	template<> struct is_integral_base<wchar_t>: true_type {};
	template<> struct is_integral_base<const wchar_t>: true_type {};
	template<> struct is_integral_base<long>: true_type {};
	template<> struct is_integral_base<const long>: true_type {};
	template<> struct is_integral_base<long long>: true_type {};
	template<> struct is_integral_base<const long long>: true_type {};
	template<typename T> struct is_integral: is_integral_base<T> {};


	template <class T1, class T2>
		struct pair {

			typedef T1		first_type;
			typedef T2		second_type;

			first_type		first;
			second_type		second;


			pair() {};
			template<class U, class V>
				pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}
			pair (const first_type& a, const second_type& b) : first(a), second (b) {}

			pair& operator= (const pair& pr) {

				first = pr.first;
				second = pr.second;

				return *this;
			}

			operator pair<const T1, T2> () const { return (pair<const T1, T2>(first, second)); }
		};

	template <class T1,class T2>
		pair<T1,T2> make_pair (T1 x, T2 y)
		{
			return ( pair<T1,T2>(x,y) );
		}

	template <class T1, class T2>
		bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first==rhs.first && lhs.second==rhs.second; }

	template <class T1, class T2>
		bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs==rhs); }

	template <class T1, class T2>
		bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }

	template <class T1, class T2>
		bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(rhs<lhs); }

	template <class T1, class T2>
		bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return rhs<lhs; }

	template <class T1, class T2>
		bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs<rhs); }

	template <class InputIterator1, class InputIterator2>
		bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2)
		{
			while (first1!=last1)
			{
				if (first2==last2 || *first2<*first1) return false;
				else if (*first1<*first2) return true;
				++first1; ++first2;
			}
			return (first2!=last2);
		}


}


#endif
