#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <iostream>
# include <limits>
# include "template_utils.hpp"
# include "Node.hpp"
# include "iterator.hpp"


namespace ft {

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
		class map {

			public:

				//		MEMBER TYPES
				typedef ft::pair<const Key, T> 						value_type;
				typedef Key											key_type;
				typedef T											mapped_type;
				typedef Compare										key_compare;
				typedef Alloc										allocator_type;
				typedef typename allocator_type::reference			reference;
				typedef typename allocator_type::const_reference	const_reference;
				typedef typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_pointer;
				typedef std::ptrdiff_t 								difference_type;
				typedef size_t										size_type;

				typedef m_iterator<value_type>						iterator;
				typedef const_m_iterator<value_type>				const_iterator;
				typedef ft::reverse_iterator<iterator>				reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

				typedef typename Alloc::template rebind< Node<value_type> >::other				node_allocator;
				typedef typename Alloc::template rebind< Node<value_type> >::other::pointer		node_pointer;

				class value_compare
				{
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

			private:

				allocator_type		alloc;
				node_allocator		node_alloc;
				key_compare			comp;
				node_pointer		root;
				node_pointer		sentinel;
				node_pointer		sentinel2;
				size_type			siz;


			public:

				//		MEMBER FUNCTIONS
				explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
					: root(NULL), siz(0) {

					this->alloc = alloc;
					this->comp = comp;

					sentinel = node_alloc.allocate(1);
					sentinel2 = node_alloc.allocate(1);
					node_alloc.construct(sentinel, value_type(key_type(), mapped_type()));
					node_alloc.construct(sentinel2, value_type(key_type(), mapped_type()));
					sentinel2->right = sentinel;
					sentinel->dad = sentinel2;

				};


				template <class InputIterator>
					map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
							const allocator_type& alloc = allocator_type()) : root(NULL), siz(0) { 

						this->alloc = alloc;
						this->comp = comp;

						sentinel = node_alloc.allocate(1);
						sentinel2 = node_alloc.allocate(1);
						node_alloc.construct(sentinel, value_type(key_type(), mapped_type()));
						node_alloc.construct(sentinel2, value_type(key_type(), mapped_type()));
						sentinel2->right = sentinel;
						sentinel->dad = sentinel2;

						insert(first, last);

					}


				map (const map& x) : root(NULL), siz(0) {

					sentinel = node_alloc.allocate(1);
					sentinel2 = node_alloc.allocate(1);
					node_alloc.construct(sentinel, value_type(key_type(), mapped_type()));
					node_alloc.construct(sentinel2, value_type(key_type(), mapped_type()));
					sentinel2->right = sentinel;
					sentinel->dad = sentinel2;

					*this = x;
				}

				~map() {

					clear();

					node_alloc.destroy(sentinel);
					node_alloc.destroy(sentinel2);
					node_alloc.deallocate(sentinel, 1);
					node_alloc.deallocate(sentinel2, 1);

				}

				map& operator= (const map& x) {

					clear();
					insert(x.begin(), x.end());

					return *this;
				}


				//		ITERATORS
				iterator begin() { return iterator(leftmost_node(sentinel)); }
				const_iterator begin() const { return const_iterator(leftmost_node(sentinel)); }

				iterator end() { return iterator(sentinel); }
				const_iterator end() const { return const_iterator(sentinel); }

				reverse_iterator rbegin() { return  reverse_iterator(rightmost_node(sentinel)); }
				const_reverse_iterator rbegin() const { return const_reverse_iterator(rightmost_node(sentinel)); }

				reverse_iterator rend() { return reverse_iterator(begin()); }
				const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }





				//		CAPACITY
				bool empty() const { return root == NULL; }
				size_type size() const { return siz; }
				size_type max_size() const { return node_alloc.max_size(); }


				//		OBSERVERS

				key_compare key_comp() const { return key_compare(comp); }
				value_compare value_comp() const { return value_compare(comp); }


				//		ELEMENT ACCESS

				mapped_type& operator[] (const key_type& k) { return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second; }


				//		MODIFIERS

			private:

				ft::pair<iterator, bool>		alloc_node(node_pointer &node, node_pointer &parent, const value_type& val) {

					node = node_alloc.allocate(1); // <---- rebind allocator to alloc nodes
					node_alloc.construct(node, Node<value_type>(val, parent));

					if (!siz)
						parent->left = node;

					siz += 1;

					return ft::pair<iterator, bool>(iterator(node), true);

				}

				ft::pair<iterator, bool>		insert_node(const value_type& val, node_pointer &node, node_pointer &parent, key_compare map_comp) {
					if (node == NULL)
						return alloc_node(node, parent, val);
					else if (map_comp(val.first, node->data.first))
						return insert_node(val, node->left, node, map_comp);
					else if (val.first == node->data.first)
						return ft::pair<iterator, bool>(iterator(node), false);
					else
						return insert_node(val, node->right, node, map_comp);

				}

			public:

				ft::pair<iterator,bool>		insert (const value_type& val) {

					return insert_node(val, root, sentinel, key_comp());
				}


				iterator insert (iterator position, const value_type& val) {

					(void)position;

					return insert_node(val, root, sentinel, key_comp()).first;
				}


				template <class InputIterator>
					void insert (InputIterator first, InputIterator last) {

						for (; first != last; ++first) {
							insert(*first);
						}

					}

			private:

