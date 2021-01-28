const nn=200005;
var n,m,i,j,k,tot,len,x,y,z:longint;
a,b,bb,t:array[0..nn] of longint;
sum,l,r:array[0..36*nn] of longint;

function build(ll,rr:longint):longint;
var p,mid:longint;
begin
inc(tot);p:=tot;
mid:=(ll+rr)>>1;
if ll<rr then begin
	l[p]:=build(ll,mid);
	r[p]:=build(mid+1,rr);
	end;
exit(p);
end;

function update(pre,ll,rr,x:longint):longint;
var p,mid:longint;
begin
inc(tot);p:=tot;
mid:=(ll+rr)>>1;
l[p]:=l[pre];
r[p]:=r[pre];
sum[p]:=sum[pre]+1;
if ll<rr then
	if mid>=x then l[p]:=update(l[p],ll,mid,x) else
		r[p]:=update(r[p],mid+1,rr,x);
exit(p);
end;

function find(st,ed,ll,rr,k:longint):longint;
var x,mid:longint;
begin
if ll=rr then exit(ll);
mid:=(ll+rr)>>1;
x:=sum[l[ed]]-sum[l[st]];
if x>=k then exit(find(l[st],l[ed],ll,mid,k)) else
	exit(find(r[st],r[ed],mid+1,rr,k-x));
end;

   procedure sort(l,r: longint);
      var
         i,j,x,y: longint;
      begin
         i:=l;
         j:=r;
         x:=a[(l+r) div 2];
         repeat
           while a[i]<x do
            inc(i);
           while x<a[j] do
            dec(j);
           if not(i>j) then
             begin
                y:=a[i];
                a[i]:=a[j];
                a[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort(l,j);
         if i<r then
           sort(i,r);
      end;

function lower(x:longint):longint;
var l,r,mid:longint;
begin
l:=1;r:=len;lower:=1;
while l<=r do begin
	mid:=(l+r)>>1;
	if bb[mid]>=x then begin lower:=mid;r:=mid-1;end
		else l:=mid+1;
	end;
end;

begin
readln(n,m);
for i:=1 to n do begin read(a[i]);b[i]:=a[i];end;
sort(1,n);
len:=1;bb[1]:=a[1];
for i:=1 to n do if a[i]<>bb[len] then begin
	inc(len);bb[len]:=a[i];
	end;
t[0]:=build(1,len);
for i:=1 to n do begin
	k:=lower(b[i]);
	t[i]:=update(t[i-1],1,len,k);
	end;
for i:=1 to m do begin
	readln(x,y,z);
	writeln(bb[find(t[x-1],t[y],1,len,z)]);
	end;
end.

