#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int &MAXN=4000000;
char S[100001];
int N;
struct Trie
{
	vector<int>head,nxt,cc,val;
	vector<vector<int> >v;
	vector<int>f;
	vector<int>tag;
	vector<int>cnt;
	vector<int>ans;
	void Clear()
	{
		head.clear(),nxt.clear(),cc.clear(),val.clear();
		v.clear(),f.clear(),tag.clear(),cnt.clear(),ans.clear();
		head.reserve(MAXN),nxt.reserve(MAXN),cc.reserve(MAXN),val.reserve(MAXN);
		v.reserve(MAXN),f.reserve(MAXN),tag.reserve(MAXN),cnt.reserve(MAXN),ans.reserve(MAXN);
		Push();
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
		for(i=head[u];i!=-1;i=nxt[i])if(cc[i]==c)return val[i];
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
		val.push_back(ans=Push());
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
	void GetFail()
	{
		f[0]=0;
		queue<int>q;
		for(int i=head[0];i!=-1;i=nxt[i])
		{
			int &u=val[i];
			q.push(u);
			f[u]=0;
		}
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=head[u];i!=-1;i=nxt[i])
			{
				int &o=val[i];
				f[o]=f[u];
				while(f[o]&&Find(f[o],cc[i])==0)f[o]=f[f[o]];
				f[o]=Find(f[o],cc[i]);
				tag[o]|=tag[f[o]];
				q.push(o);
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
	void printans()
	{
		for(int i=cnt.size()-1;i>=0;i--)
		{
			for(int j=i,c=0;tag[j];j=f[j])
			{
				c+=cnt[j],cnt[j]=0;
				for(int k=0;k<v[j].size();k++)ans[v[j][k]]+=c;
			}
		}
		for(int i=0;i<ans.size();i++)printf("%d\n",ans[i]);
	}
}TRIE;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%s%d",S,&N)==2)
	{
		TRIE.Clear();
		for(int i=0;i<N;i++)
		{
//			puts("a");
			TRIE.Insert();
//			puts("b");
		}
//		puts("c");
		TRIE.GetFail();
		TRIE.Match(S);
		TRIE.printans();
	}
	return 0;
}
