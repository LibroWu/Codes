const maxx=100005;
var o,root,u,v,x,y,n,m,i,j,k,l,tot,num,top,flag,co:longint;
ans,anss:int64;
dfn,low,head,next,vet,st,count,cutd:array[0..100005] of int64;
cut:array[0..100005] of boolean;
 
procedure clear;
var i:longint;
begin
tot:=0;num:=0;top:=0;n:=0;co:=0;inc(o);ans:=0;anss:=1;
for i:=1 to maxx do dfn[i]:=0;
for i:=1 to maxx do low[i]:=0;
for i:=1 to maxx do count[i]:=0;
for i:=1 to maxx do cutd[i]:=0;
for i:=1 to maxx do head[i]:=0;
for i:=1 to maxx do cut[i]:=false;
end;
 
function min(a,b:longint):longint;
begin if a>b then exit(b);exit(a);end;
 
function max(a,b:longint):longint;
begin if a>b then exit(a);exit(b);end;
 
procedure build(x,y:longint);
begin
inc(tot);next[tot]:=head[x];head[x]:=tot;vet[tot]:=y;
end;
 
procedure tarjan(u:longint);
var i,v,son:longint;
begin
inc(num);dfn[u]:=num;low[u]:=num;
inc(top);st[top]:=u;
son:=0;
i:=head[u];
while i<>0 do begin
    v:=vet[i];
    if dfn[v]=0 then begin
        inc(son);
        tarjan(v);
        low[u]:=min(low[u],low[v]);
        if (root=u)and(son>1)or(u<>root)and(low[v]>=dfn[u]) then cut[u]:=true;
        if  dfn[u]<=low[v] then begin
            inc(co);
            repeat
            inc(count[co]); //write(st[top],' ');
            if cut[st[top]] then inc(cutd[co]);
            dec(top);
            until st[top+1]=v;
            inc(count[co]);
            if cut[u] then inc(cutd[co]);// writeln(u);
            if (u=root)and(not cut[u]) then flag:=co;
            end;
        end else low[u]:=min(low[u],dfn[v]);
    i:=next[i];
    end;
end;
 
begin
readln(m);
while m<>0 do begin
    clear;
    for i:=1 to m do begin
        readln(u,v);
        build(u,v);
        build(v,u);
        n:=max(n,max(u,v));
        end;
    for i:=1 to n do if dfn[i]=0 then begin flag:=0; root:=i; tarjan(i);if (cut[root]) then inc(cutd[flag]);end;
    for i:=1 to co do if cutd[i]=1 then begin inc(ans);anss:=anss*(count[i]-1);end
        else if cutd[i]=0 then begin inc(ans,2);anss:=(anss*count[i]*(count[i]-1))>>1;end;
    writeln('Case ',o,': ',ans,' ',anss);
        //for i:=1 to n do if cut[i] then write(i,' ');writeln;
    readln(m);
    end;
end.