#include<cstdio>
#include<algorithm>
#include<vector>
#include<cassert>
using namespace std;
int N,S[2000],LOC[2000],CUR;
vector<int>ANS;
void Swap(int i,int j){swap(LOC[S[i]],LOC[S[j]]),swap(S[i],S[j]);}
void OperateA(){ANS.push_back(0);CUR--;if(CUR<0)CUR+=N;}
void OperateB(){ANS.push_back(1);Swap((CUR+1)%N,(CUR+2)%N),Swap(CUR,(CUR+1)%N);}
void MoveCUR(const int target){while(CUR!=target)OperateA();}
int InvPairs(){int ans=0;for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)if(S[i]>S[j])ans++;return ans;}
bool Solve()
{
	if((N-1)%2==0&&InvPairs()%2==1)return false;
	CUR=0,ANS.clear();
	int basis=0;
	if((N-1)%2==1&&InvPairs()%2==1){OperateA();basis=N-1;}
	for(int v=0;v+2<N;v++)
	{
		const int target=(basis+v)%N;
		while(LOC[v]!=target)
		{
			if((target+1)%N==LOC[v])MoveCUR(target),OperateB(),OperateB();
			else MoveCUR(((LOC[v]-2)%N+N)%N),OperateB();
		}
//		for(int i=0;i<N;i++)printf("%d ",S[i]);puts("");
//		for(int i=0;i<N;i++)printf("%d ",LOC[i]);puts("");puts("");
	}
	for(int v=0;v<N;v++)assert(LOC[v]==(LOC[0]+v)%N),assert(S[LOC[v]]==v);
	MoveCUR(LOC[0]);
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]),LOC[--S[i]]=i;
		if(!Solve())puts("NIE DA SIE");
		else
		{
			vector<int>ansa,ansb;
			for(int i=0;i<(int)ANS.size();)
			{
				int cnt=0;
				while(i+cnt<(int)ANS.size()&&ANS[i+cnt]==ANS[i])cnt++;
				ansa.push_back(cnt),ansb.push_back(ANS[i]);
				i+=cnt;
			}
			assert((int)ansa.size()<=N*N);
			printf("%d\n",(int)ansa.size());
			for(int i=0;i<(int)ansa.size();i++)
			{
				if(i)putchar(' ');
				printf("%d%c",ansa[i],'a'+ansb[i]);
			}
			puts("");
		}
		break;
	}
	return 0;
}
