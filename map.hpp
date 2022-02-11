#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <iostream>
# include <limits>
# include "template_utils.hpp"
# include "Node.hpp"
# include "iterator.hpp"


/* TO DO: 	Range constructor
 * 			erase() return value
 *			Properly free del nodes on erase()
 *
 *
 */ 

namespace ft {

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
		class map {

			public:

				//		MEMBER TYPES
				typedef ft::pair<const Key, T> 					value_type;
				typedef Key											key_type;
				typedef T											mapped_type;
				typedef Compare										key_compare;
				typedef Alloc										allocator_type;
				typedef typename allocator_type::reference			reference;
				typedef typename allocator_type::const_reference	const_reference;
				typedef typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_pointer;
				typedef std::ptrdiff_t 							difference_type;
				typedef size_t										size_type;

				typedef m_iterator<value_type>						iterator;
				typedef m_iterator<const value_type>				const_iterator;
				typedef ft::reverse_iterator<iterator>				reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

			public:

				typedef typename Alloc::template rebind< Node<value_type> >::other				node_allocator;
				typedef typename Alloc::template rebind< Node<value_type> >::other::pointer	node_pointer;
				//						 typedef typename Node<Key,T>												node;


				class value_compare
				{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
					friend class map;
					protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
					public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
				};


				//private:
			public:

				allocator_type		alloc;
				node_allocator		node_alloc;
				key_compare			comp;
				node_pointer		root;
				size_type			siz;


			public:

				//		MEMBER FUNCTIONS
				explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
					: root(NULL), siz(0) {};


				template <class InputIterator>
					map (InputIterator first, InputIterator last,
							const key_compare& comp = key_compare(),
							const allocator_type& alloc = allocator_type()) : root(NULL), siz(0) {

						// TO DO TO DO TO DO TO DO TO DO

					}


				map (const map& x) {

					alloc = x.alloc;
					comp = x.comp;
					root = x.root;
					siz = x.siz;

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
				iterator begin() { return iterator(leftmost_node(root)); }
//				const_iterator begin() const { return const_iterator(leftmost_node(root)); }

				iterator end() { return iterator(rightmost_node(root)->right); }
				const_iterator end() const { return const_iterator(rightmost_node(root)->right); }

				reverse_iterator rbegin() { return  reverse_iterator(rightmost_node(root)->right); }
				const_reverse_iterator rbegin() const { const_reverse_iterator(rightmost_node(root)->right); }

				reverse_iterator rend() { reverse_iterator(leftmost_node(root)); }
				const_reverse_iterator rend() const { const_reverse_iterator(leftmost_node(root)); }





				//		CAPACITY
				bool empty() const { return root == NULL; }
				size_type size() const {

					return siz;
											
/*											const_iterator	it = begin();
											size_type	count = 0;

											for (; it != end(); ++it)
											count++;
											return count;	*/
				}

				size_type max_size() const {
					return node_alloc.max_size();
				}



				//		OBSERVERS

				key_compare key_comp() const { return key_compare(comp); }
				value_compare value_comp() const { return value_compare(); }



				//		ELEMENT ACCESS

				mapped_type& operator[] (const key_type& k) {
					return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second;
				}


				//		MODIFIERS

				ft::pair<iterator, bool>		alloc_node(node_pointer &node, node_pointer parent, const value_type& val) {

					node = node_alloc.allocate(1); // <---- rebind allocator to alloc nodes
					node_alloc.construct(node, Node<value_type>(val, parent));

					siz += 1;

					return ft::pair<iterator, bool>(iterator(node), true);

				}

				ft::pair<iterator, bool>		insert_node(const value_type& val, node_pointer &node, node_pointer parent, key_compare map_comp) {
					if (node == NULL)
						return alloc_node(node, parent, val);
					else if (map_comp(val.first, node->data.first))
						return insert_node(val, node->left, node, map_comp);
					else if (val.first == node->data.first)
						return ft::pair<iterator, bool>(iterator(node), false);
					else
						return insert_node(val, node->right, node, map_comp);

				}

				ft::pair<iterator,bool>		insert (const value_type& val) {

					key_compare	map_comp = key_comp();
					return insert_node(val, root, NULL, key_comp());
				}


				//							 std::cout << "map_comp( 3, 5) returns " << map_comp(5, 3) << std::endl;


				iterator insert (iterator position, const value_type& val) {

					key_compare	map_comp = key_comp();
					return insert_node(val, root, NULL, key_comp());
				}
				template <class InputIterator>
					void insert (InputIterator first, InputIterator last) {

						for (; first != last; ++first) {
							insert(*first);
						}

					}

				// void erase (iterator position);
				//  ^ enable_if needed


				node_pointer delete_node(node_pointer node, const key_type &k) {

					if (node == NULL)
						return node;
					if (k < node->data.first)
						node->left = delete_node(node->left, k);
					if (k > node->data.first)
						node->right = delete_node(node->right, k);
					else if (k == node->data.first) {

						siz -= 1;

						if (node->left == NULL && node->right == NULL) {
							//node = NULL;
							return NULL; 
						}
						else if (node->left == NULL) {
							node_pointer tmp = node->right; 
							//deallocate node
							node = NULL;
							return tmp;
						}
						else if (node->right == NULL) {

							node_pointer tmp = node->left;
							// deallocate node
							node = NULL;
							return tmp;
						}
						node_pointer tmp = leftmost_node(node->right);

						node->right = delete_node(node->right, tmp->data.first);

						tmp->dad = node->dad;
						tmp->left = node->left;
						tmp->right = node->right;
						if (node->dad) {
							if (node->dad->left == node)
								node->dad->left = tmp;
							else if (node->dad->right == node)
								node->dad->right = tmp;
						}
						if (node->left)
							node->left->dad = tmp;
						if (node->right)
							node->right->dad = tmp;

						//             DEALLOCATE NODE
						node = NULL;

						return tmp;

					}
					return node;
				}


				size_type erase (const key_type& k) {

					root = delete_node(root, k);

					return 1;
				}


				void erase (iterator first, iterator last) {
					for (; first != last; ++first) {
						delete(first->first);
					}
				}

				void copy_map(map& x) {

					this->alloc = x.alloc;
					this->node_alloc = x.node_alloc;
					this->comp = x.comp;
					this->root = x.root;
					this->siz = x.siz;

				}

				void swap (map& x) {

					map swp;

					swp.copy_map(x);
					x.copy_map(*this);
					this->copy_map(swp);


				}

				void	destroy_node(node_pointer &node) {

					node_alloc.destroy(node);
					node_alloc.deallocate(node, 1);
					node = NULL;
					siz -= 1;

				}

				void	delete_tree(node_pointer &node) {

					if (node == NULL)
						return ;
					delete_tree(node->left);
					delete_tree(node->right);
					destroy_node(node);
				}

				void clear() {

					delete_tree(root);

				}






				//		OPERATIONS

				iterator find (const key_type& k) {



				}
				const_iterator find (const key_type& k) const;

				size_type count (const key_type& k) const;


				iterator lower_bound (const key_type& k) {

					key_compare cmp = key_comp();
					iterator it = begin();

					for (; it != end() && cmp(it->first, k); ++it) { ; }

					return it;
				}

				const_iterator lower_bound (const key_type& k) const {

					key_compare cmp = key_comp();
					const_iterator cit = begin();

					for (; cit != end() && cmp(cit->first, k); ++cit) { ; }

					return cit;
				}

				iterator upper_bound (const key_type& k) {
				
				}
				const_iterator upper_bound (const key_type& k) const;

				pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
				pair<iterator,iterator>             equal_range (const key_type& k);


		};
}

#endif
