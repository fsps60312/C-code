#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
using namespace std;
const int INF=2147483647;
template<class T>inline void getmin(T&a,const T&b){if(b<a)a=b;}
vector<int>S;
bool IsDigit(const char c){return '0'<=c&&c<='9';}
bool ReadInput()
{
	static char str[1000000];
	if(!fgets(str,INF,stdin))return false;
	int i=0;
	while(!IsDigit(str[i]))i++;
	S.resize(1);
	for(;;)
	{
		int v=0;
		while(IsDigit(str[i]))v=v*10+(str[i]-'0'),i++;
		S.push_back(v);
		while(!(str[i]=='\0'||str[i]=='\n')&&!IsDigit(str[i]))i++;
		if(str[i]=='\0'||str[i]=='\n')break;
	}
	return true;
}
int N,M;
vector<vector<pair<int,int> > >DP;
void DfsPrint(const int a,const int b)
{
	if(a==0&&b==0)return;
	const auto &p=DP[a][b];
	switch(p.second)
	{
		case 0:
		{
			DfsPrint(a-1,b-1);
			if(p.first>DP[a-1][b-1].first)printf("%d: %d -> %d\n",a,S[a],b);
		}break;
		case 1:
		{
			DfsPrint(a-1,b);
			printf("%d: 刪掉%d\n",a,S[a]);
		}break;
		case 2:
		{
			DfsPrint(a,b-1);
			printf("%d和%d中間: 插入%d\n",a,a+1,b);
		}break;
		default:assert(0);break;
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	while(ReadInput())
	{
		assert(!S.empty());
		N=(int)S.size()-1,M=S.back();
		DP.resize(N+1);
		for(int i=0;i<=N;i++)DP[i].resize(M+1);
		for(int i=0;i<=N;i++)DP[i][0]=make_pair(i,1);
		for(int i=0;i<=M;i++)DP[0][i]=make_pair(i,2);
		for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)
		{
			DP[i][j]=make_pair(INF,-1);
			getmin(DP[i][j],make_pair(DP[i-1][j-1].first+(S[i]==j?0:1),0));//change
			getmin(DP[i][j],make_pair(DP[i-1][j].first+1,1));//delete
			getmin(DP[i][j],make_pair(DP[i][j-1].first+1,2));//insert
		}
		DfsPrint(N,M);
	}
	return 0;
}
