#include<cstdio>
#include<vector>
#include<cassert>
#include<map>
using namespace std;
struct Djset
{
	int s[10000];
	bool reindexed;
	void clear(const int n){reindexed=false;for(int i=0;i<n;i++)s[i]=i;}
	int Find(const int a){assert(!reindexed);return s[a]==a?a:(s[a]=Find(s[a]));}
	bool Merge(int a,int b){assert(!reindexed);if((a=Find(a))==(b=Find(b)))return false;s[a]=b;return true;}
	void ReIndex(const int n,vector<vector<int> >&result)
	{
		result.clear();
		map<int,int>idx;
		for(int i=0;i<n;i++)
		{
			const int v=Find(i);
			auto it=idx.find(v);
			if(it==idx.end())
			{
				const int sz=idx.size();
				result.push_back(vector<int>());
				idx[v]=sz;
				it=idx.find(v);
			}
			assert(it!=idx.end());
			result[it->second].push_back(i);
		}
		for(int i=0;i<n;i++)s[i]=idx[s[i]];
		reindexed=true;
	}
}DJ;
struct TwoSat
{
	vector<vector<int> >ET;
	vector<bool>TF;
	void clear(const int n)
	{
		ET.resize(n*2),TF.resize(n*2);
		for(int i=0;i<n*2;i++)ET[i].clear(),TF[i]=false;
	}
}TWOSAT;
int N,T;
int S[10000];
vector<vector<int> >SAME;
bool BANNED[10000];
int CHOICE[10000];
bool Solve()
{
	for(int i=0;i<N;i++)
	{
		BANNED[i]=false;
	}
	TWOSAT.clear(N);
	for(const auto &same:SAME)
	{
		static bool contain[4];
		for(int i=0;i<4;i++)contain[i]=false;
		int cnt=0;
		for(const auto v:same)if(!contain[S[v]])contain[S[v]]=true,cnt++;
		if(cnt==4)return false;
		else if(cnt==3)
		{
			int mid;
			for(int i=0;;i++){assert(i<4);if(!contain[i]){mid=i^2;break;}}
			for(const auto v:same)if(S[v]!=mid)
			{
				if(BANNED[v])return false;
				if(v-1>=0)BANNED[v-1]=true;
				if(v+1<N)BANNED[v+1]=true;
			}
		}
		else if(cnt==2)
		{
			vector<int>tmp;
			for(int i=0;i<4;i++)if(contain[i])tmp.push_back(i);
			if((tmp[0]-tmp[1])%2==0)
			{
				for(const auto v:same)
				{
					if(BANNED[v])return false;
					if(v-1>=0)BANNED[v-1]=true;
					if(v+1<N)BANNED[v+1]=true;
				}
			}
			else
			{
				int must=-1;
				for(const auto v:same)
				{
					if(BANNED[v])
					{
						if(must==-1)must=S[v];
						else if(must!=S[v])return false;
					}
				}
				if(must!=-1)
				{
					for(const auto v:same)if(S[v]!=must)
					{
						assert(!BANNED[v]);
						if(v-1>=0)BANNED[v-1]=true;
						if(v+1<N)BANNED[v+1]=true;
					}
				}
				else
				{
					const int first=same[0];
					for(const auto v:same)
					{
						TWOSAT.Add(v,true,first,S[first]==S[v]?true:false);
						TWOSAT.Add(v,false,first,S[first]==S[v]?false:true);
						TWOSAT.Add(first,true,v,S[first]==S[v]?true:false);
						TWOSAT.Add(first,false,v,S[first]==S[v]?false:true);
						if(v-1>=0)TWOSAT.Add(v,true,v-1,false);
						if(v+1<N)TWOSAT.Add(v,true,v+1,false);
					}
				}
			}
		}
		else assert(cnt==1);
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	for(;;)
	{
		assert(scanf("%d%d",&N,&T)==2);
		if(N==0&&T==0)break;
		static char tmp[10001];assert(scanf("%s",tmp)==1);
		for(int i=0;i<N;i++)
		{
			switch(tmp[i])
			{
				case'A':S[i]=0;break;
				case'G':S[i]=1;break;
				case'T':S[i]=2;break;
				case'C':S[i]=3;break;
				default:assert(0);break;
			}
		}
		DJ.clear(N);
		for(int i=0;i<T;i++)
		{
			static int len;assert(scanf("%d:",&len)==1);
			vector<int>seq;
			for(int i=0,v;i<len;i++)assert(scanf("%d",&v)==1&&v>=0&&v<N),seq.push_back(v);
			for(int i=0,j=len-1;i<j;i++,j--)DJ.Merge(i,j);
		}
		DJ.ReIndex(N,SAME);
		puts(Solve()?"YES":"NO");
	}
	return 0;
}
