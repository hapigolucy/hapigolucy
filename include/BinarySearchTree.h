#pragma once
#include <iostream>
#include <memory>

using namespace std;

class Node
{
    public:
        int _data;
        shared_ptr<Node> left;
        shared_ptr<Node> right;

        Node(int data):_data(data),left{nullptr}, right{nullptr}
        {}

};

class BinarySearchTree
{
    shared_ptr<Node> head;
    public:
        BinarySearchTree();
        shared_ptr<Node> insertNode(shared_ptr<Node> head, int data);
        void inorderPrint(shared_ptr<Node> head);
        void preOrder(shared_ptr<Node> head);
        shared_ptr<Node> getHead() { return head; }

    protected:

    private:
        void init();
};

