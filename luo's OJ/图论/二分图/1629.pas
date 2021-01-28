var n,m,i,j,k,tot,o,x,y,count:longint;
head,link:array[0..205] of longint;
mark:Array[0..205] of boolean;
next,vet:array[0..40005] of longint;
 
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
read(o);
for o:=o downto 1 do begin
    read(n);
    read(m);
    count:=0;tot:=0;
    for i:=1 to n do begin link[i]:=0;head[i]:=0;end;
    for i:=1 to m do begin
        read(x,y);
        build(x,y);
        end;
    for i:=1 to n do begin
        fillchar(mark,sizeof(mark),false);
        IF DFS(i) then inc(count);
        end;
    writeln(n-count);
    end;
end.