#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int T,N;
int X[1000000],Y[1000000];
int random1()
{
	static int seed=20151001;
	seed*=0x0defaced;
	return ++seed;
}
int ran(const int &l,const int &r){return l+abs(random1())%(r-l+1);}
void Partsort(int *s,const int &l,const int &r,const int &idx)
{
	assert(l<=r);
	if(l==r)return;
	const int &v=s[ran(l,r)];
	int li=l,ri=r,mi=l+1;
	while(mi<=ri)
	{
		if(s[li]<v)li++;
		else if(s[li]>v)
		{
			swap(s[li],s[ri]);
			ri--;
		}
		else
		{
			swap(s[li],s[mi]);
			mi++;
		}
	}
	for(int i=l;i<li;i++)assert(s[i]<v);
	for(int i=li;i<mi;i++)assert(s[i]==v);
	for(int i=mi;i<=r;i++)assert(s[i]>v);
//	for(int i=l;i<=r;i++)printf(" %d",s[i]);printf("v=%d,",v);
//	printf("(%d,%d):(%d,%d)\n",l,r,li,ri);
	if(idx>=li&&idx<=ri)return;
	if(idx<li)
	{
		Partsort(s,l,li-1,idx);
	}
	else if(idx>ri)
	{
		Partsort(s,ri+1,r,idx);
	}
	else assert(0);
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)
		{
			scanf("%d%d",&X[i],&Y[i]);
		}
		Partsort(X,0,N-1,N/2),Partsort(Y,0,N-1,N/2);
		LL x=X[N/2],y=Y[N/2];
		LL ans=0LL;
		for(int i=0;i<N;i++)ans+=abs(x-X[i])+abs(y-Y[i]);
		printf("%lld\n",ans);
	}
	return 0;
}
