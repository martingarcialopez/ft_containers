#ifndef MAP_HPP 
# define MAP_HPP 

# include <memory>
# include <cmath>
# include <iostream>

#define HASHSIZE 831431

template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

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



namespace ft {

    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
    class map {

    public:

        //      MEMBER TYPE
        typedef Key key_type;
        typedef T mapped_type;
        typedef std::pair<const key_type, mapped_type> value_type;
        //typedef  value_compare;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;

    private:

typedef struct hashlist {
    char *name;
    char *value;
    struct hashlist *next;
}hlist;

static hlist *hashtab[HASHSIZE];

unsigned long	hash(char *str) { //djb2
	unsigned long hash = 5381;
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return hash % HASHSIZE;
}

hlist		*lookup(char *s) {
    hlist	*np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
          	return np;
    return NULL;
}

hlist		*install(char *name, char *value) {
    hlist			*np;
    unsigned long	hashval;

    if ((np = lookup(name)) == NULL) { 
        np = (hlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
          	return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    	if ((np->value = strdup(value)) == NULL)
	       	return NULL;
    }
    return np;
}

void    dlete(char *name) {
	unsigned int hashval = hash(name);
	hlist *np, *prev = NULL;

	for (np = hashtab[hashval]; np != NULL; np = np->next) {
		if (strcmp(name, np->name) == 0)
			break ;
		prev = np;
	}
	if (np != NULL) {
		if (prev == NULL)
			hashtab[hashval] = np->next;
		else
			prev->next = np->next;
		free(np->name);
		free(np->value);
		free(np);
	}
}

void		output_value(char *name) {
	hlist	*elem;

	elem = lookup(name);
	if (!elem)
		printf("%s: Not found\n", name);
	else
		printf("%s\n", elem->value);
}

void		free_hashtable(void) {
	hlist	*np;

	for (size_t i = 0; i < 0; i++) {
		for (np = hashtab[i]; np != NULL; np = np->next) {
			hashtab[i] = np->next;
			free(np->name);
			free(np->value);
			free(np);
		}
	}
}


    private:

//        static hlist *hashtab[HASHSIZE];

        size_type       len;
        size_type       siz;
        value_type *    array;
        allocator_type  alloc;


    public:


        //      MEMBER FUNCTIONS
        explicit map (/*const key_compare& comp = key_compare(),*/
              const allocator_type& alloc = allocator_type()) {}


        //      ITERATORS
        struct iterator {

        public:

        typedef T value_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::pointer pointer;
        typedef ptrdiff_t difference_type;
        typedef std::random_access_iterator_tag iterator_category;

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

        //iterator begin() { return iterator(&array[0]); }
       // iterator end() { return iterator(&array[len]); }

        //      CAPACITY


        //      ELEMENT ACCESS
        std::pair<iterator,bool> insert (const value_type& val) {

        }


        //      MODIFIERS

        //      OBSERVERS
        

        //      OPERATIONS


        


    //      NON MEMBER-FUNCTIONS OVERLOADS
    
    };

}

#endif 
