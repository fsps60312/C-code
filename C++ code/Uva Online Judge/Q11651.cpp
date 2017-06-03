#include<cstdio>
#define UI unsigned int
const UI MXREC=(25+1)*6+1;
int T,VIS[26][6];
UI B,S,DP[26][6];
UI absq(UI &a,UI &b){if(a>b)return (a-b)*(a-b);else return (b-a)*(b-a);}
struct Matrix
{
	UI v[MXREC][MXREC],sz;
	UI idx(UI n,UI d){return n*B+d;}
	void init()
	{
		sz=((B-1)*(B-1)+1)*B;
		for(UI i=0;i<sz;i++)for(UI j=0;j<sz;j++)v[i][j]=0;
		for(UI i=0;i<B;i++)//expect digit
		{
			for(UI j=0;j<B;j++)//pre digit
			{
				if(i==j)continue;
				v[0][idx(absq(i,j),j)]++; 
			}
		}
		for(UI i=(B-1)*(B-1);;i--)
		{
			for(UI j=0;j<B;j++)
			{
				v[idx(i,j)][idx(i-1,j)]++;
			}
			if(!i)break;
		}
	}
	Matrix operator*(Matrix &a)const
	{
		Matrix ans;
		for(UI i=0;i<sz;i++)
		{
			for(UI j=0;j<sz;j++)
			{
				UI &b=ans.v[i][j]=0;
				for(UI k=0;k<sz;k++)
				{
					b+=v[i][k]*a.v[k][j];
				}
			}
		}
		return ans;
	}
	Matrix operator*=(Matrix &a){return (*this)=(*this)*a;}
}MAT,I;
UI GetDP(UI score,UI rdigit)
{
	UI &dp=DP[score][rdigit];
	if(VIS[score][rdigit]++)return dp;
//	puts("a");
	if(score==0)return dp=(rdigit?1:0);
	dp=0;
	for(UI i=0,dis;i<B;i++)
	{
		if(i==rdigit)continue;
		dis=absq(i,rdigit);
		if(dis<=score)dp+=GetDP(score-dis,i);
	}
//	printf("(%u,%u):%u\n",score,rdigit,dp);
	return dp;
}
Matrix pow(Matrix &a,UI p)
{
	Matrix ans=I;
	while(p)
	{
		if(p&1)ans*=a;
		a*=a;
		p>>=1;
	}
	return ans;
}
UI solve()
{
	UI sz=(B-1)*(B-1);
//printf("sz=%u,S=%u\n",sz,S);
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
//	puts("hi");
	MAT.init();
	MAT=pow(MAT,S-sz);
	UI ans=0;
	for(UI i=(B-1)*(B-1),k=0;;i--,k++)
	{
		for(UI j=0;j<B;j++)
		{
			ans+=MAT.v[0][MAT.idx(i,j)]*GetDP(k,j);
		}
		if(!i)break;
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
	for(UI i=0;i<MXREC;i++)for(UI j=0;j<MXREC;j++)I.v[i][j]=(i==j?1:0);
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		scanf("%u%u",&B,&S);
		printf("Case %d: %u\n",kase++,solve());
	}
	return 0;
}
