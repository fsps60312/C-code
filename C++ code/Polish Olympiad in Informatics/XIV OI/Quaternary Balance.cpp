#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
const int INF=2147483647,MOD=1000000000;
template<class T>inline bool getmin(T&a,const T&b){return b<a?(a=b,true):false;}
vector<int>S;
void Carry()
{
	for(int i=0;i<(int)S.size();i++)if(S[i]>=4)
	{
		if(i+1==(int)S.size())S.push_back(0);
		S[i+1]+=S[i]/4;
		S[i]%=4;
	}
}
void Mul(const int val)
{
	for(int i=0;i<(int)S.size();i++)S[i]*=val;
	Carry();
}
void Add(const int val)
{
	assert(!S.empty());
	S[0]+=val;
	Carry();
}
bool ReadInput()
{
	static char str[1002];
	if(scanf("%s",str)!=1)return false;
	S.clear(),S.push_back(0);
	for(int i=0;str[i];i++)
	{
		assert('0'<=str[i]&&str[i]<='9');
		Mul(10),Add(str[i]-'0');
	}
//	int cur=0;
//	while(S[cur]==0)++cur;
//	rotate(S.begin(),S.begin()+cur,S.end());
//	for(int i=0;i<cur;i++)S.pop_back();
	return true;
}
int DP[2000][5],MN[2000][5];
void Update(const int i,const int pre,const int now,const int val)
{
	if(getmin(MN[i][now],MN[i-1][pre]+val))DP[i][now]=0;
	if(MN[i][now]==MN[i-1][pre]+val)(DP[i][now]+=DP[i-1][pre])%=MOD;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(ReadInput())
	{
		for(int i=0;i<=(int)S.size();i++)for(int j=0;j<5;j++)DP[i][j]=0,MN[i][j]=INF;
		for(int i=0;i<=4;i++)DP[0][i]=1,MN[0][i]=abs(S[0]-i);
		for(int i=1;i<=(int)S.size();i++)
		{
			Update(i,0,0,S[i]);
			Update(i,0,4,4-S[i]);
			Update(i,4,0,S[i]+1);
			Update(i,4,4,4-(S[i]+1));
//			printf("(%d,%d)->(%d,%d)\n",DP[i-1][0],DP[i-1][4],DP[i][0],DP[i][4]);
		}
		printf("%d\n",DP[S.size()][0]); 
	}
	return 0;
}
