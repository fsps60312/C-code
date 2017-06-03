#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
char S[20000];
int N,SA[20000];
void BuildSA()
{
	static int tmp[3][20000];
	int *x=tmp[0],*y=tmp[1],*c=tmp[2],p='z'+1;
	for(int i=0;i<p;i++)c[i]=0;
	for(int i=0;i<N;i++)c[x[i]=S[i]]++;
	for(int i=1;i<p;i++)c[i]+=c[i-1];
	for(int i=N-1;i>=0;i--)SA[--c[x[i]]]=i;
	for(int move=1;move<N;move<<=1)
	{
		int idx=0;
		for(int i=N-move;i<N;i++)y[idx++]=i;
		for(int i=0;i<N;i++)if(SA[i]>=move)y[idx++]=SA[i]-move;
		for(int i=0;i<p;i++)c[i]=0;
		for(int i=0;i<N;i++)c[x[i]]++;
		for(int i=1;i<p;i++)c[i]+=c[i-1];
		for(int i=N-1;i>=0;i--)SA[--c[x[y[i]]]]=y[i];
		swap(x,y);
		p=0;x[SA[0]]=p++;
		for(int i=1;i<N;i++)
		{
			if(y[SA[i]]!=y[SA[i-1]])x[SA[i]]=p++;
			else if((SA[i]+move<N)!=(SA[i-1]+move<N))x[SA[i]]=p++;
			else assert(SA[i]+move<N&&SA[i-1]+move<N),x[SA[i]]=(y[SA[i]+move]==y[SA[i-1]+move]?p-1:p++);
		}
		if(p==N)break;
	}
}
int RANK[20000],HEIGHT[20000];
void BuildHEIGHT()
{
	for(int i=0;i<N;i++)RANK[SA[i]]=i;
	for(int i=0,ans=0;i<N;i++)
	{
		if(ans)ans--;
		if(RANK[i]==0){HEIGHT[0]=0;continue;}
		int j=SA[RANK[i]-1];
		while(max(i,j)+ans<N&&S[i+ans]==S[j+ans])ans++;
		HEIGHT[RANK[i]]=ans;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	static int casecount;assert(fgets(S,INF,stdin)&&sscanf(S,"%d",&casecount)==1);
	while(casecount--)
	{
		assert(fgets(S,INF,stdin));
		N=0;while(S[++N]&&S[N]!='\n')assert(S[N]>='a'&&S[N]<='z');
		for(int i=0;i<N;i++)S[N+i]=S[i];
//		BuildSA();
//		BuildHEIGHT();
//		for(int i=0;i<N;i++)printf(" %d",SA[i]);puts("");
//		for(int i=0;i<N;i++)printf(" %d",HEIGHT[i]);puts("");
		N*=2;
		BuildSA();
		BuildHEIGHT();
		for(int i=0;;i++)
		{
			if(SA[i]<N/2)
			{
				int ansrank=i,ans=SA[i];
				while(ansrank+1<N&&HEIGHT[ansrank+1]>=N/2)getmin(ans,SA[++ansrank]);
				printf("%d\n",ans+1);
				break;
			}
		}
	}
	assert(scanf("%d",&casecount)!=1);
	return 0;
}
