#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;
int P,M,S[4][4][4],KASE=0;
int NOW[4][4],CNT[4][10],VIS[100];
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
bool Legal(const int &idx)
{
	bool fulled=false;
	for(int i=P-1;i>=idx;i--)
	{
		bool win=false;
		for(int j=0;j<M*2+2;j++)if(CNT[i][j]>=M){assert(CNT[i][j]==M);win=true;break;}
		if(!win&&fulled)return false;
		if(win)fulled=true;
	}
	return true;
}
vector<int>TMP[4];
int NOWREACH;
bool PRINTANS;
bool Permutate(const int idx)
{
	bool found=false;
	for(int i=0;i<M;i++)
	{
		if(VIS[NOW[idx][i]]==KASE)continue;
		found=true;
		Tag(NOW[idx][i],1);
		if(Legal(idx)&&Permutate(idx))
		{
//if(PRINTANS)TMP[idx].push_back(NOW[idx][i]);
			return true;
		}
		Tag(NOW[idx][i],-1);
	}
	if(!found)return true;
	return false;
}
bool Solve(const int &idx)
{
if(PRINTANS)printf("idx=%d\n",idx);
	if(idx==P)return true;
	if(!Permutate(idx))return false;
	return Solve(idx+1);
}
bool Solve()
{
	for(int i=0;i<P;i++)for(int j=0;j<M*2+2;j++)CNT[i][j]=0;
	KASE++;
//for(int i=0;i<P;i++)TMP[i].clear();
	bool ans=Solve(0);
//if(ans)
//{
//vector<int>aaa;
//for(int i=0;i<P;i++)
//{
//for(int j=(int)TMP[i].size()-1;j>=0;j--)aaa.push_back(TMP[i][j]);
//}
//if(aaa.size()<NOWREACH)
//{
//NOWREACH=aaa.size();
//for(int i=0;i<aaa.size();i++)printf(" %d",aaa[i]);
//puts("");
//}
//}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	for(int i=0;i<100;i++)VIS[i]=0;
	while(scanf("%d%d",&P,&M)==2&&P&&M)
	{
//NOWREACH=INF;
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
		int limit=1;
		for(int i=0;i<P;i++)limit*=M*2+2;
		int ans=INF;
		for(int s=0;s<limit;s++)
		{
			KASE++;
			int ta=0;
			for(int i=0,t=s;i<P;i++,t/=M*2+2)
			{
				int v=t%(M*2+2);
				for(int j=0;j<M;j++)
				{
					if(v<M)NOW[i][j]=S[i][v][j];
					else if(v<M*2)NOW[i][j]=S[i][j][v-M];
					else if(v==M*2)NOW[i][j]=S[i][j][j];
					else NOW[i][j]=S[i][j][M-1-j];
					if(VIS[NOW[i][j]]!=KASE)VIS[NOW[i][j]]=KASE,ta++;
				}
			}
			if(ta==5)
			{
				PRINTANS=true;
				for(int i=0;i<P;i++)for(int j=0;j<M;j++)printf(" %d",NOW[i][j]);puts("");
			}
			if(Solve())ans=min(ans,ta);
			if(ta==5)PRINTANS=false;
		}
		printf("%d\n",ans==INF?0:ans);
	}
	return 0;
}
