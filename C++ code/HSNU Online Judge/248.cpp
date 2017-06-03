#include<cstdio>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
int N;
vector<string>S;
bool CmpWord(const string &a,const string &b)
{
	for(int i=0;i<a.size()&&i<b.size();i++)if(a[i]!=b[i])return a[i]<b[i];
	return a.size()<b.size();
}
vector<char>NOW,ANS;
void Process(const string &s)
{
	int r=0;
	while(r<s.size()&&r<NOW.size()&&s[r]==NOW[r])r++;
	while(NOW.size()>r)NOW.pop_back(),ANS.push_back('-');
	for(int i=NOW.size();i<s.size();i++)NOW.push_back(s[i]),ANS.push_back(s[i]);
	ANS.push_back('P');
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		static char tmp[21];
		scanf("%s",tmp);
		S.push_back(tmp);
	}
	sort(S.begin(),S.end(),CmpWord);
	NOW.clear(),ANS.clear();
	for(int i=0;i<N;i++)Process(S[i]);
	printf("%d\n",ANS.size());
	for(int i=0;i<ANS.size();i++)printf("%c\n",ANS[i]);
	return 0;
}
