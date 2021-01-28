var n,m,i,j,k,tot,x,y,z,u,v,ans:longint;
next,vet,link,head:array[0..500005] of longint;
mark:array[0..505] of boolean;
 
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
    if (not mark[v]) then begin
        mark[v]:=true;
        if (link[v]=0)or(dfs(link[V])) then begin
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
for i:=1 to k do begin
    readln(x,y);
    build(x,y);
    end;
for i:=1 to n do begin
    fillchar(mark,sizeof(mark),false);
    if dfs(i) then inc(ans);
    end;
writeln(n+m-ans);
end.