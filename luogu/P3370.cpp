//
// Created by Libro on 2021/4/17.
//

#ifndef TICKETSYSTEM_UNORDERED_MAP_HPP
#define TICKETSYSTEM_UNORDERED_MAP_HPP

#include <cstring>
#include <string>
#include <iostream>
namespace LaMetropole {

    template<class T1, class T2>
    class pair {
    public:
        T1 first;
        T2 second;
        constexpr pair() : first(), second() {}
        pair(const T1 &x, const T2 &y) : first(x), second(y) {}
        template<class U1, class U2>
        pair(U1 &&x, U2 &&y) : first(x), second(y) {}
        template<class U1, class U2>
        pair(const pair<U1, U2> &other) : first(other.first), second(other.second) {}
        template<class U1, class U2>
        pair(pair<U1, U2> &&other) : first(other.first), second(other.second) {}
    };

    const int sizeSet[] = {97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437,
                           102877, 205759, 411527, 823117, 1646237, 3292489, 6584983, 13169977,
                           26339969,
                           52679969, 105359939, 210719881, 421439783, 842879579, 1685759167};

    template<class Key, class T>
    class unordered_map {
    public:
        typedef pair<const Key, T> value_type;
    private:


        class hash_table {
        private:
            class occupyChain {
            public:
                class Node {
                public:
                    int pos;
                    Node *next;

                    Node(int p, Node *ptr = nullptr) : pos(p), next(ptr) {}
                } *head;

                occupyChain() : head(nullptr) {}

                bool empty() {
                    return (head == nullptr);
                }

                void push(int pos) {
                    head = new Node(pos, head);
                }

                inline int front() {
                    return head->pos;
                }

                void pop() {
                    if (head) {
                        Node *tmp = head;
                        head = head->next;
                        delete tmp;
                    }
                }
            } chain;

            int Size, realSize, P;

            int (*HashFunc)(const Key &);

            void doubleSpace() {
                Node **oldTable = table;
                P = sizeSet[++realSize];
                table = new Node *[P];
                memset(table, 0, sizeof(Node * ) * P);
                occupyChain oldChain;
                oldChain.head = chain.head;
                chain.head = nullptr;
                int pos;
                while (!oldChain.empty()) {
                    pos = oldChain.front();
                    oldChain.pop();
                    for (Node *i = oldTable[pos], *j; i; i = j) {
                        j = i->next;
                        insert(i->v);
                        delete i;
                    }
                    oldTable[pos] = nullptr;
                }
                delete[] oldTable;
            }

        public:

            class Node {
            public:
                value_type v;
                Node *next;

                Node() = default;

                Node(const value_type &v, Node *ptr = nullptr) : v(v), next(ptr) {}
            } **table;

            typedef pair<Node *, bool> pointer;

            hash_table(int (*hashFunc)(const Key &) = nullptr) : Size(0), realSize(0), P(sizeSet[0]),
                                                                 HashFunc(hashFunc), table(new Node *[sizeSet[0]]) {
                memset(table, 0, sizeof(Node *) * sizeSet[0]);
            }

            ~hash_table() {
                clear();
            }

            void clear() {
                int pos;
                while (!chain.empty()) {
                    pos = chain.front();
                    chain.pop();
                    for (Node *i = table[pos], *j; i; i = j) {
                        j = i->next;
                        delete i;
                    }
                    table[pos] = nullptr;
                }
                delete[] table;
                table = nullptr;
            }

            hash_table &operator=(const hash_table &other) = delete;

            bool erase(const Key &key) {
                int pos = HashFunc(key) % P;
                if (table[pos])
                    for (Node *ptr = table[pos], *pre = nullptr; ptr; pre = ptr, ptr = ptr->next)
                        if (ptr->v.first == key) {
                            if (pre) pre->next = ptr->next;
                            else table[pos] = ptr->next;
                            delete ptr;
                            --Size;
                            return true;
                        }
                return false;
            }

            Node *find(const Key &key) const {
                int pos = HashFunc(key) % P;
                if (table[pos])
                    for (Node *ptr = table[pos]; ptr; ptr = ptr->next)
                        if (ptr->v.first == key) return ptr;
                return nullptr;
            }

            bool empty() const {
                return Size == 0;
            }

            int count() const {
                return Size;
            }

            pointer insert(const value_type &v) {
                if (Size == P) doubleSpace();
                int pos = HashFunc(v.first) % P;
                if (table[pos]) {
                    Node *ptr;
                    for (ptr = table[pos]; ptr->next; ptr = ptr->next)
                        if (ptr->v.first == v.first) return pointer(ptr, false);
                    if (ptr->v.first == v.first) return pointer(ptr, false);
                    ++Size;
                    return pointer(ptr->next = new Node(v), true);
                } else {
                    ++Size;
                    chain.push(pos);
                    return pointer(table[pos] = new Node(v), true);
                }
            }
        } Nebula;


    public:

        unordered_map() {}

        unordered_map(int ((*hashFunc)(const Key &)) = nullptr) : Nebula(hashFunc) {}

        unordered_map(const unordered_map &other) = delete;

        unordered_map &operator=(unordered_map &other) = delete;

        ~unordered_map() {}

        T &at(const Key &key) {
            typename hash_table::Node *tmp = Nebula.find(key);
            if (tmp) return tmp->v.second;
            else throw -1;
            //todo exceptions
        }

        const T &at(const Key &key) const {
            typename hash_table::Node *tmp = Nebula.find(key);
            if (tmp) return tmp->v.second;
            else throw -1;
            //todo exceptions
        }

        T &operator[](const Key &key) {
            typename hash_table::Node *tmp = Nebula.find(key);
            if (tmp) return tmp->v.second;
            else {
                return Nebula.insert(value_type(key, T())).first->v.second;
            }
        }

        const T &operator[](const Key &key) const {
            typename hash_table::Node *tmp = Nebula.find(key);
            if (tmp) return tmp->v.second;
            else throw -1;
            //todo exceptions
        }

        bool empty() const {
            return Nebula.empty();
        }

        size_t size() const {
            return Nebula.count();
        }

        void clear() {
            Nebula.clear();
        }


        int count(const Key &key) const {
            if (Nebula.find(key) == nullptr) return 0;
            return 1;
        }
    };
}

#endif //TICKETSYSTEM_UNORDERED_MAP_HPP
using namespace std;
using LaMetropole::unordered_map;

int func(const string &s){
    int len=s.length();
    int tmp=0;
    for (int i = 0; i < len; ++i) {
        tmp=tmp*128+s[i];
    }
}
string s;
unordered_map<string,bool> s_map(func);
int main(){
    int n,ans=0;
    cin>>n;
    for (int i = 0; i < n; ++i) {
        cin>>s;
        if (s_map.count(s)==0) {
            ++ans;
            s_map[s]=1;
        }
    }
    cout<<ans;
}