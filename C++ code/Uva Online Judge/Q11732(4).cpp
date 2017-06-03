#include<cstdio>
#include<cstdlib>
#include<vector>
#define LL long long
using namespace std;
char tmp[1001];
LL n;
LL Ans;
struct trietype
{
	struct sidetype
	{
		LL next;
		char c;
		LL v;
		LL ch;
	};
	sidetype side[4000000];
	LL ssz;
	void clear()
	{
		ssz=1;
		side[0].ch=-1;
		side[0].v=0;
		side[0].c=0;
		side[0].next=-1;
	}
	LL fin(LL u,char a)
	{
		//printf("fin:%c\n",a);
		if(side[u].ch==-1)
		{
			side[u].ch=ssz;
		}
		else
		{
			u=side[u].ch;
			//printf("%c",side[u].c);
			if(side[u].c==a)
			{
				//printf(" find\n");
				return u;
			}
			//printf(" fail\n");
			while(side[u].next!=-1)
			{
				//printf("%d",u);
				//printf(",%c",side[u].c);
				//printf(",%c\n",a);
				if(side[u].c==a)return u;
				u=side[u].next;
			}
			if(side[u].c==a)return u;
			side[u].next=ssz;
		}
		//printf("pass\n");
		side[ssz].c=a;
		side[ssz].v=0;
		side[ssz].next=-1;
		side[ssz].ch=-1;
		//ssz++;
		return ssz++;
	}
	void insert(char *a)
	{
		LL u=0;
		for(LL i=0;a[i];i++)
		{
			//LL j=side[u].ch;
			LL j=fin(u,a[i]);
			//printf("fin:%c,u=%lld,j=%lld\n",a[i],u,j);
			u=j;
		}
		side[u].v++;
		//printf("%lld\n",u);
	}
	LL dfs(LL u,LL dep)
	{
		//printf("%lld %lld\n",u,dep);
		vector<LL> ch;
		LL sum=0;
		if(side[u].v)
		{
			ch.push_back(side[u].v);
			sum+=side[u].v;
		}
		for(LL i=side[u].ch;i!=-1;i=side[i].next)
		{
			LL j=dfs(i,dep+2);
			if(j)
			{
				ch.push_back(j);
				sum+=j;
			}
		}
		if(sum)
		{
			LL ans=0;
			for(LL i=ch.size()-1;i>=0;i--)
			{
				ans+=ch[i]*(sum-ch[i]);
			}
			if(ans)
			{
				//if(ans%2)printf("error %lld\n",ans);
				ans>>=1;
				Ans+=ans*dep;
				//printf("%lld\t%lld\n",sum,ans*dep);
			}
		}
		if(side[u].v>=2)
		{
			LL i=side[u].v;
			Ans+=i*(i-1)*(dep+1)/2;
			//printf("%lld\t%lld\n",sum,i*(i-1)*(dep+1)/2);
		}
		return sum;
	}
};
trietype trie;
int main()
{
	//freopen("in.txt","r",stdin);
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
			//printf("%lld\t%lld\n",j,trie.ssz);
			trie.insert(tmp);
		}
		//printf("insert complete\n");
		Ans=0;
		//LL sum=0;
		//for(int i=0;i<trie.ssz;i++)sum+=trie.side[i].v;
		//printf("%lld %lld %lld\n",n,sum,trie.dfs(0,1));
		trie.dfs(0,1);
		printf("Case %lld: %lld\n",kase++,Ans);//,trie.ssz);
	}
	return 0;
}
