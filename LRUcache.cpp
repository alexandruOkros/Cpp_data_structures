#include <iostream>
#include <unordered_map>

using namespace std;

template <typename K, typename V>
struct Node {
    K key;
    V value;
    Node * prev, * next;

    Node(K Key, V Value) {
        prev = next = NULL;
        key = Key;
        value = Value;
    }
};

template <typename K, typename V>
class Dll {

    private:
        Node <K, V> * first, * last;
        int Size;

    public:
        Dll() {
            first = last = NULL;
            Size = 0;
        }

        int size() {
            return Size;
        }

        void pop_front() {
            first = first->next;
            delete first->prev;
            first->prev = NULL;

            Size--;
        }

        void push_back(int key, int value) {
            if(Size == 0) {
                last = new Node <K, V> (key, value);
                first = last;
            }
            else {
                last->next = new Node <K, V> (key, value);
                last->next->prev = last;
                last = last->next;
            }

            ++Size;
        }

        void erase(Node <K, V> * Location) {

            if(Location->prev != NULL && Location->next != NULL) {
                Location->prev->next = Location->next;
                Location->next->prev = Location->prev;
                }
            else if(Location == first)
                first = first->next,
                first->prev = NULL;
            else
                last = last->prev,
                last->next = NULL;

            delete Location;

            Size--;
        }

        Node <K, V> * front() {
            return first;
        }

        Node <K, V> * back() {
            return last;
        }

};

template <typename K, typename V>
class LruCache {

	private:
		int Capacity;
		Dll <K, V> List;
		unordered_map <K, Node <K, V> *> Map;

	public:

		LruCache(int N) {
			Capacity = N;
			}

		void insert(K key, V value) {

			unordered_map <K, Node <K, V> *>::iterator location = Map.find(key);

			if(location == Map.end()) {
				if(List.size() == Capacity) {

					Node <K, V> * P = List.front();
					List.pop_front();

					Map.erase(P->key);
                }
            } else {
				Map.erase(key);
                List.erase(location->second);
            }

			List.push_back(key, value);
			Map.insert( pair <K, Node <K, V> *> (key, List.back()) );
        }

		V get(K key) {

			unordered_map <K, Node <K, V> *>::iterator location = Map.find(key);

			if(location == Map.end())
				return -1;
            else {
                Node <K, V> * P = location->second;

                key = P->key;
                V value = P->value;

                List.push_back(key, value);
                Map[key] = List.back();
                List.erase(P);

				return value;
            }
        }
};

int main() {

    LruCache <int, int> Cache(10);

	return 0;

}
