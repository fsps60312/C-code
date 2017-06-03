#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int N;
vector<char>S;
bool Input()
{
	static char tmp[100001];
	if(scanf("%s",tmp)!=1)return false;
	S.clear();
	S.push_back('0');
	for(int i=0;tmp[i];i++)S.push_back(tmp[i]),S.push_back('0'),assert(i<100000);
	N=S.size();
	return true;
}
vector<int>DP;
int main()
{
//	freopen("in.txt","r",stdin);
	while(Input())
	{
		DP.resize(N);
		DP[0]=0;
		for(int i=1,idx=0;i<N;i++)
		{
			if(idx+DP[idx]>i)DP[i]=min(DP[idx-(i-idx)],idx+DP[idx]-i);
			else DP[i]=0;
			while(i-DP[i]-1>=0&&i+DP[i]+1<N&&S[i-DP[i]-1]==S[i+DP[i]+1])DP[i]++;
			if(i+DP[i]>idx+DP[idx])idx=i;
		}
		int ans=-1;
		for(int i=0;i<N;i++)if(i+DP[i]==N-1){ans=i;break;}
		assert(ans!=-1);
		for(int i=1;i<N;i+=2)putchar(S[i]);
		for(int i=ans-DP[ans]-1;i>=0;i-=2)putchar(S[i]);
		puts("");
	}
	return 0;
}
