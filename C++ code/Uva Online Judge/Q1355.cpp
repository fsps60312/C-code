#include<cstdio>
#include<vector>
using namespace std;
int P,M,B;
int MAT[4][4][4];
int CNT[100];
int INFE[4][100][3];
int R[4][10];
vector<int> NUM;
void getmin(int &a,int b){if(b<a)a=b;}
void getmax(int &a,int b){if(b>a)a=b;}
bool invalid(int v,int p)
{
	for(p++;p<P;p++)
	{
		int *f=INFE[p][v];
		if(f[0]==-1)continue;
		if(R[p][f[0]]++||R[p][f[1]]++)return true;
		if((f[2]&1)&&R[p][M*2]++)return true;
		if((f[2]&2)&&R[p][M*2+1]++)return true;
	}
	return false;
}
int check(int _s)
{
	for(int i=0;i<NUM.size();i++)CNT[NUM[i]]=0;
	for(int i=0;i<P;i++)for(int j=0;j<=M*2+1;j++)R[i][j]=0;
	int ans=0;
	for(int p=0,s,v;p<P;p++)
	{
		s=_s%B;
		for(int i=0;i<M;i++)
		{
			if(s<M)v=MAT[p][s][i];
			else if(s<M*2)v=MAT[p][i][s-M];
			else if(s==M*2)v=MAT[p][i][i];
			else v=MAT[p][i][M-1-i];
			if(invalid(v,p))return 2147483647;
			if(!CNT[v]++)ans++;
		}
		_s/=B;
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	NUM.reserve(100);
	while(scanf("%d%d",&P,&M)==2&&(P||M))
	{
		NUM.clear();
		for(int i=0;i<100;i++)CNT[i]=0;
		for(int i=0;i<P;i++)
		{
			for(int r=0;r<M;r++)
				for(int c=0;c<M;c++)
				{
					int &m=MAT[i][r][c];
					scanf("%d",&m);
					if(!CNT[m]++)NUM.push_back(m);
				}
		}
		B=M*2+2;
		int limit=1;
		for(int i=0;i<P;i++)limit*=B;
		for(int p=0;p<P;p++)
		{
			for(int i=0;i<NUM.size();i++)INFE[p][NUM[i]][0]=-1;
			for(int r=0;r<M;r++)
			{
				for(int c=0;c<M;c++)
				{
					int &v=MAT[p][r][c];
					INFE[p][v][0]=r;
					INFE[p][v][1]=M+c;
					INFE[p][v][2]=0;
					if(r==c)INFE[p][v][2]|=1;
					if(r+c==M-1)INFE[p][v][2]|=2;
				}
			}
		}
		int ans=2147483647;
		for(int s=0;s<limit;s++)
		{
			getmin(ans,check(s));
		}
		printf("%d\n",ans==2147483647?0:ans);
	}
	return 0;
}
