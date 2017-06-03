#include<cstdio>
#include<cassert>
#include<queue>
#include<vector>
using namespace std;
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
int CountFactors(const int n)
{
	int ans=0,i;
	for(i=1;i*i<n;i++)if(n%i==0)ans+=2;
	if(i*i==n)ans++;
	return ans;
}
#include<utility>
int main()
{
	freopen("in.txt","r",stdin);
	BuildP();
	pair<int,int>p=make_pair(-1,0);
	int pp=-1;
	for(int i=1,cnt=0;i<=1000000;i++)
	{
		const int cf=CountFactors(i);
		if(cf==p.first)++p.second;
		if(cf>p.first)pp=p.first,p=make_pair(cf,1);
		else if(cf>pp)pp=cf;
		if(cf<p.first&&(p.second>1||cf<pp));
		else printf("%d: %d\n",++cnt,i);
	}
	return 0;
}
