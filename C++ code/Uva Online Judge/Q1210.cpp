#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int N,ANS[10001];
int main()
{
	for(int i=2;i<=10000;i++)ANS[i]=0;
	vector<int>p=vector<int>{0,2,3};
	for(int i=3,j;;i++)
	{
		p.push_back(p[i-1]);
		do
		{
			p[i]+=2;
			for(j=1;p[j]*p[j]<=p[i]&&p[i]%p[j];j++);
		}while(p[i]%p[j]==0);
		if(p[i]>10000){p.pop_back();break;}
	}
	for(int i=1;i<(int)p.size();i++)p[i]+=p[i-1];
	for(int i=0;i<(int)p.size();i++)for(int j=i+1;p[j]-p[i]<=10000&&j<(int)p.size();j++)ANS[p[j]-p[i]]++;
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		printf("%d\n",ANS[N]);
	}
	return 0;
}
