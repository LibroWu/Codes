var n,m,i,j,p,r,k,l,tot:longint;
tr:array[0..1000000,0..25] of longint;
cnt:array[0..1000000] of longint;
s:string;
 
procedure insert;
var i:longint;
begin
r:=0;
for i:=1 to length(s) do
    begin
    p:=ord(s[i])-97;
    if (tr[r][p]=0) then begin
        inc(tot);
        tr[r][p]:=tot;
        end;
    r:=tr[r][p];
    inc(cnt[r]);
    end;
end;
 
function search:longint;
begin
r:=0;
for i:=1 to length(s) do
    begin
    p:=ord(s[i])-97;
    if tr[r][p]=0 then exit(0);
    r:=tr[r][p];
    end;
exit(cnt[r]);
end;
 
begin
readln(n);
for j:=1 to n do
    begin
    readln(s);
    insert;
    end;
readln(m);
for j:=1 to m do
    begin
    readln(s);
    writeln(search);
    end;
end.