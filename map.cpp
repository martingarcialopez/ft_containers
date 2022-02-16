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

/*	t_node<int, std::string>		root;
	t_node<int, std::string>		leaf2;
	t_node<int, std::string>		leaf3;
	t_node<int, std::string>		leaf4;*/


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
	mymap.erase(atoi("6"));
	printBT(mymap.root);
	/*
	   std::cout << std::endl << std::endl;

	   if (av[1])
	   else
	   mymap.erase(5);
	   mymap.print_tree_inorder(mymap.root);
	   printBT(mymap.root);
	   */
	ft::map<int, std::string>::iterator it = mymap.begin();

	std::cout << "root dad is " << mymap.root->dad << std::endl;
	std::cout << "root dad first is " << mymap.root->dad->data.first << std::endl;
	std::cout << "sentinel left is " << mymap.root->dad->left->data.first << std::endl;

	std::cout << "mymap[8] is " << mymap[8]  << std::endl;
	std::cout << "despues de mymap[8] = BRUUUUM BRUUUUUUM" << std::endl;
	mymap[8] = "BRUUUUUM BRUUUUUUM";
	std::cout << "mymap[8] is " << mymap[8]  << std::endl;

	
	ft::map<int, std::string>::iterator it2;

	it2 = mymap.find(5);

	std::cout << "elem 5 is " << it2->first << " with value " << it2->second << std::endl;
	for (; it2 != mymap.end(); ++ it2) { ; }
	printBT(mymap.root);

	std::cout << "size is " << mymap.size() << std::endl;



	{
	
	
		ft::map<int, std::string>::iterator it = mymap.begin();
		ft::map<int, std::string>::iterator ite = mymap.end();

		for (; it != ite; ++it) {

			std::cout << it->first << " ";

		}
		std::cout << std::endl;

		ft::map<int, std::string>::reverse_iterator rit = mymap.rbegin();
		ft::map<int, std::string>::reverse_iterator rite = mymap.rend();
	
		/* for (; rit != rite; ++rit) { */


		/* 	std::cout << rit->first << " "; */

		/* } */
		/* std::cout << std::endl; */

//		std::cout << rite->first << std::endl;
		--rite;
		std::cout << rite->first << std::endl;
	
		/* ft::map<int, std::string>::reverse_iterator iite = mymap.end(); */
		/* ft::map<int, std::string>::reverse_iterator iit = mymap.begin(); */
		/* --iit; */
		/* iite++; */
	
		/* for (; iite != iit; --iite) { */


		/* 	std::cout << iite->first << " "; */

		/* } */
		/* std::cout << std::endl; */
	
	
	}







	return 0;

}
