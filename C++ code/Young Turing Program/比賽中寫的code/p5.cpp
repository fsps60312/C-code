#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int N;
vector<int>S,ID;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		S.clear(),ID.clear();
		for(int i=0,v;i<N;i++)scanf("%d",&v),S.push_back(v),ID.push_back(i+1);
		for(int cur=0,cnt=1;(int)S.size()>1;cnt++)
		{
			if(cur==(int)S.size())cur=0;
			if(cnt%S[cur]==0)S.erase(S.begin()+cur),ID.erase(ID.begin()+cur);
			else cur++;
		}
		printf("%d\n",ID[0]);
	}
	return 0;
}
