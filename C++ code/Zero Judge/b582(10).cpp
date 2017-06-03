#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int T,N;
int X[1000000],Y[1000000];
inline int random1()
{
	return rand()*rand()+rand();
}
inline int ran(const int &l,const int &r){return l+abs(random1())%(r-l+1);}
void Partsort(int *s,const int &l,const int &r,const int &idx)
{
	assert(l<=r);
	if(l==r)return;
	int v=s[ran(l,r)];
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
int main()
{
	srand(time(NULL));
	freopen("in.txt","r",stdin);
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
