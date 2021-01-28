var n,m,i,j,k,s,t,tot,x,y,l,r,v,len:longint;
head,p,step,d1,d2:array[0..500005] of longint;
next,vet:array[0..1000005] of longint;
b:array[0..500005] of boolean;
 
procedure build(x,y:longint);
begin
inc(tot);next[tot]:=head[x];head[x]:=tot;vet[tot]:=y;
end;
function max(a,b:longint):longint;
begin if a>B then exit(a);exit(b);end;
 
function bfs1(u:longint):longint;
begin
for i:=1 to n do begin b[i]:=false;step[i]:=0;d1[i]:=0;end;
len:=0;
l:=0;r:=1;b[u]:=true;p[1]:=u;step[1]:=1;
while l<r do begin
    inc(l);
    x:=p[l];
    i:=head[x];
    while i<>0 do begin
        v:=vet[i];
        if not b[v] then begin
            b[v]:=true;
            inc(r);
            p[r]:=v;
            step[r]:=step[l]+1;
                        d1[v]:=step[r];
            if step[r]>len then begin
                len:=step[r];
                bfs1:=v;
                end;
            end;
        i:=next[i];
        end;
    end;
end;
 
procedure bfs2(u:longint);
begin
for i:=1 to n do begin b[i]:=false;step[i]:=0;end;
len:=0;
l:=0;r:=1;b[u]:=true;p[1]:=u;step[1]:=1;
while l<r do begin
    inc(l);
    x:=p[l];
    i:=head[x];
    while i<>0 do begin
        v:=vet[i];
        if not b[v] then begin
            b[v]:=true;
            inc(r);
            p[r]:=v;
            step[r]:=step[l]+1;
            d2[v]:=step[r];
            if step[r]>len then begin
                len:=step[r];
                end;
            end;
        i:=next[i];
        end;
    end;
end;
 
begin
readln(n);
for i:=1 to n-1 do begin
    readln(x,y);
    build(x,y);
        build(y,x);
    end;
s:=bfs1(1);
t:=bfs1(s);
bfs2(t);
//for i:=1 to n do write(d1[i],' ');writeln;
//for i:=1 to n do write(d2[i],' ');writeln;
for i:=1 to n do writeln(max(d1[i],d2[i]));
end.