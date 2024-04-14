#include "binary_search_tree.hpp"
#include <stack>

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree()
{
    root = 0;
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::BinarySearchTree(
    const BinarySearchTree<KeyType, ItemType>& rhs)
{
    root = 0;
    Node<KeyType, ItemType>** lhs = &root;

    std::stack<stackvar<KeyType, ItemType>> s;

    stackvar<KeyType, ItemType> rootvar;
    rootvar.rhs = rhs.root;
    rootvar.lhs = lhs;
    s.push(rootvar);

    while (!s.empty()) {
        stackvar<KeyType, ItemType> currentvar = s.top();
        s.pop();

        Node<KeyType, ItemType>* curr_rhs = currentvar.rhs;
        Node<KeyType, ItemType>** curr_lhs = currentvar.lhs;

        if (curr_rhs == 0)
            continue;

        // allocate new node and copy contents
        Node<KeyType, ItemType>* temp = new Node<KeyType, ItemType>;
        temp->key = curr_rhs->key;
        temp->data = curr_rhs->data;
        temp->left = 0;
        temp->right = 0;
        *curr_lhs = temp;

        // push left subtree
        currentvar.rhs = curr_rhs->left;
        currentvar.lhs = &((*curr_lhs)->left);
        s.push(currentvar);

        // push right subtree
        currentvar.rhs = curr_rhs->right;
        currentvar.lhs = &((*curr_lhs)->right);
        s.push(currentvar);
    }
}


template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>& BinarySearchTree<KeyType, ItemType>::
operator=(BinarySearchTree<KeyType, ItemType> rhs)
{
    swap(rhs);
    return *this;
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::swap(BinarySearchTree<KeyType, ItemType>& rhs)
{
    std::swap(root, rhs.root);
}

template <typename KeyType, typename ItemType>
BinarySearchTree<KeyType, ItemType>::~BinarySearchTree()
{
    destroy();
}


template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::destroy()
{
    std::stack<Node<KeyType, ItemType>*> s;
    s.push(root);

    while (!s.empty()) {
        Node<KeyType, ItemType>* curr = s.top();
        s.pop();

        if (curr != 0) {
            s.push(curr->left);
            s.push(curr->right);
            delete curr;
        }
    }
    root = 0;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::insert(
    const KeyType& key, const ItemType& item)
{
    if(isEmpty()){
        //add Node
        root = new Node<KeyType, ItemType>;
        root->key = key;
        root->data = item;
        return true;
    }

    Node<KeyType, ItemType>* curr;
    Node<KeyType, ItemType>* curr_parent;
    search(key, curr, curr_parent);

    //handle duplicates
    if(curr->key == key){
        return false;
    }

    Node<KeyType,ItemType> *new_node = new Node<KeyType,ItemType>;
    new_node->key = key;
    new_node->data = item;

    //place node at left or right
    if(key < curr->key){ //left is key < current node
        curr->left = new_node;
    } else{
        curr->right = new_node; //right if key > current node
    }
    // TODO 
    return true;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::isEmpty()
{
    return root == 0;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::retrieve(
    const KeyType& key, ItemType& item)
{
    Node<KeyType, ItemType>* curr;
    Node<KeyType, ItemType>* curr_parent;
    search(key, curr, curr_parent);

    if (curr == 0)
        return false;

    if (curr->key == key) {
        item = curr->data;
        return true;
    }

    return false;
}

template <typename KeyType, typename ItemType>
bool BinarySearchTree<KeyType, ItemType>::remove(KeyType key)
{
    if (isEmpty())
        return false; // empty tree

    // TODO
    
    //do search
    Node<KeyType, ItemType>* curr;
    Node<KeyType, ItemType>* curr_parent;
    search(key, curr, curr_parent); 

    //item not found
    if(curr->key != key){
        return false;
    }

    if(curr->left == 0 && curr->right == 0){
        // case one thing in the tree
        if(curr_parent == 0){ //root is only node
            delete curr;
            root = 0;
        } else {
            // case, found deleted item at leaf
            if (curr_parent->left == curr) {
                delete curr;
                curr_parent->left = 0;
            } else {
                delete curr;
                curr_parent->right = 0;
            }
        }
        return true;
    }
    
    if (curr->left == 0 || curr->right == 0) {
        // case, item to delete has only a right child
        // case, item to delete has only a left child
        Node<KeyType, ItemType>* temp = (curr->left != 0) ? curr->left : curr->right;

        if (curr_parent == 0) { //current is the root node
            delete curr;
            root = temp;
        } else {
            if (curr_parent->left == curr) {
                delete curr;
                curr_parent->left = temp;
            } else {
                delete curr;
                curr_parent->right = temp;
            }
        }
        return true;
    }

    // case, item to delete has two children
    Node<KeyType, ItemType>* successor;
    inorder(curr, successor, curr_parent);

    // Replace the data of curr with the data of successor
    curr->key = successor->key;
    curr->data = successor->data;
    //remove successor
    if(curr_parent->left == successor){
        curr_parent->left = successor->right;
    } else if(curr_parent->right == successor){
        curr_parent->right = successor->right;
    }
    delete successor;
    return true;
}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::inorder(Node<KeyType, ItemType>* curr,
    Node<KeyType, ItemType>*& in, Node<KeyType, ItemType>*& parent)
{
    // TODO: find inorder successor of "curr" and assign to "in"
    Node<KeyType, ItemType>* current = curr->right;
    parent = curr;

    // Traverse left until we reach the leftmost node
    while (current->left != 0) {
        parent = current;
        current = current->left;
    }

    // Set the successor node and its parent
    in = current;

}

template <typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::search(KeyType key,
    Node<KeyType, ItemType>*& curr, Node<KeyType, ItemType>*& parent)
{
    curr = root;
    parent = 0;

    if (isEmpty())
        return;

    while (true) {
        if (key == curr->key) {
            break;
        } else if (key < curr->key) {
            if (curr->left != 0) {
                parent = curr;
                curr = curr->left;
            } else
                break;
        } else {
            if (curr->right != 0) {
                parent = curr;
                curr = curr->right;
            } else
                break;
        }
    }
}

template<typename KeyType, typename ItemType>
void BinarySearchTree<KeyType, ItemType>::treeSort(KeyType arr[], int size) {
    if (size <= 0) {
        return;  
    }
   
    // TODO: check for duplicate items in the input array
    for(int i = 0; i < size; i++){
        // TODO: use the tree to sort the array items
        if(!insert(arr[i], arr[i])){ //can't insert duplicates
            return;
        }
    }
    
    // TODO: overwrite input array values with sorted values
    int i = 0;
    std::stack<Node<KeyType, ItemType>*> node_stack; //using built in stack of c++
    Node<KeyType, ItemType>* curr = root;

    //in order traversal
    while (curr != 0 || !node_stack.empty()) {
        while (curr != 0) {
            node_stack.push(curr); //add to stack
            curr = curr->left; //increment to left node
        }

        curr = node_stack.top(); //get top
        node_stack.pop(); //remove from top
        arr[i++] = curr->key;

        curr = curr->right; //go to right node
    }
}
