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