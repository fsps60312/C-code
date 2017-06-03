#include<cstdio>
#include<cassert>
#include<string>
#include<vector>
#include<map>
using namespace std;
int N,M;
vector<string>DNA;
multimap<pair<int,int>,string>ANS;
int GetUnsortedness(const char *dna)
{
	int ans=0;
	for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)if(dna[i]>dna[j])ans++;
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		ANS.clear();
		for(int i=0;i<M;i++)
		{
			static char dna[51];
			scanf("%s",dna);
			ANS.insert(make_pair(make_pair(GetUnsortedness(dna),i),dna));
		}
		static int kase=0;
		if(kase++)puts("");
		for(const auto &it:ANS)puts(it.second.c_str());
	}
	return 0;
}
