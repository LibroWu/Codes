const p=1000000007;
var n,m,i,j,k,l,q,tot,a,b:longint;
head,next,vet,dep,f,g,d,distf,distg:array[0..200005] of longint;//f=up;g=down
ff:array[0..100005,0..30] of longint;
 
procedure swap(var a,b:longint);
var k:longint;
begin k:=a;a:=b;b:=k;end;
 
procedure build(a,b:longint);
begin
inc(tot);
next[tot]:=head[a];
vet[tot]:=b;
head[a]:=tot;
end;
 
procedure prepare(u,father:longint);
var i,v:longint;
begin
dep[u]:=dep[father]+1;
distf[u]:=(distf[father]+f[u]) mod p;
distg[u]:=(distg[father]+g[u]) mod p;
for i:=0 to 19 do
       ff[u][i+1]:=ff[ff[u][i]][i];
i:=head[u];
while i<>0 do
    begin
    v:=vet[i];
    if v=father then begin i:=next[i];continue;end;
    ff[v][0]:=u;
    prepare(v,u);
    i:=next[i];
    end;
end;
 
function lca(x,y:longint):longint;
var i:longint;
begin
if dep[x]<dep[y] then swap(x,y);
for i:=20 downto 0 do
    begin
    if dep[ff[x][i]]>=dep[y] then x:=ff[x][i];
    if x=y then exit(x);
    end;
for i:=20 downto 0 do
    if ff[x][i]<>ff[y][i] then begin
        x:=ff[x][i];
        y:=ff[y][i];
        end;
exit(ff[x][0]);
end;
 
procedure dfs1(u,fa:longint);
var i,v:longint;
begin
f[u]:=1;
i:=head[u];
while i<>0 do
    begin
    v:=vet[i];
    if v=fa then begin i:=next[i];continue;end;
    dfs1(v,u);
    f[u]:=(f[u]+f[v]+1) mod p;
    i:=next[i];
    end;
end;
 
{procedure dfs2(u,fa:longint);
var i,v:longint;
begin
g[u]:=g[fa]+f[fa]-f[u];
i:=head[u];
while i<>0 do
    begin
    v:=vet[i];
    if v=fa then begin i:=next[i];continue;end;
    dfs2(v,u);
    i:=next[i];
    end;
end;}
 
procedure dfs2(u,fa:longint);
var sum,i,v:longint;
begin
sum:=0;
i:=head[u];
while i<>0 do begin
    v:=vet[i];
    if v<>fa then sum:=(sum+f[v]+1)mod p else sum:=(sum+g[u]+1) mod p;
    i:=next[i];
    end;
i:=head[u];
while i<>0 do begin
    v:=vet[i];
    if v<>fa then begin g[v]:=(sum-f[v]) mod p;
    dfs2(v,u);
    end;
    i:=next[i];
    end;
end;
 
 
function query(a,b:longint):longint;
var grandfather:longint;
begin
grandfather:=lca(a,b);
//writeln(grandfather);
exit((p+distf[a]-distf[grandfather]+distg[b]-distg[grandfather])mod p);
end;
 
 
begin
readln(n,q);
for i:=1 to n-1 do begin
    readln(a,b);
    inc(d[a]);
    inc(d[b]);
    build(a,b);
    build(b,a);
    end;
dfs1(1,0);
dfs2(1,0);f[1]:=0;
prepare(1,0);
//for i:=1 to n do write(distf[i],' ');
//writeln;
//for i:=1 to n do write(distg[i],' ');
//writeln;
for i:=1 to q do begin
    readln(a,b);
    writeln(query(a,b));
    end;
end.