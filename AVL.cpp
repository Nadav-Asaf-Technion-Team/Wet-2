#include "AVL.h"

//this is an STL function so I implemented it myself.
static int max(int a, int b) {
	return a > b ? a : b;
}

Node::Node(int key, Server* data) :
	key(key), data(data), height(0), left(NULL), right(NULL), subtree_size(1), traffic_sum(data->GetTraffic()) {
}

//these three are just to handle null nodes
static int GetNodeSubtreeSize(Node* node) {
	if (!node) return 0;
	else return node->subtree_size;
}

static int GetNodeTrafficSum(Node* node) {
	if (!node) return 0;
	else return node->traffic_sum;
}

static int GetNodeHeight(Node* node) {
	if (!node) return -1;
	else return node->height;
}

static void UpdateSumAndSize(Node* node) {
	node->subtree_size = GetNodeSubtreeSize(node->left) + GetNodeSubtreeSize(node->right) + 1;
	node->traffic_sum = GetNodeTrafficSum(node->left) + GetNodeTrafficSum(node->right) + node->data->GetTraffic();
}

AVLTree::AVLTree() : root(NULL), size(0), height(-1) {}


static void PostOrderDelete(Node* node) {
	if (!node) return;
	PostOrderDelete(node->left);
	PostOrderDelete(node->right);
	delete node;
}


AVLTree::~AVLTree() {
	PostOrderDelete(root);
}

static Node* rotateLL(Node* root) {
	Node* newRoot = root->left;
	root->left = newRoot->right;
	newRoot->right = root;
	root->height -= 2;
	UpdateSumAndSize(root);
	UpdateSumAndSize(newRoot);
	return newRoot;
}

//returns true if server > node
static bool compareServerToNode(Server& server, Node& node) {
	if (server.GetTraffic() > node.key) return true;
	else if (server.GetTraffic() < node.key) return false;
	else {
		return server.GetID() > node.data->GetID();
	}
}

static Node* rotateRR(Node* root) {
	Node* newRoot = root->right;
	root->right = newRoot->left;
	newRoot->left = root;
	root->height -= 2;
	UpdateSumAndSize(root);
	UpdateSumAndSize(newRoot);
	return newRoot;
}


static Node* rotateLR(Node* root) {
	Node* newRoot = root->left->right;
	Node* temp = root->left;
	temp->right = newRoot->left;
	newRoot->left = temp;
	root->left = newRoot->right;
	newRoot->right = root;
	root->height -= 2;
	newRoot->height += 1;
	temp->height -= 1;
	UpdateSumAndSize(root);
	UpdateSumAndSize(temp);
	UpdateSumAndSize(newRoot);
	return newRoot;
}


static Node* rotateRL(Node* root) {
	Node* newRoot = root->right->left;
	Node* temp = root->right;
	temp->left = newRoot->right;
	newRoot->right = temp;
	root->right = newRoot->left;
	newRoot->left = root;
	root->height -= 2;
	newRoot->height += 1;
	temp->height -= 1;
	UpdateSumAndSize(root);
	UpdateSumAndSize(temp);
	UpdateSumAndSize(newRoot);
	return newRoot;
}


Node* CheckAndRotate(Node* root) {
	if (GetNodeHeight(root->left) - GetNodeHeight(root->right) == 2) {
		if (GetNodeHeight(root->left->left) - GetNodeHeight(root->left->right) >= 0)
			return rotateLL(root);
		else return rotateLR(root);
	}
	else if (GetNodeHeight(root->left) - GetNodeHeight(root->right) == -2) {
		if (GetNodeHeight(root->right->left) - GetNodeHeight(root->right->right) <= 0)
			return rotateRR(root);
		else return rotateRL(root);
	}
	else
		return root;
}

 
Node* insert(Server* data, Node* root) {
	if (!root) {
		root = new Node(data->GetTraffic(), data);
		root->height = 0;
	}
	else if (!compareServerToNode(*data, *root)) {
		root->left = insert(data, root->left);
		UpdateSumAndSize(root);
		root->height = max(GetNodeHeight(root->left), GetNodeHeight(root->right)) + 1;
		root = CheckAndRotate(root);
	}
	else if (compareServerToNode(*data, *root)) {
		root->right = insert(data, root->right);
		UpdateSumAndSize(root);
		root->height = max(GetNodeHeight(root->left), GetNodeHeight(root->right)) + 1;
		root = CheckAndRotate(root);
	}
	return root;
	
}

//consider having AddNode recieve only data, and get key from data->traffic
void AVLTree::AddNode(int key, Server* data) {
	root = insert(data, root);
	size++;
}

//probably don't need this
Server* AVLTree::FindServer(int key) {
	Node* current = root;
	while (current) {
		if (current->key == key) break;
		else if (current->key < key)
			current = current->right;
		else
			current = current->left;
	}
	if (current) return current->data;
	else return NULL;
}

// TODO: static find min and max


