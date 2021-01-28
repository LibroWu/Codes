var tot,n,m,o,i,q,v,j,k,l,a,b,c,u:longint;
next,head,vet,len,dep,dist,father:Array[0..300005] of int64;
f:array[0..100005,0..30] of longint;
bb:array[0..100005] of boolean;
function getfather(v:longint):longint;
begin if father[v]=v then exit(V);father[v]:=getfather(father[v]);exit(father[v]);end;
 
procedure swap(var a,b:longint);
var k:longint;
begin k:=a;a:=b;b:=k;end;
 
procedure build(x,y,z:longint);
begin
inc(tot);
next[tot]:=head[x];
vet[tot]:=y;
len[tot]:=z;
head[x]:=tot;
end;
 
procedure prepare(u,father:longint);
var v,i:longint;
begin
dep[u]:=dep[father]+1;
bb[u]:=true;
for i:=0 to 19 do
    f[u][i+1]:=f[f[u][i]][i];
i:=head[u];
while i<>0 do
    begin
    v:=vet[i];
    if v=father then begin i:=next[i];continue;end;
    f[v][0]:=u;
    dist[v]:=dist[u]+len[i];
    prepare(v,u);
    i:=next[i];
    end;
end;
 
function lca(x,y:longint):longint;
var i:longint;
begin
if dep[x]<dep[y] then swap(x,y);
for i:=20 downto 0 do begin
    if dep[f[x][i]]>=dep[y] then x:=f[x][i];
    if x=y then exit(x);
    end;
for i:=20 downto 0 do
    if f[x][i]<>f[y][i] then begin
        x:=f[x][i];
        y:=f[y][i];
        end;
exit(f[x][0]);
end;
 
function query(a,b:longint):longint;
begin
exit(dist[a]+dist[b]-2*dist[lca(a,b)]);
end;
 
begin
readln(o);
for o:=o downto 1 do begin
readln(n,m,q);for i:=1 to n do begin bb[i]:=false;father[i]:=i;end;
for i:=1 to m do begin
    readln(a,b,c);
    u:=getfather(a);
    v:=getfather(b);
    father[u]:=v;
    build(a,b,c);
    build(b,a,c);
    end;
for i:=1 to n do if not bb[i] then
prepare(i,0);
for i:=1 to q do
    begin
    readln(a,b);
    if getfather(a)<>getfather(b) then writeln('Not connected')else
    writeln(query(a,b));
    end;
end;
end.