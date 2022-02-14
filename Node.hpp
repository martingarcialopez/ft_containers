#ifndef NODE_HPP
# define NODE_HPP

template<typename T>
class Node {

	public:

		Node() : dad(NULL), left(NULL), right(NULL) {}
		Node(T val) : dad(NULL), left(NULL), right(NULL) { data = val; }
		Node(const T &val, Node<T>* parent) : dad(parent), left(NULL), right(NULL), data(val) {}
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
Node<T>*	leftmost_node_address(Node<T>* &node) {

	while (node && node->left)
		node = node->left;
	return node;
}

template<typename T>
Node<T>*	rightmost_node_address(Node<T>* &node) {

	while (node && node->right)
		node = node->right;
	return node;
}

template<typename T>
Node<T>*	leftmost_node(Node<T>* node) {

	while (node && node->left)
		node = node->left;
	return node;
}

template<typename T>
Node<T>*	rightmost_node(Node<T>* node) {

	while (node && node->right)
		node = node->right;
	return node;
}

template<typename T>
Node<T>*	next_node(Node<T>* node) {

	if (!node)
		return node;

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
	return parent;
}

template<typename T>
const Node<T>*	next_node(const Node<T>* node) {

	if (!node)
		return node;

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
	return parent;
}

template<typename T>
Node<T>*	prev_node(Node<T>* node) {

	if (!node)
		return node;

	if (node->left != NULL)
		return rightmost_node(node->left);

	Node<T>* parent = node->dad;	
	if (parent == NULL)
		return NULL;

	if (node == parent->right)
		return parent;

	while (parent != NULL && node != parent->right) {
		node = parent;
		parent = node->dad;
	}
	return parent;
}

template<typename T>
const Node<T>*	prev_node(const Node<T>* node) {

	if (!node)
		return node;

	if (node->left != NULL)
		return rightmost_node(node->left);

	Node<T>* parent = node->dad;	
	if (parent == NULL)
		return NULL;

	if (node == parent->right)
		return parent;

	while (parent != NULL && node != parent->right) {
		node = parent;
		parent = node->dad;
	}
	return parent;
}

#endif
