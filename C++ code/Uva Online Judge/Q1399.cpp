#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
int T,N,S;
char LINE[51];
struct Ac
{
	struct Bse
	{
		int *bse,f,v;
		int &operator[](int i){return bse[i];}
		Bse():f(0),v(-1){bse=new int[N];for(int i=0;i<N;i++)bse[i]=0;}
	};
	vector<Bse> bse;
	int sz;
	void clear(){sz=1;bse.clear();bse.push_back(Bse());}
	int newnode(){bse.push_back(Bse());return sz++;}
	int getnxt(int u,int c)
	{
		if(bse[u][c])return bse[u][c];
		int ans=newnode();
		return bse[u][c]=ans;
	}
	void insert(char *s,int v){int u=0;for(int i=0;s[i];i++)u=getnxt(u,s[i]-'A');bse[u].v=v;}
	void buildfail()
	{
		queue<int>q;
		for(int i=0;i<N;i++)
		{
			int &u=bse[0][i];
			if(!u)continue;
			q.push(u);
		}
		while(!q.empty())
		{
			int fa=q.front();q.pop();
			for(int c=0;c<N;c++)
			{
				int &u=bse[fa][c];
				if(!u)continue;
				int &f=bse[u].f=bse[fa].f;
				while(f&&!bse[f][c])f=bse[f].f;
				if(bse[f][c])f=bse[f][c];
				printf("%d:%d\n",u,bse[u].f);
				q.push(u);
			}
		}
	}
	int search(char *s)
	{
		int u=0;
		for(int i=0;s[i];i++)
		{
			while(u&&!bse[u][s[i]-'A'])u=bse[u].f;
			if(bse[u][s[i]-'A'])u=bse[u][s[i]-'A'];
//			printf(" u=%d\n",u);
			if(bse[u].v!=-1)return bse[u].v;
		}
		return -1;
	}
}AC;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&S);
		AC.clear();
		for(int i=0;i<S;i++)
		{
			scanf("%s",LINE);
			AC.insert(LINE,i);
		}
		printf("sz=%d\n",AC.sz);
		AC.buildfail();
		for(int i=0;i<AC.sz;i++)printf("f[%d]:%d\n",i,AC.bse[i].f);
		while(scanf("%s",LINE)==1)
		{
			bool valid=true;
			for(int i=0;LINE[i];i++)if(LINE[i]<'A'||LINE[i]>='A'+N){valid=false;break;}
			if(!valid)break;
			printf("find:%d\n",AC.search(LINE));
		}
	}
	return 0;
}
