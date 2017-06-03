#include<cstdio>
#include<vector>
#include<string>
#include<algorithm>
#include<stack>
#include<cassert>
using namespace std;
int N;
vector<string>S;
bool CmpWord(const string &a,const string &b)
{
	for(int i=0;i<a.size()&&i<b.size();i++)if(a[i]!=b[i])return a[i]<b[i];
	return a.size()<b.size();
}
vector<char>NOW,ANS;
int Same(const char *a,const char *b,const int mx)
{
	int ans=0;
	while(ans<mx&&a[ans]==b[ans])ans++;
	return ans;
}
void Process(const string &s)
{
	int r=Same(&s[0],&NOW[0],min(s.size(),NOW.size()));
	while(NOW.size()>r)NOW.pop_back(),ANS.push_back('-');
	for(int i=NOW.size();i<s.size();i++)NOW.push_back(s[i]),ANS.push_back(s[i]);
	ANS.push_back('P');
}
stack<int>STK;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		static char tmp[21];
		scanf("%s",tmp);
		S.push_back(tmp);
//		for(int j=0;S[i][j];j++)printf(" %d",S[i][j]);puts("");
	}
	sort(S.begin(),S.end(),CmpWord);
	int u=-1,mxlen=0;
	for(int i=0;i<N;i++)if(S[i].size()>mxlen)mxlen=S[i].size(),u=i;
	assert(u!=-1);
	STK.push(u);
	int l=u,r=u;
	while(1)
	{
		int ls=(l==0?0:Same(&S[l-1][0],&S[l][0],min(S[l-1].size(),S[l].size())));
		int rs=(r+1==N?0:Same(&S[r][0],&S[r+1][0],min(S[r].size(),S[r+1].size())));
		if(ls==0&&rs==0)
		{
			for(int i=0;i<l;i++)STK.push(i);
			for(int i=r+1;i<N;i++)STK.push(i);
			break;
		}
		if(ls>rs)STK.push(--l);
		else STK.push(++r);
	}
//	puts("pass");
	NOW.clear(),ANS.clear();
	for(int i=0;i<N;i++)Process(S[STK.top()]),STK.pop();//,printf("%d\n",i);
	assert(STK.empty());
	printf("%d\n",ANS.size());
	for(int i=0;i<ANS.size();i++)printf("%c\n",ANS[i]);
	return 0;
}
