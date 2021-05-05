#include <iostream>
#include <string>

using namespace std;

struct Node {
    Node *lch, *rch, *parent;
    int v;

    Node(int v, Node *parent = nullptr, Node *lch = nullptr, Node *rch = nullptr) : v(v), lch(lch), rch(rch),
                                                                                    parent(parent) {}
} *head = nullptr;

int q, x;
char op;

void insert(int v) {
    if (head == nullptr) {
        head = new Node(v);
        return;
    }
    Node *ptr = head;
    while (ptr) {
        if (ptr->v == v) return;
        if (ptr->v > v) {
            if (ptr->lch == nullptr) {
                ptr->lch = new Node(v, ptr);
                return;
            }
            ptr = ptr->lch;
        } else {
            if (ptr->rch == nullptr) {
                ptr->rch = new Node(v, ptr);
                return;
            }
            ptr = ptr->rch;
        }
    }
}

Node *findNext(Node *ptr) {
    while (ptr->lch) ptr = ptr->lch;
    return ptr;
}

void Delete(int v) {
    Node *ptr = head;
    while (ptr) {
        if (ptr->v == v) {
            if (ptr->rch) {
                Node *next_ptr = findNext(ptr->rch);
                swap(ptr->v, next_ptr->v);
                if (next_ptr->parent->lch == next_ptr) next_ptr->parent->lch = next_ptr->rch;
                else next_ptr->parent->rch = next_ptr->rch;
                if (next_ptr->rch) next_ptr->rch->parent = next_ptr->parent;
                delete next_ptr;
            } else {
                if (ptr->parent) {
                    if (ptr->parent->lch == ptr) ptr->parent->lch = ptr->lch;
                    else ptr->parent->rch = ptr->lch;
                    if (ptr->lch) ptr->lch->parent = ptr->parent;
                } else {
                    head = ptr->lch;
                    if (ptr->lch) ptr->lch->parent = nullptr;
                }
                delete ptr;
            }
            return;
        }
        if (ptr->v > v) ptr = ptr->lch;
        else ptr = ptr->rch;
    }
}

void Find(int v) {
    string ans = "*";
    Node *ptr = head;
    while (ptr) {
        if (ptr->v == v) {
            cout << ans << '\n';
            return;
        }
        if (ptr->v > v) {
            ans += 'l';
            ptr = ptr->lch;
        } else {
            ans += 'r';
            ptr = ptr->rch;
        }
    }
    cout << "Nothing.\n";
}

int main() {
    cin >> q;
    for (int i = 0; i < q; ++i) {
        cin >> op >> x;
        switch (op) {
            case '+':
                insert(x);
                break;
            case '*':
                Find(x);
                break;
            case '-':
                Delete(x);
                break;
        }
    }
}