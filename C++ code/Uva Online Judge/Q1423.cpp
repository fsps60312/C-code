#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
int T,N,H[11],VAL[11];
int findset(int a)
{
	if(H[a]==a)return a;
	return H[a]=findset(H[a]);
}
struct Vertex
{
	int from,to;
	void maintain()
	{
		from=findset(from);
		to=findset(to);
	}
};
vector<Vertex> V;
vector<int> TO[11];
int FROMN[11];
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		V.clear();
		for(int i=0;i<=N;i++)
		{
			H[i]=i;
			TO[i].clear();
			FROMN[i]=0;
		}
		for(int i=0;i<N;i++)
		{
			for(int j=i+1;j<=N;j++)
			{
				char c;
				do
				{
					scanf("%c",&c);
				}
				while(c!='0'&&c!='+'&&c!='-');
				int ti=findset(i),tj=findset(j);
				switch(c)
				{
					case'0':
					{
						H[ti]=tj;
					}break;
					case'+':
					{
						V.push_back((Vertex){ti,tj});
					}break;
					case'-':
					{
						V.push_back((Vertex){tj,ti});
					}break;
				}
				//printf("%c",c);
			}
			//printf("\n");
		}
		for(int i=0;i<V.size();i++)
		{
			V[i].maintain();
			int from=V[i].from,to=V[i].to;
			TO[from].push_back(i);
			FROMN[to]++;
		}
		/*for(int i=0;i<=N;i++)
		{
			for(int j=0;j<TO[i].size();i++)
			{
				printf("%d to %d\n",i,V[TO[i][j]].to);
			}
		}*/
		queue<int> q;
		for(int i=0;i<=N;i++)
		{
			if(FROMN[i]==0)
			{
				VAL[i]=0;
				q.push(i);
			}
		}
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=0;i<TO[u].size();i++)
			{
				int j=V[TO[u][i]].to;
				FROMN[j]--;
				if(!FROMN[j])
				{
					VAL[j]=VAL[u]+1;
					q.push(j);
				}
			}
		}
		printf("%d",VAL[findset(1)]-VAL[findset(0)]);
		for(int i=2;i<=N;i++)printf(" %d",VAL[findset(i)]-VAL[findset(i-1)]);printf("\n");
	}
	return 0;
}
