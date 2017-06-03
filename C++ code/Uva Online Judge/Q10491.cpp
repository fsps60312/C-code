#include<cstdio>
#include<cstdlib>
int NCOWS,NCARS,NSHOWS;
double ans;
int main()
{
	while(scanf("%d%d%d",&NCOWS,&NCARS,&NSHOWS)==3)
	{
		ans=0;
		ans+=(double)NCOWS/(NCOWS+NCARS)*(NCARS)/(NCOWS+NCARS-NSHOWS-1);
		ans+=(double)NCARS/(NCOWS+NCARS)*(NCARS-1)/(NCOWS+NCARS-NSHOWS-1);
		printf("%.5lf\n",ans);
	}
	return 0;
}
