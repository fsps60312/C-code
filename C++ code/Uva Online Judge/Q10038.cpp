#include<cstdio>
#include<cstdlib>
int n,S[3000];
bool vis[3000];
int main()
{
    while(scanf("%d",&n)==1)
    {
        for(int i=0;i<n;i++)
        {
            scanf("%d",&S[i]);
            vis[i]=false;
        }
        bool isans=true;
        for(int i=1;i<n;i++)
        {
            int j;
            if(S[i]>S[i-1]) j=S[i]-S[i-1];
            else if(S[i-1]>S[i]) j=S[i-1]-S[i];
            else
            {
                isans=false;
                break;
            }
            if(j>=n||vis[j])
            {
                isans=false;
                break;
            }
            else vis[j]=true;
        }
        if(isans) printf("Jolly\n");
        else printf("Not jolly\n");
    }
}
