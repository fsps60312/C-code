#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
struct Stype
{
	int x,y,z;
	bool vis;
	bool used;
};
struct sidetype
{
	int x,y;
	//x go to where
	//index in S
};
Stype S[200],tmp[200];
int T,v,e;
vector<sidetype> side[100];
int anc[100];
vector<int> loop;
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
int countcost()
{
	int ans=0;
	for(int i=0;i<v;i++)
	{
		for(int j=0;j<side[i].size();j++)
		{
			ans+=S[side[i][j].y].z;
		}
	}
	return ans/2;
}
bool dfs(int a,int b,int c)
{
	if(a==b) return true;
	if(S[c].vis) return false;
	S[c].vis=true;
	for(int i=0;i<side[a].size();i++)
	{
		bool j=dfs(side[a][i].x,b,side[a][i].y);
		if(j)
		{
			loop.push_back(S[side[a][i].y].z);
			return true;
		}
	}
	return false;
}
int largest()
{
	int ans=0;
	for(int i=0;i<loop.size();i++)
	{
		if(loop[i]>ans) ans=loop[i];
	}
	return ans;
}
int fin(int a)
{
	if(anc[a]==a) return a;
	return anc[a]=fin(anc[a]);
}
void build(int a)
{
	sidetype b,c;
	b.x=S[a].y,b.y=a;
	side[S[a].x].push_back(b);
	c.x=S[a].x,c.y=a;
	side[S[a].y].push_back(c);
	anc[fin(S[a].x)]=fin(S[a].y);
	S[a].used=true;
}
bool connect(int a,int b)
{
	return fin(a)==fin(b);
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++)
	{
		scanf("%d%d",&v,&e);
		//printf("%d %d\n",v,e);
		for(int i=0;i<v;i++)
		{
			side[i].clear();
			anc[i]=i;
		}
		//loop.clear();
		for(int i=0;i<e;i++)
		{
			scanf("%d%d%d",&S[i].x,&S[i].y,&S[i].z);
			S[i].x--,S[i].y--;
			S[i].used=false;
		}
		if(e) rangeS(0,e-1);
		int i,now=0;
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
			int ans=2147483647,j;
			for(i=0;i<e;i++)
			{
				if(!S[i].used)
				{
					for(int k=0;k<e;k++) S[k].vis=false;
					loop.clear();
					dfs(S[i].x,S[i].y,i);
					j=countcost()+S[i].z-largest();
					if(j<ans) ans=j;
					i++;
				}
			}
			printf("Case #%d : %d\n",kase,ans);
		}
	}
}
