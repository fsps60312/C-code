#include<cstdio>
#include<cassert>
#include<utility>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
void getmax(int &a,const int b){if(b>a)a=b;}
int N,M;
char S[1000002];
int SUM[1000001];
pair<int,int>ANS[2000001];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%s",&N,&M,S+1);
	int l=N+1,r=0;
	for(int i=1;i<=N;i++)
	{
		SUM[i]=SUM[i-1]+(S[i]=='W'?1:2);
		if(S[i]=='W')getmin(l,i),getmax(r,i);
	}
	for(int i=1;i<=SUM[N];i++)ANS[i]=make_pair(-1,-1);
	if(r>0)
	{
		for(int i=1;i<=r-1;i++)ANS[SUM[r-1]-SUM[i-1]]=make_pair(i,r-1);
		for(int i=1;i<=r;i++)ANS[SUM[r]-SUM[i-1]]=make_pair(i,r);
		for(int i=l;i<=N;i++)ANS[SUM[i]-SUM[l-1]]=make_pair(l,i);
		for(int i=l+1;i<=N;i++)ANS[SUM[i]-SUM[l]]=make_pair(l+1,i);
	}
	for(int i=1;i<=N;i++)ANS[SUM[i]]=make_pair(1,i);
	for(int i=0,v;i<M;i++)
	{
		scanf("%d",&v);
		pair<int,int>ans=(v>SUM[N]?make_pair(-1,-1):ANS[v]);
		if(ans.first==-1)puts("NIE");
		else printf("%d %d\n",ans.first,ans.second);
	}
	return 0;
}
