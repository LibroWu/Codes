var n,m,i,j,k,o,ans1,ans2,len,u,a,b,c:longint;
g,maxlen:array[0..105,0..105] of longint;
mark:array[0..105] of boolean;
used:array[0..105,0..105] of boolean;
dist,pre:array[0..105] of longint;
 
function max(a,b:longint):longint;
begin if a>b then exit(a);exit(b);end;
function min(a,b:longint):longint;
begin if a<b then exit(a);exit(b);end;
 
begin
read(o);
for o:=o downto 1 do begin
    read(n,m);
    ans1:=0;ans2:=0;
    for i:=1 to n do
        for j:=1 to n do begin g[i][j]:=maxlongint;used[i][j]:=false;maxlen[i][j]:=0;end;
    for i:=1 to m do begin
        read(a,b,c);
        if c<g[a][b] then g[a][b]:=c;
        g[b][a]:=c;
        end;
    for i:=1 to n do begin mark[i]:=false;dist[i]:=g[1][i];pre[i]:=1;end;
    dist[1]:=0;mark[1]:=true;
    for i:=2 to n do begin
        u:=-1;len:=maxlongint;
        for j:=1 to n do
            if (not mark[j])and(dist[j]<len) then begin
                len:=dist[j];
                u:=j;
                end;
        ans1:=ans1+len;
        mark[u]:=true;used[u][pre[u]]:=true;used[pre[u]][u]:=true;
        for j:=1 to n do
            if (mark[j])and(j<>u) then  begin
                maxlen[u][j]:=max(maxlen[j][pre[u]],g[pre[u]][u]);
                                maxlen[j][u]:=maxlen[u][j];
                                end;
        for j:=1 to n do
            if (not mark[j])and(dist[j]>g[u][j]) then begin
                dist[j]:=g[u][j];pre[j]:=u;
                end;
        end;
        ans2:=maxlongint;
        for i:=1 to n do
            for j:=1 to n do
                if (not used[i][j])and(g[i][j]<maxlongint) then ans2:=min(ans2,ans1+g[i][j]-maxlen[i][j]);
        if ans1<>ans2 then writeln(ans1) else writeln('Not Unique!');
        end;
end.