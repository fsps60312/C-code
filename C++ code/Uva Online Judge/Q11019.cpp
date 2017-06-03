#include<cstdio>
#include<cstdlib>
#include<queue>
using namespace std;
char S[1000][1001];
int T,n,m,x,y,ridx[100];
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
vector<pairtype> Ans;
pairtype tmpAns[1000000];
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
				Ans.push_back(newpair(r,i,s[u].v));
			}
		}
		return false;
	}
};
trietype trie;
void rangeAns(int a,int b)
{
	if(a==b)return;
	int mid=(a+b)/2;
	rangeAns(a,mid);
	rangeAns(mid+1,b);
	int c=a,d=mid+1;
	for(int i=a;i<=b;i++)
	{
		if(d>b||(c<=mid&&Ans[c]<Ans[d]))tmpAns[i]=Ans[c++];
		else tmpAns[i]=Ans[d++];
	}
	for(int i=a;i<=b;i++)Ans[i]=tmpAns[i];
}
bool findans(int a,int b,int c)
{
	int Min=0,Max=Ans.size()-1,mid;
	pairtype cmp=newpair(a,b,c);
	while(Min<Max)
	{
		mid=(Min+Max)/2;
		if(Ans[mid]<cmp)Min=mid+1;
		else Max=mid;
	}
	return Ans[Max]==cmp;
}
int findans(int idx)
{
	int a=Ans[idx].a,b=Ans[idx].b;
	for(int i=1;i<x;i++)
	{
		if(!findans(a+i,b,ridx[i]))return 0;
	}
	return 1;
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
		Ans.clear();
		for(int i=0;i<n;i++)
		{
			trie.findstr(S[i],i);
		}
		int ans=0;
		//for(int i=0;i<Ans.size();i++)printf("(%d,%d,%d)\n",Ans[i].a,Ans[i].b,Ans[i].v);
		if(Ans.size())
		{
			rangeAns(0,Ans.size()-1);
			for(int i=0;i<Ans.size();i++)
			{
				if(Ans[i].v==ridx[0])
				{
					//printf("i==%d,size=%d\n",i,Ans.size());
					int j=findans(i);
					//printf("i=%d S[i]=(%d,%d,%d) findans()=%d\n",i,Ans[i].a,Ans[i].b,Ans[i].v,j);
					ans+=j;
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
