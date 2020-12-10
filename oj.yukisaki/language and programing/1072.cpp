//a class of circle
#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
using namespace std;
class CircleSet {
    friend istream &operator>>(istream &in, CircleSet &obj);
private:
    struct Circle {
        long long x, y, r;
        Circle(long long _x = 0, long long _y = 0, long long _r = 0): x(_x), y(_y), r(_r) {}
    };
    int count;//集合中圆的数目
    Circle *circles;//集合中所有圆
public:
    CircleSet(int n): count(n) {
        circles = new Circle[n];
    }
    ~CircleSet(){
        delete [] circles;
    }
    long long operator[](int p){
        return circles[p].r;
    }
    bool checkContaining(int p,int q){
        int rp=circles[p].r;
        int rq=circles[q].r;
        int xp=circles[p].x;
        int xq=circles[q].x;
        int yp=circles[p].y;
        int yq=circles[q].y;
        if (rp>rq && ((xp-xq)*(xp-xq)+(yp-yq)*(yp-yq))<(rp-rq)*(rp-rq)) return 1;
        return 0;
    }
    long long getCircleContainingQ(int q){
        long long res=1e18;
        for (int p=0;p<count;++p)
            if (checkContaining(p,q)){
                if (circles[p].r<res) res=circles[p].r;
            }
        return res;
    }
};

istream &operator>>(istream &in, CircleSet &obj) {
    for (int i = 0; i < obj.count; ++i) {
        in >> obj.circles[i].x >> obj.circles[i].y >> obj.circles[i].r;
    }
    return in;
}