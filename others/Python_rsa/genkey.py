from random import*
def isPrimeNumber(n):
    cnt=0
    d=n-1
    while d%2==0:
        cnt+=1
        d//=2
    k=0
    while k<100:
        k+=1
        a=randint(2,n-2)
        x=pow(a,d,n)
        if x==1 or x==n-1:
            continue
        i=1
        while i<cnt:
            i+=1
            x=x*x%n
            if x==n-1:
                break
        if x==n-1:
            continue
        return 0
    return 1    
def getPrimeNumber(a,b):
    print(1)
def getPrimeNumber(t=800):
    a=getrandbits(t)
    while isPrimeNumber(a)==0:
        a=getrandbits(t)
    else:
        return a
def gcd(a,b):
    if a%b==0:
        return b
    return gcd(b,a%b)
def ex_gcd(a,b):
    if b==0:
        return 1,0;
    x,y=ex_gcd(b,a%b)
    return y,x-a//b*y    
def RSA(len):
    p=getPrimeNumber(len)
    q=getPrimeNumber(len)
    n=p*q
    fi=(p-1)*(q-1)
    e=randint(2,n)
    while gcd(e,fi)!=1:
        e=randint(2,n)
    d,k=ex_gcd(e,fi)
    d=d%fi
    if (d<0):
        d+=fi
    return e,d,n
len=int(input())    
e,d,n=RSA(len)
getPrimeNumber(1,2)
F=open("E.out",mode='w')
F.write(hex(e)[2:].upper()+'\n')
F.close()
F=open("D.out",mode='w')
F.write(hex(d)[2:].upper()+'\n')
F.close()
F=open("N.out",mode='w')
F.write(hex(n)[2:].upper()+'\n')
F.close()