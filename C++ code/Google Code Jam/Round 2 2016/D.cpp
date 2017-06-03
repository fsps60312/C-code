#include<cstdio>
#include<cassert>
using namespace std;
struct DisjointSet
{
	int S[25],CNT[25];
	void Clear(){for(int i=0;i<25;i++)S[i]=i,CNT[i]=1;}
	int Find(const int a){return S[a]==a?a:(S[a]=Find(S[a]));}
	bool Merge(int a,int b){if((a=Find(a))==(b=Find(b)))return false;S[a]=b,CNT[b]+=CNT[a],CNT[a]=0;return true;}
}DJ;
int N,S[25],M[25];
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)M[i]=0;
		int cnt=0;
		for(int i=0;i<N;i++)
		{
			static char str[26];
			scanf("%s",str);
			int &v=S[i]=0;
			for(int j=0;j<N;j++)v=v*2+(str[j]-'0');
			for(int j=0;j<N;j++)if(v&(1<<j))--cnt,++M[j];
		}
		DJ.Clear();
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)if(S[i]&S[j])DJ.Merge(i,j);
		for(int i=0;i<N;i++)S[DJ.Find(i)]|=S[i];
		for(int i=0;i<N;i++)S[i]|=S[DJ.Find(i)];
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)if(S[i]&(1<<j))++cnt;
			if(S[i]==0)++cnt;
		}
		static int kase=0;
		printf("Case #%d: %d\n",++kase,cnt);
	}
	return 0;
}
