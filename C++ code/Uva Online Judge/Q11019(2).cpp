#include<cstdio>
#include<cstdlib>
#include<queue>
using namespace std;
char S[1000][1001];
int T,n,m,x,y,ridx[100],fail[101];
struct pairtype
{
	int a,b,v;
	bool operator<(pairtype z)
	{
		if(a!=z.a)return a<z.a;
		if(b!=z.b)return b<z.b;
		return v<z.v;
	}
	bool operator==(pairtype z){return a==z.a&&b==z.b&&v==z.v;}
};
pairtype newpair(int a,int b,int v){pairtype z;z.a=a,z.b=b,z.v=v;return z;}
int Ans[1000][1000];
struct trietype
{
	struct nodetype
	{
		char c;
		int next;
		int ch;
		int v;
		int f;
	};
	nodetype s[10001];
	int sz;
	int vsz;
	void clear()
	{
		sz=1;
		vsz=1;
		s[0].next=-1;
		s[0].ch=-1;
		s[0].v=0;
	}
	int fincreate(int u,char a)
	{
		if(s[u].ch==-1)
		{
			s[u].ch=sz;
		}
		else
		{
			u=s[u].ch;
			if(s[u].c==a)return u;
			while(s[u].next!=-1)
			{
				u=s[u].next;
				if(s[u].c==a)return u;
			}
			s[u].next=sz;
		}
		s[sz].c=a;
		s[sz].next=-1;
		s[sz].ch=-1;
		s[sz].v=0;
		return sz++;
	}
	int fin(int u,char a)
	{
		if(s[u].ch==-1)return -1;
		u=s[u].ch;
		if(s[u].c==a)return u;
		while(s[u].next!=-1)
		{
			u=s[u].next;
			if(s[u].c==a)return u;
		}
		return -1;
	}
	int insert(char *a)
	{
		int u=0;
		for(int i=0;a[i];i++)
		{
			//printf("1a\n");
			u=fincreate(u,a[i]);
			//printf("2a\n");
		}
		if(s[u].v)return s[u].v;
		return s[u].v=vsz++;
	}
	void getfail()
	{
		queue<int> q;
		s[0].f=0;
		for(int i=s[0].ch;i!=-1;i=s[i].next)
		{
			s[i].f=0;
			q.push(i);
		}
		while(!q.empty())
		{
			int u=q.front();q.pop();
			int i=s[u].ch;
			while(i!=-1)
			{
				int f=u;
				int ok;
				do
				{
					f=s[f].f;
					ok=fin(f,s[i].c);
				}while(f&&ok==-1);
				if(ok!=-1)s[i].f=ok;
				else s[i].f=0;
				q.push(i);
				i=s[i].next;
			}
		}
	}
	bool findstr(char *a,int r)
	{
		int u=0;
		for(int i=0;a[i];i++)
		{
			while(u&&fin(u,a[i])==-1)u=s[u].f;
			int j=fin(u,a[i]);
			if(j!=-1)u=j;
			if(s[u].v)
			{
				Ans[r][i-y+1]=s[u].v;
			}
		}
		return false;
	}
};
trietype trie;
int findans(int idx)
{
	int ans=0;
	int u=0;
	for(int i=0;i<n;i++)
	{
		//printf("i==%d,ans=%d\n",i,ans);
		while(u&&Ans[i][idx]!=ridx[u])u=fail[u];
		if(Ans[i][idx]==ridx[u])u++;
		if(u==x)
		{
			ans++;
			//u=fail[x-1];
		}
	}
	//printf("ans=%d\n",ans);
	return ans;
}
void getKMP()
{
	fail[0]=0;
	for(int i=1;i<x;i++)
	{
		int u=fail[i];
		while(u&&ridx[u]!=ridx[i])u=fail[u];
		fail[i+1]=ridx[i]==ridx[u]?u+1:0;
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	char tmp[100][101];
	while(T--)
	{
		trie.clear();
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)Ans[i][j]=0;
			scanf("%s",S[i]);
		}
		scanf("%d%d",&x,&y);
		for(int i=0;i<x;i++)
		{
			scanf("%s",tmp[i]);
			ridx[i]=trie.insert(tmp[i]);
			//printf("ridx:%d\n",ridx[i]);
		}
		//printf("a\n");
		trie.getfail();
		//printf("b\n");
		for(int i=0;i<n;i++)
		{
			trie.findstr(S[i],i);
		}
		getKMP();
		int ans=0;
		/*for(int i=0;i<x;i++)printf("KMP:%d\n",fail[i]);
		//for(int i=0;i<n;i++){for(int j=0;j<m;j++)printf(" %d",Ans[i][j]);printf("\n");}
		//for(int i=0;i<Ans.size();i++)printf("(%d,%d,%d)\n",Ans[i].a,Ans[i].b,Ans[i].v);*/
		for(int i=0;i<m;i++)
		{
			//printf("i==%d\n",i);
			int j=findans(i);
			ans+=j;
		}
		printf("%d\n",ans);
	}
	return 0;
}
