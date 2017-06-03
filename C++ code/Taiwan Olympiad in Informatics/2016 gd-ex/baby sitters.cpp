#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
bool GetPair(pair<int,int>&p)
{
	static char str[10000];
	if(!fgets(str,10000,stdin))return false;
	if(sscanf(str,"%d%d",&p.first,&p.second)!=2)return false;
	if(p.first>p.second)swap(p.first,p.second);
	++p.first,++p.second;
	return true;
}
vector<pair<int,int> >S;
int DP[201];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		pair<int,int>p;
		while(!GetPair(p));
		S.clear(),S.push_back(p);
		while(GetPair(p))S.push_back(p);
//		printf("sz=%d\n",(int)S.size());
		sort(S.begin(),S.end());
		DP[0]=0;
		for(int i=1;i<=200;i++)DP[i]=INF;
		for(int i=0;i<(int)S.size();i++)if(DP[S[i].first-1]!=INF)
		{
			for(int j=S[i].first;j<=S[i].second;j++)getmin(DP[j],DP[S[i].first-1]+1);
		}
		printf("%d\n",DP[200]);
	}
	return 0;
}
