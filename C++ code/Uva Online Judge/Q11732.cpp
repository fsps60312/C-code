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
	vector<LL> s[62];
	vector<LL> v;
	vector<vector<LL> > nod;
	LL size;
	void clear()
	{
		for(LL i=0;i<62;i++)s[i].clear();
		v.clear();
		nod.clear();
		size=0;
		push();
	}
	void push()
	{
		for(LL i=0;i<62;i++)s[i].push_back(0);
		v.push_back(0);
		vector<LL> a;
		nod.push_back(a);
		size++;
	}
	void insert(char *a)
	{
		LL u=0;
		for(LL i=0;a[i];i++)
		{
			LL j=s[trans(a[i])][u];
			if(!j)
			{
				j=s[trans(a[i])][u]=size; 
				nod[u].push_back(size);
				push();
			}
			u=j;
		}
		v[u]++;
	}
	LL dfs(LL u,LL dep)
	{
		vector<LL> node;
		LL sum=0,ans=0;
		if(v[u])
		{
			node.push_back(v[u]);
			sum+=v[u];
		}
		if(nod[u].size())
		for(LL i=nod[u].size()-1;i>=0;i--)
		{
			LL j=dfs(nod[u][i],dep+2);
			if(j)
			{
				node.push_back(j);
				sum+=j;
			}
		}
		if(sum)
		{
			//printf("dep %lld:node.size=%lld,sum=%lld\n",dep,node.size(),sum);
			for(LL i=node.size()-1;i>=0;i--)
			{
				ans+=node[i]*(sum-node[i]);
			}
			ans>>=1;
			if(ans)
			{
				Ans+=ans*dep;
				printf("%lld\t%lld\n",sum,ans*dep);
			}
		}
		if(v[u]>=2)
		{
			Ans+=((v[u]*(v[u]-1))>>1)*(dep+1);
			printf("%lld\t%lld\n",sum,((v[u]*(v[u]-1))>>1)*(dep+1));
		}
		return sum;
	}
};
trietype trie;
int main()
{
	freopen("out.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	//printf("%lld %lld %lld\n",'0','A','a');
	LL kase=1;
	while(scanf("%lld",&n)==1&&n)
	{
		trie.clear();
		for(LL i=0;i<n;i++)
		{
			scanf("%s",tmp);
			LL j=-1;while(tmp[++j]);
			printf("%lld\t%lld\n",j,trie.size);
			trie.insert(tmp);
		}
		printf("insert complete\n");
		Ans=0;
		trie.dfs(0,1);
		printf("Case %lld: %lld %lld\n",kase++,Ans,trie.size);
	}
	return 0;
}
