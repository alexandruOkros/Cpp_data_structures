#include <fstream>
#include <vector>
#include <queue>
#include <cmath>

#define Nmax 355
#define oo (1 << 30)
#define Neighbour Graph[Node][i]

using namespace std;

vector <int> Graph[Nmax];
int N, minCost, Source, Destination, Father[Nmax], Distance[Nmax];
int Capacity[Nmax][Nmax], Cost[Nmax][Nmax];
bool inQueue[Nmax];

class Heap {

    #define Root 0
    #define father (Node >> 1)
    #define leftSon (Node << 1)
    #define rightSon ((Node << 1) | 1)
    #define compare(a, b) (Distance[Heap[a]] < Distance[Heap[b]])

    private:
        int Top = 0, Heap[Nmax], Position[Nmax];

    public:

        void insert(int X, int Value) {

            Heap[++Top] = X;
            Distance[X] = Value;
            Position[X] = Top;
            up(Top);

        }

        void update(int X, int Value) {

            Distance[X] = Value;
            up(Position[X]);

        }

        void pop() {

            Heap[1] = Heap[Top--];
            Position[Heap[1]] = 1;
            down(1);

        }

        int front() {

            return Heap[1];

        }

        int size() {

            return Top;

        }

        bool empty() {

            return (Top == 0);

        }

    private:

        void up(int Node) {

            while(Node != Root && compare(Node, father)) {
                swap(Heap[Node], Heap[father]);
                swap(Position[Heap[Node]], Position[Heap[father]]);
                Node = father;
                }

        }

        void down(int Node) {

            int Son;

            do {

                Son = 0;

                if(leftSon <= size()) {

                    Son = leftSon;
                    if(rightSon <= size() && compare(rightSon, Son))
                        Son = rightSon;

                    if(compare(Node, Son))
                        Son = 0;

                }

                if(Son != 0) {
                    swap(Heap[Node], Heap[Son]);
                    swap(Position[Heap[Node]], Position[Heap[Son]]);
                    Node = Son;
                }

            } while(Son != 0);

        }

} H;

int BellmanFord() {

    int i, Node;
    queue <int> Queue;

    for(i = 1; i <= N; i++)
        Distance[i] = oo;

    Distance[Source] = 0;
    Queue.push(Source);
    inQueue[Source] = true;

    while(!Queue.empty()) {

        Node = Queue.front();
        Queue.pop();
        inQueue[Node] = false;

        for(i = 0; i < Graph[Node].size(); i++)
            if(Capacity[Node][Neighbour] > 0 && Distance[Neighbour] > Distance[Node] + Cost[Node][Neighbour]) {

                Distance[Neighbour] = Distance[Node] + Cost[Node][Neighbour];

                if(!inQueue[Neighbour]) {
                    Queue.push(Neighbour);
                    inQueue[Neighbour] = true;
                    }

                }

    }

    return Distance[Destination];

}
void initializeDijkstra() {

    int i, Node;

    for(Node = 1; Node <= N; Node++)
        for(i = 0; i < Graph[Node].size(); i++)
            if(Distance[Node] != oo && Distance[Neighbour] != oo)
                Cost[Node][Neighbour] += Distance[Node] - Distance[Neighbour];

    for(i = 1; i <= N; i++)
        H.insert(i, oo);

    H.update(Source, 0);

}
bool Dijkstra() {

    int i, Node;

    initializeDijkstra();

    while(!H.empty()) {

        Node = H.front();
        H.pop();

        for(i = 0; i < Graph[Node].size(); i++)
            if(Capacity[Node][Neighbour] > 0 && Distance[Neighbour] > Distance[Node] + Cost[Node][Neighbour]) {

                H.update(Neighbour, Distance[Node] + Cost[Node][Neighbour]);
                Father[Neighbour] = Node;

                }

        }

    return (Distance[Destination] != oo);

}
void Solve() {

    int cost, maxFlow, Node;

    cost = BellmanFord();

    while(Dijkstra()) {

        maxFlow = oo;

        for(Node = Destination; Node != Source; Node = Father[Node])
            maxFlow = min(maxFlow, Capacity[Father[Node]][Node]);

        for(Node = Destination; Node != Source; Node = Father[Node])
            Capacity[Father[Node]][Node] -= maxFlow,
            Capacity[Node][Father[Node]] += maxFlow;

        cost += Distance[Destination];
        minCost += maxFlow * cost;

        }

}
void Read() {

    int x, y, capacity, cost, M;

    ifstream in("fmcm.in");
    in >> N >> M >> Source >> Destination;

    while(M--) {

        in >> x >> y >> capacity >> cost;

        Graph[x].push_back(y);
        Graph[y].push_back(x);

        Cost[x][y] = cost;
        Cost[y][x] = -cost;

        Capacity[x][y] = capacity;

        }

    in.close();

}
void Write() {

    ofstream out("fmcm.out");
    out << minCost << '\n';
    out.close();

}
int main() {

    Read();
    Solve();
    Write();

    return 0;

}
