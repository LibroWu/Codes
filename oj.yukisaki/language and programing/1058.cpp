//
// Created by LIBRO on 2020/11/19.
//

#include <iostream>
#include <cstdio>
using namespace std;

namespace LIST
{

    struct NODE {
        // TODO
        int point;
        NODE* next;
    };

    NODE *head = nullptr;
    int len = 0;
    void init() {
        // TODO
    }
    NODE* move(int i) {
        // TODO
    }
    void insert(int i, int x) {
        // TODO
        ++len;
        NODE* tmp=new NODE;
        tmp->next= tmp;
        tmp->point=x;
        if (head== nullptr){
            head=tmp;
            return;
        }
        if (i==0){
            NODE*i;
            for (i=head->next;i->next!=head;i=i->next);
            i->next=tmp;
            tmp->next=head;
            head=tmp;
            return;
        }
        int cnt=0;
        NODE* pre,*now;
        pre=now=head;
        while(cnt!=i){
            ++cnt;
            pre=now;
            now=now->next;
        }
        tmp->next=now;
        pre->next=tmp;
    }
    void remove(int i) {
        // TODO
        --len;
        if (i==0){
            if (len==0){
                delete head;
                head= nullptr;
                return;
            }
            NODE*i,*tmp;
            for (i=head->next;i->next!=head;i=i->next);
            tmp=head;
            i->next=head->next;
            head=head->next;
            delete tmp;
            return;
        }
        int cnt=0;
        NODE* now,*pre;
        now=pre=head;
        while (cnt!=i){
            ++cnt;
            pre=now;
            now=now->next;
        }
        pre->next=now->next;
        delete now;
    }
    void remove_insert(int i) {
        //TODO
        --len;
        if (i==0){
            ++len;
            if (len==0){
                return;
            }
            head=head->next;
            return;
        }
        int cnt=0;
        NODE* now,*pre,*tmp;
        now=pre=head;
        while (cnt!=i){
            ++cnt;
            pre=now;
            now=now->next;
        }
        pre->next=now->next;
        tmp=now;
        cnt=0;
        now=pre=head;
        while (cnt!=len){
            ++cnt;
            pre=now;
            now=now->next;
        }
        pre->next=tmp;
        tmp->next=now;
        ++len;
    }
    void get_length() {
        // TODO
        cout<<len<<'\n';
    }
    void query(int i) {
        // TODO
        if (i>=len){
            cout<<"-1\n";
            return;
        }
        int cnt=0;
        NODE* p=head;
        while (cnt != i){
            ++cnt;
            p=p->next;
        }
        cout<<p->point<<"\n";
    }
    void get_max() {
        // TODO
        if (len==0){
            cout<<-1<<'\n';
            return;
        }
        int MAX=head->point;
        for (NODE* i=head->next;i!=head;i=i->next){
            if (i->point>MAX)MAX=i->point;
        }
        cout<<MAX<<'\n';
    }
    void clear() {
        // TODO
        NODE* pre;
        for (NODE*i=head->next;i!=head;pre=i,i=i->next, delete pre);
        delete head;
    }

}
int n;
int main()
{
    cin >> n;
    int op, x, p;
    LIST::init();
    for (int _ = 0; _ < n; ++_)
    {
        cin >> op;
        switch(op) {
            case 0:
                LIST::get_length();
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p,x);
                break;
            case 2:
                cin >> p;
                LIST::query(p);
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                cin >> p;
                LIST::remove_insert(p);
                break;
            case 5:
                LIST::get_max();
                break;
        }
    }
    LIST::clear();
    return 0;
}