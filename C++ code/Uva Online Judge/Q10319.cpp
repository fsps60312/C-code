#include<cstdio>
#include<vector>
#include<stack>
using namespace std;
int T,S,A,M;
bool VIS[400];
vector<int>TO[400];
struct Route
{
	int s1,a1,s2,a2;
	Route(){}
	Route(int s1,int a1,int s2,int a2):s1(s1),a1(a1),s2(s2),a2(a2){}
};
vector<Route>ROUTE;
void AddEdgeDownStreet(Route &r1,Route &r2,int &i1,int &i2,int r1iss1,int r2iss1)
{
	if((r1.a1>r1.a2)==(r2.a1>r2.a2))return;
	TO[i1*2+r1iss1].push_back(i2*2+(r2iss1^1));
}
void AddEdgeRightAvenue(Route &r1,Route &r2,int &i1,int &i2,int r1isa1,int r2isa1)
{
	if((r1.s1>r1.s2)==(r2.s1>r2.s2))return;
	TO[i1*2+(r1isa1^1)].push_back(i2*2+r2isa1);
}
vector<int>V;
bool dfs(int u)
{
	if(VIS[u^1])return false;
	if(VIS[u])return true;
	VIS[u]=true;
	V.push_back(u);
	for(int i=0;i<TO[u].size();i++)
	{
		int &j=TO[u][i];
		if(!dfs(j))return false;
	}
	return true;
}
bool solve()
{
	for(int i=0;i<M;i++)
	{
		if(VIS[i*2]||VIS[i*2+1])continue;
		V.clear();
		if(!dfs(i*2))
		{
			for(int j=0;j<V.size();j++)VIS[V[j]]=false;
			if(!dfs(i*2+1))return false;
		}
	}
	return true;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&S,&A,&M);
		for(int i=0;i<M*2;i++)
		{
			VIS[i]=false;
			TO[i].clear();
		}
		ROUTE.clear();
		for(int i=0,s1,a1,s2,a2;i<M;i++)
		{
			s1--,a1--,s2--,a2--;
			scanf("%d%d%d%d",&s1,&a1,&s2,&a2);
			ROUTE.push_back(Route(s1,a1,s2,a2));
		}
		for(int i1=0;i1<M;i1++)
		{
			for(int i2=0;i2<M;i2++)
			{
				if(i1==i2)continue;
				//walk street first
				Route &r1=ROUTE[i1],&r2=ROUTE[i2];
				if(r1.a1!=r1.a2&&r2.a1!=r2.a2)
				{
					if(r1.s1==r2.s1)AddEdgeDownStreet(r1,r2,i1,i2,1,1);
					if(r1.s2==r2.s2)AddEdgeDownStreet(r1,r2,i1,i2,0,0);
					if(r1.s1==r2.s2)AddEdgeDownStreet(r1,r2,i1,i2,1,0);
					if(r1.s2==r2.s1)AddEdgeDownStreet(r1,r2,i1,i2,0,1);
				}
				if(r1.s1!=r1.s2&&r2.s1!=r2.s2)
				{
					if(r1.a1==r2.a1)AddEdgeRightAvenue(r1,r2,i1,i2,1,1);
					if(r1.a2==r2.a2)AddEdgeRightAvenue(r1,r2,i1,i2,0,0);
					if(r1.a1==r2.a2)AddEdgeRightAvenue(r1,r2,i1,i2,1,0);
					if(r1.a2==r2.a1)AddEdgeRightAvenue(r1,r2,i1,i2,0,1);
				}
			}
		}
		printf("%s\n",solve()?"Yes":"No");
	}
	return 0;
}
