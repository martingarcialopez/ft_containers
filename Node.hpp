#ifndef NODE_HPP
# define NODE_HPP

template<typename T>
class Node {

	public:

		Node() : dad(NULL), left(NULL), right(NULL) {}
		Node(T val) : data(val), dad(NULL), left(NULL), right(NULL) {}
		Node(T val, Node<T>* parent) : data(val), dad(parent), left(NULL), right(NULL) {}
		~Node() {}
/*
		Node(Node<T>& node) {
		
			this->dad = node.dad;
			this->left = node.left;
			this->right = node.right;
			this->data = node.data;
		
		}
  				^ DA ERROR /!\ ^  */

		//		operator Node<const T> () const { return Node<const T>(*this); }

		Node		*dad;
		Node		*left;
		Node		*right;

		T			data;
};

template<typename T>
Node<T>*	leftmost_node(Node<T>* node) {


	Node<T>*	current = node;

	while (current && current->left)
		current = current->left;

	return current;

}

template<typename T>
Node<T>*	rightmost_node(Node<T> *node) {


	Node<T>*	current = node;

	while (current && current->right)
		current = current->right;

	return current;

}

template<typename T>
Node<T>*	next_node(Node<T>* node) {

	if (node->right != NULL)
		return leftmost_node(node->right);

	Node<T>* parent = node->dad;	
	if (parent == NULL)
		return NULL;

	if (node == parent->left)
		return parent;

	while (parent != NULL && node != parent->left) {
		node = parent;
		parent = node->dad;
	}
	if (parent != NULL)
		return parent;
//	return rightmost_node(node)->right;
//

	std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH" << std::endl;
	return parent;
}

#endif
