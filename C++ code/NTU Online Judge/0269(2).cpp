#include<cstdio>
#include<cassert>
#include<vector>
#include<string>
#include<map>
typedef long long LL;
using namespace std;
unsigned long long Rand()
{
	static unsigned long long seed=20150711;
	(seed*=0xdefaced)+=114741;
	return seed+=seed>>20;
}
char S[1001];
unsigned long long W[28],CNT[1001][26];
int N;
map<unsigned long long,vector<string> >M;
string DP[1000][1000];
bool Valid(const string &s,const int l,const int r)
{
	if((int)s.size()!=r-l+1||s[0]!=S[l]||s[s.size()-1]!=S[r])return false;
	static int cnt[26];
	for(int c=0;c<26;c++)cnt[c]=0;
	for(const char c:s)++cnt[c-'a'];
	assert(0);
}
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		for(int i=0;i<28;i++)W[i]=Rand();
		scanf("%s%d",S,&N);
		M.clear();
		for(int i=0;i<N;i++)
		{
			static char str[101];scanf("%s",str);
			unsigned long long hash=0;
			int n=-1;while(str[++n])hash+=W[str[n]-'a'];
			hash+=W[26]*(str[0]-'a')+W[27]*(str[n-1]-'a');
			M[hash].push_back(str);
		}
		for(int c=0;c<26;c++)CNT[0][c]=0;
		for(int i=0;i<N;i++)
		{
			for(int c=0;c<26;c++)CNT[i+1][c]=CNT[i][c];
			++CNT[i+1][S[i]-'a'];
		}
		for(int l=0;l<1000;l++)for(int r=l;r<1000;r++)
		{
			unsigned long long hash=0;
			for(int c=0;c<26;c++)hash+=W[c]*(CNT[r+1]-CNT[l]);
			hash+=W[26]*(S[l]-'a')+W[27]*(S[r]-'a');
			const auto &it=M.find(hash);
			string &ans=DP[l][r];
			ans.clear();
			if(it!=M.end())
			{
				for(const string &s:it->second)if(Valid(s,l,r)){ans=s;break;}
			}
		}
	}
	return 0;
}
