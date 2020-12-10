//A class of lists
#include <cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
class LinkList {
    //TODO
private:
    struct point{
        int value;
        point* next;
    };
    point* head;
    int len;
    void clear_(point *head){
        point* pre,*now;
        for (now=head ;now != nullptr;pre=now,now=now->next, delete pre);
    }
public:
    LinkList(){
        head = nullptr;
        len=0;
    }
    ~LinkList(){
        clear_(head);
        head = nullptr;
    }
    void push(int x){
        ++len;
        point* ptr=new point;
        ptr->next= nullptr;
        ptr->value=x;
        if (head == nullptr){
            head=ptr;
            return;
        }
        //find the point to insert
        if (head->value>=x){
            ptr->next=head;
            head=ptr;
            return;
        }
        for (point* now=head;now!= nullptr;now=now->next){
            if (now->next== nullptr||now->next->value>=x){
                ptr->next=now->next;
                now->next=ptr;
                return;
            }
        }
    }
    int getKth(int k){
        if (k>=len)
            return -1;
        point* ptr=head;
        for (int i = 0;i < k; ++i)ptr=ptr->next;
        return ptr->value;
    }
    void merge(LinkList* other){
        point* a,*b,*tmp;
        tmp=a=head;
        b=other->head;
        head = nullptr;
        len=0;
        while (a != nullptr||b != nullptr){
            while (a != nullptr && (b == nullptr || a->value <= b->value)){
                this->push(a->value);
                a=a->next;
            }
            while (b != nullptr && (a == nullptr || a->value >= b->value)) {
                this->push(b->value);
                b = b->next;
            }
        }
        clear_(tmp);
        clear_(other->head);
        other->head = nullptr;
        other->len=0;
    }
};

class LinkListArray {
private:
    int len;
    LinkList **lists;

public:
    LinkListArray(int n): len(n) {
        lists = new LinkList*[n];
        for (int i = 0; i < n; ++i) lists[i] = new LinkList;
    }
    ~LinkListArray() {
        for (int i = 0; i < len; ++i) {
            delete lists[i];
        }
        delete []lists;
    }

    void insertNumber(int n, int x) {
        lists[n]->push(x);
    }
    int queryNumber(int n, int k) {
        return lists[n]->getKth(k);
    }
    void mergeLists(int p, int q) {
        lists[p]->merge(lists[q]);
    }
};