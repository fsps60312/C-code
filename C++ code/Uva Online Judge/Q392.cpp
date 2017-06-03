#include<cstdio>
#include<cstdlib>
int S[9];
bool printed=false;
void showpart(int a,int b)//coefficient, power
{
	if(a==0) return;
	if(a!=1||b==0) printf("%d",a);
	if(b>0)
	{
		if(b==1) printf("x");
		else printf("x^%d",b);
	}
	printed=true;
}
int main()
{
	//freopen("in.txt","r",stdin);
	int tmp=0;
	while(scanf("%d%d%d%d%d%d%d%d%d",&S[tmp++],&S[tmp++],&S[tmp++],&S[tmp++],&S[tmp++],&S[tmp++],&S[tmp++],&S[tmp++],&S[tmp++])==9)
	{
		//for(int i=0;i<9;i++) printf(" %d",S[i]);printf("\n");system("pause");
		tmp=0;
		printed=false;
		for(int i=8;i>=0;i--)
		{
			if(printed)
			{
				if(S[i]>0) printf(" + ");
				else if(S[i]<0)
				{
					printf(" - ");
					S[i]*=-1;
				}
			}
			else if(S[i]<0)
			{
				printf("-");
				S[i]*=-1;
			}
			showpart(S[i],i);
		}
		if(!printed) printf("0");
		printf("\n");
	}
	return 0;
}
