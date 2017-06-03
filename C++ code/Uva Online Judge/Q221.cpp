#include<bits/stdc++.h>
using namespace std;
int N;
struct Building
{
	int idx,x1,x2,y,h,visable;
}BUILD[100];
bool cmp1(const Building &a,const Building &b){return a.y<b.y;}
bool cmp2(const Building &a,const Building &b){return a.idx<b.idx;}
bool cmp3(const Building &a,const Building &b)
{
	if(a.visable!=b.visable)return a.visable;
	if(a.x1!=b.x1)return a.x1<b.x1;
	return a.y<b.y;
}
int DP[200],ANS[200];
map<int,int>IDX;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		IDX.clear();
		for(int i=0;i<N;i++)
		{
			Building &b=BUILD[i];
			static int dep;
			scanf("%d%d%d%d%d",&b.x1,&b.y,&b.x2,&dep,&b.h);
			b.x2+=b.x1;
			b.idx=i;
			b.visable=0;
			IDX[b.x1],IDX[b.x2];
		}
		int cnt=0;
		for(map<int,int>::iterator it=IDX.begin();it!=IDX.end();it++)DP[cnt]=0,ANS[cnt]=-1,it->second=cnt++;
		sort(BUILD,BUILD+N,cmp1);
		for(int i=0,l,r;i<N;i++)
		{
			Building &b=BUILD[i];
			l=IDX[b.x1],r=IDX[b.x2];
//			printf("%d:(%d,%d)(%d,%d)%d\n",b.idx,b.x1,b.x2,l,r,b.h);
			for(int j=l;j<r;j++)
			{
				if(DP[j]<b.h)DP[j]=b.h,ANS[j]=b.idx;
			}
//			for(int i=0;i<IDX.size();i++)printf(" %d",DP[i]);puts("");
		}
		sort(BUILD,BUILD+N,cmp2);
		for(int i=0;i<IDX.size();i++)if(ANS[i]!=-1)BUILD[ANS[i]].visable=1;
		sort(BUILD,BUILD+N,cmp3);
		static int kase=1;
		if(kase>1)puts("");
		printf("For map #%d, the visible buildings are numbered as follows:\n",kase++);
		printf("%d",BUILD[0].idx+1);
		for(int i=1;BUILD[i].visable;i++)
		{
			printf(" %d",BUILD[i].idx+1);
		}
		puts("");
	}
	return 0;
}
