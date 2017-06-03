#include<cstdio>
#include<vector>
using namespace std;
int T,N,K,W[1001],LIFT[1001],LEG[1001];
struct Animal
{
	int leg,num;
	Animal(int l,int n):leg(l),num(n){} 
};
vector<Animal> ANIMAL;
int solve()
{
	ANIMAL.clear();
	for(int i=1;i<=K;i++)
	{
		int &l=LIFT[i];
		l=W[i-1]-W[i];
		if(l<0)return 0;//no solution
	}
//	printf("LIFT:");for(int i=1;i<=K;i++)printf(" %d:%d",i,LIFT[i]);puts("");
	int A=N;
	for(int i=1;i<K;i++)
	{
		int &l=LEG[i];
		l=LIFT[i]-LIFT[i+1];
		if(l<0)return 0;//no solution
		if(l)
		{
			if(--A<0)return 0;
		}
	}
	if(A==0)
	{
		if(LIFT[K]>0)return 0;//no animal can lift legs
		if(W[K]>0)return 0;//all animal lift all its legs, should = 0
		return 1;
	}
	else if(A==1)
	{
		if(LIFT[K]==0)return 0;//what?! no more animal???
		else
		{
			//Animal type: LIFT[K] units, x legs
			//W[K]-(x-K)*LIFT[K]==0//case that this type lift all its legs(float in the air?)
			//W[K]-x*LIFT[K]+K*LIFT[K]==0
			//W[K]+K*LIFT[K]==x*LIFT[K]
			//x==W[K]/LIFT[K]+K
			if(W[K]%LIFT[K])return 0;//legs of this type can't be integer
			ANIMAL.push_back(Animal(K+W[K]/LIFT[K],LIFT[K]));
			return 1;
		}
	}
	else
	{
		//define N(k) = number of type_k animal
		//define L(k) = k*N(k) (number of legs of type_k animal)
		//0==W[K]-((L(a)-K)*N(a)+(L(b)-K)*N(b)+...(A terms))
		//(L(a)-K)*N(a)+(L(b)-K)*N(b)+...(A terms)==W[K]-----(1)
		//from(1)=>W[K]>=(K-K)*N(a)+(K+1-K)*N(b)>=1
		if(W[K]<A*(A-1)/2)return 0;
		//N(a)+N(b)+...(A terms)==LIFT[K]-----(a)
		//from(a)=>LIFT[K]>=N(a)+N(b)>=2
		if(LIFT[K]<A)return 0;
		if(W[K]==A*(A-1)/2)//type_K * LIFT[K]-1 , type_K+1 * 1
		{
			ANIMAL.push_back(Animal(K,LIFT[K]-A+1));
			for(int i=1;i<A;i++)ANIMAL.push_back(Animal(K+i,1));
			return 1;
		}
//		return -1;
		if(W[K]==A*(A-1)/2+1&&LIFT[K]==A)
		{
			for(int i=0;i<A-1;i++)ANIMAL.push_back(Animal(K+i,1));
			ANIMAL.push_back(Animal(K+A,1));
			return 1;
		}
//		if(W[K]==1&&LIFT[K]==2)//(O)type_K * 1 , type_K+1 * 1
//		if(W[K]==2&&LIFT[K]==2)//(O)type_K * 1 , type_K+2 * 1
//		if(W[K]==2&&LIFT[K]==3)//(X)type_K * 1 , type_K+1 * 2 or type_K * 2 , type_K+2 * 1
//		if(W[K]==3&&LIFT[K]==2)//(X)type_K * 1 , type_K+3 * 1 or type_K+1 * 1 , type_K+2 * 1
//		if(W[K]==1&&LIFT[K]==3)//type_K * 2 , type_K+1 * 1
		return -1;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		scanf("%d%d",&N,&K);
		for(int i=0;i<=K;i++)
		{
			LEG[i]=LIFT[i]=0;
			int &w=W[i];scanf("%d",&w);
		}
		printf("Case #%d:\n",kase++);
		int type=solve();
		if(type==0)printf("No Solution\n");
		else if(type==-1)printf("Multiple Solutions\n");
		else
		{
			printf("Unique Solution\n");
			for(int i=1;i<K;i++)
			{
				if(LEG[i])
				{
					printf("%d %d\n",i,LEG[i]);
					
				}
			}
			for(int i=0;i<ANIMAL.size();i++)
			{
				Animal &a=ANIMAL[i];
				printf("%d %d\n",a.leg,a.num);
			}
		}
	}
	return 0;
}
