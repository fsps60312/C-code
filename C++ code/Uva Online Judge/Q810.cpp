#include<cstdio>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;
struct dicestatetype
{
    int up;
    int fro;
};
char gamename[30];
int n1,n2,x1,x2;
int dicering[7][7];
bool vis[11][11][7][7],found;
int S[11][11];
vector<dicestatetype> A;
dicestatetype movedice(int a,dicestatetype b)//0:up, 1:right, 2:down, 3:left
{
    dicestatetype ans;
    if(a==0)//up
    {
        ans.up=b.fro;
        ans.fro=7-b.up;
        return ans;
    }
    if(a==2)
    {
        ans.up=7-b.fro;
        ans.fro=b.up;
        return ans;
    }
    if(a==1)
    {
        ans.fro=b.fro;
        ans.up=dicering[b.fro][b.up];
        return ans;
    }
    if(a==3)
    {
        ans.fro=b.fro;
        ans.up=dicering[7-b.fro][b.up];
        return ans;
    }
}
void dfs(int x,int y,dicestatetype a)
{
    if(vis[x][y][a.up][a.fro]||found) return;
    //printf("\n%d %d",x,y);
    vis[x][y][a.up][a.fro]=true;
    if(x==x1&&y==x2)
    {
        found=true;
        return;
    }
    dicestatetype ans;
    ans.up=x;
    ans.fro=y;
    A.push_back(ans);
    dicestatetype b;
    if(x>1&&(a.up==S[x-1][y]||S[x-1][y]==-1))
    {
        b=movedice(0,a);
        dfs(x-1,y,b);
    }
    if(y<n2&&(a.up==S[x][y+1]||S[x][y+1]==-1))
    {
        b=movedice(1,a);
        dfs(x,y+1,b);
    }
    if(x<n1&&(a.up==S[x+1][y]||S[x+1][y]==-1))
    {
        b=movedice(2,a);
        dfs(x+1,y,b);
    }
    if(y>1&&(a.up==S[x][y-1]||S[x][y-1]==-1))
    {
        b=movedice(3,a);
        dfs(x,y-1,b);
    }
    if(found) return;
    A.pop_back();
}
int main()
{
    //freopen("in.txt","r",stdin);
    dicering[1][2]=3;
    dicering[1][3]=5;
    dicering[1][5]=4;
    dicering[1][4]=2;
    dicering[2][1]=4;
    dicering[2][4]=6;
    dicering[2][6]=3;
    dicering[2][3]=1;
    dicering[3][1]=2;
    dicering[3][2]=6;
    dicering[3][6]=5;
    dicering[3][5]=1;
    dicering[4][5]=6;
    dicering[4][6]=2;
    dicering[4][2]=1;
    dicering[4][1]=5;
    dicering[5][3]=6;
    dicering[5][6]=4;
    dicering[5][4]=1;
    dicering[5][1]=3;
    dicering[6][3]=2;
    dicering[6][2]=4;
    dicering[6][4]=5;
    dicering[6][5]=3;
    while(scanf("%s",gamename)==1)
    {
        if(gamename[0]=='E'&&gamename[1]=='N'&&gamename[2]=='D'&&gamename[3]==0) break;
        printf("%s",gamename);
        scanf("%d%d",&n1,&n2);//row, column
        scanf("%d%d",&x1,&x2);//start point
        dicestatetype initial;
        scanf("%d%d",&initial.up,&initial.fro);
        for(int i=1;i<=n1;i++)
        {
            for(int j=1;j<=n2;j++)
            {
                scanf("%d",&S[i][j]);
                for(int k1=1;k1<=6;k1++)
                {
                    for(int k2=1;k2<=6;k2++)
                    {
                        vis[i][j][k1][k2]=false;
                    }
                }
            }
        }
        A.clear();
        found=false;
        dicestatetype ans;
        ans.up=x1;
        ans.fro=x2;
        A.push_back(ans);
        dicestatetype b;
        if(x1>1&&(initial.up==S[x1-1][x2]||S[x1-1][x2]==-1))
        {
            b=movedice(0,initial);
            dfs(x1-1,x2,b);
        }
        if(x2<n2&&(initial.up==S[x1][x2+1]||S[x1][x2+1]==-1))
        {
            b=movedice(1,initial);
            dfs(x1,x2+1,b);
        }
        if(x1<n1&&(initial.up==S[x1+1][x2]||S[x1+1][x2]==-1))
        {
            b=movedice(2,initial);
            dfs(x1+1,x2,b);
        }
        if(x2>1&&(initial.up==S[x1][x2-1]||S[x1][x2-1]==-1))
        {
            b=movedice(3,initial);
            dfs(x1,x2-1,b);
        }
        if(found)
        {
            for(int i=0;i<A.size();i++)
            {
                if(i%9==0) printf("\n  ");
                printf("(%d,%d),",A[i].up,A[i].fro);
            }
            if(A.size()%9==0) printf("\n  ");
            printf("(%d,%d)\n",A[0].up,A[0].fro);
        }
        else
        {
            printf("\n  No Solution Possible\n");
        }
    }
    return 0;
}
