#include<cstdio>
#include<cassert>
#include<map>
#include<utility>
#include<vector>
using namespace std;
typedef long long LL;
template<class T>inline void getmax(T&a,const T&b){if(a<b)a=b;}
void bssert(bool valid){if(!valid)for(;;);}
namespace Hasher
{
	LL V[200009],POW[200009];
	int N;
	const LL BASE=1547483647,MOD=1200000007;
	void Build(const int _N,const char *s)
	{
		N=_N;
		V[0]=0;
		for(int i=0;i<N;i++)V[i+1]=(V[i]*BASE+s[i])%MOD;
		POW[0]=1;
		for(int i=1;i<=N;i++)POW[i]=(POW[i-1]*BASE)%MOD;
	}
	LL Get(const int l,const int r)
	{
		assert(0<=l&&r<N);
		assert(l<=r);
		return ((V[r+1]-V[l]*POW[r-l+1])%MOD+MOD)%MOD;
	}
};
int N;
char S[200009];
int main()
{
//	freopen("in.txt","w",stdout);
//	for(int i=0;i<10;i++){printf("200000\n");for(int i=0;i<200000;i++)putchar('a');puts("");}return 0;
//	freopen("in.txt","r",stdin);
	while(scanf("%d%s",&N,S)==2)
	{
		Hasher::Build(N,S);
		static map<pair<LL,int>,vector<int> >end_points[200009];
		for(int height=1;height<=N;height++)end_points[height].clear();
		for(int i=0;i<N;i++)end_points[1][make_pair(Hasher::Get(i,i),1)].push_back(i);//,printf("[%d]=%lld\n",i,Hasher::Get(i,i));
		int max_height=1;
		for(int height=1;height<=max_height;height++)
		{
			for(const auto &it:end_points[height])
			{
				const int length=it.first.second;
				//bssert(length>0);
				const vector<int>&s=it.second;
				for(int l=0;l+1<(int)s.size();)
				{
					int r=l+1;
					while(r+1<(int)s.size()&&Hasher::Get(s[r-1]-length+1,s[r])==Hasher::Get(s[r]-length+1,s[r+1]))++r;
					getmax(max_height,height+(r-l));
					//printf("getmax %d\n",height+(r-l));
					end_points[height+(r-l)][make_pair(Hasher::Get(s[l]-length+1,s[r]),s[r]-(s[l]-length))].push_back(s[r]);
					l=r;
				}
			}
		}
		printf("%d\n",max_height);
	}
	return 0;
}
