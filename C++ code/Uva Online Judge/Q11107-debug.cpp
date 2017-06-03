#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAXN = 111111;

int num;

int s[MAXN];

int sa[MAXN],t[MAXN],t2[MAXN],c[MAXN];

void build_sa(int n,int m)
{
    int *x = t,*y = t2;
    for(int i = 0 ;i<m;i++) c[i] = 0;
    for(int i = 0 ;i<n;i++) c[x[i] = s[i]]++;
    for(int i = 1 ;i<m;i++) c[i] += c[i-1];
    for(int i = n-1;i >=0 ;i--) sa[--c[x[i]]] = i;
    for(int k = 1;k<=n;k <<= 1)
    {
        int p = 0;
        for(int i = n - k ;i < n;i ++) y[p++] = i;
        for(int i = 0;i < n;i++) if(sa[i] >= k) y[p++] = sa[i] - k;
        for(int i = 0;i<m;i++) c[i] = 0;
        for(int i = 0;i < n;i++) c[x[y[i]]]++;
        for(int i = 1;i<m;i++) c[i] += c[i-1];
        for(int i = n - 1;i >= 0;i--) sa[--c[x[y[i]]]] = y[i];
        swap(x,y);
        p = 1;
        x[sa[0]] = 0;
        for(int i = 1;i<n;i++)
            x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i-1] + k] == y[sa[i] + k] ? p-1 : p++;
        if(p >= n) break;
        m = p;
    }
}

int height[MAXN],rank[MAXN];

void get_height(int n)
{
    for(int i = 1;i<=n;i++) rank[sa[i]] = i;
    int k = 0;
    for(int i = 0;i<n;i++)
    {
        if(k) k--;
        int j = sa[rank[i] - 1];
        while(s[i + k] == s[j + k]) k++;
        height[rank[i]] = k;
    }
}

int belong[MAXN];
int flag[111];

int check(int len,int n)
{
    memset(flag,0,sizeof(flag));
    int cc = 0;
    for(int i = 1; i <= n; i++)
    {
        if(height[i] < len)
        {
            memset(flag,0,sizeof(flag));
            cc = 0;
        }
        else
        {
            if(flag[belong[sa[i-1]]] == 0)
            {
                flag[belong[sa[i-1]]] = 1;
                cc++;
            }
            if(flag[belong[sa[i]]] == 0)
            {
                flag[belong[sa[i]]] = 1;
                cc++;
            }
            if(cc > num/2)
                return 1;
        }
    }
    return 0;
}

void print(int len,int n)
{
    memset(flag,0,sizeof(flag));
    int cc = 0;
    int ok = 0;
    for(int i = 0; i <= n; i++)
    {
        if(height[i] < len)
        {
            memset(flag,0,sizeof(flag));
            cc = 0;
            ok = 0;
        }
        else
        {
            if(flag[belong[sa[i-1]]] == 0)
            {
                flag[belong[sa[i-1]]] = 1;
                cc++;
            }
            if(flag[belong[sa[i]]] == 0)
            {
                flag[belong[sa[i]]] = 1;
                cc++;
            }
            if(!ok && cc > num/2)
            {
                for(int j = 0;j<len;j++)
                    printf("%c",s[sa[i] + j] + 'a' - 1);
                puts("");
                ok = 1;
            }
        }
    }
}

void solve(int n)
{
    int ans = 0;
    int l = 1,r = n;
    while(l <= r)
    {
        int mid = (l+r) >> 1;
        if(check(mid,n))
        {
            ans = mid;
            l = mid + 1;
        }
        else r = mid - 1;
        //printf("l = %d,r = %d,mid = %d\n",l,r,mid);
    }
    //printf("ans = %d\n",ans);
    if(ans) print(ans,n);
    else printf("?\n");
}

char str[1111];

int main()
{
	//freopen("in.txt","r",stdin);
    int first = 1;
    while(~scanf("%d",&num) && num)
    {
        if(first) first = 0;
        else puts("");

        int end = 30;
        int n = 0;
        for(int i = 0;i<num;i++)
        {
            scanf("%s",str);
            int len = strlen(str);
            for(int j = 0;j<len;j++)
            {
                s[n] = str[j] - 'a' + 1;
                belong[n] = i;
                n++;
            }
            s[n] = end++;
            belong[n] = num;
            n++;
        }
        printf("sa:");for(int i=0;i<n;i++)printf(" %d",sa[i]);printf("\n");
        printf("sa:");for(int i=0;i<n;i++)printf(" %d",height[i]);printf("\n"); 
        s[n] = 0;
        if(num == 1)
        {
            puts(str);
            continue;
        }
        build_sa(n+1,end);
        get_height(n);
        solve(n);
    }
    return 0;
}

