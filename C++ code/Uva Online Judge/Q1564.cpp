#include<cstdio>
#include<map>
#include<string>
#include<vector>
using namespace std;
void termin(char *msg){puts(msg);int a[9];for(int i=0;;i--)a[i]=9,puts(msg);}
int N,M,K,MAT[300][301],TRA[7][7];
char D1[4],D2[4];
map<string,int>DAYS;
int Mod(int a){return (a%7+7)%7;}
void Exchange(int r1,int r2){for(int i=0,v;i<=N;i++)v=MAT[r1][i],MAT[r1][i]=MAT[r2][i],MAT[r2][i]=v;}
void Mul(int r1,int ratio){for(int i=0;i<=N;i++)MAT[r1][i]*=ratio,MAT[r1][i]%=7;}
void Sub(int r1,int r2){for(int i=0;i<=N;i++)MAT[r1][i]=Mod(MAT[r1][i]-MAT[r2][i]);}
int solve()
{
	if(M<N)return -1;
	vector<int>miss;
	for(int i=0;i<M;i++)
	{
		if(i==N)
		{
			while(i<M)
			{
//				for(int j=0;j<N;j++)if(MAT[i][j])termin("should all be zero");
				if(MAT[i][N])return -1;
				i++;
			}
			return 0;
		}
		int j;for(j=i;j<M;j++)if(MAT[j][i])break;
		if(j==M){miss.push_back(i);continue;}
		if(j!=i)Exchange(i,j);
		for(j=0;j<M;j++)
		{
			if(j==i||!MAT[j][i])continue;
			Mul(j,TRA[MAT[j][i]][MAT[i][i]]);
			Sub(j,i);
			if(MAT[j][i])termin("not cleared");
		}
	}
	if(miss.size())
	{
		for(int _i=0;_i<miss.size();_i++)
		{
			int &i=miss[_i];
//			for(int j=0;j<N;j++)if(MAT[i][j])termin("not really miss");
			if(MAT[i][N])return -1;
		}
		return 1;
	}
	return 0;
}
void showMAT(char *msg)
{
	puts(msg);
	for(int i=0;i<M;i++)
	{
		for(int j=0;j<=N;j++)printf(" %d",MAT[i][j]);
		puts("");
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<7;i++)for(int j=0;j<7;j++)TRA[i][(i*j)%7]=j;
	DAYS["SUN"]=0;
	DAYS["MON"]=1;
	DAYS["TUE"]=2;
	DAYS["WED"]=3;
	DAYS["THU"]=4;
	DAYS["FRI"]=5;
	DAYS["SAT"]=6;
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		for(int i=0;i<M;i++)
		{
			scanf("%d%s%s",&K,D1,D2);
			MAT[i][N]=Mod(DAYS[D2]-DAYS[D1]+1);
			for(int j=0;j<N;j++)MAT[i][j]=0;
			for(int j=0,t;j<K;j++)
			{
				scanf("%d",&t);
				MAT[i][--t]++;
			}
		}
//		showMAT("a");
		int result=solve();
//		showMAT("b");
		if(result)printf(result==1?"Multiple solutions.\n":"Inconsistent data.\n");
		else
		{
			for(int i=0,v;i<N;i++)
			{
				if(i)printf(" ");
				v=MAT[i][N]*TRA[MAT[i][i]][1]%7;
				if(v<3)v+=7;
				printf("%d",v);
			}
			puts("");
		}
	}
	return 0;
}
