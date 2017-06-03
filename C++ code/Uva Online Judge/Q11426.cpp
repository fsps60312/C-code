#include<cstdio>
#include<cstdlib>
int phi[41];
void phi_table(int a)
{
	for(int i=2;i<=a;i++) phi[i]=0;
	phi[1]=1;
	for(int i=2;i<=a;i++)
	{
		if(!phi[i])//i is prime
		{
			for(int j=i;j<=a;j+=i)//j is multiple of i
			{
				if(!phi[j])
				{
					phi[j]=j;
				}
				phi[j]=phi[j]/i*(i-1);
			}
		}
	}
}
int main()
{
	phi_table(40);
	for(int i=1;i<=40;i++) printf("%d %d\n",i,phi[i]);
	return 0;
}
