#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
int T;
char S[13];
bool F[1<<12],VIS[1<<12];
int LINE[12][2]={{0,3},{1,4},{2,3},{3,4},{4,5},{3,7},{4,8},{6,7},{7,8},{8,9},{7,10},{8,11}};
int OPE[24];
//bool Get(const int s)
//{
//	if(!VIS[s])return F[s];
//	vector<int>v;
//	for(int i=0;i<12;i++)if(s&(1<<i))v.push_back(Get(s-(1<<i)));
//	for(int i=0;i<12;i++)if((s&OPE[i])==OPE[i])v.push_back(Get(s-OPE[i]));
//	sort(v.begin(),v.end());
//	v.resize(unique(v.begin(),v.end())-v.begin());
//	for(int i=0;i<v.size();i++)if(v[i]!=i){return F[s]=i;}
//	return F[s]=v.size();
//}
int main()
{
	for(int i=0;i<12;i++)OPE[i]=(1<<i),OPE[i+12]=(1<<LINE[i][0])+(1<<LINE[i][1]);
	for(int i=0;i<(1<<12);i++)F[i]=VIS[i]=false;
	queue<int>q;
	q.push(0);
	F[0]=true;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		if(VIS[u])continue;
		VIS[u]=true;
		const bool &sg=F[u];
		for(int i=0;i<24;i++)if((u&OPE[i])==0)
		{
			const int nxt=u+OPE[i];
			if(!sg)F[nxt]=true;
			q.push(nxt);
		}
	}
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
		printf("%d",F[n]?1:0);
	}
	puts("");
	return 0;
}
