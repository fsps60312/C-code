#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int N,S[100000];
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&S[i]);
	vector<int>s;
	for(int i=0;i<=30;i++)
	{
		int now=(1<<i)-1;
		vector<int>ts;
		for(int j=0;j<N;j++)if(S[j]&(1<<i))now&=S[j],ts.push_back(S[j]);
		if(now==0)s.clear(),s.swap(ts);
	}
	printf("%d\n",(s.size()));
	sort(s.begin(),s.end());
	for(int i=0;i<(int)s.size();i++)
	{
		if(i)putchar(' ');
		printf("%d",s[i]);
	}
	puts("");
	return 0;
}
