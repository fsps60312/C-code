#include<cstdio>
bool getmax(int &a,const int &b){if(b>a){a=b;return true;}return false;}
int N,P;
char S1[150001],S2[150001];
int V[150000],IDX[150000],NOW;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&P)==2&&N)
	{
		scanf("%s%s",S1,S2);
		int dif=0;
		NOW=0;
		int ans=-1;
		for(int i=0,n=1;i<N;i++,n++)
		{
			if(S1[i]!=S2[i])dif++;
			//n*P/100-dif
			//==(n*P-100*dif)/100
			int v=n*P-100*dif;//remain differ coda
//			printf("i=%d,v=%d\n",i,v);
			if(v<0)
			{
				int l=0,r=NOW,mid;
				while(l<r)
				{
					mid=(l+r)/2;
					if(V[mid]+v>=0)r=mid;
					else l=mid+1;
				}
				if(l<NOW)if(getmax(ans,n-IDX[l]));//printf("(%d,%d)\n",IDX[l],i);
				if(NOW>0&&V[NOW-1]>=-v)continue;
				else V[NOW]=-v,IDX[NOW]=n,NOW++;
			}
			else
			{
				if(getmax(ans,n));//printf("(0,%d)\n",i);
			}
		}
		if(ans==-1)puts("No solution.");
		else printf("%d\n",ans);
	}
	return 0;
}
