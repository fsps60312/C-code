#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;
struct Bst
{
	int mn,id;
	Bst(){}
	Bst(int m,int i):mn(m),id(i){}
	bool operator<(const Bst &b)const{return mn<b.mn;}
}V[1000000];
int N,B[250001];
void Set(int id,int l,int r,const int &loc,const int &v)
{
	if(l==r){V[id]=Bst(v,l);return;}
	int mid=(l+r)/2;
	if(loc<=mid)Set(id*2,l,mid,loc,v);
	else Set(id*2+1,mid+1,r,loc,v);
	V[id]=min(V[id*2],V[id*2+1]);
}
Bst Query(int id,int l,int r,const int &L,const int &R)
{
	if(l>R||r<L)return Bst(INF,-1);
	if(L<=l&&r<=R)return V[id];
	int mid=(l+r)/2;
	return min(Query(id*2,l,mid,L,R),Query(id*2+1,mid+1,r,L,R));
}
int Query(int l,int r,const int &low)
{
//	printf("(%d,%d,%d)\n",l,r,low);
	assert(l<=r);
	if(l==r)return B[l]>low?1:0;
	Bst b=Query(1,1,N,l,r);
	int ans=b.mn>low?1:0;
	if(b.id>l)ans+=Query(l,b.id-1,b.mn);
	if(b.id<r)ans+=Query(b.id+1,r,b.mn);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
	{
		static int w;
		int &h=B[i];
		scanf("%d%d",&w,&h);
		Set(1,1,N,i,h);
	}
	printf("%d\n",Query(1,N,0));
	return 0;
}
