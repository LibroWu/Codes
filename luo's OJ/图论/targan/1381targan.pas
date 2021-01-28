var n,m,o,i,ii,j,k,v,x,y,tot,top,co,num,ans:longint;
head,next,vet:array[0..40005] of longint;
color,st,count,dfn,low,d,l,r:array[0..300] of longint;
map,p:array[0..205,0..205] of longint;
b:array[0..205] of boolean;
 
function min(a,b:longint):longint;
begin if A>b then exit(b);exit(a);end;
 
procedure tarjan(x:longint);
var i,v:longint;
begin
inc(num);low[x]:=num;dfn[x]:=num;
inc(top);st[top]:=x;
i:=head[x];
while i<>0 do begin
    v:=vet[i];
    if dfn[v]=0 then begin
        tarjan(v);
        low[x]:=min(low[x],low[v]);
        end
    else if color[v]=0 then low[x]:=min(low[x],dfn[v]);
    i:=next[i];
    end;
if dfn[x]=low[x] then begin
    inc(co);
    while st[top]<>x do begin
        color[st[top]]:=co;
        inc(count[co]);
        dec(top);
        end;
        inc(count[co]);
        color[st[top]]:=co;
        dec(top);
    end;
end;
 
begin
readln(o);
for o:=o downto 1 do begin
readln(n);
tot:=0;num:=0;co:=0;top:=0;ans:=0;
for i:=1 to n do begin b[i]:=false;dfn[i]:=0;low[i]:=0;count[i]:=0;color[i]:=0;head[i]:=0;d[i]:=0;end;
for i:=1 to n do
    for j:=1 to n do begin
        read(x);map[i,j]:=x;p[i,j]:=0;
        if i=j then continue;
        if x=1 then begin
            inc(tot);
            next[tot]:=head[i];
            head[i]:=tot;
            vet[tot]:=j;
            end;
        end;
for i:=1 to n do if dfn[i]=0 then tarjan(i);
for i:=1 to n do begin
    ii:=head[i];
    while ii<>0 do begin
        v:=vet[ii];
        if color[v]<>color[i] then
                inc(d[color[v]]);
        ii:=next[ii];
        end;
    end;
num:=0;
for i:=1 to n do
    for j:=1 to n do
        if (map[i][j]=1)and(color[i]<>color[j]) then  begin
        inc(num);
        l[num]:=color[i];
        r[num]:=color[j];
        inc(p[color[i]][color[j]]);
        end;
for k:=1 to co do
    for i:=1 to co do
        for j:=1 to co do
            if (p[i,k]>0)and(p[k][j]>0) then inc(p[i,j],p[i,k]*p[k][j]);
ans:=ans+num; 
for i:=1 to num do
    if p[l[i]][r[i]]=1 then continue else begin dec(ans);dec(p[l[i]][r[i]]);end;
for i:=1 to co do
    if count[i]>1 then ans:=ans+count[i];
writeln(ans);
end;
end.