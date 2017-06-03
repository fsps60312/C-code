#include<cstdio>
#include<cstdlib>
	int s[2000001];
struct BinaryIndexedTree
{
	int lowbit(int a){return (-a)&a;}
	void init()
	{
		for(int i=1;i<2000001;i++)s[i]=lowbit(i);
	}
	int sum(int i)
	{
		int ans=0;
		while(i)
		{
			ans+=s[i];
			i-=lowbit(i);
		}
		return ans;
	}
	bool exist(int i){return sum(i)-sum(i-1)==1;}
	void decrease(int i)
	{//printf("decreasing %d\n",i);
		//bool deb=false;
		//if(i==2000000)deb=true;
		//if(deb)printf("demax%d\n",i+lowbit(i));
		while(i<2000001){s[i]--,i+=lowbit(i);}
		//if(deb)printf("demax%d\n",i+lowbit(i));
	}
	int getidx(int rank)
	{
		int i=1,d=0;
		while((i<<1)<2000001)i<<=1,d++;
		//for(int i=1;sum(i)<=rank;i++)printf("%d",exist(i));printf("\n%d",rank);
		for(i=0;rank>0&&d>=0;d--)
		{
			if(i+(1<<d)>2000000)continue;
			if(rank>=s[i+(1<<d)])i+=1<<d,rank-=s[i];
		}
		//printf(" %d\n",i);
		while(!exist(i))i--;
		return rank>0?0:i;
	}
	void buildlucky()
	{
		for(int i=2;i<2000001;i++)
		{
			if(!exist(i))continue;//printf("%d ",i);
			for(int j=getidx(i);j;j=getidx(sum(j)+i))
			{
				/*if(i==3){
				for(int k=1;k<=10;k++)printf("%d",exist(k));printf("\n%d %d %d\n",getidx(1),getidx(2),getidx(3));
				printf("%d\n",j);system("pause");}*/
				//if(j>1999990)printf("j=%d",j);
				decrease(j);
				//if(j>1999990)printf("j=%d,next=%d\n",j,getidx(sum(j)+i));
			}
			//printf("%d\n",i);
		}
	}
	int isluckysum(int a)
	{
		if(a&1)return -1;
		for(int i=a/2;i>0;i--)
		{
			if(exist(i)&&exist(a-i))return i;
		}
		return -1;
	}
};
int lowbit(int a){return (-a)&a;}
int n;
int main()
{//printf("p1\n");
	BinaryIndexedTree BI;//
	//printf("%d\n",BI.lowbit(2000000));
	BI.init();//printf("pass\n");
	BI.buildlucky();
	//for(int i=1;i<33;i++)printf("%d",BI.exist(i));
	while(scanf("%d",&n)==1)
	{
		int ans=BI.isluckysum(n);
		if(ans==-1)printf("%d is not the sum of two luckies!\n",n);
		else printf("%d is the sum of %d and %d.\n",n,ans,n-ans);
	}
	return 0;
}
