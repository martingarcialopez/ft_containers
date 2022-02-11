#include <string>
#include <iostream>
#include <map>
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
	//if (node->left != NULL)
	print_tree_inorder(node->left);
	print_node(node);
	//if (node->right != NULL)
	print_tree_inorder(node->right);

}


	template<typename T>
void printBT(const std::string& prefix, const Node<T> *node, bool isLeft)
{
	if( node != nullptr )
	{
		std::cout << prefix;

		std::cout << (isLeft ? "├──" : "└──" );

		// print the value of the node
		std::cout << node->data.first << std::endl;

		// enter the next tree level - left and right branch
		printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
		printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
	}
}

	template<typename T>
void printBT(const Node<T> *node)
{
	printBT("", node, false);    
}

int main(int ac, char **av) {

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

	/*	mymap.root = new ft::Node<int, std::string>;

		root.dad = NULL;
		root.key = 1;
		root.value = "hello im one";
		root.left = NULL;
		root.right = NULL;*/


	//		mymap.insert ( ft::pair<int, std::string>(3, "ayayayayaya") );
	mymap.insert ( ft::pair<int, std::string>(6, "fssschhchwhoaahaa") );
	mymap.insert ( ft::pair<int, std::string>(2, "pim pam pum") );
	mymap.insert ( ft::pair<int, std::string>(1, "hello hello") );
	mymap.insert ( ft::pair<int, std::string>(4, "eee macarena") );
	mymap.insert ( ft::pair<int, std::string>(5, "oink oink oink") );
	mymap.insert ( ft::pair<int, std::string>(8, "ei t") );
	mymap.insert ( ft::pair<int, std::string>(7, "Sven el vikingo") );
	mymap.insert ( ft::pair<int, std::string>(7, "SVEN HA MUERTO") );
	

	/*

	   if (mymap.root) {
	   std::cout << "map root key is " << mymap.root->key << std::endl;
	   std::cout << "map root value is " << mymap.root->value << std::endl;
	   } else {
	   std::cout << "map root is NULL" << std::endl;
	   }
	   */
	printBT(mymap.root);
	/*
	   std::cout << std::endl << std::endl;

	   if (av[1])
	   mymap.erase(atoi(av[1]));
	   else
	   mymap.erase(5);
	   mymap.print_tree_inorder(mymap.root);
	   printBT(mymap.root);
	   */
	ft::map<int, std::string>::iterator it = mymap.begin();

	for (; it != mymap.end() ; ++it) {
	  std::cout << it->first << "  " << it->second << std::endl;
	  std::cout << "holiiii" << std::endl;

	  }

	std::cout << "mymap[8] is " << mymap[8]  << std::endl;
	std::cout << "despues de mymap[8] = BRUUUUM BRUUUUUUM" << std::endl;
	mymap[8] = "BRUUUUUM BRUUUUUUM";
	std::cout << "mymap[8] is " << mymap[8]  << std::endl;


/*	ft::map<int, std::string>::node_pointer n(mymap.root);

	while (n != NULL) {
		n = next_node(n);
		std::cout << n->data.first << std::endl;
	}

*/
	std::cout << "map size is " << mymap.size() << std::endl;

	mymap.erase(5);
	std::cout << "erase 5" << std::endl;

	std::cout << "map size is " << mymap.size() << std::endl;
	printBT(mymap.root);

	std::cout << "map max_size is " << mymap.max_size() << std::endl;

	std::cout << "mymap.clear()" << std::endl;
	mymap.clear();
	std::cout << "map size is " << mymap.size() << std::endl;
	printBT(mymap.root);

	std::cout << "real map" << std::endl;

	std::map<int, std::string>	map2;
	std::map<int, std::string>::iterator it3 = map2.lower_bound(2);
	std::cout << "it points to " << it3->first << std::endl;


	ft::map<int, std::string>::iterator it2 = mymap.lower_bound(2);
	std::cout << "it points to " << it2->first << std::endl;

	return 0;

}
