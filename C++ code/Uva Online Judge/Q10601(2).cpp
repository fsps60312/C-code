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
LL case2222211()
{
	LL ans=0,now,n1=-1,n2=-1;
	for(now=0;now<6;now++)
	{
		if(color[now]&1)
		{
			n1=now++;
			break;
		}
	}
	for(;now<6;now++)
	{
		if(color[now]&1)
		{
			n2=now++;
			break;
		}
	}
	for(;now<6;now++)
	{
		if(color[now]&1)
		{
			return 0;
		}
	}
	if(n1==-1)
	{
		for(int i=0;i<6;i++)
		{
			cnow[i]+=2;
			ans+=dfs222222(1);
			cnow[i]-=2;
		}
	}
	else
	{
		//printf("pass\n");
		cnow[n1]++;
		cnow[n2]++;
		ans+=dfs222222(1)*2;
		cnow[n1]--;
		cnow[n2]--;
	}
	//printf(" %lld\n",ans);
	return ans;
}
int main()
{
	//freopen("in.txt","r",stdin);
	lev[0]=1;
	for(LL i=1;i<=12;i++) lev[i]=lev[i-1]*i;
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
		LL tmp1,tmp2=24;
		ans+=caseall();
		tmp1=case444();
		ans+=6*tmp1;
		tmp1=case3333();
		ans+=8*tmp1;
		tmp1=case222222();
		ans+=3*tmp1;
		tmp1=case2222211();
		ans+=6*tmp1;
		printf("%lld\n",ans/tmp2);
	}
	return 0;
}
