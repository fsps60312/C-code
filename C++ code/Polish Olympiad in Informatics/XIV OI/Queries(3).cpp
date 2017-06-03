#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
vector<pair<int,int> >FACTORS[50001];
void BuildFactors()
{
	vector<int>p;
	bool *isp=new bool[50001];
	int *one_f=new int[50001];
	for(int i=2;i<=50000;i++)isp[i]=true,one_f[i]=i;
	for(int i=2;i<=50000;i++)
	{
		if(isp[i])p.push_back(i);
		for(int j=0;p[j]*i<=50000;j++)
		{
			isp[p[j]*i]=false;
			one_f[p[j]*i]=p[j];
			if(i%p[j]==0)break;
		}
	}
	for(int i=2;i<=50000;i++)assert(isp[one_f[i]]);
	for(int i=1;i<=50000;i++)
	{
		vector<int>fs;
		for(int n=i;n>1;)fs.push_back(one_f[n]),n/=one_f[n];
		for(int j=1;j<(int)fs.size();j++)assert(fs[j-1]<=fs[j]);
		fs.resize(unique(fs.begin(),fs.end())-fs.begin());
		const int sz=(int)fs.size();
		FACTORS[i].clear();
		for(int s=1;s<)
	}
	delete[]isp;
	delete[]one_f;
}
int N;
int main()
{
	freopen("in.txt","r",stdin);
	BuildFactors();
	return 0;
}
