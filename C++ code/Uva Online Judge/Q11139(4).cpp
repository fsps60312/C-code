#include<cstdio>
#include<cstdlib>
long long ans[121],gcd[121][121],gcdsum[121][121],concave[121][121];
long long gsum(int a,int b,int c,int d)
{
	return gcdsum[c][d]-gcdsum[a-1][d]-gcdsum[c][b-1]+gcdsum[a-1][b-1];
}
long long getgcd(long long a,long long b)
{
	return b==0?a:getgcd(b,a%b);
}
long long C4(long long a)
{
	return a>=4?a*(a-1)/2*(a-2)/3*(a-3)/4:0;
}
long long C3(long long a)
{
	return a>=3?a*(a-1)/2*(a-2)/3:0;
}
long long noncollinear(long long a)
{
	a++;
	long long ans=C4(a*a);//total dots
	ans-=(C4(a)*a)<<1;//four in a line/column
	ans-=(C3(a)*(a*(a-1))*a)<<1;//three in a line/column
	long long ans1=0,ans2=0;
	for(int i=1;i<a;i++)
	{
		for(int j=1;j<a;j++)
		{
			long long k=(a-i)*(a-j);
			long long l=gcd[i][j];
			ans1+=(l-1)*(l-2)/2*k;//four in a tilt
			ans2+=(l-1)*(a*a-3)*k;//three in a tilt
		}
	}
	ans-=(ans2-ans1*3)<<1;//left-tile & right-tilt	****
	return ans;
}
/*
*     
     X
     X
     X
 XXXX 
*/
long long area_1(long long a,long long b)
{
	long long sum=(a-1)*(b-1);
	//ans+=sum*a*b
	long long ans=sum*(a*b)*2;
	//ans-=(a-1)*a*(1~b-1)/2+(b-1)*b*(1~a-1)/2
	ans-=(a-1)*a*b*(b-1)/2+(b-1)*b*a*(a-1)/2;
	//ans-=(1~a-1)(1~b-1)/2
	ans-=a*(a-1)/2*b*(b-1)/2;
	return ans<<1;//has *2, reach *4
}
long long onside_1(long long a,long long b)
{
	//ans=(a-1)gcd(1~b-1,a)+(b-1)gcd(1~a-1,b)
	long long ans=(a-1)*gsum(1,a,b-1,a)+(b-1)*gsum(1,b,a-1,b);
	//ans+=gcd(1~a-1,1~b-1)
	ans+=gsum(1,1,a-1,b-1);
	return ans<<2;//achieve *4
}
long long sum_1(long long a,long long b)
{
	return (a-1)*(b-1)*4;//achieve *4
}
/*
*    *
      
      
      
 XXXX 
*/
long long area_2next(long long a,long long b)
{
	//ans=a*b/2*(a-1)+b*a/2*(b-1)
	long long ans=a*b*(a-1)+b*a*(b-1);
	return ans;//has *2, reach *2
}
long long onside_2next(long long a,long long b)
{
	//ans=a*(a-1)+gcd(1~a-1,b)*2+b*(b-1)+gcd(1~b-1,a)
	long long ans=a*(a-1)+gsum(1,b,a-1,b)*2+b*(b-1)+gsum(1,a,b-1,a)*2;
	return ans<<1;//reach*2
}
long long sum_2next(long long a,long long b)
{
	return ((a-1)+(b-1))*2;
}
/*
*XXXX 
     X
     X
     X
     *
*/
long long area_2onside(long long a,long long b)
{
	//ans=b*(1~a-1)/2+a*(1~b-1)/2
	long long ans=b*a*(a-1)/2+a*b*(b-1)/2;
	return ans<<1;//has *2, reach *4
}
long long onside_2onside(long long a,long long b)
{
	//ans=((a-1)+(b-1))*gcd(a,b)
	long long ans=((a-1)+(b-1))*gcd[a][b];
	//ans+=gcd(1~a-1,b)+(1~a-1)
	ans+=gsum(1,b,a-1,b)+a*(a-1)/2;
	//ans+=gcd(1~b-1,a)+(1~b-1)
	ans+=gsum(1,a,b-1,a)+b*(b-1)/2;
	return ans<<2;//reach *4
}
long long sum_2onside(long long a,long long b)
{
	return ((a-1)+(b-1))*4;//reach *4
}
/*
     *
    X 
   XX 
  XXX 
*     
*/
//meet problem:
long long cont_2inside(long long a,long long b)//a>=b
{
	long long area=0,onside=0,sum=0;
	for(int i=1;i<b;i++)
	{
		long long j=i*a/b;
		if(j*b==i*a) j--;//on diagonal
		if(j==0) continue;
		//area+=j*a*b/2-i*(1~j)/2-(b-i)*(1~j)-(b-i)*(a-1~a-j)/2
		area+=j*a*b*2-i*(j+1)*j-(b-i)*(j+1)*j*2-(b-i)*(a-1+a-j)*j;
		//sum+=j;
		sum+=j;
		//onside+=gcd(1~j,i)+gcd(a-j~a-1,b-i)
		onside+=gsum(1,i,j,i)+gsum(a-j,b-i,a-1,b-i);
	}
	onside+=sum*gcd[a][b];//diagonal
	sum<<=2;
	onside<<=2;
	//pick: area==inside+onside/2-1
	//change-> inside==area-onside/2+1
	//printf("inside:%lld %lld %lld\n",area,onside,sum);
	return area-onside/2+sum;
}
long long cont_3(long long a,long long b)
{
	//ans=(a-1)(b-1)-(gcd(a,b)-1)
	long long ans=(a-1)*(b-1)-(gcd[a][b]-1);
	return ans<<1;//reach *2
}
long long cal_concave(long long a,long long b)
{
	//pick: area==inside+onside/2-1
	//change-> inside==area-onside/2+1
	long long ans=0;
	ans+=area_1(a,b);
	ans-=onside_1(a,b)>>1;
	ans+=sum_1(a,b);
	ans+=area_2next(a,b);
	ans-=onside_2next(a,b)>>1;
	ans+=sum_2next(a,b);
	ans+=area_2onside(a,b);
	ans-=onside_2onside(a,b)>>1;
	ans+=sum_2onside(a,b);
	ans+=cont_2inside(a,b);
	ans+=cont_3(a,b);
	return ans;
}
int main()
{
	for(int i=1;i<=120;i++)
	{
		for(int j=1;j<i;j++)
		{
			gcd[i][j]=gcd[j][i]=getgcd(i,j);//i>j
		}
		gcd[i][i]=i;
	}
	for(int i=0;i<=120;i++) gcdsum[0][i]=gcdsum[i][0]=0;
	for(int i=1;i<=120;i++)
	{
		for(int j=1;j<=i;j++)
		{
			gcdsum[i][j]=gcdsum[j][i]=gcdsum[i-1][j]+gcdsum[i][j-1]-gcdsum[i-1][j-1]+gcd[i][j];
		}
	}
	/*for(int i=1;i<=5;i++)
	{
		printf(" %d %lld %lld %lld\n",i,area_1(i+1,i),onside_1(i+1,i),sum_1(i+1,i),area_2onside(i,i),onside_2onside(i,i),sum_2onside(i,i)
		,cont_2inside(i,i),cont_3(i,i));
		//printf("%lld\n",cont_3(i,i));
	}
	return 0;*/
	for(int i=1;i<=120;i++)
	{
		for(int j=1;j<=i;j++)
		{
			concave[i][j]=concave[j][i]=cal_concave(i,j);//i>=j
		}
	}
	//for(int i=1;i<=8;i++){for(int j=1;j<=8;j++)printf(" %lld",cal_concave(i,j));printf("\n");}
	//for(int i=1;i<=50;i++)printf(" %lld",noncollinear(i));
	for(int i=1;i<=120;i++)
	{
		ans[i]=noncollinear(i);
		long long conquads=0;
		for(int j=1;j<=i;j++)
		{
			for(int k=1;k<=i;k++)
			{
				conquads+=concave[j][k]*(i-j+1)*(i-k+1);//include (j,k) & (k,j)
			}
			//conquads+=concave[j][j]*(i-j+1)*(i-j+1);
		}
		ans[i]+=conquads<<1;//dots form concave can form 3 different quads
	}
	long long n;
	while(scanf("%lld",&n)==1&&n)
	{
		printf("%lld %lld\n",n,ans[n]);
	}
	return 0;
}
