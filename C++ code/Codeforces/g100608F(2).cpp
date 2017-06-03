#include<cstdio>
//#include<cassert>
#include<vector>
#include<queue>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
//void bssert(bool valid){if(valid)return;}
int N,PARENT[1000],DEGREE[1000];
vector<int>ET[1000];
void Dfs(const int u,const int parent)
{
	PARENT[u]=parent;
	for(const int nxt:ET[u])if(nxt!=parent)Dfs(nxt,u);
}
int COLOR[1000];
void ColorNode(const int u)
{
	assert(!COLOR[u]);
	static bool used_color[5];
	for(int i=0;i<5;i++)used_color[i]=false;
	for(const int nxt:ET[u])
	{
		const int c=COLOR[nxt];
		used_color[c]=true;
		if(nxt!=PARENT[u])assert(c==0||c==1||c==2);
	}
	for(int i=1;;i++)
	{
		assert(i<5);
		if(!used_color[i])
		{
			COLOR[u]=i;
			printf("%d %d\n",u+1,COLOR[u]);
			fflush(stdout);
			break;
		}
	}
}
queue<int>LEAFS;
void ColorOneLeaf()
{
	bool colored=false;
	while(!colored)
	{
		assert(!LEAFS.empty());
		const int u=LEAFS.front();LEAFS.pop();
		if(!COLOR[u])ColorNode(u),colored=true;
		if(PARENT[u]!=-1&&!--DEGREE[PARENT[u]])LEAFS.push(PARENT[u]);
	}
}
int main()
{
	assert(scanf("%d",&N)==1);
	assert(N>=2);
	for(int i=0,a,b;i<N-1;i++)
	{
		assert(scanf("%d%d",&a,&b)==2),a--,b--;
		ET[a].push_back(b),ET[b].push_back(a); 
	}
	Dfs(0,-1);
	for(int i=0;i<N;i++)DEGREE[i]=0;
	for(int i=1;i<N;i++)DEGREE[PARENT[i]]++;
	while(!LEAFS.empty())LEAFS.pop();
	for(int i=0;i<N;i++)if(!DEGREE[i])LEAFS.push(i);
	for(int i=0;i<N;i++)COLOR[i]=0;
	int cnt=N;
	ColorOneLeaf(),cnt--;
	for(int u,c;;)
	{
		assert(scanf("%d%d",&u,&c)==2),u--;
//		assert(c!=-1);
		if(c==-1)break;
		assert(!COLOR[u]),COLOR[u]=c,cnt--;
		if(cnt==0)
		{
			continue;
			assert(scanf("%d%d",&u,&c)==2);
			assert(u==-1&&c==-1);break;
		}
		else
		{
			if(PARENT[u]!=-1&&!COLOR[PARENT[u]])ColorNode(PARENT[u]),cnt--;
			else ColorOneLeaf(),cnt--;
			if(cnt==0)
			{
				continue;
				assert(scanf("%d%d",&u,&c)==2);
				assert(u==-1&&c==-1);break;
			}
		}
	}
	return 0;
}
