#include<cstdio>
#include<vector>
#define debug(x,...) printf(x,##__VA_ARGS__)
#define debu2(x,...) printf(x,##__VA_ARGS__)
using namespace std;
int N;
char LINE[41];
struct Trie
{
	vector<int>bse[26];
	int sz;
	void clear(){sz=0;for(int i=0;i<26;i++)bse[i].clear(),bse[i].push_back(0);}
	int newnode(){for(int i=0;i<26;i++)bse[i].push_back(0);return ++sz;}
	int getnxt(int &u,char &c)
	{
		debug("%d %d\n",c-'a',u);
		int &v=bse[c-'a'][u];
		if(v){debug("case1\n");return v;}
		else {debug("case2\n");debug("bef bse[0][0]=%d,v=%d,sz=%d\n",bse[c-'a'][u],v,sz);v=newnode();debug("aft bse[0][0]=%d,v=%d,sz=%d\n",bse[c-'a'][u],v,sz);return v;}
	}
	int insert(char *s)
	{
		int u=0,i;
		for(i=0;s[i];i++){u=getnxt(u,s[i]);}debug("\n");
		return i;
	}
}TRI1,TRI2;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		TRI1.clear(),TRI2.clear();
		for(int i=0,n;i<N;i++)
		{
			scanf("%s",LINE);
			n=TRI1.insert(LINE);n--;
			char tmp;
			debug("\"%s\"\n",LINE);
			for(int j=n/2;j>=0;j--)tmp=LINE[j],LINE[j]=LINE[n-j],LINE[n-j]=tmp;
			debug("\"%s\"\n",LINE);
			TRI2.insert(LINE);
		}
		debu2("%d*%d\n",TRI1.sz,TRI2.sz);
		printf("%lld\n",(long long)TRI1.sz*TRI2.sz);
	}
	return 0;
}
