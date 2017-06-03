#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int T,n,f[201],tmp[201];
char S[201];
vector<int> mex;
void rangemex(int a,int b)
{
	if(a==b) return;
	int mid=(a+b)/2;
	rangemex(a,mid);
	rangemex(mid+1,b);
	int c=a,d=mid+1;
	for(int i=a;i<=b;i++)
	{
		if(d>b||(c<=mid&&mex[c]<mex[d]))
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
bool XorIsZero()
{
	bool canput[n];
	for(int i=0;i<n;i++) canput[i]=true;
	for(int i=0;i<n;i++)
	{
		if(S[i]=='X')
		{
			for(int j=i-2;j<=i+2;j++)
			{
				if(j>=0&&j<n)
				{
					canput[j]=false;
				}
			}
		}
	}
	//for(int i=0;i<n;i++) printf(" %d",canput[i]);printf("\n");
	int now=0,ans=0;
	for(int i=0;i<n;i++)
	{
		if(canput[i])
		{
			now++;
		}
		else
		{
			ans^=f[now];
			//printf("%d\n",f[now]);
			now=0;
		}
	}
	ans^=f[now];
	/*if(ans==0)
	{
		for(int i=0;i<n;i++) printf(" %d",canput[i]);printf("\n");
	}*/
	return ans==0;
}
int main()
{
	f[0]=0;//lose
	f[1]=f[2]=f[3]=1;//win
	for(int i=4,k;i<201;i++)
	{
		mex.clear();
		for(int j=1;j<=i;j++)
		{
			k=0;
			if(j-2>=1) k^=f[j-3];
			if(j+2<=i) k^=f[i-j-2];
			mex.push_back(k);
		}
		rangemex(0,mex.size()-1);
		f[i]=0;
		for(int j=0;j<mex.size();j++)
		{
			if(mex[j]==f[i])
			{
				f[i]++;
			}
		}
	}
	//for(int i=0;i<10;i++) printf(" %d",f[i]);printf("\n");
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);//T=1;
	while(T--)
	{
		scanf("%s",S);
		n=-1;
		while(S[++n]);
		vector<int> ans;
		bool canput[n];
		for(int i=0;i<n;i++) canput[i]=true;
		for(int i=0;i<n;i++)
		{
			if(S[i]=='X')
			{
				for(int j=i-2;j<=i+2;j++)
				{
					if(j>=0&&j<n)
					{
						canput[j]=false;
					}
				}
			}
		}
		vector<int> onestep; 
		for(int i=0;i<n;i++)
		{
			if(S[i]=='.')
			{
				if(i>=2&&S[i-2]=='X'&&S[i-1]=='X')
					onestep.push_back(i+1);
				else if(i>=1&&i<n-1&&S[i-1]=='X'&&S[i+1]=='X')
					onestep.push_back(i+1);
				else if(i<n-2&&S[i+1]=='X'&&S[i+2]=='X')
					onestep.push_back(i+1);
				else if(canput[i])
				{
					S[i]='X';
					if(XorIsZero()) ans.push_back(i+1);
					S[i]='.';
				}
			}
		}
		//printf("%s\n",S);
		if(onestep.size())
		{
			printf("WINNING\n%d",onestep[0]);
			for(int i=1;i<onestep.size();i++) printf(" %d",onestep[i]);
			printf("\n");
		}
		else if(ans.size())
		{
			printf("WINNING\n%d",ans[0]);
			for(int i=1;i<ans.size();i++) printf(" %d",ans[i]);
			printf("\n");
		}
		else
		{
			printf("LOSING\n\n");
		}
	}
	return 0;
}
