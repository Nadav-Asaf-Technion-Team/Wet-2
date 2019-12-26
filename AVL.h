template <class T>
class Node {
public:
	int key;
	T data;
	int height;
	Node* left;
	Node* right;
	Node(int key, T data);
};

template <class T>
class AVLTree {
private:
	Node<T>* root;
	int size;
	int height;
public:
	AVLTree();
	~AVLTree();
	void AddNode(int key, T data);
	T FindNode(int key);
	Node<T>* removeNode(int key);

};

