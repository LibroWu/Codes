const go:array[1..4] of longint=(1,-1,0,0);
    goo:array[1..4] of longint=(0,0,-1,1);
type re=record
    x,y,step:longint;
    end;
var n,m,i,j,tot,k,t,count,headd,tail,x,y,xx,yy,cc,ans:longint;
map:Array[0..13,0..13] of char;
ax,ay:array[0..2000] of longint;
b:array[0..130,0..130] of boolean;
head,next,vet,link:Array[0..1000000] of longint;
mark:array[0..5000] of boolean;
p:array[0..5000] of re;
procedure build(x,y:longint);
begin
inc(tot);next[tot]:=head[x];head[x]:=tot;vet[tot]:=y;
end;
 
function dfs(u:longint):boolean;
var i,v:longint;
begin
i:=head[u];
while i<>0 do begin
    v:=vet[i];
    if not mark[v] then begin
        mark[v]:=true;
        if (link[v]=0)or(dfs(link[v])) then begin
        link[v]:=u;
        exit(true);
        end;
                end;
    i:=next[i];
    end;
exit(false);
end;
 
begin
readln(n,m,t);
for i:=1 to n do begin
    for j:=1 to m do begin read(map[i][j]);
                if map[i][j]='.' then inc(cc);
        if map[i][j]='E' then begin
            inc(count);
            ax[count]:=i;
            ay[count]:=j;
            end;
        end;
    readln;
    end;
for i:=1 to count do begin
    headd:=0;tail:=1;
    fillchar(b,sizeof(b),false);
    p[1].x:=ax[i];
    p[1].y:=ay[i];
    b[ax[i],ay[i]]:=true;
    while headd<tail do begin
        inc(headd);
        x:=p[headd].x;
        y:=p[headd].y;
        for j:=1 to 4 do begin
            xx:=x+go[j];
            yy:=y+goo[j];
        if (xx=0)or(yy=0)or(xx=n)or(yy=m) then continue;
        if map[xx][yy]<>'.' then continue;
                if b[xx][yy] then continue;
        inc(tail);
                b[xx][yy]:=true;
        p[tail].x:=xx;
        p[tail].y:=yy;
        p[tail].step:=p[headd].step+1;
        for k:=p[tail].step to t do build((i-1)*t+k,m*(xx-1)+yy);
        end;
        end;
    end;
for i:=1 to t do begin
    for j:=1 to count do begin
    fillchar(mark,sizeof(mark),false);
    if dfs(t*(j-1)+i) then inc(ans);
    if ans=cc then break;
    end;  if ans=cc then break;
        end;
if ans<cc then writeln('impossible') else writeln(i);
end.