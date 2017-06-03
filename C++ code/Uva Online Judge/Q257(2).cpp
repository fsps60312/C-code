#include<cstdio>
#include<set>
#include<string>
using namespace std;
char S[256];
int N;
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
	for(int i=1;i+1<N;i++)if(S[i-1]==S[i+1])s.insert(SubStr(i-1,i+1));
	for(int i=1;i+2<N;i++)if(S[i]==S[i+1]&&S[i-1]==S[i+2])s.insert(SubStr(i-1,i+2));
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
	while(scanf("%s",S)==1)if(IsPalinword())puts(S);
	return 0;
}
