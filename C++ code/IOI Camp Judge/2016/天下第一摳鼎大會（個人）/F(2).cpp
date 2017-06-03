#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
int N,M,IN[100000];
vector<int>ET[100000];
int DJ[100000];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
bool Merge(int a,int b){if((a=Find(a))==(b=Find(b)))return false;DJ[a]=b;return true;}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)IN[i]=0,ET[i].clear(),DJ[i]=i;
		for(int a,b,i=0;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			ET[a].push_back(b);
			IN[b]++;
		}
		for(int i=0;i<N;i++)if(IN[i]==0)q.push(i),ans++;
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			for(const int nxt:ET[u])
			{
				if(!--IN[nxt])q.push(nxt);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
