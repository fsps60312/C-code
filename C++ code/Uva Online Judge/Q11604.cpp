#include<cstdio>
#include<cassert>
#include<string>
#include<vector>
using namespace std;
int N,L;
char LINE0[100],LINE1[22],LINE2[22],LINE3[22];
vector<string>V;
vector<int>TO[21];
void BuildEdge(string &s,string &e)
{
	assert(s.size()==L);
	for(int i=0;i<L;i++)
	{
		for(int j=0;;j++)
		{
			if(j==e.size())
			{
				TO[i].push_back(i+j);
				break;
			}
			if(i+j==L)break;
			if(s[i+j]!=e[j])break;
		}
	}
}
bool Reach(int u)
{
	if(u==L)return true;
	for(int i=0;i<TO[u].size();i++)
	{
		int &j=TO[u][i];
		if(Reach(j))return true;
	}
	return false;
}
bool solve()
{
	for(int i=0;i<V.size();i++)
	{
		L=V[i].size();
		for(int j=0;j<L;j++)TO[j].clear();
		for(int j=0;j<V.size();j++)if(i!=j)BuildEdge(V[i],V[j]);
//		printf("i=%d,L=%d,%d,%s\n",i,L,V[i].size(),V[i].c_str());
//		for(int j=0;j<L;j++)
//		{
//			printf("from %d:",j);
//			for(int k=0;k<TO[j].size();k++)printf(" %d",TO[j][k]);
//			puts("");
//		}
		if(Reach(0))return true;
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(gets(LINE0))
	{
		sscanf(LINE0,"%d",&N);
		if(!N)break;
		V.clear();
		for(int i=0;i<N;i++)
		{
			gets(LINE0);
			assert(sscanf(LINE0,"%s%s%s",LINE1,LINE2,LINE3)==2);
//			printf("%s\n",LINE2);
			V.push_back(LINE2);
		}
		static int kase=1;
		printf("Case #%d: %smbiguous.\n",kase++,solve()?"A":"Not a");
	}
	return 0;
}
