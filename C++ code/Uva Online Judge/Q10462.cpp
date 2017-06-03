#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
struct pairtype
{
	int x,y,z;
};
pairtype S[200],tmp[200];
void rangeS(int a,int b)
{
	if(a==b) return;
	int mid=(a+b)/2;
	rangeS(a,mid);
	rangeS(mid+1,b);
	int c=a,d=mid+1;
	for(int i=a;i<=b;i++)
	{
		if(d>b||(c<=mid&&S[c].z<S[d].z)) tmp[i]=S[c++];
		else tmp[i]=S[d++];
	}
	for(int i=a;i<=b;i++) S[i]=tmp[i];
}
int T,v,e;
vector<int> side[100];
vector<int> onloop;
int anc[100];
bool vis[100];
int fin(int a)
{
	if(anc[a]==a) return a;
	return anc[a]=fin(anc[a]);
}
bool connect(int a,int b)
{
	return fin(a)==fin(b);
}
void build(int a)
{
	side[S[a].x].push_back(S[a].y);
	side[S[a].x].push_back(S[a].z);
	side[S[a].y].push_back(S[a].x);
	side[S[a].y].push_back(S[a].z);
	anc[fin(S[a].x)]=fin(S[a].y);
}
int countcost()
{
	int ans=0;
	for(int i=0;i<v;i++)
	{
		for(int j=1;j<side[i].size();j+=2)
		{
			ans+=side[i][j];
		}
	}
	return ans/2;
}
int largest()
{
	int ans=0;
	for(int i=0;i<onloop.size();i++)
	{
		if(onloop[i]>ans) ans=onloop[i];
	}
	return ans;
}
bool dfs(int a,int b)
{
	//printf(" %d %d\n",a,b);
	if(vis[a]) return false;
	vis[a]=true;
	if(a==b)
	{
		//printf("find\n");
		return true;
	}
	for(int i=0;i<side[a].size();i+=2)
	{
			bool j=dfs(side[a][i],b);
			if(j)
			{
				//printf("%d\n",side[a][i+1]);
				onloop.push_back(side[a][i+1]);
				return true;
			}
	}
	return false;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++)
	{
		scanf("%d%d",&v,&e);
		printf("%d %d\n",v,e);
		for(int i=0;i<v;i++)
		{
			side[i].clear();
			anc[i]=i;
			vis[i]=false;
		}
		onloop.clear();
		for(int i=0;i<e;i++)
		{
			scanf("%d%d%d",&S[i].x,&S[i].y,&S[i].z);
			S[i].x--,S[i].y--;
		}
		if(e) rangeS(0,e-1);
		int now=0,i;
		for(i=0;i<e&&now!=v-1;i++)
		{
			if(!connect(S[i].x,S[i].y))
			{
				build(i);
				now++;
			}
		}
		if(now<v-1) printf("Case #%d : No way\n",kase);
		else if(i==e) printf("Case #%d : No second way\n",kase);
		else
		{
			//printf("pass\n");
			dfs(S[i].x,S[i].y);
			printf("Case #%d : %d\n",kase,countcost()+S[i].z-largest());
		}
	}
	return 0;
}
