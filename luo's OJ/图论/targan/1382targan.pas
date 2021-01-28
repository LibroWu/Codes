VAR tot,n,m,i,j,k,l,o,num,x,y,z,u,v,ii,s,t:longint;
b:array[0..10005] of boolean;
cut:Array[0..200005] of boolean;
head,dfn,low:array[0..10005] of longint;
next,vet,op:array[0..200005] of longint;
flag:boolean;
 
function min(a,b:longint):longint;
begin if a<b then exit(a);exit(b);end; 
procedure build(x,y,z:longint);
begin
inc(tot);next[tot]:=head[x];head[x]:=tot;vet[tot]:=y;op[tot]:=tot+z;
end;
 
procedure tarjan(u,fa:longint);
var i,v:longint;
ok:boolean;
begin
inc(num);low[u]:=num;dfn[u]:=num;
i:=head[u];
ok:=false;
while i<>0 do begin
    v:=vet[i];
    if (v=fa)and(not ok) then begin ok:=true;i:=next[i];continue;end;
    if dfn[v]=0 then begin
        tarjan(v,u);
        low[u]:=min(low[u],low[v]);
        if dfn[u]<low[v] then begin
            cut[i]:=true;
            cut[op[i]]:=true;
            end;
        end
    else low[u]:=min(low[u],dfn[v]);
    i:=next[i];
    end;
end;
 
procedure dfs(u,fa:longint);
var i,v:longint;
begin
if flag then exit;
if u=t then begin flag:=true;exit;end;
i:=head[u];
b[u]:=true;
while i<>0 do begin
    if cut[i] then begin i:=next[i];continue;end;
    v:=vet[i];
    if not b[v] then dfs(v,u);
    i:=next[i];
    end;
end;    
 
begin
readln(o);
for o:=o downto 1 do begin
    readln(n,m);
    for i:=1 to n do begin dfn[i]:=0; head[i]:=0;low[i]:=0;end;
    tot:=0;num:=0;
    for i:=1 to m do begin
        readln(x,y);
        build(x,y,1);
        build(y,x,-1);
        end;
    fillchar(b,sizeof(b),false);
    fillchar(cut,sizeof(cut),false);
    for i:=1 to n do if dfn[i]=0 then tarjan(i,0);
    readln(s,t);
    flag:=false;
    dfs(s,0);
    if flag then writeln('YES') else writeln('NO');
    end;
end.