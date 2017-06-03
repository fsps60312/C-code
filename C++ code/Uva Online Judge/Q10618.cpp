#include<cstdio>
const int INF=1<<30;
const int ENE[4]={1,3,5,7};
char STR[71];
int N,DP[71][4][4][4];//step, left foot, right foot, pre-action
void termin(){int a[10];for(int i=0;;i--)a[i]=100;}
bool getmin(int &a,int b){if(b<a){a=b;return true;}return false;}
int can_move_left(int lf,int rf,int to)
{
	if(to==rf||rf==3)return -1;
	if(to==lf)return 0;
	if((to&1)==(lf&1))return 3;
	return 2;
}
int can_move_right(int lf,int rf,int to)
{
	if(to==lf||lf==1)return -1;
	if(to==rf)return 0;
	if((to&1)==(rf&1))return 3;
	return 2;
}
struct Pre
{
	int d,lf,rf,pa;
}PRE[71][4][4][4];
void dfs_print(Pre p)
{
	if(p.d==0)return;
	Pre &q=PRE[p.d][p.lf][p.rf][p.pa];
	dfs_print(q);
	if(p.lf==q.lf&&p.rf==q.rf)
	{
		int i=-1;
		switch(STR[q.d])
		{
			case'U':i=0;break;
			case'R':i=1;break;
			case'D':i=2;break;
			case'L':i=3;break;
			default:termin;break;
		}
		if(i==-1)printf(".");
		else
		{
			if(p.lf==i)printf("L");
			else printf("R");
		}
	}
	else if(p.lf==q.lf)printf("R");
	else printf("L");
}
int main()
{
	//freopen("in.txt","r",stdin); 
	while(scanf("%s",STR)==1&&STR[0]!='#')
	{
		N=-1;while(STR[++N]);
		for(int i=0;i<=N;i++)
		{
			for(int j=0;j<4;j++)
			{
				for(int k=0;k<4;k++)
				{
					for(int l=0;l<4;l++)
					{
						DP[i][j][k][l]=INF;
					}
				}
			}
		}
		DP[0][3][1][0]=0;
		for(int d=0;d<N;d++)
		{
//			int tmp=INF;
			for(int lf=0;lf<4;lf++)
			{
				for(int rf=0;rf<4;rf++)
				{
					for(int pa=0;pa<4;pa++)
					{
						int &dp=DP[d][lf][rf][pa];
						if(dp==INF)continue;
//						getmin(tmp,dp);
						if(STR[d]=='.')
						{
							for(int i=0;i<4;i++)
							{
								int j=can_move_left(lf,rf,i);
								if(j!=-1&&getmin(DP[d+1][i][rf][j],dp+(j?ENE[pa]:0)))
								{
									PRE[d+1][i][rf][j]=(Pre){d,lf,rf,pa};
								}
								j=can_move_right(lf,rf,i);
								if(j!=-1&&getmin(DP[d+1][lf][i][j],dp+(j?ENE[pa]:0)))
								{
									PRE[d+1][lf][i][j]=(Pre){d,lf,rf,pa};
								}
							}
						}
						else
						{
							int i;
							switch(STR[d])
							{
								case 'U':i=0;break;
								case 'R':i=1;break;
								case 'D':i=2;break;
								case 'L':i=3;break;
								default:termin();break;
							}
							int j=can_move_left(lf,rf,i);
							if(j!=-1)
							{
								if(!j)j++;
								if(getmin(DP[d+1][i][rf][j],dp+ENE[pa]))
								{
									PRE[d+1][i][rf][j]=(Pre){d,lf,rf,pa};
								}
							}
							j=can_move_right(lf,rf,i);
							if(j!=-1)
							{
								if(!j)j++;
								if(getmin(DP[d+1][lf][i][j],dp+ENE[pa]))
								{
									PRE[d+1][lf][i][j]=(Pre){d,lf,rf,pa};
								}
							}
						}
					}
				}
			}
//			printf("step %d : %d\n",d,tmp);
		}
		int ans=INF;
		Pre pre;
		for(int lf=0;lf<4;lf++)
		{
			for(int rf=0;rf<4;rf++)
			{
				for(int pa=0;pa<4;pa++)
				{
					int &dp=DP[N][lf][rf][pa];
					if(dp==INF)continue;
					if(getmin(ans,dp))pre=PRE[N][lf][rf][pa];
				}
			}
		}
		//printf("energy=%d\n",ans);
		dfs_print(pre);
		printf("\n");
	}
	return 0;
}
