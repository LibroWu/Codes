var n,m,i,j,k,tot,ans,numa,numb,x:longint;
A,B:array[0..45] of longint;
head,link:array[0..1005] of longint;
next,vet:array[0..100005] of longint;
mark:array[0..1005] of boolean;
 
 
 
procedure build(x,y:longint);
begin
inc(tot);next[tot]:=head[x];head[x]:=tot;vet[tot]:=y;
end;
 
function dfs(u:longint):boolean;
var i,v:longint;
begin
i:=head[u];
while i<>0 do begin
    v:=vet[i];
    if not mark[v] then begin
               mark[v]:=true;
    if (link[v]=0)or(dfs(link[v])) then begin
        link[v]:=u;
        exit(true);
        end;
                end;
    i:=next[i];
    end;
exit(false);
end;
 
function prime(x:longint):boolean;
var i:longint;
begin
for i:=2 to trunc(sqrt(x)) do
        if x mod i=0 then exit(false);
exit(true);
end;
 
begin
readln(n);
for i:=1 to n do begin read(x);
        if odd(x) then begin inc(numa);a[numa]:=x;end
                else begin inc(numb);b[numb]:=x;end;
                end;
for i:=1 to numa do
        for j:=1 to numb do
                if  prime(a[i]+b[j]) then build(i,j);
for i:=1 to numa do begin
        fillchar(mark,sizeof(mark),false);
        if dfs(i) then inc(ans);
        end;
writeln(ans);
end.