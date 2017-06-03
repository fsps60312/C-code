#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
bool Solve(vector<int>s,const int K)
{
	int now=0;
	for(int bit=30;bit>=0;bit--)
	{
		static vector<int>tmp[2];
		for(const int v:s)tmp[(v&(1<<bit))>>bit].push_back(v);
		s.swap(tmp[0]);
		if((now^K)&(1<<bit))
		{
			if(tmp[1].empty())return false;
			now^=tmp[1][0];
		}
		for(int i=1;i<(int)tmp[1].size();i++)s.push_back(tmp[1][i-1]^tmp[1][i]);
		for(int d=0;d<2;d++)vector<int>().swap(tmp[d]);
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int N,K;
	scanf("%d%d",&N,&K);
	vector<int>s;
	for(int i=0,v;i<N;i++)scanf("%d",&v),s.push_back(v);
	puts(Solve(s,K)?"Yes":"No");
	return 0;
}
