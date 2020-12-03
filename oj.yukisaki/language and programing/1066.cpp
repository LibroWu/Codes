//libro
#include <string>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class mystring
{
private:
    char *ch = nullptr;
    int len = 0;

public:

    mystring()=default;
    mystring(int _len, int c)
    {
        // TODO
        len=_len;
        ch=new char[_len];
        for(int i=0;i<_len;i++){
            ch[i]=(char)c;
        }
    }
    mystring(string &c)
    {
        // TODO
        len=c.length();
        ch=new char[len];
        for(int i=0;i<len;i++){
            ch[i]=c[i];
        }
    }
    ~mystring()
    {
        // TODO

        delete []ch;
    }

    // TODO
/*    void out(){
        int i=0;
        while(ch[i]!='\0'){
            cout<<ch[i++];
        }
    }*/
    char operator[] (const int &index){
        if(index>=len) return '0';
        return ch[index];
    }
    bool operator< (const mystring &mystr1){
        int length=mystr1.len<len?mystr1.len:len;

        bool flag=0;
        for(int i=0;i<length;i++){
            if(ch[i]>mystr1.ch[i]){return false;}
            if(ch[i]<mystr1.ch[i]){flag=1;}
        }
        if(flag)return true;
        if(len>=mystr1.len) return false;
        else return true;
    }
    mystring & ADD(mystring &mystr1){
        len=strlen(ch)+strlen(mystr1.ch);
        char * newch=new char[len];
        for(int i=0;i<strlen(ch);i++){
            newch[i]=ch[i];
        }
        for(int i=0;i<strlen(mystr1.ch);i++){
            newch[i+strlen(ch)]=mystr1.ch[i];
        }
        delete ch;
        ch=newch;
        return *this;
    }
    int  get_len(){
        return len;
    }
    friend ostream& operator<<(ostream & out,mystring& my);
};

ostream& operator<<(ostream&out,mystring& my){
    for (int i=0;i<my.len;++i) out<<my.ch[i];
    return out;
}

string str_in1, str_in2;
int n, id;
int main() {

    cin >> id;
    if (id == 1) {
        mystring str1(100, 'a');
        //str1.out();
        //puts("");
         cout << str1 << endl;
    } else if (id == 2) {
        cin >> str_in1;
        mystring str2 = str_in1;
        cin >> n;
        for (int i = 0, x; i < n; ++i) {
            cin >> x;
            cout << str2[x] << endl;
        }
    } else if (id == 3) {
        cin >> str_in1 >> str_in2;
        mystring str2 = str_in1;
        mystring str3 = str_in2;
        cout << (int) (str2 < str3) << endl;
    } else if (id == 4) {
        cin >> str_in1 >> str_in2;
        mystring str2 = str_in1;
        mystring str3 = str_in2;
        str2.ADD(str3);
        //str2.out();
        //puts("");
         cout << str2 << endl;
    } else {
        cin >> str_in1 >> str_in2;
        mystring str2 = str_in1;
        mystring str3 = str_in2;
        cin >> n;
        for (int i = 0, x; i < n; ++i) {
            cin >> x;
            cout << str3[x] << endl;
        }
        cout << str2.get_len() << " " << str3.get_len() << endl;
        cout << (int) (str2 < str3) << endl;
        str2.ADD(str3);
        //str2.out();
        //puts("");
         cout << str2 << endl;
        cout << str2.get_len() << endl;
    }

    return 0;
}