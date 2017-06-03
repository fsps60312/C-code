#include<cstdio>
#include<vector>
#include<queue>
#define debug(x,...) {}//printf(x,##__VA_ARGS__)
using namespace std;
int T,N,S;
char LINE[51];
struct Ac
{
	struct Bse
	{
		int *bse,f,v,vis,to;
		int &operator[](int i){return bse[i];}
		Bse():f(0),v(-1),vis(0){bse=new int[N];for(int i=0;i<N;i++)bse[i]=0;}
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
				q.push(u);
			}
		}
	}
	bool hasloop(int u,vector<char>&now,vector<char>&ans)
	{
		debug("u=%d,%s\n",u,now.begin());
		if(bse[u].v!=-1)
		{
			if(now.size()>ans.size())ans=now;
			return false;
		}
		int &vis=bse[u].vis;
		if(vis&1)
		{
			debug("{%d",u);
			for(int i=bse[u][bse[u].to];i!=u;i=bse[i][bse[i].to])debug(",%d",i);
			debug("}:%s\n",now.begin());
			return true;//find loop
		}
//		else if(vis&2)return false;//checked
		vis|=1;
		for(int &c=bse[u].to=N-1;c>=0;c--)
		{
			now.push_back('A'+c);
			int &v=bse[u][c];
			if(v)
			{
				if(hasloop(v,now,ans))return true;
			}
			else
			{
				int f=bse[u].f;
				while(f&&!bse[f][c])f=bse[f].f;
				if(bse[f][c])f=bse[f][c];
				if(hasloop(f,now,ans))return true;
			}
			now.pop_back();
		}
		vis&=~1;
		vis|=2;
		return false;
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
		debug("sz=%d\n",AC.sz);
		AC.buildfail();
		for(int i=0;i<AC.sz;i++)debug("f[%d]:%d\n",i,AC.bse[i].f);
		vector<char>now,ans;
		if(AC.hasloop(0,now,ans))printf("No\n");
		else
		{
			ans[ans.size()-1]=0;
			printf("%s\n",ans.begin());
		}
	}
	return 0;
}
