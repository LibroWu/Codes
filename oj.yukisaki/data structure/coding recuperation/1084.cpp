//1084
#include <iostream>
#include <cstring>

using namespace std;

template<class T>
class List {
public:
    class Node {
    public:
        T value;
        Node *next;

        Node(T &e) : value(e), next(nullptr) {}
    };

    Node *head, *tail;

    List() : head(nullptr), tail(nullptr) {}

    ~List() {
        for (Node *i = head, *j; i; i = j) {
            j = i->next;
            delete i;
        }
    }

    void push_back(T &e) {
        if (!head) {
            head = tail = new Node(e);
        }
        else {
            tail->next = new Node(e);
            tail = tail->next;
        }
    }

    void print() {
        for (Node *i = head; i; i = i->next) {
            cout << i->value << ' ';
        }
    }
};

int n, m;

template<class U>
void merge() {
    List<U> a, b;
    U x;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        a.push_back(x);
    }
    for (int i = 0; i < m; ++i) {
        cin >> x;
        b.push_back(x);
    }
    a.tail->next = b.head;
    b.head = nullptr;
    a.print();
}

int main() {
    char ch[10];
    scanf("%s\n", ch);
    cin >> n >> m;
    if (strcmp(ch, "int") == 0) {
        merge<int>();
    }
    else if (strcmp(ch, "char")==0) {
        merge<char>();
    }
    else if (strcmp(ch, "double")==0) {
        merge<double>();
    }
}