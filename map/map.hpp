#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <iostream>
# include <limits>
//# include "iterator.hpp"



namespace ft {

	template<typename Key, typename T>
		struct Node {

			Node() { dad = NULL; left = NULL; right = NULL; };
			Node(std::pair<const Key, T> val)/* : data(val)*/ {

				dad = NULL;
				left = NULL;
				right = NULL;


				key = val.first;
				value = val.second;
			}
			~Node() {};

			Node		*dad;
			Node		*left;
			Node		*right;

//			std::pair<Key, T> data;
			Key			key;
			T			value;


		};
/*
	template<typename Key, typename T>
		void	print_node(t_node<Key, T> *node) {

			std::cout << node->key << std::endl;
		}

	template<typename Key, typename T>
		void	print_tree_inorder(t_node<Key, T> *node) {

			if (!node)
				return ;
			print_node(node);
			if (node->left != NULL)
				print_tree_inorder(node->left);
			if (node->right != NULL)
				print_tree_inorder(node->right);

		}
*/
	template < class Key,                                     // map::key_type
           	 class T,                                       // map::mapped_type
           	 class Compare = std::less<Key>,                     // map::key_compare
           	 class Alloc = std::allocator<std::pair<const Key,T> >    // map::allocator_type
				 > class map {

					 public:

						 //		MEMBER TYPES
						 typedef std::pair<const Key, T> 					value_type;
						 typedef Key										key_type;
						 typedef T											mapped_type;
						 typedef Compare									key_compare;
						 typedef Alloc										allocator_type;
        				 typedef typename allocator_type::reference			reference;
        				 typedef typename allocator_type::const_reference	const_reference;
        				 typedef typename allocator_type::pointer			pointer;
        				 typedef typename allocator_type::const_pointer		const_pointer;
        				 typedef std::ptrdiff_t 							difference_type;
        				 typedef size_t										size_type;

						 typedef int										iterator;
						 typedef int										const_iterator;


					 //private:
					public:

						 allocator_type		alloc;
						 key_compare		comp;
						 Node<key_type, mapped_type>	*root;


					 public:

						 //		MEMBER FUNCTIONS
						 explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
						 
							 root = NULL;
						 };

						 template <class InputIterator>
							 map (InputIterator first, InputIterator last,
									 const key_compare& comp = key_compare(),
									 const allocator_type& alloc = allocator_type()) {

								 // TO DO TO DO TO DO TO DO TO DO

							 }


						 map (const map& x) {

							 alloc = x.alloc;
							 comp = x.comp;
							 root = x.root;

						 }

						 ~map() {

							 // TO_DO: DEALOCATE EVERYTHING
						 }

						 map& operator= (const map& x) {

							 alloc = x.alloc;
							 comp = x.comp;
							 root = x.root;

							 return *this;
						 }


						 //		ITERATORS




						 //		CAPACITY



						 //		OBSERVERS

						key_compare key_comp() const { return key_compare(comp); }


						 //		ELEMENT ACCESS

						 mapped_type& operator[] (const key_type& k);


						 //		MODIFIERS

						 std::pair<iterator, bool>		alloc_node(Node<key_type, mapped_type>* node, const value_type& val) {
						 
							node = alloc.allocate(sizeof(Node<key_type, mapped_type>)); // <---- rebind allocator to alloc nodes
							alloc.construct(node, Node<key_type, mapped_type>(val));

							return std::pair<iterator, bool>();
						 
						 }

						 std::pair<iterator, bool>		recursive_insert(const value_type& val, Node<key_type,
								 mapped_type>* node, key_compare map_comp) {

							 if (node == NULL)
								 return alloc_node(node, val);
							 else if (map_comp(val.first, node->key))
									 return recursive_insert(val, node->left, map_comp);
							else
									 return recursive_insert(val, node->right, map_comp);

						}

						 std::pair<iterator,bool>		insert (const value_type& val) {
							 
							 key_compare	map_comp = key_comp();
							 return recursive_insert(val, root, key_comp());
						}

							
//							 std::cout << "map_comp( 3, 5) returns " << map_comp(5, 3) << std::endl;


						 iterator insert (iterator position, const value_type& val);
						 template <class InputIterator>
							 void insert (InputIterator first, InputIterator last);

						 void erase (iterator position);
						 size_type erase (const key_type& k);
						 void erase (iterator first, iterator last);

						 void swap (map& x);

						 void clear();






						 //		OPERATIONS

						 iterator find (const key_type& k);
						 const_iterator find (const key_type& k) const;



						 // TMP TMP TMP TMP TMP TMP TMP 

							 void	print_node(Node<key_type, mapped_type> *node) {

								 std::cout << "key: " << node->key << "       value: " <<
									 node->value << std::endl;
							 }

							 void	print_tree_inorder(Node<key_type, mapped_type> *node) {

								 if (!node)
									 return ;
								 print_node(node);
								 if (node->left != NULL)
									 print_tree_inorder(node->left);
								 if (node->right != NULL)
									 print_tree_inorder(node->right);

							 }

						 // TMP TMP TMP TMP TMP TMP TMP 

		   		 };

};


#endif
