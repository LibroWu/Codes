//
// Created by Libro on 2021/3/29.
//

#include <iostream>

using namespace std;

struct Node {
    int value;
    Node *parent, *lch, *rch;
};

void read(int &tmp) {
    tmp = 0;
    char c = getchar();
    while (c == ' ') c = getchar();
    if (c == '.') return;
    while (c <= '9' && c >= '0') {
        tmp = (tmp << 3) + (tmp << 1) + c - '0';
        c = getchar();
    }
}

void build(Node *&ptr) {
    int v;
    read(v);
    if (v == 0) {
        ptr = nullptr;
        return;
    }
    ptr=new Node;
    ptr->value=v;
    build(ptr->lch);
    if (ptr->lch) ptr->lch->parent=ptr;
    build(ptr->rch);
    if (ptr->rch) ptr->rch->parent=ptr;
}

void RMS(Node* ptr){
    if (ptr->lch) RMS(ptr->lch);
    cout<<ptr->value<<' ';
    if (ptr->rch) RMS(ptr->rch);
}
void RLS(Node* ptr){
    if (ptr->lch) RLS(ptr->lch);
    if (ptr->rch) RLS(ptr->rch);
    cout<<ptr->value<<' ';
}

void cutTheTree(Node* ptr){
    if (ptr->lch) cutTheTree(ptr->lch);
    if (ptr->rch) cutTheTree(ptr->rch);
    delete ptr;
}

int main() {
    Node *head;
    build(head);
    RMS(head);
    cout<<'\n';
    RLS(head);
    cutTheTree(head);
}