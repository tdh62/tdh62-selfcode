#include"stdio.h"
#define N 1
static int a[N],i,j,k,l,x,cnt=0,cnt1=0,sum=0,sum1=0;
static float pjz1=0,pjz2=0;
int ReadDat(int a[N]){
	printf("请输入%d个四位数:\n",N);
	for(x=0;x<N;x++)
	{
		printf("a[%d]:",x);
		scanf("%d",&a[x]);
	}
	return 0;
}
float jsValue(int a[N]){
	for(x=0;x<N;x++){
		i=a[x]/1000;
		j=(a[x]%1000)/100;
		k=(a[x]%1000%100)/10;
		l=a[x]%1000%100%10;
		if((i+j)==(k+l)){
			cnt=cnt+1;
			sum=sum+a[x];}
		else{
			cnt1=cnt1+1;
			sum1=sum1+a[x];}
	}
	pjz1=(float)sum/cnt;
	pjz2=(float)sum1/cnt1;
	return 0;
}
float WriteDat(float pjz1,float pjz2){
	printf("满足该条件的所有数的平均值为%f\n不满足该条件的所有数的平均值为%f\n",pjz1,pjz2);
	return 0;
}
void main(){
	
	ReadDat(a);
	jsValue(a);
	WriteDat(pjz1,pjz2);
}
