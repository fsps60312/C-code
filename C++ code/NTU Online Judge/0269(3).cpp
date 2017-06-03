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
map<unsigned long long,vector<string> >M;
bool Valid(const string &s,const int l,const int r)
{
//	assert(0);
//	puts("check_valid");
	if((int)s.size()!=r-l+1||s[0]!=S[l]||s[r-l]!=S[r])return false;
	static unsigned long long cnt[26];
	for(int c=0;c<26;c++)cnt[c]=0;
	for(const char c:s)++cnt[c-'a'];
	for(int c=0;c<26;c++)if(cnt[c]!=CNT[r+1][c]-CNT[l][c])return false;
//	if(true)printf("(%d,%d,%s),pass\n",l,r,s.c_str());
	return true;
}
bool GetValidString(const int l,const int r,string &ans)
{
	ans.clear();
	unsigned long long hash=0;
	for(int c=0;c<26;c++)hash+=W[c]*(CNT[r+1][c]-CNT[l][c]);
	hash+=W[26]*(S[l]-'a')+W[27]*(S[r]-'a');
//	printf("iash=%llu\n",hash);
	const auto &it=M.find(hash);
	if(it!=M.end())
	{
		for(const string &s:it->second)if(Valid(s,l,r))
		{
			if(ans.empty())ans=s;
			else return false;
		}
	}
//	if(!ans.empty())printf("(%d,%d,%s),pass\n",l,r,ans.c_str());
	return true;
}
string DP[1000],ANS[1000];
bool STATE[1000];
int N,L;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		for(int i=0;i<28;i++)W[i]=Rand();
		scanf("%s%d",S,&N);
		L=-1;while(S[++L]);
		M.clear();
		for(int i=0;i<N;i++)
		{
			static char str[101];scanf("%s",str);
//			printf("str=%s\n",str);
			unsigned long long hash=0;
			int n=-1;while(str[++n])assert('a'<=str[n]&&str[n]<='z'),hash+=W[str[n]-'a'];
			hash+=W[26]*(str[0]-'a')+W[27]*(str[n-1]-'a');
//			printf("hash=%llu\n",hash);
			M[hash].push_back(str);
		}
		for(int c=0;c<26;c++)CNT[0][c]=0;
		for(int i=0;i<L;i++)
		{
			for(int c=0;c<26;c++)CNT[i+1][c]=CNT[i][c];
			++CNT[i+1][S[i]-'a'];
		}
		for(int i=0;i<L;i++)STATE[i]=GetValidString(0,i,DP[i]),ANS[i]=DP[i];
		for(int r=1;r<L;r++)
		{
			for(int l=1;l<=r&&(DP[r].empty()||STATE[r]);l++)if(!DP[l-1].empty())
			{
				string s;
				const bool state=GetValidString(l,r,s)&&STATE[l-1];
				if(!s.empty())
				{
					if(!DP[r].empty()){STATE[r]=false;break;}
					else DP[r]=DP[l-1]+s,ANS[r]=ANS[l-1]+" "+s,STATE[r]=state;
				}
			}
		}
		if(DP[L-1].empty())puts("impossible");
		else if(!STATE[L-1])puts("ambiguous");
		else puts(ANS[L-1].c_str());
	}
	return 0;
}
