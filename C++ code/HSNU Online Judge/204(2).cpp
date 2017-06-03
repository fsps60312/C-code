#include<bits/stdc++.h>
using namespace std;
int N,M[20];
set<int>S;
vector<int>INS;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&M[i]);
		S.clear();
		S.insert(0);
		for(int i=0;i<N;i++)
		{
			int &v=M[i];
			INS.clear();
			for(auto j=S.begin();j!=S.end();j++)INS.push_back((*j)+v);
			for(auto j=INS.begin();j!=INS.end();j++)S.insert(*j);
		}
		int ans=0;
		for(auto i=S.begin();i!=S.end();i++)
		{
//			printf(" %d,",*i);
			if(!((*i)&1)&&S.find((*i)>>1)!=S.end())ans++;
		}
		printf("%d\n",--ans);
		break;
	}
	return 0;
}
