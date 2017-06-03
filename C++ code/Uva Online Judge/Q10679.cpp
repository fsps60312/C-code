#include<cstdio>
#include<cstdlib>
const int l1=1000000,l2=55;
struct Trie
{
	int s[l1][l2];
	int val[l1];
	int sz;
	void memset(int a)
	{
		for(int i=0;i<l2;i++) s[a][i]=0;
	}
	void init()
	{
		sz=1;
		memset(0);
	}
	int index(char a)
	{
		return a>='a'?a-'a':a-'A'+26;
	}
	void insert(char *a,int b)
	{
		int i=0,j=0;
		while(a[j])
		{
			int k=index(a[j]);
			if(!s[i][k])
			{
				memset(sz);
				val[sz]=0;
				s[i][k]=sz;
				sz++;
			}
			j++;
			i=s[i][k];
		}
		val[i]=b;
	}
};
int T,q;
char S[100001],tmp[1001];
Trie trie;
int main()
{
	printf("%d %d",'a','A');
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s%d",S,&q);
		trie.init();
		while(q--)
		{
			scanf("%s",tmp);
			trie.insert(tmp);
		}
	}
	return 0;
}
