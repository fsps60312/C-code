#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int N,W,H,P[15];
int DP[101][101][15];
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
		for(int i=0;i<A[a].size()&&i<N;i++)if(getDP(w1,h,i)){found=true;break;}
		if(!found)continue;
		found=false;
		a=(w-w1)*h;
		for(int i=0;i<A[a].size()&&i<N;i++)if(getDP(w-w1,h,i)){found=true;break;}
		if(!found)continue;
		return dp=1;
	}
	for(int h1=1,a;h1<h;h1++)
	{
		a=w*h1;
		bool found=false;
		for(int i=0;i<A[a].size()&&i<N;i++)if(getDP(w,h1,i)){found=true;break;}
		if(!found)continue;
		found=false;
		a=w*(h-h1);
		for(int i=0;i<A[a].size()&&i<N;i++)if(getDP(w,h-h1,i)){found=true;break;}
		if(!found)continue;
		return dp=1;
	}
	return dp=0;
}
void PushToA(int idx,int s)
{
	if(idx==N)
	{
		int a=0;
		for(int k=0;k<N;k++)if(s&(1<<k))a+=P[k];
		A[a].push_back(s);
//		for(int k=0;k<N;k++)
//		{
//			printf("%d",s&1);
//			s>>=1;
//		}printf("\n");
		return;
	}
	int r=idx;
	while(r<N&&P[r]==P[idx])r++;
	for(int i=0;i<=r-idx;i++)
	{
		PushToA(r,s|(((1<<i)-1)<<idx));
	}
}
int main()
{
//	freopen("inn.txt","r",stdin);
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		scanf("%d%d",&W,&H);
		if(W<H)swap(W,H);
		for(int i=W*H;i>=0;i--)A[i].clear();
		int sum=0;
		for(int i=0;i<N;i++)
		{
			scanf("%d",&P[i]);
			sum+=P[i];
			for(int j=0;j<=W;j++)for(int k=0;k<=H;k++)DP[j][k][i]=-1;
		}
		sort(P,P+N);
		PushToA(0,0);
		printf("Case %d: ",kase++);
		printf(sum==W*H&&A[W*H].size()&&getDP(W,H,0)?"Yes\n":"No\n");
	}
	return 0;
}
