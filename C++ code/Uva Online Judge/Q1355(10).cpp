#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;
int P,M,S[4][4][4],KASE=0;
int NOW[4][4],CNT[4][10],VIS[100];
vector<int>V;
void Tag(const int &v,const int &d)
{
	if(d==1)
	{
		assert(VIS[v]!=KASE);
		VIS[v]=KASE;
	}
	else if(d==-1)
	{
		assert(VIS[v]==KASE);
		VIS[v]=0;
	}
	else assert(0);
	for(int i=0;i<P;i++)
	{
		for(int j=0;j<M;j++)
		{
			for(int k=0;k<M;k++)
			{
				if(S[i][j][k]!=v)continue;
				CNT[i][j]+=d;
				CNT[i][M+k]+=d;
				if(j==k)CNT[i][M*2]+=d;
				if(j+k==M-1)CNT[i][M*2+1]+=d;
			}
		}
	}
}
bool Legal()
{
	bool fulled=false;
	for(int i=P-1;i>=0;i--)
	{
		bool win=false;
		for(int j=0;j<M*2+2;j++)if(CNT[i][j]>=M){assert(CNT[i][j]==M);win=true;break;}
		if(!win&&fulled)return false;
		if(win)fulled=true;
	}
	return true;
}
vector<int>ANS;
bool Permutate()
{
	bool found=false;
	for(int i=0;i<V.size();i++)
	{
		if(VIS[V[i]]==KASE)continue;
		found=true;
		Tag(V[i],1);
		if(Legal()&&Permutate())
		{
			ANS.push_back(V[i]); 
			return true;
		}
		Tag(V[i],-1);
	}
	if(!found)return true;
	return false;
}
bool Solve()
{
	KASE++;
	ANS.clear();
	return Permutate();
}
int main()
{
	freopen("inn.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	for(int i=0;i<100;i++)VIS[i]=0;
	while(scanf("%d%d",&P,&M)==2&&P&&M)
	{
		for(int i=0;i<P;i++)
		{
			for(int r=0;r<M;r++)
			{
				for(int c=0;c<M;c++)
				{
					scanf("%d",&S[i][r][c]);
				}
			}
		}
		static int kase=1;
		int limit=1;
		for(int i=0;i<P;i++)limit*=M*2+2;
		int ans=INF;
		for(int s=0;s<limit;s++)
		{
			KASE++;
			int ta=0;
			V.clear();
			for(int i=0,t=s;i<P;i++,t/=M*2+2)
			{
				int v=t%(M*2+2);
				for(int j=0;j<M;j++)
				{
					if(v<M)NOW[i][j]=S[i][v][j];
					else if(v<M*2)NOW[i][j]=S[i][j][v-M];
					else if(v==M*2)NOW[i][j]=S[i][j][j];
					else NOW[i][j]=S[i][j][M-1-j];
					if(VIS[NOW[i][j]]!=KASE)
					{
						V.push_back(NOW[i][j]);
						VIS[NOW[i][j]]=KASE,ta++;
					}
				}
			}
			if(ta==6&&Solve())
			{
				for(int i=ANS.size()-1;i>=0;i--)printf(" %d",ANS[i]);puts("");
			}
		}
		printf("%d\n",ans==INF?0:ans);
	}
	return 0;
}
