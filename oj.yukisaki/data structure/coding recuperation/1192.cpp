//
// Created by Libro on 2021/5/24.
//

#include <iostream>
#include <cstring>
const int N=10005;
const int M=10005;
int Head[N],tot;

struct Edge{
    int vet,weight,next;
} edge[M];

void initialise(){
    memset(Head,0,sizeof(Head));
    tot=0;
}

void build(int u,int v,int weight){
    edge[++tot].next=Head[u];
    edge[tot].vet=v;
    Head[u]=tot;
}