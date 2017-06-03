#include<cstdio>
#include<cstdlib>
int p1,p2,X,P[10000];
char c;
int power(int a,int b)
{
	int c=1;
	for(int i=0;i<b;i++) c*=a;
	return c;
}
bool show(int a,int b)
{
	if(b==1) return false;
	if(P[a]*P[a]>b)
	{
		printf("%d 1",b);
		return true;
	}
	int c=0;
	for(int i=a;P[i]*P[i]<=b;i++)
	{
		if(b%P[i]==0)
		{
			while(b%P[i]==0)
			{
				b/=P[i];
				c++;
			}
			bool printed=show(i+1,b);
			if(printed) printf(" ");
			printf("%d %d",P[i],c);
			return true;
		}
	}
    printf("%d 1",b);
    return true;
}
int main()
{
	P[0]=2,P[1]=3;
	for(int i=2;i<10000;i++)
	{
		P[i]=P[i-1];
		int j;
		do
		{
			P[i]+=2;
			for(j=0;P[j]*P[j]<=P[i];j++)
			{
				if(P[i]%P[j]==0) break;
			}
		}while(P[i]%P[j]==0);
	}
	//for(int i=0;i<100;i++) printf("%d\n",P[i]);
	X=1;
	while(scanf("%d",&p1)==1)
	{
		if(p1==0) break;
		scanf("%d%c",&p2,&c);
		//printf(" %d %d\n",p1,p2);
		X*=power(p1,p2);
		if(c=='\n')
		{
			//printf(" %d\n",X);
			show(0,X-1);
			printf("\n");
			X=1;
		}
	}
	return 0;
}
