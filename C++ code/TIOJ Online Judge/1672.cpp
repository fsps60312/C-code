#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
struct Djset
{
	int s[40000];
	void clear(const int n){assert(n<=40000);for(int i=0;i<n;i++)s[i]=i;}
	int find(const int a){return s[a]==a?a:(s[a]=find(s[a]));}
	bool merge(int a,int b){if((a=find(a))==(b=find(b)))return false;s[a]=b;return true;}
	int operator[](const int i){return find(i);}
}DJ;
struct Experiment
{
	int l,r,c;
	Experiment(){}
	Experiment(const int _l,const int _r,const int _c):l(_l),r(_r),c(_c){}
};
vector<Experiment>EXP;
int N,M;
void Discretize()
{
	vector<int>v;
	for(const Experiment &e:EXP)v.push_back(e.l),v.push_back(e.r);
	sort(v.begin(),v.end()),v.resize(unique(v.begin(),v.end())-v.begin());
	M=v.size();
	for(Experiment &e:EXP)e.l=lower_bound(v.begin(),v.end(),e.l)-v.begin(),e.r=lower_bound(v.begin(),v.end(),e.r)-v.begin();
	v.clear(),vector<int>().swap(v);
}
int Solve()
{
	DJ.clear(M*2);
	for(int i=0;i<(int)EXP.size();i++)
	{
		const Experiment &e=EXP[i];
		if(e.c==0)
		{
			DJ.merge(e.l,e.r);
			DJ.merge(M+e.l,M+e.r);
		}
		else if(e.c==1)
		{
			DJ.merge(e.l,M+e.r);
			DJ.merge(M+e.l,e.r);
		}
		else assert(0);
		if(DJ[e.l]==DJ[M+e.l])return i;
	}
	return EXP.size();
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(;;)
	{
		assert(scanf("%d%d",&N,&M)==2);
		if(N==0&&M==0)break;
		EXP.clear();
		for(int i=0,l,r,c;i<M;i++)
		{
			assert(scanf("%d%d%d",&l,&r,&c)==3);
			if(l>r)swap(l,r);
			EXP.push_back(Experiment(l-1,r,c));
		}
		Discretize();
		const int ans=Solve();
		if(ans==(int)EXP.size())puts("He didn't lie.");
		else printf("%d\n",ans+1);
	}
	assert(scanf("%d",&N)==-1);
	return 0;
}
