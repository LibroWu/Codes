//
// Created by Libro on 2021/4/17.
//

#include <iostream>

using namespace std;


const int N = 100005;
const int M = 86405;

class segmentTree {
public:
    int  p[N << 2], flag[N << 2],number[N<<2];

    void build(int l,int r,int t){
        flag[t]=0;
        if (l==r) {
            p[t]=0;
            number[t]=l;
            return;
        }
        int mid=l+r>>1;
        build(l,mid,t<<1);
        build(mid+1,r,t<<1|1);
        push_up(t);
    }
    void push_down(int t, int l, int r) {
        if (flag[t] == 0 || l == r) return;
        int mid = l + r >> 1;
        p[t << 1] += flag[t] ;
        p[t << 1 | 1] += flag[t] ;
        flag[t << 1] += flag[t];
        flag[t << 1 | 1] += flag[t];
        flag[t] = 0;
    }

    void push_up(int t) {
        if (p[t<<1]>=p[t<<1|1]) {
            p[t]=p[t<<1];
            number[t]=number[t<<1];
        } else {
            p[t]=p[t<<1|1];
            number[t]=number[t<<1|1];
        }
    }

    void add(int l, int r, int x, int y, int t, int k) {
        push_down(t, l, r);
        if (l == x && y == r) {
            p[t] += k;
            flag[t] += k;
            return;
        }
        int mid = l + r >> 1;
        if (y <= mid) add(l, mid, x, y, t << 1, k);
        else if (x > mid) add(mid + 1, r, x, y, t << 1 | 1, k);
        else {
            add(l, mid, x, mid, t << 1, k);
            add(mid + 1, r, mid + 1, y, t << 1 | 1, k);
        }
        push_up(t);
    }
    struct Pair{
        int P,num;
    };
    Pair query(int l, int r, int x, int y, int t) {
        push_down(t, l, r);
        Pair tmp;
        if (l == x && y == r) {
            tmp.P=p[t];
            tmp.num=number[t];
            return tmp;
        }
        int mid = l + r >> 1;
        if (y <= mid) tmp = query(l, mid, x, y, t << 1);
        else if (x > mid) tmp = query(mid + 1, r, x, y, t << 1 | 1);
        else {
            Pair tmp1,tmp2;
            tmp1 = query(l, mid, x, mid, t << 1);
            tmp2 = query(mid + 1, r, mid + 1, y, t << 1 | 1);
            if (tmp1.P>=tmp2.P) tmp=tmp1;
            else tmp=tmp2;
        }
        push_up(t);
        return tmp;
    }
};

int n, m;
int H[N], hh[M], mm[M], ss[M], A[M], Next[M], Map[N];

segmentTree tr;

int main() {
    cin >> n >>m;
    m +=1;
    for (int i = 1; i <= n; ++i) cin >> H[i];
    for (int i = 1; i < m; ++i) {
        cin >> hh[i] >> mm[i] >> ss[i] >> A[i];
    }
    //while (cin >> hh[m] >> mm[m] >> ss[m] >> A[m]) ++m;
    for (int i = 1; i <= n; ++i) Map[i]=m;
    tr.build(1,m-1,1);
    int ans=-1000000000, ans_l, ans_r;
    for (int i = m-1; i >= 1; --i) {
        Next[i] = Map[A[i]];
        Map[A[i]] = i;
        int h=H[A[i]];
        for (int j = i; j < m; j=Next[j]) {
            tr.add(1,m-1,j,Next[j]-1,1,h);
            h/=2;
            if (h==0) break;
        }
        segmentTree::Pair tmp=tr.query(1,m-1,i,m-1,1);
        if (tmp.P>=ans) {
            ans=tmp.P;
            ans_l=i;
            ans_r=tmp.num;
        }
    }
    cout<<hh[ans_l]<<' '<<mm[ans_l]<<' '<<ss[ans_l]<<'\n';
    cout<<hh[ans_r]<<' '<<mm[ans_r]<<' '<<ss[ans_r]<<'\n';
}