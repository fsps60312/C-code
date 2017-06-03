#include<cstdio>
void termin(){int a[10];for(int i=0;;i--)a[i]=100;}
const int INF=1<<30;
bool getmin(int &a,int b){if(b<a){a=b;return true;}return false;}
int ANS[1<<15],PRE[1<<15],SN;
bool MAT[15][15];
char S1[2],S2[2];
bool NOEIN[1<<15];
inline bool get_NOEIN(int s)
{
	for(int i=0;i<SN;i++)
	{
		if(!(s&(1<<i)))continue;
		for(int j=i+1;j<SN;j++)
		{
			if(!(s&(1<<j)))continue;
			if(MAT[i][j])return false;
		}
	}
	return true;
}
int N,PRI[15],RES[100][2],IDX1[15],IDX2[15];
int main()
{
//	printf("%d\n",'Z'-'L');return 0;
//	freopen("in.txt","r",stdin); 
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<15;i++)
		{
			IDX1[i]=IDX2[i]=-1;
			for(int j=0;j<15;j++)
			{
				MAT[i][j]=false;
			}
		}
		SN=0;
		for(int i=0;i<N;i++)
		{
			scanf("%s%s",S1,S2);
			int &n1=RES[i][0]=S1[0]-'L',&n2=RES[i][1]=S2[0]-'L';
			if(IDX1[n1]==-1){IDX1[n1]=SN,IDX2[SN++]=n1;}
			if(IDX1[n2]==-1){IDX1[n2]=SN,IDX2[SN++]=n2;}
			n1=IDX1[n1],n2=IDX1[n2];
			if(n1==n2)termin();
			MAT[n1][n2]=MAT[n2][n1]=true;
		}
		for(int i=0;i<(1<<SN);i++)
		{
			NOEIN[i]=get_NOEIN(i);
		}
		ANS[0]=0;
		for(int i=1;i<(1<<SN);i++)
		{
			ANS[i]=INF;
			for(int s=i;s;s=(s-1)&i)
			{
				if(NOEIN[s])
				{
					if(getmin(ANS[i],ANS[i-s]+1))
					{
						PRE[i]=i-s;
					}
				}
			}
		}
		printf("%d\n",ANS[(1<<SN)-1]-2);
		for(int i=(1<<SN)-1,p=0;i;i=PRE[i],p++)
		{
			int j=i-PRE[i];
			for(int k=0;k<SN;k++)
			{
				if(j&(1<<k))
				{
					PRI[k]=p;
				}
			}
		}
		for(int i=0;i<N;i++)
		{
			int &n1=PRI[RES[i][0]],&n2=PRI[RES[i][1]];
//			printf("%d %d\t",n1,n2);
			if(n1>n2)printf("%c %c\n",'L'+IDX2[RES[i][0]],'L'+IDX2[RES[i][1]]);
			else if(n1<n2) printf("%c %c\n",'L'+IDX2[RES[i][1]],'L'+IDX2[RES[i][0]]);
			else termin();
		}
	}
	return 0;
}
