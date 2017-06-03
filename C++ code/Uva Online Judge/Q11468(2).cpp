#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
int T,K;
int idx(char a)
{
	if(a>='a')return a-'a';
	if(a>='A')return a-'A'+26;
	return a-'0'+52;
}
struct ltype
{
	int i;
	double p;
};
vector<ltype> inl;
struct trietype
{
	struct vtype
	{
		int f;
		int v;
		double p,tmpp;
	};
	vtype newv(){vtype ans;ans.v=0;return ans;}
	vector<int> s[62];
	vector<vtype> v;
	int sz;
	void push()
	{
		for(int i=0;i<62;i++)s[i].push_back(0);
		v.push_back(newv());
		sz++;
	}
	void clear()
	{
		for(int i=0;i<62;i++)s[i].clear();
		v.clear();
		sz=0;
		push();
	}
	int fin(int u,int i)
	{
		if(s[i][u])return s[i][u];
		s[i][u]=sz;
		push();
		return sz-1;
	}
	void insert(char *str)
	{
		int u=0;
		for(int i=0;str[i];i++)
		{
			u=fin(u,idx(str[i]));
		}
		v[u].v++;
	}
	void getf()
	{
		v[0].f=0;
		queue<int> q;
		for(int i=0;i<62;i++)
		{
			int j=s[i][0];
			if(j)
			{
				v[j].f=0;
				q.push(j);
			}
		}
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=0;i<62;i++)
			{
				int j=s[i][u];
				if(j)
				{
					q.push(j);
					int k=v[u].f;
					while(k&&!s[i][k])k=v[k].f;
					v[j].f=s[i][k];
					v[j].v|=v[v[j].f].v;
				}
			}
		}
	}
	double simulate(int t)
	{
		for(int i=0;i<sz;i++)v[i].p=v[i].tmpp=0;
		v[0].p=1;
		while(t--)
		{
			for(int i=0;i<sz;i++)
			{
				for(int o=0;o<inl.size();o++)
				{
					int j=inl[o].i;
					if(s[j][i])
					{
						v[s[j][i]].tmpp+=v[i].p*inl[o].p;
					}
					else
					{
						int u=v[i].f;
						while(u&&!s[j][u])u=v[u].f;
						if(s[j][u])u=s[j][u];
						v[u].tmpp+=v[i].p*inl[o].p;
					}
				}
			}
			for(int i=0;i<sz;i++)
			{
				v[i].p=v[i].v>0?0:v[i].tmpp;
				v[i].tmpp=0;
			}
		}
		double ans=0;
		for(int i=0;i<sz;i++)ans+=v[i].p;
		return ans;
	}
};
void check(char *a)
{
	for(int i=0;a[i];i++)
	{
		if((a[i]>='a'&&a[i]<='z')||(a[i]>='A'&&a[i]<='Z')||(a[i]>='0'&&a[i]<='9'))continue;
		while(1)printf("wrong!");
	}
}
trietype trie;
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		scanf("%d",&K);
		trie.clear();
		char tmp[51];
		while(K--)
		{
			scanf("%s",tmp);
			trie.insert(tmp);
			//check(tmp);
		}
		trie.getf();
		scanf("%d",&K);
		inl.clear();
		//bool vis[62];for(int i=0;i<62;i++)vis[i]=false;
		//double psum=0;
		while(K--)
		{
			ltype l;
			scanf("%s %lf",tmp,&l.p);
			//psum+=l.p;
			l.i=idx(tmp[0]);
			/*if(vis[l.i])
			{
				continue;
				printf("error!\n");
			}
			vis[l.i]=true;
			check(tmp);*/
			inl.push_back(l);
		}
		//psum-=1;
		//if(psum>1e-8||psum<-1e-8)printf("psum=%lf\n",psum);
		scanf("%d",&K);
		printf("Case #%d: %.6lf\n",kase++,trie.simulate(K));
	}
	return 0;
}
