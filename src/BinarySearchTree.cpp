#include "BinarySearchTree.h"

using namespace std;

BinarySearchTree::BinarySearchTree()
{
    //ctor
    init();
}

void BinarySearchTree::init() {
    int headData = 10;

    head = insertNode(nullptr, headData);
    insertNode(head, 5);
    insertNode(head, 20);
    insertNode(head, 3);
    insertNode(head, 7);
    insertNode(head, 30);
}

shared_ptr<Node> BinarySearchTree::insertNode(shared_ptr<Node> head, int data)
{
    if(head == nullptr)
        return make_shared<Node>(data);

    if(data > head->_data)
        head->right = insertNode(head->right, data);
    else
        head->left  = insertNode(head->left,  data);

    return head;
}

void BinarySearchTree::inorderPrint(shared_ptr<Node> head) {
    if(head == nullptr)
        return;

    inorderPrint(head->left);
    cout << head->_data << " ";
    inorderPrint(head->right);
}

void BinarySearchTree::preOrder(shared_ptr<Node> head) {
    if(head == nullptr)
        return;
    cout << head->_data << " ";
    preOrder(head->left);
    preOrder(head->right);
}
