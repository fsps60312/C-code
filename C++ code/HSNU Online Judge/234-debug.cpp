#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<set>
#include<vector>
#include<map>
#include<queue>
using namespace std;
int N,M;
struct Period
{
	int d1,d2;
	bool operator<(Period a)const{return d2>a.d2;}
}PERIOD[200005];
struct Gap
{
	int l,r,cnt;
	Gap(){}
	Gap(const int &l,const int &r,const int &cnt):l(l),r(r),cnt(cnt){}
	bool operator<(Gap a)const{return r<a.r;}
};
set<Gap>S;
priority_queue<Period>PQ;
vector<int>DATE;
map<int,int>IDX;
int DP[200005*2][20];
int main()
{
	freopen("in.txt","r",stdin);
	memset(DP,-1,sizeof(DP));
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		Period &p=PERIOD[i];
		scanf("%d%d",&p.d1,&p.d2);
		DATE.push_back(p.d1),DATE.push_back(p.d2);
	}
	sort(DATE.begin(),DATE.end()),DATE.resize(unique(DATE.begin(),DATE.end())-DATE.begin());
	M=DATE.size();
	for(int i=0;i<DATE.size();i++)IDX[DATE[i]]=i;
	for(int i=0;i<N;i++)
	{
		Period &p=PERIOD[i];
		p.d1=IDX[p.d1],p.d2=IDX[p.d2];
		PQ.push(p);
	}
	for(int i=0;i<M;i++)
	{
		while(PQ.size()&&PQ.top().d1<i)PQ.pop();
		if(PQ.size())DP[i][0]=PQ.top().d2;
	}
	for(int j=1;j<20;j++)
	{
		for(int i=0;i<M;i++)
		{
			int &dp=DP[i][j-1];
			if(dp==-1)continue;
			DP[i][j]=DP[dp+1][j-1];
         }
	}
	for(int i=0;i<M;i++)
	{
		for(int j=0;j<5;j++)printf("%d ",DP[i][j]);puts("");
	}
	int ans=0;
	for(int i=19,x=0;i>=0;i--)
	{
		if(DP[x][i]!=-1)
		{
			ans+=1<<i;
			x=DP[x][i]+1;
		}
	}
	//ans=7;
	printf("%d\n",ans);
	S.insert(Gap(0,M-1,ans));
	for(int i=0;i<N;i++)
	{
		Period &p=PERIOD[i];
		set<Gap>::iterator it=S.lower_bound(Gap(0,p.d2,0));
		if(it==S.end()||(*it).l>p.d1) continue;
		int ladd=0,radd=0;
		if((*it).l!=p.d1)
		{
			for(int j=19,x=(*it).l;j>=0;j--)
			{
				if(DP[x][j]!=-1&&DP[x][j]<p.d1)
				{
					ladd+=1<<j;
					x=DP[x][j]+1;
				}
			}
		}
		if((*it).r!=p.d2)
		{
			for(int j=19,x=p.d2+1;j>=0;j--)
			{
				if(DP[x][j]!=-1&&DP[x][j]<=(*it).r)
				{
					radd+=1<<j;
					x=DP[x][j]+1;
				}
			}
		}
		if(ladd+1+radd!=(*it).cnt) continue;
		printf("%d ",i+1);
		Gap in=(*it);
		S.erase(it);
		if(ladd)S.insert(Gap(in.l,p.d1-1,ladd));
		if(radd)S.insert(Gap(p.d2+1,in.r,radd));
	}
}
