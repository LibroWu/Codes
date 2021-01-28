var n,i,ii,m,j,k,l,tot,top,num,x,y,u,v,co,ans:longint; 
head,next,vet,h,nxt,vt,st,color,d,dfn,low,dp,count,dd:array[0..300005] of longint;
 
function min(a,b:longint):longint;
begin if a>b then exit(b);exit(a);end;
 
function max(a,b:longint):longint;
begin if a<b then exit(b);exit(a);end;
 
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
        end else
    if color[v]=0 then low[x]:=min(low[x],dfn[v]);
    i:=next[i];
    end;
if dfn[x]=low[x] then begin
    inc(co);
    while st[top]<>x do begin
        inc(count[co]);
        color[st[top]]:=co;
                //write(st[top],' ');
        dec(top);
        end;
    inc(count[co]);
        //writeln(st[top]);
    color[st[top]]:=co;
    dec(top);
    end;
end;
 
function dfs(x:longint):longint;
var i,v,j,ii:longint;
begin
if dp[x]>0 then exit(dp[x]);
if d[x]=0 then begin dp[x]:=count[x];exit(dp[x]);end;
        ii:=h[x];
        while ii<>0 do begin
        v:=vt[ii];
        if v<>x then dp[x]:=max(dp[x],dfs(v));
        ii:=nxt[ii];
        end;
dp[x]:=dp[x]+count[x];
exit(dp[x]);
end;
 
begin
readln(n,m);
for i:=1 to m do begin
    readln(x,y);
    inc(tot);
    next[tot]:=head[x];
    head[x]:=tot;
    vet[tot]:=y;
    end;
tot:=0;
for i:=1 to n do if dfn[i]=0 then tarjan(i);
for i:=1 to n do begin
    ii:=head[i];
    while ii<>0 do begin
        v:=vet[ii];
        if color[i]<>color[v] then begin
        inc(tot);nxt[tot]:=h[color[v]];h[color[v]]:=tot;vt[tot]:=color[i];
         inc(dd[color[i]]); inc(d[color[v]]);
        end;
        ii:=next[ii];
        end;
    end;
//for i:=1 to n do write(color[i],' ');writeln;
//for i:=1 to co do write(count[i],' ');writeln;
//for i:=1 to co do write(dd[i],' ');writeln;
//for i:=1 to co do write(d[i],' ');writeln;
for i:=1 to co do if dd[i]=0 then ans:=max(ans,dfs(i));
writeln(ans);
end.
end.