				node_pointer delete_node(node_pointer node, const key_type &k) {

					if (node == NULL)
						return node;
					if (k < node->data.first)
						node->left = delete_node(node->left, k);
					if (k > node->data.first)
						node->right = delete_node(node->right, k);
					else if (k == node->data.first) {

						if (node->left == NULL && node->right == NULL) {
							destroy_node(node);
							return NULL; 
						}
						else if (node->left == NULL) {

							node_pointer tmp = node->right; 
							tmp->dad = node->dad;
							destroy_node(node);
							return tmp;
						}
						else if (node->right == NULL) {

							node_pointer tmp = node->left;
							tmp->dad = node->dad;
							destroy_node(node);
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

						destroy_node(node);
						siz += 1;

						return tmp;

					}
					return node;
				}

			public:

				void erase (iterator position) {
					root = delete_node(root, position->first);
					sentinel->left = root;
				}

				size_type erase (const key_type& k) {

					size_type tmp = siz;
					root = delete_node(root, k);
					sentinel->left = root;
					return tmp - siz;

				}

				void erase (iterator first, iterator last) {

					key_type	first_value;

					while (first != last) {

						first_value = first->first;
						++first;
						erase(first_value);
					}
				}

				void swap (map& x) {

					allocator_type		tmp_alloc;
					node_allocator		tmp_node_alloc;
					key_compare			tmp_comp;
					node_pointer		tmp_root;
					node_pointer		tmp_sentinel;
					node_pointer		tmp_sentinel2;
					size_type			tmp_siz;
					
					tmp_alloc = x.alloc;
					tmp_node_alloc = x.node_alloc;
					tmp_comp = x.comp;
					tmp_root = x.root;
					tmp_siz = x.siz;
					tmp_sentinel = x.sentinel;
					tmp_sentinel2 = x.sentinel2;

					x.alloc = this->alloc;
					x.node_alloc = this->node_alloc;
					x.comp = this->comp;
					x.root = this->root;
					x.siz = this->siz;
					x.sentinel = this->sentinel;
					x.sentinel2 = this->sentinel2;

					this->alloc = tmp_alloc;
					this->node_alloc = tmp_node_alloc;
					this->comp = tmp_comp;
					this->root = tmp_root;
					this->siz = tmp_siz;
					this->sentinel = tmp_sentinel;
					this->sentinel2 = tmp_sentinel2;
				}

			private:

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

			public:

				void clear() {

					delete_tree(root);
					sentinel->left = NULL;
				}


				//		OPERATIONS

			private:

				iterator find_node(const key_type& k, node_pointer node, key_compare cmp) {

					if (node == NULL)
						return end();
					else if (k == node->data.first)
						return iterator(node);
					else if (cmp(k, node->data.first))
						return find_node(k, node->left, cmp);
					else
						return find_node(k, node->right, cmp);

				}

				const_iterator const_find_node(const key_type& k, node_pointer const node, key_compare cmp) const {

					if (node == NULL)
						return end();
					else if (k == node->data.first)
						return iterator(node);
					else if (cmp(k, node->data.first))
						return const_find_node(k, node->left, cmp);
					else
						return const_find_node(k, node->right, cmp);

				}

			public:

				iterator find (const key_type& k) {

					return find_node(k, root, key_comp());
				}

				const_iterator find (const key_type& k) const {

					return const_find_node(k, root, key_comp());
				}

				size_type count (const key_type& k) const {

					return find(k) != end();
				}


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

					key_compare cmp = key_comp();
					iterator it = begin();

					for (; it != end() && cmp(it->first, k); ++it) { ; }

					if ( it != end() && !cmp(k, it->first))
						return ++it;

					return it;
				}

				const_iterator upper_bound (const key_type& k) const {

					key_compare cmp = key_comp();
					const_iterator cit = begin();

					for (; cit != end() && cmp(cit->first, k); ++cit) { ; }

					if ( cit != end() && !cmp(k, cit->first))
						return ++cit;

					return cit;
				}

				pair<iterator,iterator>             equal_range (const key_type& k) {

					pair<iterator, iterator>	ret;

					ret.first = lower_bound(k);
					ret.second = upper_bound(k);

					return ret;
				}

				pair<const_iterator,const_iterator> equal_range (const key_type& k) const {

					pair<const_iterator, const_iterator>	ret;

					ret.first = lower_bound(k);
					ret.second = upper_bound(k);

					return ret;
				}

		};



	template<typename Key, typename T, typename Compare, typename Alloc>
		bool operator==(const map<Key, T, Compare, Alloc>& a, const map<Key, T, Compare, Alloc>& b) {
			return a.size() == b.size() && ft::equal(a.begin(), a.end(), b.begin());
		}

	template<typename Key, typename T, typename Compare, typename Alloc>
		bool operator!=(const map<Key, T, Compare, Alloc>& a, const map<Key, T, Compare, Alloc>& b) {
			return !(a == b);
		}

	template<typename Key, typename T, typename Compare, typename Alloc>
		bool operator<(const map<Key, T, Compare, Alloc>& a, const map<Key, T, Compare, Alloc>& b) {
			return ft::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
		}

	template<typename Key, typename T, typename Compare, typename Alloc>
		bool operator>(const map<Key, T, Compare, Alloc>& a, const map<Key, T, Compare, Alloc>& b) {
			return !(a < b) && a != b;
		}

	template<typename Key, typename T, typename Compare, typename Alloc>
		bool operator<=(const map<Key, T, Compare, Alloc>& a, const map<Key, T, Compare, Alloc>& b) {
			return !(a > b);
		}

	template<typename Key, typename T, typename Compare, typename Alloc>
		bool operator>=(const map<Key, T, Compare, Alloc>& a, const map<Key, T, Compare, Alloc>& b) {
			return !(a < b);
		}

}

#endif
