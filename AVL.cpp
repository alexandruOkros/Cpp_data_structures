#include <iostream>

using namespace std;

template <typename T>
class AVL {

    private:
        struct Node {
            T Value;
            int height;
            Node * left, * right;
            Node(Node * node, int Height) {
                Value = 0;
                height = Height;
                left = right = node;
                }
        };

    private:
        Node * Root, * NIL;

    public:
        AVL() {
            NIL = new Node(NIL, -1);
            Root = NIL;
        }

        void insert(const T & Value) {
            Root = insert(Root, Value);
        }

        bool search(const T & Value) {
            return search(Root, Value);
        }

        void erase(const T & Value) {
            Root = erase(Root, Value);
        }

    private:
        Node * insert(Node * node, const T & Value) {

            if(node == NIL) {
                node = new Node(NIL, 0);
                node->Value = Value;
                return node;
            }

            if(Value < node->Value)
                node->left = insert(node->left, Value);
            else
            if(Value > node->Value)
                node->right = insert(node->right, Value);

            return balance(node);
        }

        bool search(Node * node, const T & Value) {

            if(node == NIL)
                return false;
            else
            if(Value == node->Value)
                return true;
            else
            if(Value < node->Value)
                return search(node->left, Value);
            else
                return search(node->right, Value);
        }

        Node * erase(Node * node, const T & Value) {

            if(node == NIL)
                return NIL;

            if(node->Value == Value) {

                if(node->left == NIL || node->right == NIL) {
                    Node * p = (node->left == NIL ? node->right : node->left);
                    delete node;
                    return p;
                } else {
                    Node * p;
                    p = node->left;

                    while(p->right != NIL)
                        p = p->right;

                    node->Value = p->Value;
                    node->left = erase(node->left, p->Value);
                }
            } else if(Value < node->Value)
                node->left = erase(node->left, Value);
            else
                node->right = erase(node->right, Value);

            return balance(node);
        }

        void setHeight(Node * node) {
            node->height = 1 + max(node->left->height, node->right->height);
        }

        Node * leftRotate(Node * node) {
            Node * p = node->right;
            node->right = p->left;
            p->left = node;

            setHeight(node);
            setHeight(p);

            return p;
        }

        Node * rightRotate(Node * node) {
            Node * p = node->left;
            node->left = p->right;
            p->right = node;

            setHeight(node);
            setHeight(p);

            return p;
        }

        Node * balance(Node * node) {

            setHeight(node);

            if(node->left->height + 1 < node->right->height) {
                if(node->right->left->height > node->right->right->height)
                    node->right = rightRotate(node->right);
                node = leftRotate(node);
            } else if(node->right->height + 1 < node->left->height) {
                if(node->left->right->height > node->left->left->height)
                    node->left = leftRotate(node->left);
                node = rightRotate(node);
            }

            return node;
        }
};

int main() {

    AVL <int> Avl;

    for(int i = 2; i <= 20; i += 2)
        Avl.insert(i);

    Avl.erase(10);
    Avl.erase(9);


    for(int i = 1; i <= 20; i++)
        if(Avl.search(i))
            cout << i << endl;


    return 0;
}
