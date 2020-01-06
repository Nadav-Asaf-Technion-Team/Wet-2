#include "AVL.h"
#include <assert.h>
#include <iostream>
using std::endl;
using std::cout;

#define COUNT 10

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

//Stores a tree in an array - in order
static void TreeToArray(Node* root, Server** arr, int* index) {
	if (root == NULL)
		return;
	TreeToArray(root->left, arr, index);
	arr[*index] = root->data;
	(*index)++;
	TreeToArray(root->right, arr, index);
}

static Node* ArrayToTree(Server** arr, int start, int end) {
	if (start > end) {
		return NULL;
	}
	int mid = (start + end) / 2;
	Node* root = new Node(arr[mid]->GetTraffic(), arr[mid]);

	root->left = ArrayToTree(arr, start, mid - 1);
	root->right = ArrayToTree(arr, mid + 1, end);
	return root;
}

Server** MergeServerArrays(Server** arr1, Server** arr2, int size1, int size2) {
	Server** merged_array = new Server * [size1 + size2];
	int i = 0, j = 0, k = 0;
	while (i < size1 && j < size2) {
		if (compServers(arr1[i], arr2[j]) < 0) {
			merged_array[k] = arr1[i];
			i++;
		}
		else {
			merged_array[k] = arr2[j];
			j++;
		}
		k++;
	}
	 
	// if there are more Servers in arr1
	while (i < size1) {
		merged_array[k] = arr1[i];
		i++;
		k++;
	}
	while (j < size2) {
		merged_array[k] = arr2[j];
		j++;
		k++;
	}
	return merged_array;
}

AVLTree::AVLTree() : root(NULL) {}


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

//returns positive value if server > node, 9 if equal
static int compareServerToNode(Server& server, Node& node) {
	if (server.GetTraffic() - node.key == 0) {
		return server.GetID() - node.data->GetID();
	}
	else return server.GetTraffic() - node.key;
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

//NOT a recursive function
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

static Node* FindMin(Node* node) {
	if (!node) return NULL;
	else if (!(node->left)) return node;
	else return FindMin(node->left);
}
 
Node* insert(Server* data, Node* root) {
	if (!root) {
		root = new Node(data->GetTraffic(), data);
		root->height = 0;
	}
	else if (compareServerToNode(*data, *root) < 0) {
		root->left = insert(data, root->left);
		UpdateSumAndSize(root);
		root->height = max(GetNodeHeight(root->left), GetNodeHeight(root->right)) + 1;
		root = CheckAndRotate(root);
	}
	else if (compareServerToNode(*data, *root) > 0) {
		root->right = insert(data, root->right);
		UpdateSumAndSize(root);
		root->height = max(GetNodeHeight(root->left), GetNodeHeight(root->right)) + 1;
		root = CheckAndRotate(root);
	}
	return root;
	
}

void AVLTree::AddServer(Server* data) {
	assert(FindServer(data) == NULL);
	root = insert(data, root);
}

//returns null if server isn't in the tree.
Node* remove(Server* data, Node* node) {
	Node* temp;
	
	//not found
	if (!node) return NULL;

	//searching
	else if (compareServerToNode(*data, *node) < 0) {
		node->left = remove(data, node->left);
	}
	else if (compareServerToNode(*data, *node) > 0) {
		node->right = remove(data, node->right);
	}

	//found
	//2 children
	else if (node->left && node->right) {
		temp = FindMin(node->right);
		node->key = temp->key;
		node->data = temp->data;
		node->right = remove(node->data, node->right);
	}
	//one or no children
	else {
		temp = node;
		if (!node->left)
			node = node->right;
		else if (!node->right)
			node = node->left;
		delete temp;
	}
	if (!node) return node;

	node->height = max(GetNodeHeight(node->left), GetNodeHeight(node->right)) + 1;
	UpdateSumAndSize(node);
	node = CheckAndRotate(node);
	return node;

}

//should return error
void AVLTree::RemoveNode(Server* data) {
	assert(FindServer(data) != NULL);
	root = remove(data, root);
}

int AVLTree::GetSize() {
	return root ? root->subtree_size : 0;
}


Server* AVLTree::FindServer(Server* data) {
	Node* current = root;
	while (current) {
		if (compareServerToNode(*data, *current) == 0) break;
		else if (compareServerToNode(*data, *current) > 0)
			current = current->right;
		else
			current = current->left;
	}
	if (current) return current->data;
	else return NULL;
}

void PrintUtil(Node* root, int space) {
	// Base case  
	if (root == NULL)
		return;

	// Increase distance between levels  
	space += COUNT;

	// Process right child first  
	PrintUtil(root->right, space);

	// Print current node after space  
	// count  
	cout << endl;
	for (int i = COUNT; i < space; i++)
		cout << " ";
	cout << root->data->GetTraffic() << "\n";

	// Process left child  
	PrintUtil(root->left, space);
}

void AVLTree::PrintTree() {
	PrintUtil(root, 0);
}

int AVLTree::SumHighestTraffics(int k) {
	if (k >= root->subtree_size)
		return root->traffic_sum;
	else if (k == 0)
		return 0;
	Node* current = root;
	int total_sum = 0, total_nodes = 0;
	while (1) {
		if (current->subtree_size + total_nodes == k) {
			return total_sum + current->traffic_sum;
		}
		else if (current->subtree_size + total_nodes > k) {
			if (GetNodeSubtreeSize(current->right) + 1 + total_nodes == k) {
				return current->key + GetNodeTrafficSum(current->right) + total_sum;
			}
			else if (GetNodeSubtreeSize(current->right) + 1 + total_nodes > k) {
				current = current->right;
				continue;
			}
			else {
				total_nodes += GetNodeSubtreeSize(current->right) + 1;
				total_sum += current->key + GetNodeTrafficSum(current->right);
				current = current->left;
				continue;
			}
		}
	}
}

AVLTree* MergeTrees(AVLTree* t1, AVLTree* t2) {
	Server** arr1 = new Server * [t1->GetSize()];
	Server** arr2 = new Server * [t2->GetSize()];
	int index1 = 0;
	int index2 = 0;
	TreeToArray(t1->root, arr1, &index1);
	TreeToArray(t2->root, arr2, &index2);
	Server** merged_arr = MergeServerArrays(arr1, arr2, t1->GetSize(), t2->GetSize());
	delete[] arr1;
	delete[] arr2;
	AVLTree* mergedTree = new AVLTree();
	mergedTree->root = ArrayToTree(merged_arr, 0, t1->GetSize() + t2->GetSize() - 1);
	return mergedTree;
}

