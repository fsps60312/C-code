#include<cstdio>
typedef long long LL;
int N;
LL X[100000];
LL B;
LL Sum(const int l,const int r){return X[r]-X[l];}
int main()
{
	LL mx;
	scanf("%d%lld%lld",&N,&mx,&B);
	for(int i=0;i<N;i++)
	{
		scanf("%lld",&X[i]);
	}
	LL now=0LL;
	int ans=0;
	for(int l=0,r=0;r<N;r++,now+=Sum((l+r)/2,r))
	{
		while(now>B)now-=Sum(l,(l+r+1)/2),l++;
		if(r-l+1>ans)ans=r-l+1;
	}
	printf("%d\n",ans);
	return 0;
}
