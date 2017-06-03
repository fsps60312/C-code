#include<cstdio>
#include<algorithm>
using namespace std;
int M,N,CNT[2];
struct Cut
{
	int type,cost;
	Cut(){}
	Cut(const int &t,const int &c):type(t),cost(c){}
	bool operator<(const Cut &p)const{return cost>p.cost;}
};
vector<Cut>CUT;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&M,&N)==2)
	{
		CUT.clear();
		for(int i=0,v;i<M-1;i++)
		{
			scanf("%d",&v);
			CUT.push_back(Cut(0,v));
		}
		for(int i=0,v;i<N-1;i++)
		{
			scanf("%d",&v);
			CUT.push_back(Cut(1,v));
		}
		sort(CUT.begin(),CUT.end());
		CNT[0]=CNT[1]=1;
		int ans=0;
		for(int i=0;i<CUT.size();i++)
		{
			const Cut &c=CUT[i];
			ans+=c.cost*CNT[c.type];
			CNT[c.type^1]++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
