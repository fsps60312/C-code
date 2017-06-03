#include<cstdio>
#include<cstdlib>
typedef long long LL;
LL T,color[6],lev[13],cnow[6]={0,0,0,0,0,0};
LL caseall()
{
	LL ans=lev[12];
	for(LL i=0;i<6;i++)
	{
		ans/=lev[color[i]];
	}
	return ans;
}
LL dfs444(LL a)
{
	if(a==3)
	{
		for(LL i=0;i<6;i++)
		{
			if(cnow[i]!=color[i]) return 0;
		}
		return 1;
	}
	LL ans=0;
	for(LL i=0;i<6;i++)
	{
		cnow[i]+=4;
		ans+=dfs444(a+1);
		cnow[i]-=4;
	}
	return ans;
}
LL case444()
{
	return dfs444(0);
}
LL dfs3333(LL a)
{
	if(a==4)
	{
		for(LL i=0;i<6;i++)
		{
			if(cnow[i]!=color[i]) return 0;
		}
		return 1;
	}
	LL ans=0;
	for(LL i=0;i<6;i++)
	{
		cnow[i]+=3;
		ans+=dfs3333(a+1);
		cnow[i]-=3;
	}
	return ans;
}
LL case3333()
{
	return dfs3333(0);
}
LL dfs222222(LL a)
{
	if(a==6)
	{
		for(LL i=0;i<6;i++)
		{
			if(cnow[i]!=color[i]) return 0;
		}
		return 1;
	}
	LL ans=0;
	for(LL i=0;i<6;i++)
	{
		cnow[i]+=2;
		ans+=dfs222222(a+1);
		cnow[i]-=2;
	}
	return ans;
}
LL case222222()
{
	return dfs222222(0);
}
LL dfs2222211(LL a)
{
	if(a==7)
	{
		for(LL i=0;i<6;i++)
		{
			if(cnow[i]!=color[i]) return 0;
		}
		return 1;
	}
	LL ans=0;
	if(a<5)
	{
		for(LL i=0;i<6;i++)
		{
			cnow[i]+=2;
			ans+=dfs2222211(a+1);
			cnow[i]-=2;
		}
	}
	else
	{
		for(LL i=0;i<6;i++)
		{
			cnow[i]++;
			ans+=dfs2222211(a+1);
			cnow[i]--;
		}
	}
	return ans;
}
LL case2222211()
{
	return dfs2222211(0);
}
int main()
{
	//freopen("in.txt","r",stdin);
	lev[0]=1;
	for(LL i=1;i<=12;i++) lev[i]=lev[i-1]*i;
	//for(int i=0;i<=12;i++) printf("%lld\n",lev[i]);printf("\n");
	scanf("%lld",&T);
	for(LL kase=1;kase<=T;kase++)
	{
		for(LL i=0;i<6;i++) color[i]=cnow[i]=0;
		for(LL i=0,j;i<12;i++)
		{
			scanf("%lld",&j);
			color[--j]++;
		}
		LL ans=0;
		//for(int i=0;i<6;i++) printf(" %d",color[i]);printf("\n");
		LL tmp1,tmp2=24;
		ans+=caseall();
		//printf("pass1\n");
		tmp1=case444();
		ans+=6*tmp1;
		//if(tmp1) tmp2+=6;
		tmp1=case3333();
		ans+=8*tmp1;
		//if(tmp1) tmp2+=8;
		tmp1=case222222();
		ans+=3*tmp1;
		//if(tmp1) tmp2+=3;
		tmp1=case2222211();
		ans+=6*tmp1;
		//if(tmp1) tmp2+=6;
		//for(LL i=0;i<6;i++) ans/=lev[color[i]];
		printf("%lld\n",ans/tmp2);
	}
	return 0;
}
