#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
const int MAXN=4000000;
char S[100001];
int N;
struct Trie
{
	int head[MAXN],nxt[MAXN],cc[MAXN],val[MAXN],hsz;
	vector<int>v[MAXN];
	int f[MAXN],tag[MAXN],cnt[MAXN],ans[MAXN],nsz;
	inline void Clear()
	{
		hsz=nsz=0;
		Push();
	}
	inline int Push()
	{
		head[hsz]=-1;
		v[hsz].clear();
		f[hsz]=tag[hsz]=cnt[hsz]=0;
		return hsz++;
	}
	inline int Find(const int &u,const int &c)
	{
		static int i;
		for(i=head[u];i!=-1;i=nxt[i])if(cc[i]==c)return val[i];
		return 0;
	}
	inline int GetNxt(const int &u,const int &c)
	{
		static int ans;
		ans=Find(u,c);
		if(ans)return ans;
		nxt[nsz]=head[u];
		cc[nsz]=c;
		val[nsz]=(ans=Push());
		head[u]=nsz++;
		return ans;
	}
	inline void Insert(const int &i)
	{
		const int lettera='a',letterz='z';
		int u=0,c=getchar();
		while(c<lettera||c>letterz)c=getchar();
		for(int i=0;c>=lettera&&c<=letterz;i++,c=getchar())u=GetNxt(u,c-lettera);
		v[u].push_back(i),tag[u]=1;
		ans[i]=0;
	}
	inline void GetFail(vector<int>&s)
	{
		f[0]=0;
		static queue<int>q;
		s.clear();
		s.push_back(0);
		for(int i=head[0];i!=-1;i=nxt[i])
		{
			int &u=val[i];
			q.push(u);
			s.push_back(u);
			f[u]=0;
		}
		while(!q.empty())
		{
			static int u,i;u=q.front();q.pop();
			for(i=head[u];i!=-1;i=nxt[i])
			{
				int &o=val[i];
				f[o]=f[u];
				while(f[o]&&Find(f[o],cc[i])==0)f[o]=f[f[o]];
				f[o]=Find(f[o],cc[i]);
				tag[o]|=tag[f[o]];
				q.push(o);
				s.push_back(o);
			}
		}
	}
	inline void Match(char *s)
	{
		int u=0;
		for(int i=0;s[i];i++)
		{
			while(u&&Find(u,s[i]-'a')==0)u=f[u];
			u=Find(u,s[i]-'a');
			cnt[u]++;
		}
	}
	inline void printans(const vector<int>&s)
	{
		for(int _i=s.size()-1;_i>=0;_i--)
		{
			const int &i=s[_i];
			if(tag[i])
			{
				const int &c=cnt[i];
				cnt[f[i]]+=c;
				static int k;
				for(k=0;k<v[i].size();k++)ans[v[i][k]]+=c;
			}
		}
		for(int i=0;i<N;i++)printf("%d\n",ans[i]);
	}
}TRIE;
int main()
{
//	freopen("in.txt","r",stdin);
	static vector<int>s;
	s.reserve(MAXN);
	while(scanf("%s%d",S,&N)==2)
	{
		TRIE.Clear();
		for(int i=0;i<N;i++)
		{
			TRIE.Insert(i);
		}
		TRIE.GetFail(s);
		TRIE.Match(S);
		TRIE.printans(s);
	}
	return 0;
}
