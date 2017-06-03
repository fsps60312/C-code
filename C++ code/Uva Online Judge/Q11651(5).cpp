#include<cstdio>
#define UI unsigned int
const UI MXREC=25*6+6;
int T,VIS[26][6];
UI B,S,DP[26][6];
UI absq(UI &a,UI &b){if(a>b)return (a-b)*(a-b);else return (b-a)*(b-a);}
struct Matrix
{
	UI v[MXREC][MXREC],sz;
	UI idx(UI n,UI d){return n*B+d;}
	void show(char *msg)
	{
		puts(msg);
		for(int i=0;i<sz;i++)
		{
			for(int j=0;j<sz;j++)printf(" %u",v[i][j]);
			puts("");
		}
	}
	void init()
	{
		sz=((B-1)*(B-1))*B+B;
		for(UI i=0;i<sz;i++)for(UI j=0;j<sz;j++)v[i][j]=0;
		for(UI i=0;i<B;i++)//expect digit
		{
			for(UI j=0;j<B;j++)//pre digit
			{
				if(i==j)continue;
				v[idx(0,i)][idx(absq(i,j)-1,j)]++;
			}
		}
		for(UI i=(B-1)*(B-1);;i--)
		{
			if(!i)break;
			for(UI j=0;j<B;j++)
			{
				v[idx(i,j)][idx(i-1,j)]++;
			}
		}
	}
	Matrix operator*(Matrix &a)const
	{
		Matrix ans;
		ans.sz=sz;
		for(UI i=0;i<sz;i++)for(UI j=0;j<sz;j++)ans.v[i][j]=0LL;
		for(UI i=0;i<sz;i++)
		{
            for(UI k=0;k<sz;k++)
			{
			    if(!v[i][k])continue;
                for(UI j=0;j<sz;j++)
                {
                    UI &b=ans.v[i][j];
					b+=v[i][k]*a.v[k][j];
				}
			}
		}
		return ans;
	}
	Matrix operator*=(Matrix &a){return (*this)=(*this)*a;}
}MAT;
UI GetDP(UI score,UI rdigit)
{
	UI &dp=DP[score][rdigit];
	if(VIS[score][rdigit]++)return dp;
	if(score==0)return dp=(rdigit?1:0);
	dp=0;
	for(UI i=0,dis;i<B;i++)
	{
		if(i==rdigit)continue;
		dis=absq(i,rdigit);
		if(dis<=score)dp+=GetDP(score-dis,i);
	}
	return dp;
}
Matrix I(UI sz)
{
    Matrix ans;
    ans.sz=sz;
    for(UI i=0LL;i<sz;i++)
    {
        for(UI j=0LL;j<sz;j++)
        {
            ans.v[i][j]=(i==j?1LL:0LL);
        }
    }
    return ans;
}
Matrix pow(Matrix a,UI p)
{
	Matrix ans=I(a.sz);
	while(p)
	{
//		puts("a1");
		if(p&1)ans*=a;
//		puts("b1");
		a*=a;
//		puts("c1");
		p>>=1;
	}
	return ans;
}
UI solve()
{
	UI sz=(B-1)*(B-1);
	for(UI i=S<sz?S:sz;;i--)
	{
		for(UI j=0;j<B;j++)VIS[i][j]=0;
		if(!i)break;
	}
	if(S<=sz)
	{
		UI ans=0;
		for(UI i=0;i<B;i++)ans+=GetDP(S,i);
		return ans;
	}
	MAT.init();
//	MAT.show("before");
//	printf("S-sz==%d\n",(int)(S-sz));
//	puts("a");
	MAT=pow(MAT,S-sz);
//	puts("b");
//	MAT.show("after");
	UI ans=0;
	for(UI i1=0;i1<=(B-1)*(B-1);i1++)
	{
		for(UI j1=0;j1<B;j1++)//pre digit
		{
		    for(UI j2=0;j2<B;j2++)
            {
                ans+=MAT.v[j2][MAT.idx(i1,j1)]*GetDP((B-1)*(B-1)-i1,j1);
            }
		}
	}
	return ans;
}
int main()
{
	//base 5
	//f(i,j):i score, rightest is j
	//f(n,0)=f(n-1,1)+f(n-4,2)+f(n-9,3)+f(n-16,4)
	//f(n,1)=f(n-1,0)+f(n-1,2)+f(n-4,3)+f(n-9,4)
	//f(n,2)=f(n-4,0)+f(n-1,1)+f(n-1,3)+f(n-4,4)
	//f(n,3)=f(n-9,0)+f(n-4,1)+f(n-1,2)+f(n-1,4)
	//f(n,4)=f(n-16,0)+f(n-9,1)+f(n-4,2)+f(n-1,3)
	//DP[i][j]:
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		scanf("%u%u",&B,&S);
		printf("Case %d: %u\n",kase++,solve());
	}
	return 0;
}
