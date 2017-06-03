#include<cstdio>
#include<map>
using namespace std;
void termin(){int a[9];for(int i=0;;i--)a[i]=9;}
int N,CN,L[4],CNT[26];
char S[501],IDX[26];
struct Dp
{
	vector<int> s;
	int dep;
	bool operator<(Dp a)const{if(s!=a.s)return s<a.s;return dep<a.dep;}
	bool operator==(Dp a)const{return s==a.s&&dep==a.dep;}
};
map<Dp,bool> DP;
bool check1(int n)
{
	int t=0;
	for(int i=0;i<N;i++)
	{
		t+=L[i];
		if(t>=n)return true;
		t--;
	}
	return false;
}
bool check2(int n)
{
	int t=1;
	for(int i=0;i<N;i++)t+=L[i]-1;
	for(int i=0;i<26;i++)CNT[i]=0;
	for(int i=0;i<n;i++)
	{
		int &c=CNT[S[i]-'a'];
		if(!c)
		{
			t--;
			if(t<0)return false;
		}
		c++;
	}
	return true;
}
bool CanSplit(Dp d)
{
	if(DP.find(d)!=DP.end())return DP[d];
	int l=L[d.dep];
	for(int i=0;i<)
}
bool solve()
{
	int n=-1;while(S[++n]);
	if(n>256)return false;
	if(check1(n))return true;
	if(!check2(n))return false;
	CN=0;
	for(int i=0;i<26;i++)
	{
		if(CNT[i])
		{
			IDX[i]=CN++;
		}
	}
	vector<int> s;
	for(int i=0;i<n;i++)s.push_back(IDX[S[i]-'a']);
	DP.clear();
	return CanSplit((Dp)P{s,N-1});
}
int main()
{
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)
		{
			scanf("%d",&L[i]);
		}
		scanf("%s",S);
		printf(solve()?"Yes\n":"No\n");
	}
	return 0;
}
