#include<cstdio>
#include<cstdlib>
#include<vector>
#define LL long long
using namespace std;
char tmp[1001];
LL n;
LL Ans;
LL trans(char a)
{
	if(a>='a')return a-'a'+36;
	if(a>='A')return a-'A'+10;
	return a-'0';
}
struct trietype
{
	struct nodetype
	{
		vector<int> ch;
		char c;
		LL v;
	};
	vector<nodetype> node;
	LL size;
	void clear()
	{
		node.clear();
		size=0;
		push();
	}
	void push()
	{
		nodetype a;
		a.v=0;
		a.ch.clear();
		node.push_back(a);
		size++;
	}
	LL fin(LL u,char a)
	{
		for(LL i=0;i<node[u].ch.size();i++)
		{
			LL j=node[u].ch[i];
			if(node[j].c==a)return j;
		}
		LL sz=size;
		node[u].ch.push_back(sz);
		push();
		node[sz].c=a;
		return sz;
	}
	void insert(char *a)
	{
		LL u=0;
		for(LL i=0;a[i];i++)
		{
			LL j=fin(u,a[i]);
			u=j;
		}
		node[u].v++;
	}
	LL dfs(LL u,LL dep)
	{
		//printf("%lld %lld\n",u,dep);
		vector<LL> ch;
		if(node[u].v)ch.push_back(node[u].v);
		LL sum=ch.size()?ch[0]:0;
		for(LL i=0;i<node[u].ch.size();i++)
		{
			LL j=dfs(node[u].ch[i],dep+2);
			if(j)
			{
				ch.push_back(j);
				sum+=j;
			}
		}
		LL ans=0;
		if(ch.size())
		{
			for(LL i=0;i<ch.size();i++)
			{
				ans+=ch[i]*(sum-ch[i]);
			}
			ans>>=1;
			Ans+=ans*dep;
		}
		if(node[u].v>=2)
		{
			LL i=node[u].v;
			Ans+=i*(i-1)/2*(dep+1);
		}
		return sum;
	}
};
trietype trie;
int main()
{
	freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	//printf("%lld %lld %lld\n",'0','A','a');
	LL kase=1;
	while(scanf("%lld",&n)==1&&n)
	{
		trie.clear();
		for(LL i=0;i<n;i++)
		{
			scanf("%s",tmp);
			trie.insert(tmp);
		}
		//printf("insert complete\n");
		Ans=0;
		trie.dfs(0,1);
		printf("Case %lld: %lld\n",kase++,Ans);
	}
	return 0;
}
