#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int max(int a, int b) { return a>b?a:b; }
int min(int a, int b) { return a>b?b:a; }

int n, m,  V1[55], V2[555], TO[555], MAT[55][555], MEM[22], a[22], t[22];
bool T1[55], T2[555];

bool check_paired(int u) {
    T1[u] = 1;
    for(int i = 0;i < n*m; i++)
	{
		if(T2[i])continue;
		if(MAT[u][i] == V1[u] + V2[i])
		{
	        T2[i] = 1;
	        if(TO[i]==-1 || check_paired(TO[i]))
			{
	            TO[i] = u;
	            return true;
	        }
	    }
	}
    return false;
}

void update()
{
    int low = 1<<30;
    for(int i=0;i<n;i++)
	{
		if(!T1[i])continue;
	    for(int j=0;j<n*m;j++)
		{
			if(T2[j])continue;
	        low = min(low, MAT[i][j]-V1[i]-V2[j]);
		}
	}
	printf("%d\n",low);
    for(int i = 0;i < n; i++)
	{
		printf(" %d",V1[i]);
		if(!T1[i])continue;
		printf("T");
        V1[i] += low;
	}printf("\n");
    for(int i = 0;i < n*m; i++)
	{
		printf(" %d",V2[i]);
		if(!T2[i])continue;
		printf("T");
        V2[i] -= low;
	}printf("\n");
}

void KM()
{
    int i, j;
    for(i = 0;i < n; i++)
	{
        V1[i] = 1<<30;
        for(j = 0;j < n*m; j++)
		{
            V1[i] = min(V1[i], MAT[i][j]);
            V2[j] =0;
			TO[j] = -1;
        }
    }

    for(i = 0;i < n; i++)
	{
        while(true)
		{
			printf("i=%d\n",i);
            for(j = 0;j < n*m; j++)    T1[j] = T2[j] = 0;//, slack[j] = 1<<30;
            if(check_paired(i))  break;
            else    update();
        }
    }
}

void solve() {
    for(int i = 0;i < m; i++)  scanf("%d", &MEM[i]);
    for(int i = 0;i < n; i++)
        for(int j = 0;j < n*m; j++)
            MAT[i][j] = 1<<30;
    for(int i = 0;i < n; i++) {
        int k;
        scanf("%d", &k);
        for(int j = 0;j < k; j++)  scanf("%d%d", &a[j], &t[j]);
        a[k+1] = 1<<30;
        for(int j = 0;j < m; j++) {
            for(int l = 0;l < k; l++) if(MEM[j] >= a[l] && MEM[j] < a[l+1]) {
                for(int ii = 0;ii < n; ii++) {
                    MAT[i][(j)*n + ii] = (ii+1)*t[l];
				printf("(%d,%d) m=%d\n",i,j*n+ii,MAT[i][j*n+ii]);
                }
            }
        }
    }   

    KM();
}

int main() {
	freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
    int cas = 1;
    while(scanf("%d%d", &m, &n)==2&&(n||m)) {
        solve();
        return 0;
        printf("Case %d\n", cas++);
        int ans = 0;
        for(int i = 0;i < n; i++)  ans += V1[i];
        for(int i = 0;i < n*m; i++)    ans += V2[i];
        printf("Average turnaround time = %.2lf\n", (double)ans/n);
       
        int from[55], to[55], in[55], sum; // from表示程序?什么???始，to表示?束??，in表示在哪??存?域里?行
        for(int i = n*m-1;i >= 0; i--) {
            if(i%n == n-1)    sum = 0;
            if(TO[i]) {
                int tmp = MAT[TO[i]][i];
                from[TO[i]] = sum;
                int num = i%n;
                if(i%n == n-1)    num = n;
                to[TO[i]] = sum = tmp/num + sum;
                in[TO[i]] = i/n + 1;
                if(i%n == n-1)    in[TO[i]]--;
            }
        }
        for(int i = 0;i < n; i++)
            printf("Program %d runs in region %d from %d to %d\n", i, in[i], from[i], to[i]);
    }
    return 0;
}

