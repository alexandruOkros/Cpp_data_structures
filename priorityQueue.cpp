#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class priorityQueue {

    #define root 1
    #define father(x) (x >> 1)
    #define leftSon(x) (x << 1)
    #define rightSon(x) ((x << 1) | 1)
    #define compare(a, b) (H[a - 1] < H[b - 1])
    #define change(a, b) swap(H[a - 1], H[b - 1])

    private:
        vector <T> H;

    public:
        void insert(T Value) {
            H.push_back(Value);
            up(H.size());
            }

        void pop() {
            H[0] = H[H.size() - 1];
            H.pop_back();
            down(root);
            }

        T front() {
            return H[0];
            }

        bool empty() {
            return (H.size() == 0);
            }

    private:
        void up(int Node) {

            while(Node != root && compare(Node, father(Node))) {
                change(Node, father(Node));
                Node = father(Node);
                }

            }

        void down(int Node) {

            T son;

            do {
                son = 0;

                if(leftSon(Node) <= H.size()) {
                    son = leftSon(Node);
                    if(rightSon(Node) <= H.size() && compare(rightSon(Node), son))
                        son = rightSon(Node);
                    }

                if(compare(Node, son))
                    son = 0;

                if(son != 0) {
                    change(Node, son);
                    Node = son;
                    }
            } while(son);

            }
};

int main() {

    priorityQueue <int> heap;

    heap.insert(4);
    heap.insert(2);
    heap.insert(12);
    heap.insert(26);
    heap.insert(4);
    heap.insert(5);
    heap.insert(3);
    heap.insert(-99);

    while(!heap.empty()) {
        cout << heap.front() << endl;
        heap.pop();
        }


    return 0;
}
