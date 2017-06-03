#include<cstdio>
#include<vector>
typedef long long LL;
using namespace std;
int N;
char LINE[41];
struct Trie
{
	vector<int>bse[26];
	LL sz,cnt[26];
	void clear(){sz=0LL;for(int i=0;i<26;i++)cnt[i]=0LL,bse[i].clear(),bse[i].push_back(0);}
	int newnode(){for(int i=0;i<26;i++)bse[i].push_back(0);return ++sz;}
	int getnxt(int c,int &u)
	{
		int &v=bse[c][u];
		if(v)return v;
		int ans=newnode();
		if(u)cnt[c]++;
		return bse[c][u]=ans;
	}
	int insert(char *s)
	{
		int u=0,i;
		for(i=0;s[i];i++)u=getnxt(s[i]-'a',u);
		return i;
	}
}PRE,SUF;
LL SINGLE[26];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		PRE.clear(),SUF.clear();
		for(int i=0;i<26;i++)SINGLE[i]=0;
		for(int i=0,n;i<N;i++)
		{
			scanf("%s",LINE);
			n=PRE.insert(LINE);n--;
			if(!n)SINGLE[LINE[0]-'a']=1LL;
			char tmp;
			for(int j=n/2;j>=0;j--)tmp=LINE[j],LINE[j]=LINE[n-j],LINE[n-j]=tmp;
			SUF.insert(LINE);
		}
		LL ans=PRE.sz*SUF.sz;
		for(int i=0;i<26;i++)
		{
			ans-=PRE.cnt[i]*SUF.cnt[i];
			ans+=SINGLE[i];
		}
		printf("%lld\n",ans);
	}
	return 0;
}
