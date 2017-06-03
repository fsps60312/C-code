#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int MAXN=4000000;
char S[100001];
int N;
struct Trie
{
	vector<int>head,nxt,cc;
	vector<vector<int> >v;
	vector<int>f;
	vector<int>tag;
	vector<int>cnt;
	vector<int>ans;
	void Clear()
	{
		head.clear(),nxt.clear(),cc.clear();
		v.clear(),f.clear(),tag.clear(),cnt.clear(),ans.clear();
		head.reserve(MAXN),nxt.reserve(MAXN),cc.reserve(MAXN);
		v.reserve(MAXN),f.reserve(MAXN),tag.reserve(MAXN),cnt.reserve(MAXN),ans.reserve(MAXN);
		Push();
		nxt.push_back(-1),cc.push_back(-1);
	}
	int Push()
	{
		static int sz;sz=head.size();
		head.push_back(-1);
		v.push_back(vector<int>());
		f.push_back(0);
		tag.push_back(0);
		cnt.push_back(0);
		return sz;
	}
	int Find(const int &u,const int &c)
	{
		static int i;
		for(i=head[u];i!=-1;i=nxt[i])if(cc[i]==c)return i;
		return 0;
	}
	int GetNxt(const int &u,const int &c)
	{
		static int ans,sz;
		ans=Find(u,c);
		if(ans)return ans;
		sz=nxt.size();
		nxt.push_back(head[u]);
		cc.push_back(c);
		ans=Push();
		head[u]=sz;
		return ans;
	}
	void Insert()
	{
		const int lettera='a',letterz='z';
		int u=0,c=getchar();
		while(c<'a'||c>'z')c=getchar();
		for(int i=0;c>=lettera&&c<=letterz;i++,c=getchar())u=GetNxt(u,c-lettera);
		v[u].push_back(ans.size()),tag[u]=1;
		ans.push_back(0);
	}
	void GetFail(vector<int>&s)
	{
		f[0]=0;
		static queue<int>q;
		s.clear();
		s.push_back(0);
		for(int i=head[0];i!=-1;i=nxt[i])
		{
			int &u=i;
			q.push(u);
			s.push_back(u);
			f[u]=0;
		}
		while(!q.empty())
		{
			static int u,i;u=q.front();q.pop();
			for(i=head[u];i!=-1;i=nxt[i])
			{
				int &o=i;
				int &ff=f[o]=f[u],&c=cc[i];
				while(ff&&Find(ff,c)==0)ff=f[ff];
				ff=Find(ff,c);
				tag[o]|=tag[ff];
				q.push(o);
				s.push_back(o);
			}
		}
	}
	void Match(char *s)
	{
		int u=0;
		for(int i=0;s[i];i++)
		{
			while(u&&Find(u,s[i]-'a')==0)u=f[u];
			u=Find(u,s[i]-'a');
			cnt[u]++;
		}
	}
	void printans(const vector<int>&s)
	{
//		for(int i=0;i<val.size();i++)printf("val[%d]=%d\n",i,val[i]);
		for(int _i=s.size()-1;_i>=0;_i--)
		{
			const int &i=s[_i];
			if(tag[i])
			{
//				printf("i=%d,c=%d\n",i,cnt[i]);
				cnt[f[i]]+=cnt[i];
				static int k;
				for(k=0;k<v[i].size();k++)ans[v[i][k]]+=cnt[i];
			}
		}
		for(int i=0;i<ans.size();i++)printf("%d\n",ans[i]);
	}
}TRIE;
char A[100001];
int F[100001];
void GetFail(const char *a,int *fail)
{
	fail[0]=fail[1]=0;
	for(int i=1,f;a[i];i++)
	{
		f=fail[i];
		while(f&&a[f]!=a[i])f=fail[f];
		fail[i+1]=(a[f]==a[i]?++f:0);
	}
//	for(int i=0;i==0||a[i-1];i++)printf(" %d",fail[i]);puts("");
}
int Query(const char *s,const char *a,const int *fail)
{
	int ans=0;
	for(int i=0,u=0;s[i];i++)
	{
		while(u&&a[u]!=s[i])u=fail[u];
		if(s[i]==a[u])u++;
		if(!a[u])ans++;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static vector<int>s;
	s.reserve(MAXN);
	while(scanf("%s%d",S,&N)==2)
	{
		int l=-1;while(S[++l]);
		if(l*N>=300000000)
		{
			TRIE.Clear();
			for(int i=0;i<N;i++)
			{
				TRIE.Insert();
			}
			TRIE.GetFail(s);
			TRIE.Match(S);
			TRIE.printans(s);
		}
		else
		{
			for(int i=0;i<N;i++)
			{
				scanf("%s",A);
				GetFail(A,F);
				printf("%d\n",Query(S,A,F));
			}
		}
	}
	return 0;
}
