var n,m,i,j,k,l,num,top,tot,co,ii,x,y,u,v,count,ans,cutedge:longint;
head,next,vet,op,low,dfn,color,d,st:array[0..30005] of longint;
visit:array[0..30005] of boolean;
 
function min(a,b:longint):longint;
begin if a<b then exit(a);exit(b);end;
 
procedure add(x,y:longint);
begin
inc(tot);
next[tot]:=head[x];head[x]:=tot;
vet[tot]:=y;op[tot]:=tot+1;
inc(tot);
next[tot]:=head[y];head[y]:=tot;
vet[tot]:=x;op[tot]:=tot-1;
end;
 
procedure tarjan(x:longint);
var i,v:longint;
begin
inc(num);dfn[x]:=num;low[x]:=num;
inc(top);st[top]:=x;
i:=head[x];
while i<>0 do begin
    if not visit[op[i]] then begin
        visit[i]:=true;
        v:=vet[i];
        if dfn[v]=0 then begin
            tarjan(v);
            low[x]:=min(low[x],low[v]);
            if low[v]>dfn[x] then inc(cutedge);
            end
        else low[x]:=min(low[x],dfn[v]);
    end else visit[i]:=true;
    i:=next[i];
    end;
if dfn[x]=low[x] then begin
    inc(co);
    while st[top]<>x do begin
        color[st[top]]:=co;
        dec(top);
        end;
    color[st[top]]:=co;
    dec(top);
    end;
end;
 
begin
readln(n,m);
for i:=1 to m do begin
    readln(u,v);
    ADD(u,v);
    end;
for i:=1 to n do
    if dfn[i]=0 then tarjan(i);
for i:=1 to n do begin
    ii:=head[i];
    while ii<>0 do begin
        v:=vet[ii];
        if color[v]<>color[i] then
            inc(d[color[v]]);
        ii:=next[ii];
        end;
    end;
for i:=1 to co do if d[i]=1 then inc(count);
writeln(cutedge);
ans:=(count+1)>>1;
writeln(ans);
end.