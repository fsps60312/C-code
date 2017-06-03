#include<cstdio>
#include<algorithm>
using namespace std;
void getmin(int &a,int b){if(b<a)a=b;}
int N,MN;
struct Value
{
	int v,p,r,vis;
}S[1000];
bool cmpp(Value a,Value b){return a.p<b.p;}
bool cmpv(Value a,Value b){return a.v!=b.v?a.v<b.v:a.p<b.p;}
int getCYC(int fa)
{
	int ans=0,sum=0,mn=1000,cnt,u=fa;
	for(cnt=0;;cnt++,u=S[u].r)
	{
		if(cnt&&u==fa)break;
		S[u].vis=1;
		sum+=S[u].v;
		getmin(mn,S[u].v);
	}
	if(cnt==1)return 0;
	return min(mn*(cnt-2)+sum,2*(MN+mn)+MN*(cnt-1)+sum-mn);
}
int main()
{
//	freopen("in.txt","r",stdin);
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		MN=1000;
		for(int i=0;i<N;i++)
		{
			scanf("%d",&S[i].v);
			getmin(MN,S[i].v);
			S[i].p=i;
			S[i].vis=0;
		}
		sort(S,S+N,cmpv);
		for(int i=0;i<N;i++)S[i].r=i;
		sort(S,S+N,cmpp);
		int ans=0;
		for(int i=0;i<N;i++)
		{
			if(S[i].vis)continue;
			ans+=getCYC(i);
		}
		printf("Case %d: %d\n\n",kase++,ans);
	}
	return 0;
}
