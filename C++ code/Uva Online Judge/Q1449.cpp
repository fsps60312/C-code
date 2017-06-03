#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
int n;
char S[1000001];
struct anstype
{
	int x,y;
};
anstype newans(int a,int b){anstype z;z.x=a,z.y=b;return z;}
vector<anstype> ans;
anstype tmp[150];
struct trietype
{
	/*struct nodetype
	{
		int v;
	};*/
	struct vtype
	{
		int f,mom,sum,ans;
		char c;
	};
	//nodetype newnode(int a){nodetype z;z.v=a;return z;}
	vtype newv(int a){vtype z;z.sum=a,z.ans=0;return z;}
	//vector<nodetype> s[26];
	vector<int> s[26];
	vector<vtype> v;
	int size;
	void push()
	{
		for(int i=0;i<26;i++)s[i].push_back(0);
		v.push_back(newv(0));
		size++;
	}
	void clear()
	{
		for(int i=0;i<26;i++)s[i].clear();
		v.clear();
		size=0;
		push();
	}
	int insert(char *a)
	{
		int u=0;
		for(int i=0;a[i];i++)
		{
			int j=s[a[i]-'a'][u];
			if(!j)
			{
				j=s[a[i]-'a'][u]=size;
				push();
				v[size-1].c=a[i];
				v[size-1].mom=u;
			}
			u=j;
		}
		v[u].sum++;
		if(v[u].sum>1)return -1;
		return u;
	}
	void getfail()
	{
		queue<int> q;
		q.push(0);
		v[0].f=0;
		//v[0].c='a';
		vector<int> o;
		//int u=0;
		while(!q.empty())
		{
			int a=q.front();q.pop();
			//printf("%d\n",a);
			//o.push_back(a);
			for(int i=0;i<26;i++)
			{
				if(s[i][a])
				{
					int now=s[i][a];
					q.push(now);
					if(v[now].mom==0)v[now].f=0;
					else
					{
						int u=v[a].f;//if(now failed) turn to v[a].f
						while(u&&!s[v[now].c-'a'][u])u=v[u].f;
						v[now].f=s[v[now].c-'a'][u];//>0?s[v[now].c-'a'][u]:0;
					}
					//printf("%d:%d\n",now,v[now].f);
				}
			}
		}
		//for(int i=0;i<v.size();i++)printf("%d:%d\n",i,v[i].f);
	}
	void record(int a)
	{
		//printf("ans:%d %c\n",a,v[a].c);
		v[a].ans++;
		int u=v[a].f;
		while(u)
		{
			if(v[u].sum)
			{
				record(u);
				break;
			}
			u=v[u].f;
		}
	}
	void fin()
	{
		int u=0;
		for(int i=0;S[i];i++)
		{
			while(u&&!s[S[i]-'a'][u])u=v[u].f;
			if(s[S[i]-'a'][u])u=s[S[i]-'a'][u];
			//else u=s[S[i]-'a'][u].v;
			if(v[u].sum)
			{
				record(u);
				//if(!S[i+1]) break;
				//while(u&&!s[S[i+1]-'a'][u].v)u=v[u].f;
			}
		}
	}
	void print(int a)
	{
		vector<int> out;
		while(a)
		{
			out.push_back(a);
			a=v[a].mom;
		}
		if(out.size())
		for(int i=out.size()-1;i>=0;i--)
			printf("%c",v[out[i]].c); 
	}
};
trietype trie;
bool cmpans(anstype a,anstype b)
{
	if(trie.v[a.y].ans!=trie.v[b.y].ans)return trie.v[a.y].ans>trie.v[b.y].ans;
	return a.x<b.x;
}
void rangeans(int a,int b)
{
	if(a==b) return;
	int mid=(a+b)/2;
	rangeans(a,mid);rangeans(mid+1,b);
	int c=a,d=mid+1;
	for(int i=a;i<=b;i++)
	{
		if(d>b||(c<=mid&&cmpans(ans[c],ans[d])))tmp[i]=ans[c++];
		else tmp[i]=ans[d++];
	}
	for(int i=a;i<=b;i++)ans[i]=tmp[i];
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	while(scanf("%d",&n)==1&&n)
	{
		trie.clear();
		ans.clear();
		for(int i=0;i<n;i++)
		{
			scanf("%s",S);
			int j=trie.insert(S);
			if(j!=-1)ans.push_back(newans(i,j));
		}
		trie.getfail();
		scanf("%s",S);
		trie.fin();
		rangeans(0,ans.size()-1);
		int n1=trie.v[ans[0].y].ans;
		printf("%d\n",n1);
		for(int i=0;i<ans.size()&&trie.v[ans[i].y].ans==n1;i++)
		{
			trie.print(ans[i].y);
			printf("\n");
		}
		int j=0;
		for(int i=0;S[i];i++)if(S[i]=='h')j++;
		printf("h are %d\n",j);
	}
	return 0;
}
