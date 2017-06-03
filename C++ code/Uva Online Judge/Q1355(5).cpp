#include<cstdio>
#include<vector>
using namespace std;
int P,M,B;
int MAT[4][4][4];
int CNT[100];
int INFE[4][100][3];
int R[4][10],VIS[16];
vector<int> NUM;
void getmin(int &a,int b){if(b<a)a=b;}
void getmax(int &a,int b){if(b>a)a=b;}
bool valid(int *v,int _p,int dep,int vl)//v[3] exist order make it fit rule
{//_p may bingo at last, but not bingo now
	if(dep==0)
	{
		return true;
	}
	for(int i=0;i<vl;i++)
	{
		if(VIS[i])continue;
		VIS[i]++;
		bool canbingo=true,found=false;
		int bingo=_p-1;
		for(int p=_p;p<P;p++)
		{
			int *f=INFE[p][v[i]];
			if(f[0]!=-1)
			{
				if(++R[p][f[0]]==M)bingo=p;
				if(++R[p][f[1]]==M)bingo=p;
				if((f[2]&1)&&++R[p][M*2]==M)bingo=p;
				if((f[2]&2)&&++R[p][M*2+1]==M)bingo=p;
			}
			if(bingo!=p)canbingo=false;
			else if(bingo==p&&!canbingo){found=true;break;}
		}
		if(!found&&valid(v,bingo+1,dep-1,vl))
		{
			VIS[i]--;
			return true;
		}
		VIS[i]--;
		for(int p=_p;p<P;p++)
		{
			int *f=INFE[p][v[i]];
			if(f[0]!=-1)
			{
				--R[p][f[0]];
				--R[p][f[1]];
				if(f[2]&1)--R[p][M*2];
				if(f[2]&2)--R[p][M*2+1];
			}
		}
	}
	return false;
}
int check(int _s)
{
	for(int i=0;i<NUM.size();i++)CNT[NUM[i]]=0;
	for(int i=0;i<P;i++)for(int j=0;j<M*2+2;j++)R[i][j]=0;
	int ans=0;
	int v[16],vl=0;
	for(int p=0,s;p<P;p++,_s/=B)
	{
		s=_s%B;
		for(int i=0;i<M;i++)
		{
			if(s<M)v[i]=MAT[p][s][i];
			else if(s<M*2)v[i]=MAT[p][i][s-M];
			else if(s==M*2)v[i]=MAT[p][i][i];
			else v[i]=MAT[p][i][M-1-i];
			if(!CNT[v[i]]++)
			{
				ans++;
				v[vl++]=v[i];
			}
		}
	}
	if(!valid(v,0,vl,vl))return 2147483647;
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	NUM.reserve(100);
	for(int i=0;i<4;i++)VIS[i]=0;
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
			int v=check(s);
			if(v>=ans)
			{
				continue;
			}
			ans=v;
		}
		printf("%d\n",ans==2147483647?0:ans);
	}
	return 0;
}
