#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
const int MOD=20071027;
int n,ways[300001];
char S[300001],tmp[101];
struct Trietype
{
	vector<int> s[26];
	vector<int> v;
	int size;
	void clear()
	{
		for(int i=0;i<26;i++)s[i].clear();
		v.clear();
		size=0;
		push();
	}
	void push()
	{
		for(int i=0;i<26;i++)s[i].push_back(0);
		v.push_back(0);
		size++;
	}
	void insert()
	{
		int u=0;
		for(int i=0;tmp[i];i++)
		{
			if(!s[tmp[i]-'a'][u])
			{
				push();
				s[tmp[i]-'a'][u]=size-1;
			}
			u=s[tmp[i]-'a'][u];
		}
		v[u]++;
	}
	void find(int a)
	{
		int u=0;
		for(int i=a;S[i];i++)
		{
			if(!s[S[i]-'a'][u])break;
			u=s[S[i]-'a'][u];
			if(v[u]>0)
			{
			//printf(" %d",a);
				ways[i+1]+=ways[a]*v[u];
				ways[i+1]%=MOD;
			}
		}//printf("\n");
	}
};
Trietype trie;
int main()
{
	ways[0]=1;
	int kase=1;
	while(scanf("%s",S)==1)
	{
		trie.clear();
		scanf("%d",&n);
		for(int i=0;i<n;i++)
		{
			scanf("%s",tmp);
			trie.insert();
		}
		int strl=-1;
		while(S[++strl])ways[strl]=0;ways[strl]=0;
		ways[0]=1;
		for(int i=0;S[i];i++)
		{
			trie.find(i);
		}
		//for(int i=0;i<=strl;i++)printf(" %d",ways[i]);printf("\n");
		printf("Case %d: %d\n",kase++,ways[strl]);
	}
	return 0;
}
