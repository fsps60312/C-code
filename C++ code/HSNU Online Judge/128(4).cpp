#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
struct Bit
{
	int s[1000001],n;
	void clear(const int _n){n=_n;for(int i=1;i<=n;i++)s[i]=0;}
	void Add(int i,const int v){while(i<=n)s[i]+=v,i+=(i&(-i));}
	int Query(int i){int ans=0;while(i)ans+=s[i],i-=(i&(-i));return ans;}
}BIT;
void BuildFail(const int n,const vector<int>&s,vector<int>&rank,vector<int>&fail)
{
	rank.clear(),BIT.clear(n);
	for(int i=0;i<n;i++)BIT.Add(s[i],1),rank.push_back(BIT.Query(s[i]));
	fail.clear(),fail.resize(2,0),BIT.clear(n);
	for(int r=1,l=1;r<n;r++)
	{
//		printf("r=%d,fail=%d\n",r,fail[r]);
		BIT.Add(s[r],1);
		int f=fail[r];
		while(l+f<r)BIT.Add(s[l++],-1);
		while(rank[f]!=BIT.Query(s[r]))
		{
//			printf("f=%d,query=%d\n",rank[f],BIT.Query(s[r]));
			assert(f>0);
			f=fail[f];
			while(l+f<r)BIT.Add(s[l++],-1);
		}
		fail.push_back(f+1);
	}
//	for(auto v:fail)printf(" %d",v);puts("");
}
vector<int>LOGO,FAIL,RANK;
int N,BUILD[1000000];
void ReIndex()
{
	map<int,int>idx;
	for(int i=0;i<N;i++)idx[BUILD[i]]=-1;
	assert((int)idx.size()==N);
	int cnt=1;
	for(auto &it:idx)it.second=cnt++;
	for(int i=0;i<N;i++)BUILD[i]=idx[BUILD[i]];
}
void Solve(vector<int>&ans)
{
	BIT.clear(N);
	ans.clear();
	int u=0;
	for(int r=0,l=0;r<N;r++)
	{
		BIT.Add(BUILD[r],1);
		while(l+u<r)BIT.Add(BUILD[l++],-1);
		assert(l+u==r);
		while(RANK[u]!=BIT.Query(BUILD[r]))
		{
			assert(u>0);
			u=FAIL[u];
			while(l+u<r)BIT.Add(BUILD[l++],-1);
		}
//		printf("i=%d,build=%d,match=%d\n",r,BUILD[r],u+1);
		if(++u==(int)LOGO.size())
		{
			ans.push_back(l);
			u=FAIL[u]+1;
		}
	}
}
int main()
{
	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	if(1)
	{
		static int ln;scanf(2,"%d%d",&ln,&N);
		LOGO.resize(ln);
		for(int i=1,v;i<=ln;i++)scanf(1,"%d",&v),LOGO[--v]=i;
		BuildFail(ln,LOGO,RANK,FAIL);
	}
	for(int i=0;i<N;i++)scanf(1,"%d",&BUILD[i]);
	ReIndex();
	static vector<int>ans;
	Solve(ans);
	printf("%d\n",(int)ans.size());
	if(!ans.empty())
	{
		for(int i=0;i<(int)ans.size();i++)
		{
			if(i)putchar(' ');
			printf("%d",ans[i]+1);
		}
		puts("");
	}
	return 0;
}
