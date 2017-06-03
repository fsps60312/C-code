#include<stdio.h>

#include<algorithm>

using namespace std;

#define N 2000005

int s[N]={0},a[N]={0},b[N]={0};

void CC(){

    int i,len;

    for(i=2000000;s[i]==0 && i>=0;i--);

    len=i+1;

    if(s[0]==2) s[0]=0,s[1]++;

    if(s[0]==3) s[0]=0,s[2]++;

    if(s[1]==2) s[1]=0,s[0]++,s[2]++;

    for(i=len-1;i>=2;i--){

        while(s[i] && s[i+1]){

            if(s[i+2] && s[i+3]==0) continue;

            s[i]--;

            s[i+1]--;

            s[i+2]++;

        }

        if(s[i]==3)//s[i+2]==0,s[i+1]==0

            s[i]=0,s[i-2]++,s[i+2]++;

        if(s[i]==2)

            s[i]=0,s[i-2]++,s[i+1]++;

    }

    for(i=2000000;s[i]==0 && i>=0;i--);

    len=i+1;

    for(i=0;i<=200000;i++){

        if(s[i] && s[i+1]){

            if(s[i+2] && s[i+3]==0) continue;

            s[i]--;

            s[i+1]--;

            s[i+2]++;

        }

    }

}

int main(){

    int n,m,len,i,j;

    scanf("%d",&n);

    for(i=0;i<n;i++)

        scanf("%d",&a[i]);

    scanf("%d",&m);

    for(i=0;i<m;i++)

        scanf("%d",&b[i]);

    len=max(n,m);

    for(i=0;i<len;i++)

        s[i]=a[i]+b[i];

    CC();

    for(i=2000000;s[i]==0 && i>=0;i--);

    len=i+1;

    printf("%d",len);

    for(i=0;i<len;i++)

        printf(" %d",s[i]);

    puts("");

}
