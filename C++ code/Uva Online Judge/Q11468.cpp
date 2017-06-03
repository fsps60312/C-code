#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
int T,K;
struct pairtype
{
	int i;
	double p;
};
vector<pairtype> odd;
int trans(char a)
{
	if(a>='a')return a-'a';
	if(a>='A')return a-'A'+26;
	return a-'0'+52;
}
struct trietype
{
	vector<int> s[62];
	struct vtype
	{
		int v;
		int f;
		char c;
		double p,tmpp;
	};
	vtype newv(){vtype a;a.v=0;return a;}
	vector<vtype> v;
	int size;
	void push()
	{
		printf("push1\n");system("pause");
		for(int i=0;i<62;i++)s[i].push_back(0);
		printf("push2\n");system("pause");
		v.push_back(newv());
		printf("push3\n");system("pause");
		size++;
	}
	void clear()
	{
		for(int i=0;i<62;i++)s[i].clear();
		v.clear();
		size=0;
		push();
	}
	void insert(char *a)
	{
		int u=0;
		for(int i=0;a[i];i++)
		{
			int j=s[trans(a[i])][u];
			if(!j)
			{
				//printf("a now at %c\n",a[i]);system("pause");
				j=s[trans(a[i])][u]=size;
				v[j].c=a[i];
				//printf("b now at %c\n",a[i]);system("pause");
				push();
				//printf("c now at %c\n",a[i]);system("pause");
			}
			u=j;
		}
		v[u].v++;
	}
	void getfail()
	{
		queue<int> q;
		v[0].f=0;
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
					//calculate v[j].f
					int k=v[u].f;
					while(k&&!s[i][k])k=v[k].f;
					v[j].f=s[i][k];
				}
			}
		}
	}
	double simulate(int t)
	{
		for(int i=0;i<size;i++)v[i].p=v[i].tmpp=0;
		v[0].p=1;
		while(t--)
		{
			for(int i=0;i<size;i++)
			{
				if(!v[i].v)
				{
					for(int o=0;o<odd.size();o++)
					{
						int j=s[odd[o].i][i];
						if(j)
						{
							v[j].tmpp+=v[i].p*odd[o].p;
						}
						else
						{
							int u=v[i].f;
							while(u&&!v[u].f&&!s[odd[o].i][u])u=v[u].f;
							//if(v[u].f)continue;
							if(s[odd[o].i][u])u=s[odd[o].i][u];
							//if(v[u].f)continue;
							v[u].tmpp+=v[i].p*odd[o].p;
						}
					}
				}
			}
			for(int i=0;i<size;i++)
			{
				if(!v[i].v)
				{
					v[i].p=v[i].tmpp;
					v[i].tmpp=0;
				}
			}
		}
		double ans=0;
		for(int i=0;i<size;i++)
		{
			if(!v[i].v)
			{
				ans+=v[i].p;
			}
		}
		return ans;
	}
};
trietype trie;
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		scanf("%d",&K);
		//printf("K=%d\n",K);
		trie.clear();
		for(int i=0;i<K;i++)
		{
			char tmp[100];
			scanf("%s",tmp);
	//printf("a%d %d %d\n",'a','A','0');
			//printf("insert:%s\n",tmp);system("pause");
			trie.insert(tmp);
	//printf("b%d %d %d\n",'a','A','0');
		}
	//printf("%d %d %d\n",'a','A','0');
		trie.getfail();
		//for(int i=0;i<trie.size;i++)printf(" %d",trie.v[i].f);
	//printf("%d %d %d\n",'a','A','0');
		scanf("%d",&K);
		//printf("K=%d\n",K);
		odd.clear();
		bool vis[62];for(int i=0;i<62;i++)vis[i]=false;
		for(int i=0;i<K;i++)
		{
			char tmp[100];
			pairtype j;
			scanf("%s",tmp);
			scanf("%lf",&j.p);
			//printf("letter:%s %lf\n",tmp,j.p);
			int k=trans(tmp[0]);
			if(k>=62)printf("error\n");
			if(vis[k])continue;
			j.i=k;
			vis[k]=true;
			odd.push_back(j);
		}
		scanf("%d",&K);
		//printf("K=%d\n",K);
		printf("Case #%d: %.6lf\n",kase++,trie.simulate(K));
	}
	return 0;
}
