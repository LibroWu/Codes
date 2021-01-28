var n,m,i,j,k,o,u:longint;
a,x,y:array[0..1005] of longint;
g,maxlen:Array[0..1005,0..1005] of double;
dist:array[0..1005] of double;
pre:Array[0..1005] of longint;
used:array[0..1005,0..1005] of boolean;
mark:array[0..1005] of boolean;
len,ans1,ans2:double;
 
function getdist(i,j:longint):double;
begin exit(sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j])));end;
 
function max(a,b:double):double;
begin if a>b then exit(a);exit(b);end;
function min(a,b:double):double;
begin if a<b then exit(a);exit(b);end;
 
begin
readln(o);
for o:=o downto 1 do begin
    readln(n);ans1:=0;
    for i:=1 to n do readln(x[i],y[i],a[i]);
    for i:=1 to n do
        for j:=1 to n do g[i][j]:=getdist(i,j);
    for i:=1 to n do begin pre[i]:=1;dist[i]:=g[1][i];mark[i]:=false;end;
    mark[1]:=true;
    for i:=2 to n do begin
        u:=-1;len:=10000000;
        for j:=1 to n do if not mark[j] then
            if dist[j]<len then begin
                len:=dist[j];
                u:=j;
                end;
    mark[u]:=true;ans1:=ans1+len;
    used[u][pre[u]]:=true;used[pre[u]][u]:=true;
    for j:=1 to n do
        if mark[j] and (j<>u) then begin
            maxlen[u][j]:=max(maxlen[j][pre[u]],g[u][pre[u]]);
            maxlen[j][u]:=maxlen[u][j];
            end;
    for j:=1 to n do
        if g[u][j]<dist[j] then begin
            dist[j]:=g[u][j];
            pre[j]:=u;
            end;
        end;
    ans2:=0;
    for i:=1 to n do
        for j:=1 to n do
            if i<>j then
                ans2:=max(ans2,(a[i]+a[j])/(ans1-maxlen[i][j]));
    writeln(ans2:0:2);
    end;
end.