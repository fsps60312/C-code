#include<cstdio>
#include<cassert>
#include<string>
#include<vector>
#include<set>
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
	assert(u<=L);
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
		for(int j=0;j<L;j++)
		{
			TO[j].clear();
			assert(V[i][j]=='0'||V[i][j]=='1');
		}
		for(int j=0;j<V.size();j++)if(i!=j)BuildEdge(V[i],V[j]);
		if(Reach(0))return true;
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(gets(LINE0))
	{
		assert(sscanf(LINE0,"%d",&N)==1);
		if(!N)break;
		V.clear();
		set<string>s;
		for(int i=0;i<N;i++)
		{
			gets(LINE0);
			assert(sscanf(LINE0,"%s%s%s",LINE1,LINE2,LINE3)==2);
//			printf("%s\n",LINE2);
			V.push_back(LINE2);
			assert(s.find(LINE1)==s.end());
			s.insert(LINE1);
		}
		static int kase=1;
		printf("Case #%d: %smbiguous.\n",kase++,solve()?"A":"Not a");
	}
	return 0;
}
