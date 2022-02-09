#ifndef NODE_HPP
# define NODE_HPP

template<typename Key, typename T>
class Node {

	public:

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



#endif
