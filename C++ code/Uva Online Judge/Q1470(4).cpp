#include<cstdio>
#define termin(x,...) {while(1)printf(x,##__VA_ARGS__);}
int T,N,SA[600000],HT[600000],RNK[600000],SPS[21][600000],SYM[300000],TMP[300000];
char S[600000];
void show(char *msg,int *s,int n){printf("%s:",msg);for(int i=0;i<n;i++)printf(" %d",s[i]);puts("");}
void buildSA(int n)
{
	int *c=SPS[0],*x=SPS[1],*y=SPS[2];
	int kind=256;
	for(int i=0;i<kind;i++)c[i]=0;
	for(int i=0;i<n;i++)c[x[i]=S[i]]++;
	for(int i=1;i<kind;i++)c[i]+=c[i-1];
	for(int i=n-1;i>=0;i--)SA[--c[x[i]]]=i;//SA[x]=y -> rank x is loc y
	for(int dis=1;dis<n;dis<<=1)
	{
		int p=0;
		for(int i=n-dis;i<n;i++)y[p++]=i;
		for(int i=0;i<n;i++)if(SA[i]>=dis)y[p++]=SA[i]-dis;
		for(int i=0;i<kind;i++)c[i]=0;
		for(int i=0;i<n;i++)c[x[i]]++;
		for(int i=1;i<kind;i++)c[i]+=c[i-1];
		for(int i=n-1;i>=0;i--)SA[--c[x[y[i]]]]=y[i];
		p=0,y[SA[0]]=p++;
		for(int i=1;i<n;i++)
		{
			if(x[SA[i]]!=x[SA[i-1]])y[SA[i]]=p++;
			else if(SA[i]+dis>=n&&SA[i-1]+dis>=n)y[SA[i]]=p-1;
			else if(SA[i]+dis>=n||SA[i-1]+dis>=n)y[SA[i]]=p++;
			else y[SA[i]]=(x[SA[i]]==x[SA[i-1]]&&x[SA[i]+dis]==x[SA[i-1]+dis])?p-1:p++;
		}
		kind=p;
		if(kind>=n)break;
		int *tmp=x;x=y,y=tmp;
	}
}
void buildHT(int n)
{
	for(int i=0;i<n;i++)RNK[SA[i]]=i;
	int ans=0;
	for(int loc=0;loc<n;loc++)
	{
		if(ans)ans--;
		int r=RNK[loc];
		if(!r){HT[r]=0;continue;}
		while(S[SA[r]+ans]==S[SA[r-1]+ans])ans++;
		HT[r]=ans;
	}
}
int min(int a,int b){return a<b?a:b;}
void buildSPS(int n)
{
	for(int i=0;i<n;i++)SPS[0][i]=HT[i];
	for(int h=1;(1<<h)<=n;h++)
	{
		for(int i=0;i+(1<<h)<=n;i++)
		{
			SPS[h][i]=min(SPS[h-1][i],SPS[h-1][i+(1<<(h-1))]);
		}
	}
}
int querySPS(int r1,int r2)
{
	if(r1==r2)termin("should not be same\n");
	if(r1>r2){int tmp=r1;r1=r2,r2=tmp;}
	r1++;
	int h=0;
	while((1<<(h+1))<=r2-r1+1)h++;
	return min(SPS[h][r1],SPS[h][r2-(1<<h)+1]);
}
int querySUF(int i1,int i2){return querySPS(RNK[i1],RNK[i2]);}
struct Bst
{
	int *bse;
	void build(int sz,int *data){bse=new int[sz*4];build(1,0,sz-1,data);}
	void build(int id,int l,int r,int *data)
	{
		if(l==r){bse[id]=data[l];return;}
		int mid=(l+r)/2,i1=id*2,i2=id*2+1;
		build(i1,l,mid,data),build(i2,mid+1,r,data);
		bse[id]=max(bse[i1],bse[i2]);
	}
	int query(int id,int l,int r,int L,int R,int bound,bool querymax)
	{
		if(bse[id]<bound||r<L||l>R)return -1;
		if(l==r)return l;
		int mid=(l+r)/2,i1=id*2,i2=id*2+1;
		int ans=-1;
		if((querymax&&bse[i2]>=bound)
		||(!querymax&&bse[i1]<bound))ans=query(i2,mid+1,r,L,R,bound);
		else ans=query(i1,l,mid,L,R,bound);
		if(ans==-1)termin("Bst::query ans=%d\n",ans);
		return ans;
	}
}TOR,TOL;
int main()
{
	gets(S);sscanf(S,"%d",&T);
	while(T--)
	{
		gets(S);
		N=-1;while(S[++N]);
		for(int i=0;i<N;i++)S[N+i]=S[N-1-i];
		buildSA(N*2);
		buildHT(N*2);
		buildSPS(N*2);
		for(int i=0;i<N-1;i++)SYM[i]=min(min(i-0+1,(N-1)-(i+1)+1),querySUF(i,N*2-1-(i+1)));
		for(int i=0;i<N-1;i++)TMP[i]=i-SYM[i]+1;
		TOR.build(N-1,TMP);
		for(int i=0;i<N-1;i++)TMP[i]=i+1+SYM[i]-1;
		TOL.build(N-1,TMP);
	}
	return 0;
}
