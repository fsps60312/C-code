#include<cstdio>
#include<cassert>
#include<queue>
#include<vector>
#include<map>
using namespace std;
const int BOUND=100000;
vector<int>P;
void BuildP()
{
	P.clear();
	bool *isp=new bool[1000001];
	for(int i=2;i<=1000000;i++)isp[i]=true;
	for(int i=2;i<=1000000;i++)
	{
		if(isp[i])P.push_back(i);
		for(int j=0;i*P[j]<=1000000;j++)
		{
			isp[i*P[j]]=false;
			if(i%P[j]==0)break;
		}
	}
	delete[]isp;
//	for(int i=0;i<100;i++)printf("%d\n",P[i]);
}
#include<utility>
typedef long long LL;
map<LL,pair<int,map<int,int> > >S;
int main()
{
//	freopen("in.txt","r",stdin);
	BuildP();
	S.clear();
	if(true)
	{
		map<int,int>sec;
		S[1LL]=make_pair(1,sec);
	}
	vector<LL>ans;
	pair<int,int>p=make_pair(-1,0);
	int pp=-1;
	while(!S.empty())
	{
		const auto &it=*S.begin();
		const int cf=it.second.first;
//		printf("val=%lld,cf=%d\n",it.first,cf);
		if(cf==p.first)++p.second;
		if(cf>p.first)pp=p.first,p=make_pair(cf,1);
		else if(cf>pp)pp=cf;
		if(cf<p.first&&(p.second>1||cf<pp));
		else ans.push_back(it.first),printf("%lld\n",it.first);
		for(int i=0;i<(int)P.size()&&it.first*P[i]<=BOUND;i++)
		{
			map<int,int>nxtm=it.second.second;
			const int v=++nxtm[P[i]];
			const int nxtc=cf/v*(v+1);
			S[it.first*P[i]]=make_pair(nxtc,nxtm);
		}
		S.erase(S.begin());
	}
	int n;scanf("%d",&n),--n;
	printf("%lld\n",n>=(int)ans.size()?-1LL:ans[n]);
	return 0;
}
