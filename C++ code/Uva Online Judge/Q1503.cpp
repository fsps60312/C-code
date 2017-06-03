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
	if(W[0]<=0)return 0;
	for(int i=1;i<=K;i++)
	{
		int &l=LIFT[i];
		l=W[i-1]-W[i];
		if(l<0||W[i]<=0)return 0;//no solution
	}
	printf("LIFT:");for(int i=1;i<=K;i++)printf(" %d:%d",i,LIFT[i]);puts("");
	int A=N,SUM=0;
	for(int i=2;i<=K;i++)
	{
		int &l=LEG[i];
		l=LIFT[i-1]-LIFT[i];
		if(l<0)return 0;//no solution
		if(l)
		{
			SUM+=l;
			if(--A<0)return 0;
		}
	}
	//still don't know number of animals of one leg
	if(A==0)
	{
		if(LIFT[K]>0)return 0;//no animal can lift legs
		if(W[K]!=SUM)return 0;//all animal stand on one leg, should equal to sum
		return 1;
	}
	else if(A==1)
	{
		if(LIFT[K]==0)//should have animal with one leg
		{
			LEG[1]=W[K]-SUM;
			if(LEG[1]<=0)return 0;//can't find another type of animal
			else return 1;
		}
		else
		{
			//Animal type: LIFT[K] units, x legs
			//W[K]-(x-K)*LIFT[K]==sum//case that this type lift all its legs(float in the air?)
			//W[K]-x*LIFT[K]+K*LIFT[K]==sum
			//W[K]+K*LIFT[K]-sum==x*LIFT[K]
			//x==(W[K]-sum)/LIFT[K]+K
			if((W[K]-SUM)%LIFT[K])return 0;//legs of this type can't be integer
			ANIMAL.push_back(Animal(K+(W[K]-SUM)/LIFT[K],LIFT[K]));
			return 1;
		}
	}
	else//left A>=2 types, >K legs, LIFT[K] units
	{
		//define N(k) = number of type_k animal
		//define L(k) = k*N(k) (number of legs of type_k animal)
		//sum+N(1)+(N(a)+N(b)+...(A-1 terms))==W[K]-((L(a)-K-1)*N(a)+(L(b)-K-1)*N(b)+...(A-1 terms))
		//or sum+(N(a)+N(b)+...(A terms))==W[K]-((L(a)-K-1)*N(a)+(L(b)-K-1)*N(b)+...(A terms))
		//sum+N(1)+((L(a)-K)*N(a)+(L(b)-K)*N(b)+...(A-1 terms))==W[K]-----(1)
		//or sum+((L(a)-K)*N(a)+(L(b)-K)*N(b)+...(A terms))==W[K]-----(2)
		//from(1)=>W[K]>=sum+1+(((K+1)-K)*N(a))>=sum+1+N(a)>=sum+2
		//from(2)=>W[K]>=sum+(1*N(a)+2*N(b))>=sum+3
		if(W[K]<SUM+2)return 0;
		//N(a)+N(b)+...(A-1 terms)==LIFT[K]-----(a)
		//or N(a)+N(b)+...(A terms)==LIFT[K]
		//from(a)=>LIFT[K]>=N(a)>=1
		if(LIFT[K]<1)return 0;
		if(W[K]==SUM+2&&LIFT[K]==1)//type_1 * 1 , type_K+1 * 1
		{
			LEG[1]=1;
			ANIMAL.push_back(Animal(K+1,1));
			return 1;
		}
		if(W[K]-LIFT[K]<=SUM)return 0;
//		if(W[K]==SUM+3&&LIFT[K]==2)//(O)type_1 * 1 , type_K+1 * 2
//		if(W[K]==SUM+3&&LIFT[K]==1)//(X)type_1 * 2 , type_K+1 * 1 or type_1 * 1 , type_K+2 * 1
//		(X)if(W[K]==SUM+3&&LIFT[K]==2)//type_1 * 0 , type_K+1 * 1 , type_K+2 * 1
//		if(W[K]==SUM+3&&LIFT[K]==3)//no solution
//		(X)if(W[K]-LIFT[K]==SUM+1)//type_1 * 1 , type_K+1 * LIFT[K]
//		{
//			LEG[1]=1;
//			ANIMAL.push_back(Animal(K+1,LIFT[K]));
//			return 1;
//		}
		return -1;
	}
}
int main()
{
	freopen("in.txt","r",stdin);
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
			for(int i=1;i<=K;i++)if(LEG[i])printf("%d %d\n",i,LEG[i]);
			for(int i=0;i<ANIMAL.size();i++)
			{
				Animal &a=ANIMAL[i];
				printf("%d %d\n",a.leg,a.num);
			}
		}
	}
	return 0;
}
