#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
int N,M,K,X,Y;
vector<int>ET[10000],EF[10000];
bool HOLD[10000][26];
bool IS_AG_HOLD[10000],VIS[10000];
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("kripke.in","r",stdin);
	freopen("kripke.out","w",stdout);
	while(scanf("%d%d%d",&N,&M,&K)==3)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,c;i<N;i++)
		{
			scanf("%d",&c);
			for(int j=0;j<26;j++)HOLD[i][j]=false;
			for(char s[2];c--;)
			{
				scanf("%s",s);
				HOLD[i][s[0]-'a']=true;
			}
		}
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b);
			EF[b].push_back(a);
		}
		{
			static char s[100];scanf("%s",s);
			X=s[2]-'a',Y=s[7]-'a';
			assert(0<=X&&X<K&&0<=Y&&Y<K);
		}
		{
			for(int i=0;i<N;i++)IS_AG_HOLD[i]=true;
			queue<int>q;
			for(int i=0;i<N;i++)if(!HOLD[i][Y])IS_AG_HOLD[i]=false,q.push(i);
			while(!q.empty())
			{
				const int u=q.front();q.pop();
				for(const int nxt:EF[u])
				{
					if(IS_AG_HOLD[nxt])IS_AG_HOLD[nxt]=false,q.push(nxt);
				}
			}
		}
		vector<int>ans;
		{
			for(int i=0;i<N;i++)VIS[i]=false;
			queue<int>q;
			for(int i=0;i<N;i++)if(IS_AG_HOLD[i])VIS[i]=true,q.push(i);
			while(!q.empty())
			{
				const int u=q.front();q.pop();
				ans.push_back(u);
				for(const int nxt:EF[u])
				{
					if(HOLD[nxt][X]&&!VIS[nxt])VIS[nxt]=true,q.push(nxt);
				}
			}
		}
		sort(ans.begin(),ans.end());
		printf("%d\n",(int)ans.size());
		for(const int v:ans)printf("%d\n",v+1);
	}
	return 0;
}
