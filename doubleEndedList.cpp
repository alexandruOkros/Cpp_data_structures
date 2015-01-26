#include <iostream>
#include <string>

using namespace std;

template <typename T>
class List {

    private:
        struct Node {
            T item;
            Node * prev, * next;
            Node() {
                prev = next = NULL;
            }
        };

        Node * first, * last;

    public:
        List() {
            first = last = NULL;
        }

        T front() {
            if(first != NULL)
                return first->item;
            else
                return NULL;
        }

        T back() {
            if(last != NULL)
                return last->item;
            else
                return NULL;
        }

        void push_front(T newItem) {

            Node * node = new Node;
            node->item = newItem;

            if(first == NULL)
                first = last = node;
            else {
                first->prev = node;
                node->next = first;
                first = node;
            }
        }

        void pop_front() {

            if(first == NULL)
                return;

            if(first->next == NULL) {
                first = last = NULL;
            } else {
                first = first->next;
                delete first->prev;
                first->prev = NULL;
            }
        }

        void push_back(T newItem) {

            Node * node = new Node;
            node->item = newItem;

            if(last == NULL)
                first = last = node;
            else {
                last->next = node;
                node->prev = last;
                last = node;
            }
        }

        void pop_back() {

            if(last == NULL)
                return;

            if(last->prev == NULL)
                first = last = NULL;
            else {
                last = last->prev;
                delete last->next;
                last->next = NULL;
            }
        }

        bool empty() {
            return (first == NULL);
        }
};

int main() {

    List <int> ls;

    ls.push_back(2);
    ls.push_front(3);

    cout << ls.front() << endl;
    cout << ls.back() << endl;

    ls.pop_front();

    cout << ls.front() << endl;
    cout << ls.back() << endl;

    cout << ls.empty() << endl;
    ls.pop_back();
    cout << ls.empty() << endl;

    return 0;
}
