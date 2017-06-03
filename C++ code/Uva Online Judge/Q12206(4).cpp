#include<cstdio>
#include<cstdlib>
int N,M,TARRY[3][40000],SA[40000];
char STR[40001];
void build_SA()
{
	int *x=TARRY[0],*y=TARRY[1],*c=TARRY[2];
	int m=26;
	for(int i=0;i<m;i++)c[i]=0;
	for(int i=0;i<N;i++)c[x[i]=STR[i]-'a']++;
	for(int i=1;i<m;i++)c[i]+=c[i-1];
	for(int i=N-1;i>=0;i--)SA[--c[x[i]]]=i;//SA[i] is the idx at rank i
	for(int k=1;k<N;k<<=1)
	{
		int p=0;
		for(int i=N-k;i<N;i++)y[p++]=i;//x[i] is the value of i
		for(int i=0;i<N;i++)if(SA[i]>=k)y[p++]=SA[i]-k;//y[i] is the idx of rank i
		for(int i=0;i<m;i++)c[i]=0;
		for(int i=0;i<N;i++)c[x[i]]++;
		for(int i=1;i<m;i++)c[i]+=c[i-1];
		//for(int i=0;i<N;i++)printf(" %d",SA[i]);printf("\n");
		for(int i=N-1;i>=0;i--)SA[--c[x[y[i]]]]=y[i];//SA[i] is the idx at rank i
		int *t=x;
		x=y,y=t;
		p=1,x[SA[0]]=0;//cal x from y
		for(int i=1;i<N;i++)//i is rank, SA[i] is idx at rank i
		{
			if(y[SA[i]]==y[SA[i-1]])
			{
				int a=SA[i]+k,b=SA[i-1]+k;
				if(a<N&&b<N)
				{
					if(y[a]==y[b])x[SA[i]]=p-1;
					else x[SA[i]]=p++;
				}
				else if(a>=N&&b>=N)
				{
					x[SA[i]]=p-1;
				}
				else
				{
					x[SA[i]]=p++;
				}
			}
			else x[SA[i]]=p++;
		}
		if(p==N)return;
		if(p>m)m=p;
	}
}
int HEIGHT[40000],RANK[40000];
void build_HEIGHT()
{
	for(int i=0;i<N;i++)RANK[SA[i]]=i;
	int h=1;
	for(int i=0;i<N;i++)//i is idx
	{
		if(h)h--;
		if(RANK[i]==0)continue;
		int j=SA[RANK[i]-1];
		while(STR[i+h]==STR[j+h])h++;
		//printf("idx:(%d,%d) h:%d (%c,%c)\n",i,j,h,STR[i+h],STR[j+h]);
		HEIGHT[RANK[i]]=h;
	}
}
void getmax(int &a,int b){if(b>a)a=b;}
int findpos(int len)//return pos
{
	int pos=-1;
	for(int i=1;i<N;i++)
	{
		if(HEIGHT[i]>=len)
		{
			int cnt=1,tp=SA[i-1];
			while(i<N&&HEIGHT[i]>=len)
			{
				cnt++;
				getmax(tp,SA[i]);
				i++;
			}
			if(cnt>=M)getmax(pos,tp);
		}
	}
	return pos;
}
int get_len()
{
	int l=0,r=N+1;
	while(l<r)
	{
		int mid=(l+r)/2;
		if(findpos(mid)==-1)r=mid;
		else l=mid+1;
	}
	return l-1;
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%d",&M)==1&&M)
	{
		scanf("%s",STR);
		N=-1;while(STR[++N]);
		if(M==1){printf("%d 0\n",N);continue;}
		build_SA();
		//for(int i=0;i<N;i++)printf(" %d",SA[i]);printf("\n");
		build_HEIGHT();
		//for(int i=0;i<N;i++)printf(" %d",HEIGHT[i]);printf(" %s\n",STR);
		int len=get_len();
		if(len==0)printf("none\n");
		else printf("%d %d\n",len,findpos(len));
	}
	return 0;
}
