var tr:array[0..5000005,0..2] of longint;
tot,n,m,i,j,k,l,r,p:longint;
cnt,pre:array[0..5000005] of longint;
s:ansistring;
 
function min(a,b:longint):longint;
begin if a>b then exit(b);exit(a);end;
function max(a,b:longint):longint;
begin if a>b then exit(a);exit(b);end;
 
procedure insert(s:ansistring;x:longint);
var i,p,r:longint;
begin
r:=0;
for i:=1 to length(s) do begin
    p:=ord(s[i])-97;
    if tr[r][p]=0 then begin inc(tot);tr[r][p]:=tot;end;
    r:=tr[r][p];
    cnt[r]:=max(cnt[r],x-pre[r]-1);
    pre[r]:=x
    end;
end;
 
function search(s:ansistring):longint;
var i,p,r:longint;
begin
r:=0;
for i:=1 to length(s) do begin
    p:=ord(s[i])-97;
    if tr[r][p]=0 then exit(n);
    r:=tr[r][p];
    end;
exit(max(cnt[r],n-pre[r]));
end;
 
begin
readln(n,m);
for i:=1 to n do begin
    readln(s);
    insert(s,i);
    end;
for i:=1 to m do begin
    readln(s);
    writeln(search(s));
    end;
end.