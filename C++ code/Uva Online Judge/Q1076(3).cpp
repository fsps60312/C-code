#include<cstdio>
#include<cstdlib>
#include<queue>
#define debug(...) ;//__VA_ARGS__
using namespace std;
int N,M;
#define LL long long
LL POW26[26];
int WANTV,DP[26][10],AN;
char DFSTS[26];
char ANS[42][26];
int C(int a,int b)
{
	int ans=1;
	for(int i=1;i<=a-b;i++)
	{
		ans*=b+i;
		ans/=i;
	}
	return ans;
}
int countbit(int a)
{
	a=((a&0xaaaaaaaa)>>1)+(a&0x55555555);
	a=((a&0xcccccccc)>>2)+(a&0x33333333);
	a=((a&0xf0f0f0f0)>>4)+(a&0x0f0f0f0f);
	a=((a&0xff00ff00)>>8)+(a&0x00ff00ff);
	a=((a&0xffff0000)>>16)+(a&0x0000ffff);
	return a;
}
void addans(int sl)
{
	//if(sl==N){DFSTS[sl+1]=0;printf("%s\n",DFSTS+1);}
	if(AN>=42||N-sl>0){AN=43;return;}
	for(int i=1;;i++)
	{
		if(i<=sl)ANS[AN][i-1]=DFSTS[i];
		else
		{
			ANS[AN][i-1]=0;
			break;
		}
	}
	AN++;
}
struct Trie
{
	struct Node
	{
		int v,fail,c;
		bool isend;
		int ch[26];
	}s[101];
	int sz;
	bool inited;
	void init(int u,int c)
	{
		inited=true;
		Node &a=s[u];
		a.v=0,a.c=c;
		a.isend=false;
		for(int i=0;i<26;i++)a.ch[i]=0;
	}
	void clear(){sz=1;init(0,-1);}
	int getch(int u,int chn)
	{
		if(!s[u].ch[chn])
		{
			init(sz,chn);
			s[u].ch[chn]=sz++;
		}
		return s[u].ch[chn];
	}
	void insert(char *str,int v)
	{
		int u=0;
		inited=false;
		s[u].v|=v;
		for(int i=0;str[i];i++)
		{
			u=getch(u,str[i]-'a');
			s[u].v|=v;
		}
		s[u].isend=true;
	}
	void walkaround(int u,int vis,int step,int segn)
	{
		//printf("u=%d,step=%d,vis=%d\n",u,step,vis);
		if(step>N)return;
		if(u)DFSTS[step]='a'+s[u].c;
		if((vis|s[u].v)==vis)return;
		if(s[u].isend)
		{
			int tu=s[u].fail;
			//tu=s[tu].ch[s[u].c];
			//printf("fail:%d -> %d\n",u,tu);
			if((vis|s[u].v)==WANTV)
			{
				addans(step);
				DP[step][segn]++;
				return;
			}
			if(tu)walkaround(tu,vis|s[u].v,step,segn);
			walkaround(0,vis|s[u].v,step,segn+1);
		}
		else
		{
			for(int i=0;i<26;i++)
			{
				int ni=s[u].ch[i];
				if(ni)
				{
					walkaround(ni,vis,step+1,segn);
				}
			}
		}
	}
	void getfail()
	{
		s[0].fail=0;
		queue<int> q;
		for(int i=0;i<26;i++)
		{
			int ni=s[0].ch[i];
			if(ni)
			{
				s[ni].fail=0;
				q.push(ni);
			}
		}
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int c=0;c<26;c++)
			{
				int ni=s[u].ch[c];
				if(ni)
				{
					int f=s[u].fail;
					while(f&&!s[f].ch[c])f=s[f].fail;
					s[ni].fail=s[f].ch[c];
					q.push(ni);
				}
			}
		}
		debug(for(int i=0;i<sz;i++)printf("fail[%d]=%d\n",i,s[i].fail););
	}
}trie;
bool strcmp(char *s1,char *s2)
{
	int i;
	for(i=0;s1[i]&&s2[i];i++)
	{
		if(s1[i]!=s2[i])return false;
	}
	return s1[i]==0&&s2[i]==0;
}
bool consist(char *a,char *b)
{
	for(int i=0;a[i];i++)
	{
		if(strcmp(a+i,b))return true;
	}
	return false;
}
LL solve()
{
	if(M==0)return POW26[N];
	char tstr[M][11];
	for(int i=0;i<M;i++)
	{
		scanf("%s",tstr[i]);
		for(int j=0;j<i;j++)
		{
			if(strcmp(tstr[j],tstr[i]))
			{
				i--;
				M--;
				break;
			}
		}
	}
	for(int i=0,j=1;i<M;i++)
	{
		bool ok=true;
		for(int k=0;k<M;k++)
		{
			if(k!=i&&consist(tstr[k],tstr[i]))
			{
				ok=false;
				break;
			}
		}
		if(!ok)continue;
		trie.insert(tstr[i],j);
		j<<=1,WANTV=j-1;
		//printf("str=%s,i=%d,trie.sz=%d\n",tstr[i],i,trie.sz);
	}
	//printf("alls=\"%s\"\n",alls);
	//for(int i=0;alls[i];i++)printf(" %d",fail[i]);printf("\n");
	trie.getfail();
	/*for(int i=0;i<trie.sz;i++)
	{
		Trie::Node j=trie.s[i];
		printf("%d:%c,v=%d,fail=%d,isend=%d\n",i,'a'+j.c,j.v,j.fail,j.isend);
	}*/
	for(int i=0;i<=N;i++)
	{
		for(int j=0;j<M;j++)
		{
			DP[i][j]=0;
		}
	}
	trie.walkaround(0,0,0,0);
	LL ans=0;
	for(int i=0;i<=N;i++)
	{
		for(int j=0;j<M;j++)
		{
			ans+=DP[i][j]*POW26[N-i]*C(N-i+j+1,N-i);
		}
	}
	//for(int i=0;i<=N;i++)for(int j=0;j<M;j++)printf("DP[%d][%d]=%d\n",i,j,DP[i][j]);
	return ans;
}
int ORDER[42];
void getorder()
{
	for(int i=0;i<AN;i++)
	{
		int ans=i;
		for(int j=i+1;j<AN;j++)
		{
			if(strcmp(ANS[j],ANS[i]))ans=j;
		}
		ORDER[i]=ans;
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	POW26[0]=1;for(int i=1;i<=25;i++)POW26[i]=POW26[i-1]*26;
	int kase=1;
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		trie.clear();
		AN=0;
		LL ans=solve();
		printf("Case %d: %lld suspects\n",kase++,ans);
		if(ans<=42)
		{
			getorder();
			for(int i=0;i<ans;i++)
			{
				printf("%s\n",ANS[ORDER[i]]);
			}
		}
	}
	return 0;
}
