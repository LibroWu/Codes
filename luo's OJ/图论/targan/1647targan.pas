var n,m,i,ii,j,k,tot,top,a,b,x,y,u,v,num,co,ans:longint;
head,next,vet,st,color,d,dfn,low:array[0..2000005] of longint;
 
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
    else if color[v]=0 then
        low[x]:=min(low[x],dfn[v]);
    i:=next[i];
    end;
if dfn[x]=low[x] then begin
    inc(co);
    while st[top]<>x do begin
        color[st[top]]:=co;
        dec(top);
        end;
    color[x]:=co;
    dec(top);
    end;
end;
 
 
begin
readln(n);
for i:=1 to n do begin
    read(x); while x<>0 do begin
            inc(tot);
            next[tot]:=head[i];
            head[i]:=tot;
            vet[tot]:=x;
            read(x);
            end;
    end;
for i:=1 to n do
    if dfn[i]=0 then tarjan(i);
for i:=1 to n do begin
    ii:=head[i];
    while ii<>0 do begin
        v:=vet[ii];
    if color[v]<>color[i] then  inc(d[color[v]]);
        ii:=next[ii];
    end;
        end;
for i:=1 to co do if d[i]=0 then inc(ans);
writeln(ans);
end.
 