#include<cstdio>
#include<vector>
using namespace std;
int T,L,R;
vector<int>S;
bool AllSame(const vector<int>&a)
{
	for(int i=1;i<a.size();i++)if(a[i]!=a[0])return false;
	return true;
}
void Solve(vector<int>&s,const int len)
{
	if(AllSame(s)){while(s.size()<len)s.push_back(s[0]);return;}
	vector<int>nxts;
	for(int i=1;i<s.size();i++)nxts.push_back(s[i]-s[i-1]);
	Solve(nxts,len-1);
	for(int i=s.size();i<len;i++)s.push_back(s[i-1]+nxts[i-1]);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&L,&R);
		S.clear();
		for(int i=0,v;i<L;i++)scanf("%d",&v),S.push_back(v);
		Solve(S,L+R);
		for(int i=L;i<L+R;i++)
		{
			if(i>L)putchar(' ');
			printf("%d",S[i]);
		}
		puts("");
	}
	return 0;
}
