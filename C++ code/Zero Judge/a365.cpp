#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
int T;
char S[13];
int F[1<<12];
int LINE[12][2]={{0,3},{1,4},{2,3},{3,4},{4,5},{3,7},{4,8},{6,7},{7,8},{8,9},{7,10},{8,11}};
int OPE[12];
int Get(const int s)
{
	if(F[s]!=-1)return F[s];
	vector<int>v;
	for(int i=0;i<12;i++)if(s&(1<<i))v.push_back(Get(s-(1<<i)));
	for(int i=0;i<12;i++)if((s&OPE[i])==OPE[i])v.push_back(Get(s-OPE[i]));
	sort(v.begin(),v.end());
	v.resize(unique(v.begin(),v.end())-v.begin());
	for(int i=0;i<v.size();i++)if(v[i]!=i){return F[s]=i;}
	return F[s]=v.size();
}
int main()
{
	for(int i=0;i<12;i++)OPE[i]=(1<<LINE[i][0])+(1<<LINE[i][1]);
	for(int i=0;i<(1<<12);i++)F[i]=-1;
	F[0]=1;
	scanf("%d",&T);
	while(T--)
	{
		int n=0;
		for(int i=0;i<12;i++)
		{
			static char c;
			do
			{
				scanf("%c",&c);
			}while(c!='1'&&c!='0');
			if(c=='1')n|=1<<i;
		}
		printf("%d",Get(n)==0?0:1);
	}
	puts("");
	return 0;
}
