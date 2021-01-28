uses math;
var
  n,x,y,i,tot:longint;
  head,next,vet,ans,fa,dep:array[0..100000] of longint;
  
procedure build(x,y:longint);
begin
  inc(tot);
  next[tot]:=head[x];head[x]:=tot;vet[tot]:=y;
end;
  
procedure dfs(u:longint);
var
  i,v:longint;
begin
  dep[u]:=1;
  i:=head[u];
  while i<>0 do
    begin
      v:=vet[i];
      if fa[u]<>v then
        begin
          fa[v]:=u;
          dfs(v);
          dep[u]:=max(dep[v]+1,dep[u]);
        end;
      i:=next[i];
    end;
end;
  
procedure sda(u,d:longint);
var
  max1,max2,tot1,tot2,i,v:longint;
begin
  ans[u]:=d+1;
  max1:=0;max2:=0;tot1:=0;tot2:=0;
  i:=head[u];
  while i<>0 do
    begin
      v:=vet[i];
      if fa[u]<>v then
        begin
          ans[u]:=max(ans[u],dep[v]+1);
          if dep[v]>max1 then
            begin
              max2:=max1;tot2:=tot1;
              max1:=dep[v];tot1:=v;
            end
            else
            if dep[v]>max2 then
              begin
                max2:=dep[v];
                tot2:=v;
              end;
        end;
      i:=next[i];
    end;
  i:=head[u];
  while i<>0 do
    begin
      v:=vet[i];
      if fa[u]<>v then
        begin
          if tot1<>v then sda(v,max(d+1,max1+1))
                     else sda(v,max(d+1,max2+1));
        end;
      i:=next[i]; 
    end;
end;
  
begin
  readln(n);
  for i:=1 to n-1 do
    begin
      readln(x,y);
      build(x,y);
      build(y,x);
    end;
  dfs(1);
  sda(1,0);
  for i:=1 to n do writeln(ans[i]);
end.