//
// Created by Libro on 2021/3/15.
//

#include <cstdio>

using namespace std;
int Stack[10005],tmp,top;
char c;

int main(){
    top=tmp=0;
    while ((c=getchar())!='@'){
        if (c=='.') {
            Stack[top++]=tmp;
            tmp=0;
        }
        else if (c<='9' && c>='0'){
            tmp=(tmp<<3)+(tmp<<1)+c-'0';
        }
        else {
            switch (c) {
                case '+':Stack[top-2]+=Stack[top-1];--top;break;
                case '-':Stack[top-2]-=Stack[top-1];--top;break;
                case '*':Stack[top-2]*=Stack[top-1];--top;break;
                case '/':Stack[top-2]/=Stack[top-1];--top;break;
            }
        }
    }
    printf("%d\n",Stack[0]);
    return 0;
}