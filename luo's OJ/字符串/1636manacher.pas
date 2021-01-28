uses math;
var
  p:array[0..1000000] of longint;
  s1:array[1..1000001]of char;
  i,j,id,mx,ans,n:longint;
   
begin
while not(eof) do
begin
fillchar(s1,sizeof(s1),0);
n:=1;
s1[1]:='*';
ans:=0;
   
fillchar(p,sizeof(p),0);
while not(eoln) do
 begin
 inc(n);
 read(s1[n]);
 inc(n);
 s1[n]:='*';
 end;
readln;
  //for i:=1 to n do write(s1[i]);
  //writeln;
p[1]:=1;mx:=2;id:=1;
  for i:=1 to n do
    begin
      p[i]:=1;
      if mx>i then
      p[i]:=min(p[id*2-i], p[id]-i+id);
   
   
    while (i-p[i]>=1)and(i+p[i]<=n)and(s1[i+p[i]]=s1[i-p[i]]) do inc(p[i]);
   
    if p[i]>ans then ans:=p[i];
      if i+p[i]>mx then
        begin
          id:=i;
          mx:=i+p[i];
        end;
         //write(p[i]);
  end;
   
writeln(ans-1);
end;
end.