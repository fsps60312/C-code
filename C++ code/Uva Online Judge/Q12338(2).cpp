#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
struct Trie
{
	vector<int>head,next;
	vector<char>alphabet;
	void clear(){head.clear(),next.clear(),alphabet.clear();head.push_back(-1),next.push_back(-1),alphabet.push_back('\0');}
	int GetNxt(const int u,const char c)
	{
		for(int now=head[u];now!=-1;now=next[now])if(alphabet[now]==c)return now;
		const int sz=next.size();
		next.push_back(head[u]);
		alphabet.push_back(c);
		head.push_back(-1);
		head[u]=sz;
		return sz;
	}
	int Insert(const char *str)
	{
		int u=0;
		for(int i=0;str[i];i++)u=GetNxt(u,str[i]);
		return u;
	}
	vector<int>depth;
	vector<vector<int> >father;
	void BuildFa(const int u,const int fa,const int dep)
	{
		depth[u]=dep;
		father[u].clear();
		father[u].push_back(fa);
		for(int now=fa,i=0;i<(int)father[now].size();i++)father[u].push_back(now=father[now][i]);
		for(int now=head[u];now!=-1;now=next[now])BuildFa(now,u,dep+1);
	}
	void BuildFa()
	{
		father.resize(head.size()),depth.resize(head.size());
		father[0].clear(),depth[0]=0;
		for(int now=head[0];now!=-1;now=next[now])BuildFa(now,0,1);
	}
	int GetDepOfLCA(int a,int b)
	{
		if(depth[a]<depth[b])swap(a,b);
		for(int i=30,s=depth[a]-depth[b];i>=0;i--)if(s&(1<<i))a=father[a][i];
//		printf("(%d,%d)\n",depth[a],depth[b]);
		assert(depth[a]==depth[b]);
		if(a==b)return depth[a];
		for(int i=30;i>=0;i--)if(i<(int)father[a].size()&&i<(int)father[b].size()&&father[a][i]!=father[b][i])a=father[a][i],b=father[b][i];
		assert(depth[a]>0);
		return depth[a]-1;
	}
}TRIE;
int T,N,Q;
vector<int>LEAF;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		TRIE.clear(),LEAF.clear();
		for(int i=0;i<N;i++)
		{
			static char tmp[10001];
			scanf("%s",tmp);
			LEAF.push_back(TRIE.Insert(tmp));
		}
		TRIE.BuildFa();
		static int kase=1;
		printf("Case %d:\n",kase++);
		scanf("%d",&Q);
		while(Q--)
		{
			static int a,b;scanf("%d%d",&a,&b);
			printf("%d\n",TRIE.GetDepOfLCA(LEAF[--a],LEAF[--b]));
		}
	}
	return 0;
}
