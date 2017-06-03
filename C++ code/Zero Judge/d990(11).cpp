#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int MAXN=4000000;
int S[100001];
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
		while(c<lettera||c>letterz)c=getchar();
		for(int i=0;c>=lettera&&c<=letterz;i++,c=getchar())u=GetNxt(u,c-lettera);
		v[u].push_back(ans.size()),tag[u]=1;
		ans.push_back(0);
	}
	void GetFail(vector<int>&s)
	{
		f[0]=0;
		static int q[MAXN],l,r;
		l=0,r=-1;
		s.clear();
//		s.push_back(0);
		for(int i=head[0];i!=-1;i=nxt[i])
		{
			int &u=i;
			q[++r]=u;
			if(tag[u])s.push_back(u);
			f[u]=0;
		}
		while(l<=r)
		{
			static int u,i;u=q[l++];
			for(i=head[u];i!=-1;i=nxt[i])
			{
				int &o=i;
				int &ff=f[o]=f[u],&c=cc[i];
				while(ff&&Find(ff,c)==0)ff=f[ff];
				ff=Find(ff,c);
				tag[o]|=tag[ff];
				q[++r]=o;
				if(tag[o])s.push_back(o);
			}
		}
	}
	void Match(int *s)
	{
		const int lettera='a';
		int u=0;
		for(int i=0;s[i];i++)
		{
			while(u&&Find(u,s[i]-lettera)==0)u=f[u];
			u=Find(u,s[i]-lettera);
			cnt[u]++;
		}
	}
	void printans(const vector<int>&s)
	{
		for(int _i=s.size()-1;_i>=0;_i--)
		{
			const int &i=s[_i];
			cnt[f[i]]+=cnt[i];
			static int k;
			for(k=0;k<v[i].size();k++)ans[v[i][k]]+=cnt[i];
		}
		for(int i=0;i<ans.size();i++)
		{
			int &n=ans[i];
			static vector<int>o;o.clear();
			static int j;
			const int zero='0',nxtline='\n';
			while(n)
			{
				o.push_back(n%10);
				n/=10;
			}
			if(o.size()==0)putchar(zero);
			else for(j=o.size()-1;j>=0;j--)putchar(zero+o[j]);
			putchar(nxtline);
		}
	}
}TRIE;
void GetS()
{
	const int lettera='a',letterz='z';
	int c=getchar(),i;
	while(c<lettera||c>letterz)c=getchar();
	for(i=0;c>=lettera&&c<=letterz;c=getchar(),i++)S[i]=c;
	S[i]=0;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static vector<int>s;
	s.reserve(MAXN);
	GetS();scanf("%d",&N);
	TRIE.Clear();
	for(int i=0;i<N;i++)TRIE.Insert();
	TRIE.GetFail(s);
	TRIE.Match(S);
	TRIE.printans(s);
	return 0;
}
