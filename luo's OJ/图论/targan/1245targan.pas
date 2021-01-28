var n,m,i,ii,u,v,j,k,l,x,y,a,b,tot,num,top,co,p,ans,anss:longint;
head,next,vet,color,st,dfn,low,cost,pay,d,minn:array[0..10005] of longint;
bb:boolean;
 
function min(a,b:longint):longint;
begin if A>b then exit(B);exit(A);end;
 
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
    inc(co);cost[co]:=maxlongint;
    while st[top]<>x do begin
        if st[top]<minn[co] then minn[co]:=st[top];
        color[st[top]]:=co;
        cost[co]:=min(cost[co],pay[st[top]]);
        dec(top);
        end;
    if st[top]<minn[co] then minn[co]:=st[top];
    color[st[top]]:=co;
    cost[co]:=min(cost[co],pay[st[top]]);
    dec(top);
    end;
end;
 
 
begin
readln(n);
readln(p);
for i:=1 to n do begin pay[i]:=maxlongint;minn[i]:=maxlongint;end;
for i:=1 to p do begin readln(x,y);pay[x]:=y;end;
readln(m);
for i:=1 to m do begin readln(x,y);
    inc(tot);
    next[tot]:=head[x];
    head[x]:=tot;
    vet[tot]:=y;
    end;
for i:=1 to n do
    if dfn[i]=0 then tarjan(i);
for i:=1 to n do begin
    ii:=head[i];
    while ii<>0 do begin
        v:=vet[ii];
        if color[v]<>color[i] then begin inc(d[color[v]]);
        if cost[color[i]]<>maxlongint then cost[color[v]]:=cost[color[i]];
        end;
        ii:=next[ii];
        end;
    end;
for i:=1 to n do begin
    ii:=head[i];
    while ii<>0 do begin
        v:=vet[ii];
        if color[v]<>color[i] then begin// inc(d[color[v]]);
        if cost[color[i]]<>maxlongint then cost[color[v]]:=cost[color[i]];
        end;
        ii:=next[ii];
        end;
    end;
//for i:=1 to co do write(minn[i],' ');writeln;
//for i:=1 to co do write(cost[i],' ');writeln;
bb:=false;anss:=maxlongint;
for i:=1 to co do if d[i]=0 then if cost[i]=maxlongint then bb:=true else ans:=ans+cost[i];
if bb then begin writeln('NO');
for i:=1 to co do if cost[i]=maxlongint then anss:=min(anss,minn[i]);
    writeln(anss);
    end
else begin
     writeln('YES');
     writeln(ans);
    end;
end.