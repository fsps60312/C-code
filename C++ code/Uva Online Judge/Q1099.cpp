#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int N,W,H,P[15];
int DP[100][100][15];
vector<int> A[10001];
int cntbits(int a)
{
	a=((a&0xaaaaaaaa)>>1)+(a&0x55555555);
	a=((a&0xcccccccc)>>2)+(a&0x33333333);
	a=((a&0xf0f0f0f0)>>4)+(a&0x0f0f0f0f);
	a=((a&0xff00ff00)>>8)+(a&0x00ff00ff);
	a=((a&0xffff0000)>>16)+(a&0x0000ffff);
	return a;
}
int getDP(int w,int h,int s)
{
	if(w<h)swap(w,h);
	int &dp=DP[w][h][s];
	if(dp!=-1)return dp;
	s=A[w*h][s];
	if(cntbits(s)==1)return dp=1;
	for(int w1=1,a;w1<w;w1++)
	{
		a=w1*h;
		bool found=false;
		for(int i=0;i<A[a].size();i++)if(getDP(w1,h,i)){found=true;break;}
		if(!found)continue;
		found=false;
		a=(w-w1)*h;
		for(int i=0;i<A[a].size();i++)if(getDP(w-w1,h,i)){found=true;break;}
		if(!found)continue;
		return dp=1;
	}
	for(int h1=1,a;h1<h;h1++)
	{
		a=w*h1;
		bool found=false;
		for(int i=0;i<A[a].size();i++)if(getDP(w,h1,i)){found=true;break;}
		if(!found)continue;
		found=false;
		a=w*(h-h1);
		for(int i=0;i<A[a].size();i++)if(getDP(w,h-h1,i)){found=true;break;}
		if(!found)continue;
		return dp=1;
	}
	return dp=0;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		scanf("%d%d",&W,&H);
		if(W<H)swap(W,H);
		for(int i=W*H;i>=0;i--)A[i].clear();
		for(int i=0;i<N;i++)
		{
			scanf("%d",&P[i]);
			for(int j=0;j<=W;j++)for(int k=0;k<=H;k++)DP[j][k][i]=-1;
		}
		for(int i=0,a=0,k;i<1<<N;i++,a=0)
		{
			for(k=0;k<N;k++)if(i&(1<<k))a+=P[k];
			A[a].push_back(i);
		}
		printf("Case %d: ",kase++);
		printf(getDP(W,H,0)?"Yes\n":"No\n");
	}
	return 0;
}
