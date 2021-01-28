var n,m,i,j,k,tot,ans,l,r,u,v,ii,x,y,z:longint;
head,next,vet,p,step,len:array[0..1000005] of longint;
b:Array[0..1000005] of boolean;
procedure build(x,y,z:longint);
begin
inc(tot);next[tot]:=head[x];head[x]:=tot;vet[tot]:=y;len[tot]:=z;
end;
 
begin
read(n);
for i:=1 to n-1 do begin
    read(x,y,z);
    build(x,y,z);
        build(y,x,z);
    end;
step[1]:=0;
l:=0;r:=1;p[r]:=i;b[i]:=true;
while l<r do begin
        inc(l);
        u:=p[l];
        ii:=head[u];
        while ii<>0 do begin
            v:=vet[ii];
            if not b[v] then begin
                b[v]:=true;
                inc(r);
                p[r]:=v;
                step[r]:=step[l]+len[ii];
                if step[r]>ans then begin ans:=step[r];k:=v;end;
                end;
            ii:=next[ii];
            end;
        end;
fillchar(b,sizeof(b),false);
l:=0;r:=1;p[r]:=k;b[k]:=true;
while l<r do begin
        inc(l);
        u:=p[l];
        ii:=head[u];
        while ii<>0 do begin
            v:=vet[ii];
            if not b[v] then begin
                b[v]:=true;
                inc(r);
                p[r]:=v;
                step[r]:=step[l]+len[ii];
                if step[r]>ans then begin ans:=step[r];k:=v;end;
                end;
            ii:=next[ii];
            end;
        end;
writeln(ans);
end.