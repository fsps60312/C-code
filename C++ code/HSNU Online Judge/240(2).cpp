#include<cstdio>
#include<vector>
using namespace std;
int T,N;
vector<int>VOCA[9];
bool WIN[9];
void Dfs(const int dep,const int cnt,const int s)
{
	if(cnt==9)return;
	bool &win=WIN[cnt];
	bool pre=win;
	if(win)
	{
		win=false;
		for(int i=0;i<VOCA[cnt].size();i++)
		{
			const int v=VOCA[cnt][i];
			if((v&s)!=v){win=true;break;}
		}
	}
//	if(s==3)printf("cnt=%d,win=%d\n",cnt,win);
	if(pre!=win)//{for(int i=s,j=0;j<26;j++,i>>=1)printf("%d",i&1);printf(": %d\n",win);}
	{
		printf("lose %d\n",cnt);
	}
	if(dep==26)return;
	Dfs(dep+1,cnt,s);
	Dfs(dep+1,cnt+1,s|(1<<dep));
}
int main()
{
	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=2;i<=8;i++)VOCA[i].clear(),WIN[i]=true;
		for(int i=0;i<N;i++)
		{
			static char tmp[8];
			scanf("%s",tmp);
			int len=-1;while(tmp[++len]);
			int s=0;
			for(int i=0;i<len;i++)s|=1<<(tmp[i]-'A');
			VOCA[len+1].push_back(s);
		}
		for(int len=1;len<=8;len++)
		{
			printf("len %d: ",len);
			for(int i=0;i<VOCA[len].size();i++)
			{
				int s=VOCA[len][i];
				printf(" ");
				for(int j=0;j<26;j++,s>>=1)printf("%d",s&1);
			}
			puts("");
		}
		Dfs(0,0,0);
		bool result=false;
		for(int i=2;i<=8;i++)result|=WIN[i];
		puts(result?"Yes":"No");
	}
	return 0;
}
