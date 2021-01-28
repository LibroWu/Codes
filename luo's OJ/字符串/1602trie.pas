var n,num,p,r,i,j,k,tot:longint;
tr:Array[0..1000000,0..25] of longint;
cnt:array[0..1000000] of longint;
s,s1:string;
 
procedure insert;
begin
r:=0;
for i:=1 to length(s) do
    begin
    p:=ord(s[i])-97;
    if tr[r][p]=0 then begin
        inc(tot);
        tr[r][p]:=tot;
        end;
    r:=tr[r][p];
    inc(cnt[r]);
    end;
end;
 
procedure search;
begin
r:=0;
for i:=1 to length(s) do
    begin
    p:=ord(s[i])-97;
    if tr[r][p]=0 then begin writeln('No');exit;end;
    r:=tr[r][p];
    end;
writeln('Yes');
end;
 
procedure del;
begin
r:=0;
for i:=1 to length(s) do begin
    p:=ord(s[i])-97;
    if tr[r][p]=0 then exit;
    r:=tr[r][p];
    end;
num:=cnt[r];
r:=0;
for i:=1 to length(s) do begin
    p:=ord(s[i])-97;
    if cnt[tr[r][p]]<=num then begin
        tr[r][p]:=0;
        exit;
        end;
    r:=tr[r][p];
    cnt[r]:=cnt[r]-num;
    end;
end;
 
begin
readln(n);
tot:=0;
for n:=n downto 1 do
    begin
    readln(s);
    s1:=copy(s,1,pos(' ',s)-1);
    delete(s,1,pos(' ',s));
    if s1='insert' then insert;
    if s1='search' then search;
    if s1='delete' then del;
    end;
end.