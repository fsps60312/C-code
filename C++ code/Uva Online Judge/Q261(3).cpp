#include<cstdio>
#include<algorithm>
#include<cassert>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int N;
char S[101];
int SA[100],TMP[3][256];
void BuildSA()
{
	int *x=TMP[0],*y=TMP[1],*c=TMP[2],p=256;
	for(int i=0;i<p;i++)c[i]=0;
	for(int i=0;i<N;i++)c[x[i]=S[i]]++;
	for(int i=1;i<p;i++)c[i]+=c[i-1];
	for(int i=N-1;i>=0;i--)SA[--c[x[i]]]=i;
	for(int move=1;move<=N;move<<=1)//rank i, loc SA[i]
	{
		int idx=0;
		for(int i=N-move;i<N;i++)y[idx++]=i;
		for(int i=0;i<N;i++)if(SA[i]>=move)y[idx++]=SA[i]-move;
		for(int i=0;i<p;i++)c[i]=0;
		for(int i=0;i<N;i++)c[x[i]]++;
		for(int i=1;i<p;i++)c[i]+=c[i-1];
		for(int i=N-1;i>=0;i--)SA[--c[x[y[i]]]]=y[i];
		swap(x,y);
		p=0;
		x[SA[0]]=p++;
		for(int i=1;i<N;i++)
		{
			if(y[SA[i]]!=y[SA[i-1]])x[SA[i]]=p++;
			else if((SA[i]+move<N)!=(SA[i-1]+move<N))x[SA[i]]=p++;
			else
			{
				assert(SA[i]+move<N&&SA[i-1]+move<N);
				x[SA[i]]=(y[SA[i]+move]==y[SA[i-1]+move]?p-1:p++);
			}
		}
		if(p==N)break;
	}
}
int RANK[100],HEIGHT[100];
void BuildHEIGHT()
{
	for(int i=0;i<N;i++)RANK[SA[i]]=i;
	for(int i=0,now=0;i<N;i++)
	{
		if(now)now--;
		if(RANK[i]==0){HEIGHT[0]=0;continue;}
		int b=SA[RANK[i]-1];
		while(S[i+now]==S[b+now])now++;
		HEIGHT[RANK[i]]=now;
	}
}
int IDX[100],VIS[100];
int Solve()
{
	int ans=INF;
	for(int len=1;len*2<=N;len++)
	{
		int idx=0;IDX[SA[0]]=idx++;
		for(int i=1;i<N;i++)IDX[SA[i]]=(HEIGHT[i]>=len?idx-1:idx++);
		static int kase=0;kase++;
		for(int i=0,cnt=0;i+len<=N;i++)if(VIS[IDX[i]]!=kase)
		{
			VIS[IDX[i]]=kase,cnt++;
			if(cnt>len+1){getmin(ans,i+len);break;}
		}
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<100;i++)VIS[i]=0;
	while(fgets(S,INF,stdin))
	{
		N=-1;while(S[++N])if(S[N]=='\n'){S[N]='\0';break;}
		BuildSA();
		BuildHEIGHT();
		int ans=Solve();
		if(ans==INF)puts("YES");
		else printf("NO:%d\n",ans);
	}
	return 0;
}
