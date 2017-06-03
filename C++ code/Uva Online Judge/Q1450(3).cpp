#include<cstdio>
#define max(x,y) (x>y?x:y)
int T,N,E[5000],W[5000],SUM;
void termin(){int a[1];for(int i=0;;i--)a[i]=9;}
bool fitans(int mx)
{
	int retain=0,e=0,w=0,ne,nw;
	for(int i=0;i<N;i++)
	{
		e+=E[i],w+=W[i];
		ne=max(0,e-mx);
		nw=max(0,w-mx);
		if(ne+nw>retain)return false;
		e-=ne,w-=nw;
		retain-=ne+nw;
		if((e==0&&w==0)||w+e==retain)continue;
		if(e>0&&w>0)retain++;
		else if(e>0)e--;
		else w--;
	}
	return true;
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		SUM=0;
		for(int i=0;i<N;i++)
		{
			scanf("%d%d",&E[i],&W[i]);
			SUM+=E[i]+W[i];
		}
		//if(SUM<=0)termin();
		int l=1,r=SUM;
		while(l<r)
		{
			int mid=(l+r)/2;
			if(fitans(mid))r=mid;
			else l=mid+1;
		}
		printf("%d\n",l-1);
	}
	return 0;
}
