#include<cstdio>
int T,N,R,S[50];
struct Matrix
{
	int v[50][50];
	Matrix operator*(Matrix &a)
	{
		Matrix ans;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)
			{
				int &b=ans.v[i][j]=0;
				for(int k=0;k<N;k++)b+=v[i][k]*a.v[k][j];
				b%=1000;
			}
		}
		return ans;
	}
	Matrix operator*=(Matrix &a){return (*this)=(*this)*a;}
}MAT;
Matrix I()
{
	Matrix ans;
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)ans.v[i][j]=i==j;
	return ans;
}
Matrix pow(Matrix a,int p)
{
	Matrix ans=I();
	while(p)
	{
		if(p&1)ans*=a;
		a*=a;
		p>>=1;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&R);
		for(int i=0;i<N;i++){scanf("%d",&S[i]);S[i]%=1000;}
		for(int i=0,a,b;i<N;i++)
		{
			scanf("%d",&a);
			for(int j=0;j<N;j++)MAT.v[i][j]=0;
			while(a--)
			{
				scanf("%d",&b);
				MAT.v[i][b]=1;
			}
		}
		MAT=pow(MAT,R);
		for(int i=0,a=0;i<N;i++,a=0)
		{
			for(int j=0;j<N;j++)
			{
				a+=MAT.v[i][j]*S[j];
			}
			if(i)printf(" ");
			printf("%d",a%1000);
		}
		puts("");
	}
	return 0;
}
