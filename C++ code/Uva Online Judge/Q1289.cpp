#include<bits/stdc++.h>
using namespace std;
int N;
vector<int>STK[50],ALL;
struct Pair
{
	int x,y;
	Pair(){}
	Pair(const int &x,const int &y):x(x),y(y){}
	bool operator<(const Pair &p)const{return x!=p.x?x<p.x:y<p.y;}
};
set<Pair>STAIR;
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	while(scanf("%d",&N)==1)
	{
		ALL.clear();
		STAIR.clear();
		for(int i=0,h;i<N;i++)
		{
			STK[i].clear();
			scanf("%d",&h);
			for(int v;h--;){scanf("%d",&v);STK[i].push_back(v);ALL.push_back(v);}
		}
		sort(ALL.begin(),ALL.end());
		for(int i=1;i<ALL.size();i++)
		{
			assert(ALL[i-1]<=ALL[i]);
			if(ALL[i-1]<ALL[i])STAIR.insert(Pair(ALL[i-1],ALL[i]));
		}
		int ans=0;
		for(int i=0;i<N;i++)
		{
			for(int j=1;j<STK[i].size();j++)
			{
				assert(STK[i][j-1]<=STK[i][j]);
				if(STK[i][j-1]<STK[i][j])
				{
					Pair p=Pair(STK[i][j-1],STK[i][j]);
					if(STAIR.find(p)!=STAIR.end())STAIR.erase(p);
					else ans++;
				}
			}
		}
		ans+=ans+N-1;
		static int kase=1;
		printf("Case %d: %d\n",kase++,ans);
	}
	return 0;
}
