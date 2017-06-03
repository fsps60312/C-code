#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
#include<utility>
#include<algorithm>
using namespace std;
vector<int>P;
void BuildPrimes()
{
	bool *isp=new bool[51001];
	for(int i=2;i<=51000;i++)isp[i]=true;
	for(int i=2;i<=51000;i++)
	{
		if(isp[i])P.push_back(i);
		for(int j=0;P[j]*i<=51000;j++)
		{
			isp[P[j]*i]=false;
			if(i%P[j]==0)break;
		}
	}
	delete[]isp;
	printf("%lld\n",lower_bound(P.begin(),P.end(),50000)-P.begin());
}
int N;
vector<int>S[50001];
int ANS[100000];
int main()
{
	freopen("in.txt","r",stdin);
	BuildPrimes();
	while(scanf("%d",&N)==1)
	{
		for(int i=1;i<=50000;i++)S[i].clear();
		for(int i=0,a,b,d;i<N;i++)scanf("%d%d%d",&a,&b,&d),S[a/d].push_back(i*2),S[b/d].push_back(i*2+1);
		set<pair<int,int> >s;
		s.insert(make_pair(0,1));
		for(int i=0;i<(int)P.size();i++)
		{
			vector<pair<int,int> >to_insert;
			for(set<pair<int,int> >::const_iterator it=s.begin();it!=s.end()&&abs(it->second)*P[i]<=50000;++it)
			{
				to_insert.push_back(make_pair(0,it->second*(-P[i])));
			}
			for(int j=0;j<(int)to_insert.size();j++)s.insert(to_insert[j]);
		}
		int now=0;
		for(int n=1;n<=50000;n++)
		{
			for(pair<int,int>p;(p=*s.begin()).first<n;)
			{
				s.erase(s.begin());
				if(p.second<0)--now;
				else ++now;
				s.insert(make_pair(p.first+abs(p.second),p.second));
			}
			for(int i=0;i<(int)S[n].size();i++)ANS[S[n][i]]=now;
		}
		for(int i=0;i<N;i++)printf("%d\n",ANS[i*2]*ANS[i*2+1]);
	}
	return 0;
}
