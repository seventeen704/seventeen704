#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp;
	FILE *fq;
	FILE *fo;

	fp = fopen ("packet2.txt", "r");
	fq = fopen ("rule1.txt","r");
	fo = fopen ("res2.txt","w");
	
	//规则集变量
	int ip10[1000],ip11[1000],ip12[1000],ip13[1000];//源IP地址
	int ip20[1000],ip21[1000],ip22[1000],ip23[1000];//目的IP地址
 	int w1[10000],w2[10000];
	int opo2[10000],opo3[10000];//源端口范围
	int ppo2[10000],ppo3[10000];//目的端口范围
	int h2[10000],h3[10000];//协议号
	long long int i=0;
	long long int m;
	long long int n;
	long long int a,f,j,k;
	
	//数据集变量
	long long int ip0[10000];//十进制的源IP地址
	int ip00[1000],ip01[1000],ip02[1000],ip03[1000];//源IP地址
	long long int b[100],c[100];
	long long int ip3[10000];//十进制的目的IP地址
	int ip30[1000],ip31[1000],ip32[1000],ip33[1000];//目的IP地址
	long long int opo1[10000],ppo1[10000];//源、目的端口
	long long int h1[10000];//协议号
	long long int x[10000];
	int cnt;
	
	//读入规则集
	while(16 == fscanf(fq, "@%d.%d.%d.%d/%d %d.%d.%d.%d/%d %d : %d %d : %d %x/%x\n",&ip10[i],&ip11[i],&ip12[i],&ip13[i],&w1[i],&ip20[i],&ip21[i],&ip22[i],&ip23[i],&w2[i],&opo2[i],&opo3[i],&ppo2[i],&ppo3[i],&h2[i],&h3[i]))
	{
		//printf("%d ",i+1);
		//printf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",ip10[i],ip11[i],ip12[i],ip13[i],w1[i],ip20[i],ip21[i],ip22[i],ip23[i],w2[i],opo2[i],opo3[i],ppo2[i],ppo3[i],h2[i],h3[i]);
		i++;
	}
	a=i-1;//规则集行数
	i=0;
	while(5 == fscanf(fp, "%lld %lld %lld %lld %lld", &ip0[i],&ip3[i],&opo1[i],&ppo1[i],&h1[i]))
	{
		int j=0;
		while(ip0[i]!=0 || ip3[i]!=0 )//数据集IP地址转换，十进制转换成点分十进制
		{  
			b[j]=ip0[i]%16;
			c[j]=ip3[i]%16;
			ip0[i]=ip0[i]/16;
			ip3[i]=ip3[i]/16;
			j++;
		}
		ip00[i]=b[j-1]*16+b[j-2]*1;
		ip30[i]=c[j-1]*16+c[j-2]*1;
		ip01[i]=b[j-3]*16+b[j-4]*1;
		ip31[i]=c[j-3]*16+c[j-4]*1;
		ip02[i]=b[j-5]*16+b[j-6]*1;
		ip32[i]=c[j-5]*16+c[j-6]*1;
		ip03[i]=b[j-7]*16+b[j-8]*1;
		ip33[i]=c[j-7]*16+c[j-8]*1;
		//以下进行匹配过程思路：借用计数器，只有当源、目的IP地址，源、目的端口、协议号都匹配的时候才算匹配。
		for(k=0;k<=a;k++)
		{
			cnt=0;
			if(ip00[i]!=ip10[k] || ip01[i]!=ip11[k] || ip02[i]!=ip12[k] || ip03[i]!=ip13[k])//源IP地址比对
			{
				cnt++;
			}
			if(ip30[i]!=ip20[k] || ip31[i]!=ip21[k] || ip32[i]!=ip22[k] || ip33[i]!=ip23[k])//目的IP地址比对
			{
				cnt++;
			}
			if(opo1[i]<opo2[k] || opo1[i]>opo3[k])//源端口比对
			{
				cnt++;
			}
			if(ppo1[i]<ppo2[k] || ppo1[i]>ppo3[k])//目的端口比对
			{
				cnt++;
			}
			if(h3[k] == 255)//协议号比对
			{
				if(h1[i]!=h2[k])
				cnt++;
			}
			if(cnt == 0)
			{
				x[i]=k;
				break;
			}
		}
		if(k==a+1)
		{
			x[i]=-1;
		}
		fprintf(fo,"%d\n", x[i]);  //输出为文件
		i++;
	}
//	f=i-1;//规则集数据行数
//	for(i=0;i<=f;i++)
//	{
//		printf("%d ",i+1);
//		printf("%lld\n",x[i]);
//	}
 }
