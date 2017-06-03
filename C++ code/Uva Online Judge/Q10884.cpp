#include<cstdio>
#include<cstdlib>
int T,n;
//Big sum[26];
/*
0:not touched
1:touched left
2:touched right
3:touched both
*/
const int MAX=33;
class Big
{
	public:
		int digit[MAX];
		Big(int a=0)
		{
			for(int i=0;i<MAX;i++)
			{
				digit[i]=a%10;
				a/=10;
			}
		}
		Big operator=(Big a)
		{
			for(int i=0;i<MAX;i++)
			{
				digit[i]=a.digit[i];
			}
			return *this;
		}
		Big operator+=(Big a)
		{
			for(int i=0;i<MAX;i++)
			{
				digit[i]+=a.digit[i];
			}
			carry();
			return *this;
		}
		Big operator-=(Big a)
		{
			for(int i=0;i<MAX;i++)
			{
				digit[i]-=a.digit[i];
			}
			carry();
			return *this;
		}
		void print()
		{
			int i=MAX;
			while(!digit[--i]&&i>=0);
			if(i==-1) printf("0");
			for(;i>=0;i--) printf("%d",digit[i]);
		}
	private:
	void carry()
	{
		for(int i=0;i<MAX-1;i++)
		{
			digit[i+1]+=digit[i]/10;
			digit[i]%=10;
			if(digit[i]<0) digit[i]+=10,digit[i+1]--;
		}
	}
};
Big ans[51];
Big ways[26][51];
Big dp[26][26][51][4];
Big cont(int a,int b)//a is side, b is sum
{
    for(int i0=0;i0<a;i0++)
    {
        for(int i1=i0+1;i1<=a;i1++)
        {
            for(int i2=b-a;i2>0;i2--)
            {
                for(int i3=0;i3<4;i3++)
                {
                    dp[i0][i1][i2][i3]=0;
                }
            }
        }
    }
    for(int i0=1;i0<a;i0++)
    {
        for(int i1=i0+1;i1<a;i1++)
        {
            dp[i0][i1][1][0]=1;
        }
    }
    for(int i0=1;i0<a;i0++)
    {
        dp[0][i0][1][1]=1;
        dp[i0][a][1][2]=1;
    }
    dp[0][a][1][3]=1;
    b-=a;
    for(int i=2;i<=b;i++)
    {
        //condition 0:
        for(int i0=1;i0<a;i0++)
        {
            for(int i1=i0+1;i1<a;i1++)
            {
                for(int i2=i0;i2<i1;i2++)
                {
                    for(int i3=i2+1;i3<=i1;i3++)
                    {
                        dp[i0][i1][i][0]+=dp[i2][i3][i-1][0];
                    }
                }
            }
        }
        //condition 1:
        //condition 2:
        //only from condition 0:
        for(int i0=1;i0<a;i0++)
        {
            for(int i1=1;i1<i0;i1++)
            {
                for(int i2=i1+1;i2<=i0;i2++)
                {
                    dp[0][i0][i][1]+=dp[i1][i2][i-1][0];
                }
            }
            for(int i1=i0;i1<a;i1++)
            {
                for(int i2=i1+1;i2<a;i2++)
                {
                    dp[i0][a][i][2]+=dp[i1][i2][i-1][0];
                }
            }
        }
        //from condition 1
        for(int i0=0;i0<a;i0++)
        {
            for(int i1=i0+1;i1<=a;i1++)
            {
                for(int i2=0;i2<=i0;i2++)
                {
                    for(int i3=i0+1;i3<=i1;i3++)
                    {
                        dp[i0][i1][i][1]+=dp[i2][i3][i-1][1];
                    }
                }
            }
        }
        //from condition 2
        for(int i0=0;i0<a;i0++)
        {
        	for(int i1=i0+1;i1<=a;i1++)
        	{
        		for(int i2=i1;i2<=a;i2++)
        		{
        			for(int i3=i0;i3<i1;i3++)
        			{
        				dp[i0][i1][i][2]+=dp[i3][i2][i-1][2];
					}
				}
			}
		}
		//condition 3:
		//from condition 0
		for(int i1=1;i1<a;i1++)
		{
			for(int i2=i1+1;i2<a;i2++)
			{
				dp[0][a][i][3]+=dp[i1][i2][i-1][0];
			}
		}
		//from condition 1
		for(int i0=0;i0<a;i0++)
		{
			for(int i1=0;i1<=i0;i1++)
			{
				for(int i2=i0+1;i2<a;i2++)
				{
					dp[i0][a][i][3]+=dp[i1][i2][i-1][1];
				}
			}
		}
		//from condition 2
		for(int i0=2;i0<=a;i0++)
		{
			for(int i1=1;i1<i0;i1++)
			{
				for(int i2=i0;i2<=a;i2++)
				{
					dp[0][i0][i][3]+=dp[i1][i2][i-1][2];
				}
			}
		}
		//from condition 3
		for(int i0=0;i0<a;i0++)
		{
			for(int i1=i0+1;i1<=a;i1++)
			{
				for(int i2=0;i2<=i0;i2++)
				{
					for(int i3=i1;i3<=a;i3++)
					{
						dp[i0][i1][i][3]+=dp[i2][i3][i-1][3];
					}
				}
			}
		}
    }
    Big ans=0;
    for(int i=0;i<a;i++)
    {
    	for(int j=i+1;j<=a;j++)
    	{
    		ans+=dp[i][j][b][3];
		}
	}
	return ans;
}
int main()
{
	//Big a=100;
	//a.print();
    for(int i=2;i<=50;i++)
    {
        for(int j=i/2;j>0;j--)
        {
            ways[j][i]=cont(j,i);
        }
    }
    for(int i=2;i<=50;i++)
    {
        ans[i-1]=0;
        ans[i]=0;
        for(int j=i/2;j>0;j--)
        {
            ans[i]+=ways[j][i];
        }
        ans[i]+=ans[i];
        if(!i&1)
        {
            ans[i]-=ways[i>>1][i];
        }
    }
    scanf("%d",&T);
    for(int kase=1;kase<=T;kase++)
    {
        scanf("%d",&n);
        printf("Case #%d: ",kase);
        if(n&1)
        {
        	printf("0\n");
		}
		else
		{
			ans[n>>1].print();
			printf("\n");
		}
    }
    return 0;
}
