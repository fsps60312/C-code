#include "elephants.h"
#include <stdio.h>
#include <stdlib.h>
//#include"elephants.cpp"
#define MAX_N 1000000
#define MAX_M 1000000

static int N_,L_,M_;
static int X_[MAX_N];
static int ii[MAX_M];
static int yy[MAX_M];
static int sol[MAX_M];

inline 
void my_assert(int e) {if (!e) abort();}

void read_input()
{
  int i;
  my_assert(3==scanf("%d %d %d",&N_,&L_,&M_));
  for(i=0; i<N_; i++)
    my_assert(1==scanf("%d",&X_[i]));
  for(i=0; i<M_; i++)
    my_assert(3==scanf("%d %d %d",&ii[i],&yy[i],&sol[i]));
puts("Input finished.");
}
unsigned int Rand()
{
	static unsigned int seed=0x20160803;
	seed*=0xdefaced,seed+=162202;
	return seed+=seed>>20;
}
//#include<algorithm>
//using namespace std;
void get_random_input()
{
  int i;
  N_=5000,L_=5000000,M_=5000;
  for(i=0; i<N_; i++)X_[i]=Rand()%1000000000;
  sort(X_,X_+N_);
  for(int i=1;i<N_;i++)assert(X_[i-1]<=X_[i]); 
  for(i=0; i<M_; i++)ii[i]=Rand()%N_,yy[i]=Rand()%1000000000;
//  puts("a");
//    my_assert(3==scanf("%d %d %d",&ii[i],&yy[i],&sol[i]));
puts("aaaInput finished.");
}
//int init(int a,int b,int c[]);
//int update(int a,int b);
int main()
{
  int i, ans;

  read_input();
//	get_random_input();
	puts("b");
  init(N_,L_,X_);
  for(i=0; i<M_; i++) {
    ans = update(ii[i],yy[i]);
    if(ans==sol[i]||1)continue;
      printf("Incorrect.  In %d-th move, answered %d (%d expected).\n",
	     i+1, ans, sol[i]);
    return 0;
  }
  printf("Correct.\n");
  return 0;
}
