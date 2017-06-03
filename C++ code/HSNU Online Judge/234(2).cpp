#include<cstdio>
#include<map>
#include<vector>
#include<algorithm>
#include<set>
#include<cassert>
using namespace std;
int N;
struct Company
{
	int d1,d2,idx;
	Company(){}
	Company(const int &d1,const int &d2,const int &idx):d1(d1),d2(d2),idx(idx){}
};
vector<Company>COMPANY;
map<int,int>IDX;
void Reindex()
{
	int cnt=0;
	for(auto it=IDX.begin();it!=IDX.end();it++)it->second=cnt++;
	for(int i=0;i<N;i++)
	{
		Company &c=COMPANY[i];
		c.d1=IDX[c.d1],c.d2=IDX[c.d2];
	}
}
bool cmpd2(const Company &a,const Company &b){return a.d2<b.d2;}
vector<vector<int> >DP;
struct Seg
{
	int l,r,cnt;
	Seg(){}
	Seg(const int &l,const int &r,const int &cnt):l(l),r(r),cnt(cnt){}
	bool operator<(const Seg &a)const{return l>a.l;}
};
set<Seg>S;
int GetCnt(const int &l,const int &r)
{
	int ans=0;
	int idx=l;
	while(idx<=r)
	{
		int i;
		if(idx>=DP.size()||!DP[idx].size())return ans;
		for(i=0;i+1<DP[idx].size()&&DP[idx][i+1]<=r;i++);
		idx=DP[idx][i]+1;
		ans+=1<<i;
	}
	return ans-1;
}
bool cmpidx(const Company &a,const Company &b){return a.idx<b.idx;}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)
		{
			static int d1,d2;scanf("%d%d",&d1,&d2);
			COMPANY.push_back(Company(d1,d2,i));
			IDX[d1]=IDX[d2]=0;
		}
		Reindex();
		sort(COMPANY.begin(),COMPANY.end(),cmpd2);
		DP.clear();
		for(int i=0,j=0;i<IDX.size();i++)
		{
			while(j<COMPANY.size()&&COMPANY[j].d1<i)j++;
			if(j==COMPANY.size())break;
			DP.push_back(vector<int>());
			DP[i].push_back(COMPANY[j].d2);
		}
		for(int d=1;(1<<d)<DP.size();d++)
		{
			for(int i=0;i+(1<<d)<DP.size();i++)
			{
				int x=i;
				if(d-1>=DP[x].size())continue;
				x=DP[x][d-1]+1;
				if(x>=DP.size()||d-1>=DP[x].size())continue;
				x=DP[x][d-1];
				DP[i].push_back(x);
			}
		}
//for(int i=0;i<DP.size();i++)for(int j=0;j<DP[i].size();j++)printf(" %d",DP[i][j]);puts("");
		S.clear();
		int ans=GetCnt(0,IDX.size()-1);
		printf("%d\n",ans);
		S.insert(Seg(0,IDX.size()-1,ans));
		int cnt=0;
		sort(COMPANY.begin(),COMPANY.end(),cmpidx);
//		for(int i=0;i<8;i++)
//		{
//			auto it=S.lower_bound(Seg(i,0,0));
//			printf("i=%d ",i);
//			if(it==S.end())puts("end");
//			else printf("(%d,%d,%d)\n",(*it).l,(*it).r,(*it).cnt);
//		}
		for(int i=0;i<N;i++)
		{
			Company &c=COMPANY[i];
			auto it=S.lower_bound(Seg(c.d1,c.d2,-1));
			if(it==S.end()||c.d2>(*it).r)continue;
			int v1,v2;
			if((*it).l==c.d1)v1=0;
			else v1=GetCnt((*it).l,c.d1-1);
			if(c.d2==(*it).r)v2=0;
			else v2=GetCnt(c.d2+1,(*it).r);
			if(v1+v2!=(*it).cnt-1)continue;
//printf("\n%d(%d,%d)%d\n",i,(*it).l,(*it).r,(*it).cnt);
			S.erase(it);
			if(v1)S.insert(Seg((*it).l,c.d1-1,v1));
			if(v2)S.insert(Seg(c.d2+1,(*it).r,v2));
			printf("%d ",i+1);
			cnt++;
		}
		puts("");
		assert(cnt==ans);
		break;
	}
	return 0;
}
