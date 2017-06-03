#include<cstdio>
#include<cstdlib>
struct pairtype
{
	double p;
	bool won;
};
double p,q;
pairtype tmp[101][101];//win, lose
int T,n;
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++)
	{
		scanf("%lf/%lf %d",&p,&q,&n);
		p/=q;
		q=1-p;
		tmp[0][0].won=false;
		tmp[0][0].p=1;
		for(int i=1;i<=n;i++)
		{
			for(int j=0;j<=i;j++)
			{
				tmp[j][i-j].won=(double)j/i>p?true:false;
				tmp[j][i-j].p=0;
			}
		}
		for(int i=1;i<=n;i++)
		{
			if(!tmp[0][i-1].won) tmp[0][i].p+=tmp[0][i-1].p*q;
			for(int j=1;j<i;j++)
			{
				if(!tmp[j-1][i-j].won) tmp[j][i-j].p+=tmp[j-1][i-j].p*p;
				if(!tmp[j][i-j-1].won) tmp[j][i-j].p+=tmp[j][i-j-1].p*q;
			}
			if(!tmp[i-1][0].won) tmp[i][0].p+=tmp[i-1][0].p*p;
		}
		p=0;
		for(int i=1;i<=n;i++)
		{
			for(int j=0;j<=i;j++)
			{
				if(tmp[j][i-j].won) p+=tmp[j][i-j].p;
			}
		}
		q=1-p;
		//printf(" %lf\n",q);
		//p:win, q:lose
		//S=1*q+2*q*p+3*q*p^2+4*q*p^3...
		//p*S=    q*p+2*q*p^2+3*q*p^3...
		//(1-p)S=q*(1/(1-p))
		//q*S=1
		//S=1/q
		int ans=1/q;
		printf("Case #%d: %d\n",kase,ans);
	}
	return 0;
}
