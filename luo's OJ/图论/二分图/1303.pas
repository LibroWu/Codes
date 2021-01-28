const go:array[1..4] of longint=(1,-1,0,0);
    goo:array[1..4] of longint=(0,0,1,-1);
var n,m,i,j,k,x,y,xx,yy,ii,tot,ans,count:longint;
map,od:array[0..35,0..35] of boolean;
head,next,vet,link:array[0..9005] of longint;
mark:array[0..1024] of boolean;
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
 
begin
readln(n,m,k);
for i:=1 to k do begin readln(x,y);map[x][y]:=true;dec(count);end;
if odd(M) then for i:=1 to n do
        for j:=1 to m do if odd(m*(i-1)+j) then od[i][j]:=true;
if not odd(m) then for i:=1 to n do begin
        if odd(i) then for j:=1 to m do if odd(j) then od[i][j]:=true;
        if not odd(i) then for j:=1 to m do if not odd(j) then od[i][j]:=true;
        end;
for i:=1 to n do
        for j:=1 to m do if od[i][j] then
        if not map[i][j] then
        for ii:=1 to 4 do begin
            xx:=i+go[ii];
            yy:=j+goo[ii];
            if (xx=0)or(yy=0)or(xx=n+1)or(yy=m+1) then continue;
            if map[xx][yy] then continue;
            build(m*(i-1)+j,m*(xx-1)+yy);
            end;
for i:=1 to n do
    for j:=1 to m do if od[i][j] then begin
        fillchar(mark,sizeof(mark),false);
        if dfs(m*(i-1)+j) then inc(ans);
        end;
count:=count+n*m;
if ans*2=count then writeln('YES') else writeln('NO');
end.
 