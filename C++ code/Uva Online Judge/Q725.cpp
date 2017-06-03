#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
int N,NUMBER[5];
bool VIS[10];
vector<pair<int,int> >ANS[80];
bool Check(const int v,const int dep)
{
	if(dep==5)return true;
	if(VIS[v%10])return false;
	VIS[v%10]=true;
	bool ans=Check(v/10,dep+1);
	VIS[v%10]=false;
	return ans;
}
void Dfs(const int dep)
{
	if(dep==5)
	{
		int down=0;
		for(int i=0;i<5;i++)down=down*10+NUMBER[i];
		for(int val=2;val*down<100000;val++)
		{
			if(Check(val*down,0))ANS[val].push_back(make_pair(val*down,down));
		}
		return;
	}
	for(int i=0;i<10;i++)if(!VIS[i])
	{
		VIS[i]=true;
		NUMBER[dep]=i;
		Dfs(dep+1);
		VIS[i]=false;
	}
}
int main()
{
	for(int i=0;i<10;i++)VIS[i]=false;
	Dfs(0);
	for(int i=2;i<=79;i++)sort(ANS[i].begin(),ANS[i].end());
	while(scanf("%d",&N)==1)
	{
		if(N==0)break;
		static int kase=0;
		if(kase++)puts("");
		if(ANS[N].empty())printf("There are no solutions for %d.\n",N);
		else
		{
			for(const pair<int,int>&p:ANS[N])printf("%05d / %05d = %d\n",p.first,p.second,N);
		}
	}
	return 0;
}
