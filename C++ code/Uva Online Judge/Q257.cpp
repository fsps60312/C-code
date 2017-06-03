#include<cstdio>
#include<set>
#include<string>
using namespace std;
char S[256];
int N;
bool IsPalindrome(const int l,const int r)
{
	for(int i=0;l+i<r-i;i++)if(S[l+i]!=S[r-i])return false;
	return true;
}
string SubStr(const int l,const int r)
{
	string ans;
	for(int i=l;i<=r;i++)ans.push_back(S[i]);
	return ans;
}
bool IsPalinword()
{
	N=-1;while(S[++N]);
	set<string>s;
	for(int i=1,len;i+1<N;i++)if(S[i-1]==S[i+1])
	{
		for(len=1;i-len>=0&&i+len<N&&S[i-len]==S[i+len];len++)
			if(IsPalindrome(i-len,i+len))s.insert(SubStr(i-len,i+len));len--;
	}
	for(int i=1,len;i+2<N;i++)if(S[i]==S[i+1]&&S[i-1]==S[i+2])
	{
		for(len=1;i-len>=0&&i+1+len<N&&S[i-len]==S[i+1+len];len++)
			if(IsPalindrome(i-len,i+1+len))s.insert(SubStr(i-len,i+1+len));
	}
	for(const string &s1:s)
	{
		for(const string &s2:s)
		{
			if(s1.find(s2)==string::npos&&s2.find(s1)==string::npos)return true;
		}
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	set<string>vis;
	while(scanf("%s",S)==1)if(IsPalinword()&&vis.find(S)==vis.end())puts(S),vis.insert(S);
	return 0;
}
