# 第一次commit:

## 1.git clone数据

打开git bash输入git clone  https://github.com/zhaoxizxzx/dataset
会成功将数据克隆到dataset文件夹中

![](https://img2022.cnblogs.com/blog/2724887/202201/2724887-20220121233059706-262160140.png)

## 2.如何使用C语言读取文本

例如：读取packet1.txt文件

代码如下：

#include<stdio.h>
#include<stdlib.h>

int main()
{
	int ch;
	FILE *fp;//文件指针
	char fname[50];	// 储存文件名
	printf("Enter　the　name　of　the　file:　");
	scanf("%s",fname);
	fp = fopen(fname,"r");	// 打开待读取文件
	if (fp == NULL)// 如果失败
	{
		printf("Failed　to　open　file.　Bye\n");
		exit(1); // 退出程序
	}
	while((ch=getc(fp))!=EOF)
		putchar(ch);
	fclose(fp);// 关闭文件
	return 0;
}

刚开始时，没有将packet1.txt与代码文件放在同一个目录中，所以没有成功读取。

![](https://img2022.cnblogs.com/blog/2724887/202201/2724887-20220121232510975-1667456589.png)

于是，通过搜索资料，我试着把二者放在同一个目录下（同一个文件夹里），随后成功读取了packet1.txt中的数据

![](https://img2022.cnblogs.com/blog/2724887/202201/2724887-20220121232500627-1797853322.png)

## 3.将生成的数据输出为文件

以工人发放工资为例，代码如下：

#include <stdio.h>  
#include <stdlib.h>  

int main()  
{  

```c
FILE *fp;  
int i, No;  
int salary;  
fp=fopen("data.txt","w");  
if(fp==NULL) 
{  
	printf("File cannot open! " );  
	exit(0);  
}  
//输入5名员工的工号及工资，并保存到文件中  
for(i=0; i<5; i++)  
{  
	scanf("%d %d", &No, &salary);  
	fprintf(fp,"%d, %d\n", No, salary);  
}  
fclose(fp);  
return 0;  
```

}  

![](https://img2022.cnblogs.com/blog/2724887/202201/2724887-20220121234300622-2079358790.png)

在保存代码的文件夹里就能找到输出的文件

![](https://img2022.cnblogs.com/blog/2724887/202201/2724887-20220121234325913-282315847.png)

![](https://img2022.cnblogs.com/blog/2724887/202201/2724887-20220121234417180-1097854880.png)

## 4.参考文献

1.C Primer Plus 第6版中文版

2.https://blog.csdn.net/Zzwtyds/article/details/75095698?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2~default~CTRLIST~Rate-1.pc_relevant_aa&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2~default~CTRLIST~Rate-1.pc_relevant_aa&utm_relevant_index=2

3.https://blog.csdn.net/weixin_43503632/article/details/106030959

