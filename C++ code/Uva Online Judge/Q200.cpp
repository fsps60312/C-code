#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
char TSTR[2][21];
vector<int> LINK[26];
int IN[26],USED[26];
void init()
{
	for(int i=0;i<26;i++)
	{
		LINK[i].clear();
		IN[i]=USED[i]=0;
	}
	char *x=TSTR[0],*y=TSTR[1];
	while(scanf("%s",y)==1&&y[0]!='#')
	{
		int u=0;
		while(x[u]==y[u])u++;
		if(x[u])
		{
			int a=x[u]-'A',b=y[u]-'A';
			//printf("%d %d\n",a,b);
			USED[a]=USED[b]=1;
			LINK[a].push_back(b);
			IN[b]++;
		}
		char *t=x;x=y,y=t;
	}
}
int main()
{
	while(scanf("%s",TSTR[0])==1)
	{
		init();
		//for(int i=0;i<26;i++)printf(" %c:%d",'A'+i,IN[i]);
		queue<int> q;
		for(int i=0;i<26;i++)if(!IN[i]&&USED[i])q.push(i);
		while(!q.empty())
		{
			int u=q.front();q.pop();
			printf("%c",'A'+u);
			for(int i=0;i<LINK[u].size();i++)
			{
				int j=LINK[u][i];
				IN[j]--;
				if(!IN[j])q.push(j);
			}
		}
		//for(int i=0;i<26;i++)printf(" %c:%d",'A'+i,IN[i]);
		printf("\n");
	}
	return 0;
}
