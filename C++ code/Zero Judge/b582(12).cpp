#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int T,N;
int X[1000000],Y[1000000];
int Select(int *s,const int &l,const int &r)
{
	int v[5],sz=r-l+1;
	if(sz<=5)
	{
		for(int i=l;i<=r;i++)v[i-l]=s[i];
		sort(v,v+sz);
		return v[sz/2];
	}
	for(int p=1,li=l,ri;p<=5;p++)
	{
		ri=l+sz*p/5;
		v[p-1]=Select(s,li,ri-1);
		li=ri;
	}
	sort(v,v+5);
	return v[2];
}
void Partsort(int *s,const int &l,const int &r,const int &idx)
{
	assert(l<=r);
	if(l==r)return;
	int v=Select(s,l,r);
	int li=l-1,ri=r+1,mi=r+1;
	while(li+1<mi)
	{
		if(s[li+1]<v)li++;
		else if(s[li+1]>v)
		{
			if(mi--<ri--)swap(s[mi],s[ri]);
			if(li+1!=mi)swap(s[li+1],s[ri]);
		}
		else
		{
			swap(s[li+1],s[--mi]);
		}
	}
	if(idx>=mi&&idx<ri)return;
	if(idx<=li)
	{
		Partsort(s,l,li,idx);
	}
	else
	{
		Partsort(s,ri,r,idx);
	}
}
inline bool Digit(const int &c){static int c0='0',c9='9';return c>=c0&&c<=c9;}
inline void GetInt(int &v)
{
	static int c,c0='0',dash='-';
	static bool nega;
	nega=false;
	while(!Digit(c=getchar()))nega=(c==dash);
	v=c-c0;
	while(Digit(c=getchar()))v*=10,v+=c-c0;
	if(nega)v*=-1;
//	printf("v=%d\n",v);
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)
		{
			GetInt(X[i]),GetInt(Y[i]);
		}
		Partsort(X,0,N-1,N/2),Partsort(Y,0,N-1,N/2);
		LL x=X[N/2],y=Y[N/2];
		LL ans=0LL;
		for(int i=0;i<N;i++)ans+=abs(x-X[i])+abs(y-Y[i]);
		printf("%lld\n",ans);
	}
	return 0;
}
