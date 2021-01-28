VAR n,m,k,i,j,tot,x,y,u,v,ans:longint;
head,link:array[0..105] of longint;
next,vet:array[0..1005] of longint;
mark:Array[0..105] of boolean;
 
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
read(n);
while n<>0 do begin
    read(m,k);
    ans:=0;tot:=0;
    for i:=0 to m do link[i]:=0;
    for i:=0 to n do head[i]:=0;
    for i:=1 to k do begin
        read(j,x,y);
                if (x<>0)and(y<>0) then
        build(x,y);
        end;
    for i:=1 to n do begin
        fillchar(mark,sizeof(mark),false);
        if dfs(i) then inc(ans);
        end;
    writeln(ans);
    read(n);
    end;
end.