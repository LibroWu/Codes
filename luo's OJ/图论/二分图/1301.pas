var n,i,j,m,k,x,y,tot,ans,count,kk,yy,anss:longint;
head,link,d,linkk:Array[0..105] of longint;
next,vet:array[0..10005] of longint;
mark:array[0..105] of boolean;
 
procedure build(x,y:longint);
begin
inc(tot);next[tot]:=head[x];head[x]:=tot;vet[tot]:=y;
end;
 
function dfs(u:longint):boolean;
var i,v:longint;
begin
i:=head[u];
while i<>0 do begin
    v:=vet[i]; if (u=kk)and(v=yy) then begin i:=next[i];continue;end;
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
for i:=1 to k do begin
    readln(x,y);
    build(x,y);
    inc(d[x]);
    end;
kk:=-1;yy:=-1;
for i:=1 to n do begin
    fillchar(mark,sizeof(mark),false);
    if dfs(i) then inc(ans);
    end;
for i:=1 to m do linkk[i]:=link[i];
for i:=1 to m do if link[i]>0 then begin
    kk:=linkk[i];
    yy:=i;
    fillchar(link,sizeof(link),0);
    anss:=0;
    for j:=1 to n do begin
        fillchar(mark,sizeof(mark),false);
        if dfs(j) then ;
        end;
         for j:=1 to m do if link[j]>0 then inc(anss);
    if anss<>ans then inc(count);
      //  for j:=1 to m do link[j]:=linkk[j];
    end;
writeln('Board have ',count,' important blanks for ',ans,' chessmen.');
end.