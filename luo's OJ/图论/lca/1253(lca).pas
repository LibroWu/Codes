var tot,n,m,i,q,v,j,k,l,a,b,c:longint;
next,head,vet,len,dep,dist:Array[0..300005] of longint;
f:array[0..100005,0..30] of longint;
 
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
 
function get(a,b:longint):longint;
begin exit(dist[a]+dist[b]-2*dist[lca(a,b)]);end;
 
 
function query(a,b,c:longint):longint;
var grandfather:longint;
begin
grandfather:=lca(a,lca(b,c));
exit(dist[a]+dist[b]+dist[c]-3*dist[grandfather]-get(grandfather,lca(a,b))-get(grandfather,lca(c,b))-get(grandfather,lca(a,c)));
end;
 
begin
readln(n);
m:=n-1;
for i:=1 to m do begin
    readln(a,b,c);
    build(a,b,c);
    build(b,a,c);
    end;
prepare(1,0);
readln(q);
for i:=1 to q do
    begin
    readln(a,b,c);
    writeln(query(a,b,c));
    end;
end.