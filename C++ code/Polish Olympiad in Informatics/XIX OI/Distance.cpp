#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
using namespace std;
const int INF=2147483647;
template<class Type>
void getmin(Type &a,const Type &b){if(b<a)a=b;}
int N,A[100000],FP[1000001];
vector<int>P;
void BuildP()
{
	bool *isp=new bool[1000001];
	for(int i=2;i<=1000000;i++)isp[i]=true;
	for(int i=2;i<=1000000;i++)
	{
		if(isp[i])P.push_back(i),FP[i]=i;
		for(int j=0;i*P[j]<=1000000;j++)
		{
			FP[i*P[j]]=P[j];
			isp[i*P[j]]=false;
			if(i%P[j]==0)break;
		}
	}
	delete[]isp;
}
void Dfs(const vector<pair<int,int> >&fs,const int dep,vector<int>&ans,const int now)
{
	if(dep==-1){ans.push_back(now);return;}
	for(int i=0,f=1;i<=fs[dep].second;i++,f*=fs[dep].first)Dfs(fs,dep-1,ans,now*f);
}
vector<int>GetFactors(int n)
{
	vector<pair<int,int> >fs;
	while(n>1)
	{
		const int p=FP[n];
		if(fs.empty()||fs.back().first!=p)fs.push_back(make_pair(p,1));
		else fs.back().second++;
		n/=p;
	}
	vector<int>ans;
	Dfs(fs,(int)fs.size()-1,ans,1);
	return ans;
}
int PCNT[1000001];
pair<int,int>BEST1[1000001],BEST2[1000001];
int main()
{
//	freopen("in.txt","r",stdin);
	BuildP();
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&A[i]);
	for(int i=1;i<=1000000;i++)
	{
		BEST1[i]=BEST2[i]=make_pair(INF,-1);
		PCNT[i]=0;
		int n=i;
		while(n>1)PCNT[i]++,n/=FP[n];
	}
	for(int i=0;i<N;i++)
	{
		const vector<int>&fs=GetFactors(A[i]);
		for(int j=0;j<(int)fs.size();j++)
		{
			const pair<int,int>&p=make_pair(PCNT[A[i]/fs[j]],i);
			if(p<BEST1[fs[j]])BEST2[fs[j]]=BEST1[fs[j]],BEST1[fs[j]]=p;
			else if(p<BEST2[fs[j]])BEST2[fs[j]]=p;
		}
	}
	for(int i=0;i<N;i++)
	{
		pair<int,int>ans=make_pair(INF,-1);
		const vector<int>&fs=GetFactors(A[i]);
		for(int j=0;j<(int)fs.size();j++)
		{
			pair<int,int>p=BEST1[fs[j]];
			if(p.second==i)p=BEST2[fs[j]];
			p.first+=PCNT[A[i]/fs[j]];
			if(p<ans)ans=p;
		}
		printf("%d\n",ans.second+1);
	}
	return 0;
}
