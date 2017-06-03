#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int n,q,x[100],T=1;
struct matrixtype
{
	double s[100][100];
	void exchange(int a,int b)
	{
		double c;
		for(int i=0;i<n;i++)
		{
			c=s[a][i];
			s[a][i]=s[b][i];
			s[b][i]=c;
		}
	}
	void addto(int a,int b,double c)
	{
		for(int i=0;i<n;i++)
		{
			s[b][i]+=s[a][i]*c;
		}
	}
	matrixtype inverse()
	{
		matrixtype a;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				a.s[i][j]=0;
			}
		}
		for(int i=0;i<n;i++) a.s[i][i]=1;
		for(int i=0;i<n;i++)
		{
			if(s[i][i]==0)
			{
				for(int j=i+1;j<n;j++)
				{
					if(s[j][i]>0)
					{
						exchange(i,j);
						a.exchange(i,j);
						break;
					}
				}
			}
			for(int j=i+1;j<n;j++)
			{
				double k=-s[j][i]/s[i][i];
				addto(i,j,k);
				a.addto(i,j,k);
			}
		}
		for(int i=n-1;i>=0;i--)
		{
			for(int j=i-1;j>=0;j--)
			{
				double k=-s[j][i]/s[i][i];
				addto(i,j,k);
				a.addto(i,j,k);
			}
		}
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				a.s[i][j]/=s[i][i];
			}
		}
		return a;
	}
};
matrixtype p;
vector<int> side[100];
void show(matrixtype a)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			printf(" %lf",a.s[i][j]);
		}
		printf("\n");
	}
}
matrixtype mul(matrixtype a,matrixtype b)
{
	matrixtype c;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			c.s[i][j]=0;
			for(int k=0;k<n;k++)
			{
				c.s[i][j]+=a.s[i][k]*b.s[k][j];
			}
		}
	}
	return c;
}
int main()
{
	//freopen("in.txt","r",stdin);
	//printf("pass\n");
	while(scanf("%d",&n)==1)
	{
		//printf("pass\n");
		if(n==0) break;
		for(int i=0;i<n;i++) side[i].clear();
		while(scanf("%d%d",&x[0],&x[1])==2)
		{
			if(x[0]==0&&x[1]==0) break;
			side[--x[0]].push_back(--x[1]);
		}
		scanf("%d",&q);
		for(int i=0;i<q;i++)
		{
			scanf("%d",&x[i]);
		}
		bool infinity=true;
		for(int i=0;i<n;i++)
		{
			if(side[i].size()==0)
			{
				infinity=false;
			}
			for(int j=0;j<n;j++) p.s[j][i]=0;
			double k=(double)1/side[i].size();
			for(int j=0;j<side[i].size();j++)//from i to j
			{
				p.s[side[i][j]][i]=k;
			}
		}
		//show(p);printf("\n");
		printf("Case #%d:\n",T++);
		//printf("pass\n");
		if(infinity)
		{
			for(int i=0;i<q;i++) printf("infinity\n");
		}
		else
		{
			double a1[n];
			for(int i=0;i<n;i++)
			{
				a1[i]=p.s[i][0];
			}
			//a1 is the matrix: A[]*o
			//ans is (I-A[])^-2 * a1
			//show(p);printf("\n");
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<n;j++)
				{
					p.s[i][j]*=-1;
					if(i==j) p.s[i][j]+=1;
				}
			}
			p=p.inverse();
			double a3[n];
			for(int i=0;i<n;i++)
			{
				a3[i]=0;
				for(int j=0;j<n;j++)
				{
					a3[i]+=p.s[i][j]*a1[j];
				}
			}
			//printf("pass\n");
			//show(p);printf("\n");
			/*p=mul(p,p); 
			//show(p);printf("\n");
			//p.s is the matrix: (I-A[])^2
			//find p.s^-1 then * a1
			//matrixtype P=p;
			//p=p.inverse();
			//P=mul(P,p);
			show(p);printf("\n");
			//show(P);printf("\n");
			for(int i=0;i<n;i++) printf(" %lf",a1[i]);printf("\n");
			double a2[n];
			for(int i=0;i<n;i++)
			{
				a2[i]=0;
				for(int j=0;j<n;j++)
				{
					a2[i]+=p.s[i][j]*a1[j];
				}
			}
			for(int i=0;i<n;i++) printf(" %lf",a2[i]);printf("\n");
			for(int i=0;i<n;i++) printf(" %lf",a3[i]);printf("\n");*/
			a3[0]+=1;
			for(int i=0;i<q;i++)
			{
			//printf("%d\n",n);
				printf("%.3lf\n",a3[x[i]-1]);
			}
		}
		//o,A[]
		//I*S=(A[]*o)+2*(A[]^2*o)+3*(A[]^3*o)+...
		//A[]*S=      1*(A[]^2*o)+2*(A[]^3*o)+...
		//(I-A[])*S=(A[]+A[]^2+A[]^3+...)*o
		//A[](I-A[])*S= (A[]^2+A[]^3+...)*o
		//(I-A[])^2*S=A[]*o
		//find A[]*o & (I-A[])^-2
	}
	return 0;
}
