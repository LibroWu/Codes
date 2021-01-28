VAR n,m,i,ii,j,k,l,tot,co,a,b,c,u,v,num,top,ans:longint;
head,next,vet,color,low,dfn,st,d,count:array[0..100000] of longint;
 
 
function min(a,b:longint):longint;
begin if a>b then exit(b);exit(a);end;
 
procedure tarjan(x:longint);
var i,v:longint;
begin
inc(num);dfn[x]:=num;low[x]:=num;
inc(top);st[top]:=x;
i:=head[x];
while i<>0 do begin
    v:=vet[i];
    if dfn[v]=0 then begin
        tarjan(v);
        low[x]:=min(low[x],low[v]);
        end
    else
    if color[v]=0 then low[x]:=min(low[x],dfn[v]);
    i:=next[i];
    end;
if dfn[x]=low[x] then begin
    inc(co);
    while st[top]<>x do begin
        color[st[top]]:=co;
        inc(count[co]);
        dec(top);
        end;
    color[x]:=co;
    inc(count[co]);
    dec(top);
    end;
end;
 
 
begin
readln(n,m);
for i:=1 to m do begin
    readln(a,b);
    inc(tot);
    next[tot]:=head[a];
    head[a]:=tot;
    vet[tot]:=b;
    end;
for i:=1 to n do
    if dfn[i]=0 then
        tarjan(i);
for i:=1 to n do begin
    ii:=head[i];
    while ii<>0 do    begin
        v:=vet[ii];
        if color[v]<>color[i] then inc(d[color[i]]);
        ii:=next[ii];
        end;
        end;
u:=0;
for i:=1 to co do if d[i]=0 then begin inc(ans,count[i]);inc(u);end;
if u=1 then
writeln(ans)else writeln(0);
end.