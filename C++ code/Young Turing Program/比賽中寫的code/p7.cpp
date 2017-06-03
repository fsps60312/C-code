#include<bits/stdc++.h>
using namespace std;
typedef double DB;
struct Matrix
{
	static const int size=4;
	DB c[size][size];
	Matrix() {memset(c,0,sizeof c);}
	Matrix operator * (const Matrix & rhs) const
	{
		Matrix res;
		for(int i=0;i<size;i++)
			for(int j=0;j<size;j++)
				for(int k=0;k<size;k++) res.c[i][j]+=c[i][k]*rhs.c[k][j];
		return res;
	}
};
Matrix mat;
int main()
{
	mat.c[0][1]=6,mat.c[0][2]=8;
	mat.c[1][0]=0.5,mat.c[2][1]=0.5;
	Matrix m;
	scanf("%lf%lf%lf",&m.c[0][0],&m.c[1][0],&m.c[2][0]);
	Matrix ans = mat * m;
	for(int i=0;i<3;i++) printf("%d%c",(int)(ans.c[i][0]+0.5),i==2?'\n':' ');
}
