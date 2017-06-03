#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int N,K,MID,LEFT[1000001],RIGHT[1000001];
int IDX[1999999],SUM[1000001];
char S[1000002];
vector<vector<int> >ANS;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		scanf("%s",S+1);
		for(int i=0;i<N;i++)LEFT[i+1]=i,RIGHT[i]=i+1;
		LEFT[0]=N,RIGHT[N]=0;
		MID=N/(1+K)*K;
		for(int i=0;i<=MID*2;i++)IDX[i]=-1;
		int sum=0;
		IDX[MID+sum]=0;
		SUM[0]=0;
		ANS.clear();
		for(int i=1;i;i=RIGHT[i])
		{
			if(S[i]=='b')sum++;//black
			else if(S[i]=='c')sum-=K;//white
			else assert(0);
//			printf("sum[%d]=%d\n",i,sum);
			SUM[i]=sum;
			if(IDX[MID+sum]!=-1)
			{
				vector<int>ans;
				for(int j=RIGHT[IDX[MID+sum]];;j=RIGHT[j])
				{
//					printf("i=%d,j=%d\n",i,j);
					ans.push_back(j);
					RIGHT[LEFT[j]]=RIGHT[j];
					LEFT[RIGHT[j]]=LEFT[j];
					assert(IDX[MID+SUM[j]]!=-1);
					if(j==i)break;
					IDX[MID+SUM[j]]=-1;
				}
				assert((int)ans.size()==K+1);
				ANS.push_back(ans);
			}
			else
			{
				assert(IDX[MID+sum]==-1);
				IDX[MID+sum]=i;
			}
		}
		assert((int)ANS.size()==N/(K+1));
		for(int i=N/(K+1)-1;i>=0;i--)
		{
			for(int j=0;j<K+1;j++)
			{
				if(j)putchar(' ');
				printf("%d",ANS[i][j]);
			}
			puts("");
		}
	}
	return 0;
}
