#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
using namespace std;
char SA[5001],SB[5001];
vector<pair<char,int> >A,B;
bool Solve()
{
	A.clear(),B.clear();
	for(int i=0;SA[i];i++)
	{
		if(A.empty()||A.back().first!=SA[i])A.push_back(make_pair(SA[i],1));
		else ++A.back().second;
	}
	for(int i=0;SB[i];i++)
	{
		if(B.empty()||B.back().first!=SB[i])B.push_back(make_pair(SB[i],1));
		else ++B.back().second;
	}
	if(A[0].first!=B[0].first||A[0].second<B[0].second)return false;
	for(int i=0,j=0;;i++)
	{
		if(SB[i]==SA[j])++j;
		if(SA[j]=='\0')return true;
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%s%s",SA,SB);
	puts(Solve()?"Yes":"No");
	return 0;
}
