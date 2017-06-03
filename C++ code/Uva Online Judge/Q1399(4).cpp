#include<cstdio>
#include<vector>
#include<queue>
//#define debug(x,...) {}//printf(x,##__VA_ARGS__)
#define termin(x,...) {printf(x,##__VA_ARGS__);while(1);}
using namespace std;
bool getmax(int &a,int b){if(b>a){a=b;return true;}return false;}
int T,N,S;
char LINE[51];
struct Ac
{
	struct Bse
	{
		int *bse,f,v,vis,ans,to,c;
		int &operator[](int i){return bse[i];}
		Bse():f(0),v(-1),vis(0),ans(-1),to(-1),c(-1){bse=new int[N];for(int i=0;i<N;i++)bse[i]=0;}
	};
	vector<Bse> bse;
	int sz;
	void clear(){sz=1;bse.clear();bse.push_back(Bse());}
	int newnode(int c){Bse tmp=Bse();tmp.c=c;bse.push_back(tmp);return sz++;}
	int getnxt(int u,int c)
	{
		if(bse[u][c])return bse[u][c];
		int ans=newnode(c);
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
				q.push(u);
				if(bse[f].v!=-1)bse[u].v=-2;
			}
		}
	}
	int findloop(int u)
	{
		int &vis=bse[u].vis,&ans=bse[u].ans;
		if(bse[u].v!=-1)
		{
			return ans=0;
		}
		if(vis&1)return -1;//find loop
		else if(vis&2)return ans;//checked
		vis|=1;
		for(int c=N-1,tmp;c>=0;c--)
		{
			int &v=bse[u][c];
			if(v)
			{
				if((tmp=findloop(v))==-1)return -1;
				else if(getmax(ans,tmp+1))bse[u].to=v;
			}
			else
			{
				int f=bse[u].f;
				while(f&&!bse[f][c])f=bse[f].f;
				if(bse[f][c])f=bse[f][c];
				if((tmp=findloop(f))==-1)return -1;
				else if(getmax(ans,tmp+1))bse[u].to=f;
			}
		}
		vis&=~1;
		vis|=2;
		return ans;
	}
	void dfsprint()
	{
		for(int i=1,u=0,&ans=bse[0].ans;i<ans;i++)
		{
			u=bse[u].to;
			printf("%c",'A'+bse[u].c);
		}
		puts("");
	}
}AC;
int main()
{
//	freopen("in.txt","r",stdin);
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
		AC.buildfail();
		int ans=AC.findloop(0);
		if(ans==-1)printf("No\n");
		else
		{
//			printf("%d\n",ans);
			AC.dfsprint();
		}
	}
	return 0;
}
