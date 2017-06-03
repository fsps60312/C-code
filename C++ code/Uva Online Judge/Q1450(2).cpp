#include<cstdio>
#define max(x,y) (x>y?x:y)
int T,N,E[5001],W[5001],SE[5000],SW[5000],MXE[5001],MXW[5001];
void getmax(int &a,int b){if(b>a)a=b;}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)
		{
			scanf("%d%d",&E[i],&W[i]);
			if(i==0)SE[i]=E[i],SW[i]=W[i];
			else SE[i]=max(0,SE[i-1]-1)+E[i],SW[i]=max(0,SW[i-1]-1)+W[i];
		}
		E[N]=W[N]=0;
		MXE[N]=MXW[N]=0;
		for(int i=N-1;i>=0;i--)
		{
			MXE[i]=max(MXE[i+1],SE[i]);
			MXW[i]=max(MXW[i+1],SW[i]);
		}
		for(int i=0;i<N;i++)
		{
			MXE[i]-=SE[i];
			MXW[i]-=SW[i];
			//printf(" %d %d\n",MXE[i],MXW[i]);
		}
		int a=0,b=0,ans=0;
		for(int i=0;i<N;i++)
		{
			a+=E[i],b+=W[i];
			//printf(" %d %d ",a,b);
			getmax(ans,a);
			getmax(ans,b);
			if(a==0&&b==0)continue;
			bool adda;
			if(a==0)adda=false;
			else if(b==0)adda=true;
			else if(a+MXE[i]>b+MXW[i]) adda=true;
			else if(a+MXE[i]<b+MXW[i]) adda=false;
			else
			{
				adda=a+E[i+1]>b+W[i+1];
			}
			if(adda)a--;
			else b--;
		}
		printf("%d\n",--ans);
	}
	return 0;
}
