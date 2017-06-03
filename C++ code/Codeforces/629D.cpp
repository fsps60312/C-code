#include<cstdio>
#include<cassert>
#include<cmath>
#include<map>
#include<vector>
using namespace std;
const double PI=acos(-1.0);
int N;
double R[100000],H[100000];
double Area(const int i){return PI*R[i]*R[i]*H[i];}
map<double,double>DP;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%lf%lf",&R[i],&H[i]);
		DP.clear();
		DP[0.0]=0.0;
		for(int i=0;i<N;i++)
		{
			auto it=DP.lower_bound(R[i]);
			it--;
			auto p=make_pair(R[i],it->second+Area(i));
			it++;
			if(it->second>=p.second)continue;
			for(;it!=DP.end();)
			{
				if(p.second>=it->second)DP.erase(it++);
				else it++;
			}
			DP.insert(p);
		}
		printf("%.9f\n",DP.rbegin()->second);
	}
	return 0;
}
