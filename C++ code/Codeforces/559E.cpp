#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct SpotLight
{
	int a,l;
	bool operator<(const SpotLight &s)const{return a<s.a;}
};
int N,M;
vector<SpotLight>S;
vector<int>VALS;
int DP[300];
void Discretize()
{
	vector<int>&v=VALS;
	v.clear();
	for(const SpotLight &s:S)v.push_back(s.a-s.l),v.push_back(s.a),v.push_back(s.a+s.l);
	sort(v.begin(),v.end()),v.resize(unique(v.begin(),v.end())-v.begin());
	M=v.size();
}
int Id(const int v){return lower_bound(VALS.begin(),VALS.end(),v)-VALS.begin();}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		S.clear();
		for(int i=0;i<N;i++)
		{
			static SpotLight s;
			scanf("%d%d",&s.a,&s.l);
			S.push_back(s);
		}
		sort(S.begin(),S.end());
		Discretize();
		for(int i=0;i<M;i++)DP[i]=0;
		for(int i=0;i<M;i++)printf("%2d",VALS[i]);puts("");
		for(const SpotLight &s:S)
		{
			const int v1=DP[Id(s.a)]+s.l,v2=DP[Id(s.a-s.l)]+s.l;
			for(int i=Id(s.a);i<M;i++)getmax(DP[i],v1-max(s.a+s.l-VALS[i],0));
			for(int i=Id(s.a-s.l);i<M;i++)getmax(DP[i],v2-max(s.a-VALS[i],0));
			for(int i=0;i<M;i++)printf(" %d",DP[i]);puts("");
		}
		printf("%d\n",DP[M-1]);
	}
	return 0;
}
