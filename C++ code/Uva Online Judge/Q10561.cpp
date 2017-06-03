#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
char S[201],state[201],tmp[201];
int T,n;
vector<int> mex;
bool isX(int a)
{
	if(a>=n||a<0) return false;
	return S[a]=='X';
}
bool canput(int a)
{
	for(int i=a-2;i<=a+2;i++)
	{
		if(isX(i)) return false;
	}
	return true;
}
bool canwin()
{
	int now=0;
	int bef=-3;
	int ans=0;
	mex.clear();
	for(int i=0;i<n;i++)
	{
		if(S[i]=='X')
		{
			if(i-bef<=2) return true;
			bef=i;
		}
		if(canput(i))
		{
			now++;
		}
		else
		{
			if(now) mex.push_back(now);
			now=0;
		}
	}
	for(int i=0;i<mex.size();i++)
	{
		//printf(" %d",mex[i]);
		ans^=mex[i];
	}//printf("\n");
	return ans==0;
}
void rangemex(int a,int b)
{
	if(a==b) return;
	int mid=(a+b)/2;
	rangemex(a,mid);
	rangemex(mid+1,b);
	int c=a,d=mid+1;
	for(int i=a;i<=b;i++)
	{
		if(b>d||(c<=mid&&mex[c]<mex[d]))
		{
			tmp[i]=mex[c];
			c++;
		}
		else
		{
			tmp[i]=mex[d];
			d++;
		}
	}
	for(int i=a;i<=b;i++) mex[i]=tmp[i];
}
int main()
{
	freopen("in.txt","r",stdin);
	state[0]=1;//lose
	state[1]=state[2]=state[3]=0;//win
	for(int i=4,k;i<=200;i++)
	{
		mex.clear();
		for(int j=1;j<=i;j++)
		{
			k=0;
			if(j-2>=1) k^=state[j-3];
			if(j+2<=i) k^=state[i-j-2];
			mex.push_back(k);
		}
		rangemex(0,mex.size()-1);
		state[i]=0;
		for(int j=0;j<mex.size();j++)
		{
			if(mex[j]==state[i]) state[i]++;
		}
	}
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s",S);
        printf("%s\n",S);
        n=-1;
        while(S[++n]);
        vector<int> ans;
        for(int i=0;i<n;i++)
        {
        	if(S[i]=='.')
        	{
        		S[i]='X';
        		if((isX(i-2)&&isX(i-1))||(isX(i-1)&&isX(i+1))||(isX(i+1)&&isX(i+2))||!canwin()) ans.push_back(i+1);
        		S[i]='.';
			}
		}
		if(ans.size()) printf("WINNING\n%d",ans[0]);
		else printf("LOSING\n");
		for(int i=1;i<ans.size();i++) printf(" %d",ans[i]);
		printf("\n");
    }
    return 0;
}
