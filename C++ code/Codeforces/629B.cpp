#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Guest
{
	int gender,day,dif;
	bool operator<(const Guest &g)const{return day<g.day;}
};
int N;
vector<Guest>G;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		G.clear();
		for(int i=0,a,b;i<N;i++)
		{
			static char gender[2];
			static Guest g;
			scanf("%s%d%d",gender,&a,&b);
			if(gender[0]=='M')g.gender=0;
			else if(gender[0]=='F')g.gender=1;
			else assert(0);
			g.day=a,g.dif=1;
			G.push_back(g);
			g.day=b+1,g.dif=-1;
			G.push_back(g);
		}
		sort(G.begin(),G.end());
		int cnt[2]={0,0};
		int ans=0;
		for(int i=0;i<(int)G.size();)
		{
			const int day=G[i].day;
			while(i<(int)G.size()&&G[i].day==day)
			{
				cnt[G[i].gender]+=G[i].dif;i++;
			}
			getmax(ans,min(cnt[0],cnt[1]));
		}
		printf("%d\n",ans*2);
	}
	return 0;
}
