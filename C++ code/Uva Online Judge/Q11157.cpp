#include<cstdio>
#include<cstdlib>
int T,N,D,bn,sn1,sn2;
int B[101],S1[51],S2[51],tmp[101];
char a,b;
int main()
{
	scanf("%d",&T);
	for(int t=1;t<=T;t++)
	{
		scanf("%d%d",&N,&D);
		bn=0,sn1=0,sn2=0;
		for(int i=0;i<N;i++)
		{
			a=b=0;
			while(a!='B'&&a!='S') scanf("%c",&a);
			while(b!='-') scanf("%c",&b);
			if(a=='B')
			{
				scanf("%d",&B[bn]);
				bn++;
				//printf("pass\n");
			}
			else if(sn1==sn2)
			{
				scanf("%d",&S1[sn1]);
				//printf(" %d\n",S1[sn1]);
				sn1++;
			}
			else
			{
				scanf("%d",&S2[sn2]);
				//printf(" %d\n",S2[sn2]);
				sn2++;
			}
		}
		int maxn=0,now1=0,now2=0,breakn=bn+sn1,nowsite=0,site;
		while(now1+now2<breakn)
		{
			if(now1==bn||(now2<sn1&&S1[now2]<B[now1]))
			{
				site=S1[now2];
				now2++;
			}
			else
			{
				site=B[now1];
				now1++;
			}
			if(site-nowsite>maxn) maxn=site-nowsite;
			nowsite=site;
		}
		if(D-nowsite>maxn) maxn=D-nowsite;
		now1=0,now2=0,nowsite=0,breakn=bn+sn2;
		while(now1+now2<breakn)
		{
			if(now1==bn||(now2<sn2&&S2[now2]<B[now1]))
			{
				site=S2[now2];
				now2++;
			}
			else
			{
				site=B[now1];
				now1++;
			}
			if(site-nowsite>maxn) maxn=site-nowsite;
			nowsite=site;
		}
		//printf("%d %d %d %d %d\n",maxn,site,nowsite,bn,sn1,sn2);
		if(D-nowsite>maxn) maxn=D-nowsite;
		printf("Case %d: %d\n",t,maxn);
	}
	return 0;
}
