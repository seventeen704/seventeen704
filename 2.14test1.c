#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int main()
{
	long start,end;
	long q = 10000000L;
	double duration;
	start = clock() ;
	FILE *fp;
	FILE *fq;
	FILE *fo;
	//打开文件
	fp = fopen ("packet1.txt", "r");
	fq = fopen ("rule.txt","r");
	fo = fopen ("res1.txt","w");
	
	//规则集变量
	int ip1[1000][100];//读入的源IP地址
	char ip_1[10][10];//储存八位的二进制源IP地址
	char ip_4[40],ip_5[40],ip_6[40];//储存32位的二进制源IP地址
	char ip_7[40],ip_8[40],ip_9[40];
	long long int ip_11[1000];//最小
	long long int ip_12[1000];//最大
	int ip2[1000][100];//目的IP地址
	char ip_2[10][10];//储存二进制的目的IP地址
	long long int ip_21[1000];//最小
	long long int ip_22[1000];//最大
	int w1[1000],w2[1000];//网络前缀所占位数
	int opo2[1000],opo3[1000];
	int ppo2[1000],ppo3[1000];
	int h2[1000],h3[1000];//协议号
	
	//数据集变量
	long long int ip0[10000];//源IP地址
	long long int ip3[10000];//目的IP地址
	int opo1[10000],ppo1[10000];//源、目的端口
	int h1[10000];//协议号
	
	long long int x[10000];
	int cnt;
	long long int i=0;
	long long int m;
	long long int n;
	long long int a,f,j,k,l;
	
	
	
	//读入规则集    转换IP地址
	//转换IP地址思路：先把四个十进制数字转换成32位的二进制数字（四个拼接），再根据网络前缀所占位数，把后面的数字全变为0或者1，然后再转换成十进制
	while(16 == fscanf(fq, "@%d.%d.%d.%d/%d %d.%d.%d.%d/%d %d : %d %d : %d %x/%x\n",&ip1[i][0],&ip1[i][1],&ip1[i][2],&ip1[i][3],&w1[i],&ip2[i][0],&ip2[i][1],&ip2[i][2],&ip2[i][3],&w2[i],&opo2[i],&opo3[i],&ppo2[i],&ppo3[i],&h2[i],&h3[i]))
	{
//		printf("%d ",i+1);
//	    printf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",ip1[i][0],ip1[i][1],ip1[i][2],ip1[i][3],w1[i],ip2[i][0],ip2[i][1],ip2[i][2],ip2[i][3],w2[i],opo2[i],opo3[i],ppo2[i],ppo3[i],h2[i],h3[i]);		
			for(j=0;j<=3;j++)
			{
				char ip_3[10]="00000000";
				itoa(ip1[i][j],ip_1[j],2);
				m=strlen(ip_1[j]);//决定补几个0
				k=0;
				if(m<=8)
				{
					for(l=8-m;l<=7;l++)
					{
						ip_3[l]=ip_1[j][k];
						k++;
						if(k == m)
						break;
					}
				}
				strcpy(ip_1[j],ip_3);
			}
			strcpy(ip_4,ip_1[0]);
			for(j=1;j<=3;j++)
			{
				strcat(ip_4,ip_1[j]);
			}//最后的ip_4就是所求的32位的二进制字符串

//			
//			printf("\n");
//		}

		//再根据网络前缀所占位数求出最小和最大
		strcpy(ip_5,ip_4);
		strcpy(ip_6,ip_4);
		for(j=w1[i];j<=31;j++)
		{
			ip_5[j]='0';
		}
		for(j=w1[i];j<=31;j++)
		{
			ip_6[j]='1';
		}
		ip_11[i]=0;
		ip_12[i]=0;
		for(j=0;j<32;++j) 
		{
			if (ip_5[j] == '1') 
			{
				ip_11[i]+=pow(2.0,32-j-1);
			}
		}
		for(j=0;j<32;++j) 
		{
			if (ip_6[j] == '1') 
			{
				ip_12[i]+=pow(2.0,32-j-1);
			}
		}
				
		//目的IP地址
		for(j=0;j<=3;j++)
			{
				char ip_3[10]="00000000";
				itoa(ip2[i][j],ip_2[j],2);
				m=strlen(ip_2[j]);//决定补几个0
				k=0;
				if(m<=8)
				{
					for(l=8-m;l<=7;l++)
					{
						ip_3[l]=ip_2[j][k];
						k++;
						if(k == m)
						break;
					}
				}
				strcpy(ip_2[j],ip_3);
			}
			strcpy(ip_7,ip_2[0]);
			for(j=1;j<=3;j++)
			{
				strcat(ip_7,ip_2[j]);
			}//最后的ip_4就是所求的32位的二进制字符串

//			
//			printf("\n");
//		}

		//再根据网络前缀所占位数求出最小和最大
		strcpy(ip_8,ip_7);
		strcpy(ip_9,ip_7);
		for(j=w2[i];j<=31;j++)
		{
			ip_8[j]='0';
		}
		for(j=w2[i];j<=31;j++)
		{
			ip_9[j]='1';
		}
		ip_21[i]=0;
		ip_22[i]=0;
		for(j=0;j<32;++j) 
		{
			if (ip_8[j] == '1') 
			{
				ip_21[i]+=pow(2.0,32-j-1);
			}
		}
		for(j=0;j<32;++j) 
		{
			if (ip_9[j] == '1') 
			{
				ip_22[i]+=pow(2.0,32-j-1);
			}
		}
//		printf("%d ",i+1);
//		printf("%s %s %s %lld %lld\n",ip_4,ip_5,ip_6,ip_11[i],ip_12[i]);
//		printf("%s %s %s %lld %lld\n",ip_7,ip_8,ip_9,ip_21[i],ip_22[i]);
		i++;
	}
	a=i-1;//规则集行数
	i=0;
	while(5 == fscanf(fp, "%lld %lld %d %d %d", &ip0[i],&ip3[i],&opo1[i],&ppo1[i],&h1[i]))
	{
		for(k=0;k<=a;k++)
		{
			cnt=0;
			if(ip0[i]<ip_11[k] || ip0[i]>ip_12[k])
			{
				cnt++;
			}
			if(ip3[i]<ip_21[k] || ip3[i]>ip_22[k])
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
		fprintf(fo,"%d\n", x[i]); 
//		printf("%d ",i+1);
//		printf("%lld\n",x[i]);
		i++;
	}
	while( q-- );
	end = clock() ;
	duration = (double)(end - start) / CLOCKS_PER_SEC;
	printf("%fms\n",duration);//单位：毫秒
	
//	f=i-1;//规则集数据行数
//	for(i=0;i<=f;i++)
//	{
//		printf("%d ",i+1);
//		printf("%lld\n",x[i]);
//	}
	return 0;
}
