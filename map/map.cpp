#include <string>
#include <iostream>
#include "map.hpp"

template<typename Key, typename T>
struct t_node {

	t_node		*dad;
	t_node		*left;
	t_node		*right;

	Key			key;
	T			value;

};

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

int main() {

	t_node<int, std::string>		root;
	t_node<int, std::string>		leaf2;
	t_node<int, std::string>		leaf3;
	t_node<int, std::string>		leaf4;


/*
	root.dad = NULL;
	root.key = 1;
	root.value = "hello im one";
	root.left = &leaf2;
	root.right = &leaf3;


	leaf2.dad = &root;
	leaf2.key = 2;
	leaf2.value = "hello im leaf 2";
	leaf2.left = NULL;
	leaf2.right = NULL;

	leaf3.dad = &root;
	leaf3.key = 3;
	leaf3.value = "hello im leaf 3";
	leaf3.left = &leaf4;
	leaf3.right = NULL;

	leaf4.dad = &leaf3;
	leaf4.key = 4;
	leaf4.value = "hello im leaf 4";
	leaf4.left = NULL;
	leaf4.right = NULL;
*/

	ft::map<int, std::string>	mymap;

	mymap.insert ( std::pair<int, std::string>(1, "hello hello") );

	mymap.print_tree_inorder(mymap.root);
	
	return 0;

}
