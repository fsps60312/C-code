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
vector<char>A,B;
int N,M;
vector<vector<pair<int,int> > >DP;
#include<string>
string Get(const vector<char>&s,const int idx)
{
	string ans=s[idx];
	for(int i=idx-1;i>=0&&IsDigit(s[i]);i--)ans=s[i]+ans;
	for(int i=idx+1;i<(int)s.size()&&IsDigit(s[i]);i++)ans=ans+s[i];
	return ans;
}
void DfsPrint(const int a,const int b)
{
	if(a==0&&b==0)return;
	const auto &p=DP[a][b];
	switch(p.second)
	{
		case 0:
		{
			DfsPrint(a-1,b-1);
			if(p.first>DP[a-1][b-1].first)printf("%d: %s -> %s\n",a,Get(A,a).c_str(),Get(B,b).c_str());
		}break;
		case 1:
		{
			DfsPrint(a-1,b);
			printf("%d: %s -> %s\n",a,Get(A[a]);
		}break;
		case 2:
		{
			DfsPrint(a,b-1);
			printf("%d和%d中間: 插入'%c'\n",a,a+1,B[b]);
		}break;
		default:assert(0);break;
	}
}
int main()
{
	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(ReadInput())
	{
		assert(!S.empty());
		N=(int)S.size()-1,M=S.back();
		A.resize(1),B.resize(1);
		for(int i=1;i<=N;i++)
		{
			vector<char>s;
			for(int v=S[i];v;v/=10)s.push_back((char)('0'+v%10));
			if(i>1)A.push_back(' ');
			while(!s.empty())A.push_back(s.back()),s.pop_back();
		}
		for(int i=1;i<=M;i++)
		{
			vector<char>s;
			for(int v=i;v;v/=10)s.push_back((char)('0'+v%10));
			if(i>1)B.push_back(' ');
			while(!s.empty())B.push_back(s.back()),s.pop_back();
		}
		N=(int)A.size()-1,M=(int)B.size()-1;
		DP.resize(N+1);
		for(int i=0;i<=N;i++)DP[i].resize(M+1);
		for(int i=0;i<=N;i++)DP[i][0]=make_pair(i,1);
		for(int i=0;i<=M;i++)DP[0][i]=make_pair(i,2);
		for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)
		{
			DP[i][j]=make_pair(INF,-1);
			getmin(DP[i][j],make_pair(DP[i-1][j-1].first+(A[i]==B[j]?0:1),0));//change
			getmin(DP[i][j],make_pair(DP[i-1][j].first+1,1));//delete
			getmin(DP[i][j],make_pair(DP[i][j-1].first+1,2));//insert
		}
		DfsPrint(N,M);
	}
	return 0;
}
