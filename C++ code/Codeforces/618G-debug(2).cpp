#include<cstdio>
#include<cassert>
using namespace std;
const double EPS=1e-15;
struct Matrix
{
	double S[51][51];
	Matrix()
	{
		for(int i=0;i<=50;i++)for(int j=0;j<=50;j++)S[i][j]=0.0;
	}
};
Matrix matrix_mult(Matrix A, Matrix B) {
    Matrix C;
    for (int i = 0; i <=50; i++)
      for (int j = 0; j <=50; j++)
        for (int k = 0; k <=50; k++)
          C.S[i][k] += A.S[i][j] * B.S[j][k];
    return C;
}
Matrix mat_exp(Matrix A,int e)
{
	if (e == 0) {
		Matrix ans;
      for (int i = 0; i <=50; i++) ans.S[i][i] = 1.0;
      return ans;
    }
    if (e == 1)
      return A;
    else if (e % 2 == 0) {
      Matrix A1 = mat_exp(A, e / 2);
      return matrix_mult(A1, A1);
    } else
      return matrix_mult(A, mat_exp(A, e - 1));
}
int N;
double P,Q;
double Solve()
{
	const int maxp=50;
	double a[maxp][maxp];
    double b[maxp][maxp];
    for(int i=0;i<maxp;i++)for(int j=0;j<maxp;j++)a[i][j]=b[i][j]=0.0;
    for (int len = 1; len < maxp; len++) { 
      for (int pow = 1; pow < maxp; pow++) {
        if (pow == 1) a[len][pow] += P;
        if (pow == 2) {
          a[len][pow] += Q;
          b[len][pow] += Q;
        }
        a[len][pow] += a[len-1][pow-1] * a[len][pow-1];
        b[len][pow] += a[len-1][pow-1] * b[len][pow-1];
      }
    }
    for (int len = maxp - 1; len >= 1; len--) {
      for (int pow = 1; pow < maxp; pow++) {
        a[len][pow] *= 1 - a[len-1][pow];
        b[len][pow] *= 1 - a[len-1][pow];
      }
    }
    
    // value of a slime that has been merged i times
    long vals[maxp];
    for (int i = 0; i < maxp; i++) vals[i] = i;//1l << i;
    // manually do first few cases
    double dp[maxp][maxp];
    double sum[maxp][maxp];
    for(int i=0;i<maxp;i++)for(int j=0;j<maxp;j++)dp[i][j]=sum[i][j]=0.0;
    for (int cur = 1; cur < maxp; cur++)
      dp[maxp-1][cur] = vals[cur];
    
    // manual dp
    for (int i = maxp-2; i >= 0; i--) {
      for (int cur = 1; cur < maxp; cur++) {
        for (int next = 1; next < maxp; next++) {
          if (cur == next) continue;
          if (cur == 1) {
            dp[i][cur] += b[maxp-i-1][next] * dp[i+1][next];
            sum[i][cur] += b[maxp-i-1][next];
          } else {
            if (cur < next) continue;
            dp[i][cur] += a[maxp-i-1][next] * dp[i+1][next];
            sum[i][cur] += a[maxp-i-1][next];
          }
        }
      }
      for (int cur = 1; cur < maxp; cur++) {
        dp[i][cur] = vals[cur] + dp[i][cur] / sum[i][cur];
      }
    }
    if (N < maxp) {
      int k = (int)N;
      double exp = 0;
      for (int i = 1; i < maxp; i++) {
        exp += a[k][i] * dp[maxp-k][i];
      }
      return exp;
    }
    
    double vec[maxp+1];
    for(int i=0;i<maxp;i++)vec[i]=dp[0][i];
//    System.arraycopy(dp[0], 0, vec, 0, maxp);
    vec[maxp] = 1;
    Matrix mat;
    mat.S[maxp][maxp] = 1;
    for (int i = 1; i < maxp; i++) {
      for (int j = 1; j < maxp; j++) {
        if (i == j) continue;
        if (i == 1) {
          mat.S[i][j] += b[maxp-1][j] / sum[0][i];
        } else {
          if (i < j) continue;
          mat.S[i][j] += a[maxp-1][j] / sum[0][i];
        }
      }
      mat.S[i][maxp] += i;
    }
    mat=mat_exp(mat,N-maxp);
    double ans[maxp];
    for(int i=0;i<maxp;i++)ans[i]=0.0;
	for (int i = 0; i <maxp ; i++) {
      for (int j = 0; j <= maxp; j++) {
        ans[i] += mat.S[i][j] * vec[j];
      }
    }
    
//    vec = vec_mult(mat, vec);
    double exp = 0;
    for (int i = 1; i < maxp; i++) {
      exp += a[maxp-1][i] * ans[i];
    }
    return exp;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%lf",&N,&P)==2)
	{
		P/=1e9,Q=1.0-P;
		printf("%.10f\n",Solve());
	}
	return 0;
}
