#include<cstdio>
#include<cstdlib>
int T,n,rest;
char S[1010],Min;
bool isans[1000];
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",S);
		n=-1;
		while(S[++n]) isans[n]=true;
		rest=n;
		for(int i=0;i<n&&rest>1;i++)//length
		{
			Min='T';
			for(int j=0;j<n;j++) if(S[(i+j)%n]<Min&&isans[j]) Min=S[(i+j)%n];
			for(int j=0;j<n&&rest>1;j++)
			{
				int k=(i+j)%n;
				if(S[k]>Min&&S[k]=='T'&&isans[j])
				{
					isans[j]=false;
					rest--;
				}
			}
			for(int j=0;j<n&&rest>1;j++)
			{
				int k=(i+j)%n;
				if(S[k]>Min&&S[k]=='G'&&isans[j])
				{
					isans[j]=false;
					rest--;
				}
			}
			for(int j=0;j<n&&rest>1;j++)
			{
				int k=(i+j)%n;
				if(S[k]>Min&&S[k]=='C'&&isans[j])
				{
					isans[j]=false;
					rest--;
				}
			}
			//for(int j=0;j<n;j++) if(isans[j]) printf(" %d",j);printf("\n");
		}
		for(int i=0;i<n;i++)
		{
			if(isans[i])
			{
				for(int j=0;j<n;j++) printf("%c",S[(i+j)%n]);
				printf("\n");
				break;
			}
		}
	}
	return 0;
}
