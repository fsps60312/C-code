#include<cstdio>
#define LL long long
LL N,S;
LL V[100001],SUM[100001];
void getmin(int &a,int b){if(b<a)a=b;}
int main()
{
	SUM[0]=0;
	V[0]=-9223372036854775807LL;
	while(scanf("%lld%lld",&N,&S)==2)
	{
		for(int i=1;i<=N;i++)scanf("%lld",&V[i]);
		for(int i=1;i<=N;i++)SUM[i]=SUM[i-1]+V[i];
		int ans=2147483647,l=0,r,s=1;
		for(r=1;r<=N;r++)
		{
			while(SUM[r]-SUM[l+1]>=S)l++;
			if(V[r]<V[r-1])s=r;
			if(SUM[r]-SUM[l]>=S&&l+1>=s)getmin(ans,r-l);
		}
		printf("%d\n",ans==2147483647?0:ans);
	}
	return 0;
}
