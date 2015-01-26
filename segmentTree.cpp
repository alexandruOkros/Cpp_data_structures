#include <fstream>

#define oo (1 << 30)

using namespace std;

class SegmentTree {

    #define root 1
    #define middle ((left + right) >> 1)
    #define leftSon (node << 1)
    #define rightSon ((node << 1) | 1)

    private:
        int size;
        int * tree;

        void update(int node, int left, int right, const int & index, const int & value) {

            if(left == right) {
                tree[node] = value;
                return;
            }

            if(index <= middle)
                update(leftSon, left, middle, index, value);
            else
                update(rightSon, middle + 1, right, index, value);

            tree[node] = max(tree[leftSon], tree[rightSon]);
        }

        int query(int node, int left, int right, const int & a, const int & b) {

            if(a <= left && right <= b)
                return tree[node];

            int e = -oo;
            if(a <= middle)
                e = query(leftSon, left, middle, a, b);
            if(middle < b)
                e = max(e, query(rightSon, middle + 1, right, a, b));

            return e;
        }

    public:
        SegmentTree(int Size) {
            size = Size;
            tree = new int[4*size+1];
        }

        void update(const int & index, const int & value) {
            update(root, 1, size, index, value);
        }

        int query(const int & a, const int & b) {
            return query(root, 1, size, a, b);
        }
};
