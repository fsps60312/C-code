#include<cstdio>
#include<cstdlib>
int S[750*750],tmp[750*750],input[750][2];
int K;
void rangeS(int a,int b)
{
	if(a==b) return;
	int mid=(a+b)/2;
	rangeS(a,mid);
	rangeS(mid+1,b);
	int c=a,d=mid+1;
	for(int i=a;i<=b;i++)
	{
		if(d>b||(c<=mid&&S[c]<S[d])) tmp[i]=S[c++];
		else tmp[i]=S[d++];
	}
	for(int i=a;i<=b;i++) S[i]=tmp[i];
}
int main()
{
	while(scanf("%d",&K)==1)
	{
		for(int i=0;i<K;i++)
		{
			scanf("%d",&input[i][0]);
		}
		for(int i=1;i<K;i++)
		{
			for(int j=0;j<K;j++)
			{
				scanf("%d",&input[j][1]);
				for(int k=0;k<K;k++)
				{
					S[j*K+k]=input[j][1]+input[k][0];
				}
			}
			rangeS(0,K*K-1);
		//for(int j=0;j<K*K;j++) printf(" %d",S[j]);printf("\n");
			for(int j=0;j<K;j++) input[j][0]=S[j];
		}
		printf("%d",input[0][0]);
		for(int i=1;i<K;i++) printf(" %d",input[i][0]);
		printf("\n");
	}
	return 0;
}
