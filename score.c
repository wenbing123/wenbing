/*************************************************
** Դ�ļ�   : score.c
** ����˵�� : Function Definitions
** �����汾 : V1.0
/**************************************************/

/*----------------ͷ�ļ�--------------*/
#define  _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "SCORE.h"

/*----------------��������-------------*/

//1.1�ֶ�����ѧ����������
void readData(SS stu[], int N)
{

	printf("�밴�����¸�ʽ����ѧ����Ϣ��ѧ��,����,ƽʱ�ɼ�,��ĩ�ɼ���ʵ��ɼ�\n");

	for (int i = 0; i < N; i++)
	{
		printf("��%d��ѧ��:", i + 1);
		scanf("%s %s %f %f %f", &stu[i].number, &stu[i].name, &stu[i].dailyScore, &stu[i].finalScore, &stu[i].expScore);
		printf("\n");
	}

	printf("------�ɼ�¼�����!--------\n");

}

//1.2���ļ����ȡѧ����������
SS* readDataFromFile(int *N)
{

	printf("\n\n------��һ��: ���ļ���ȡѧ���ĳɼ���Ϣ--------\n\n");

	SS *stu;// �����¿ռ�,��ȡ�ļ��е�ÿ��ѧ����Ϣ

	FILE *fp = NULL;
	int count = 0;
	int index = 0;

	fp = fopen("data.txt", "r");

	//1.��ȡѧ����Ŀ
	if (fp != NULL)
	{
		fscanf(fp, "%d", &count);
		*N = count;
	}
	else
	{
		printf("failed to open the info file\n");
		getchar();
	}

	printf("ѧ����ĿΪ:%d\n", count);


	//2.������ѧ������洢�ռ�
	stu = (SS*)malloc(count * sizeof(SS));


	//3.��ȡÿ��ѧ������Ϣ
	while ((!feof(fp)))
	{

		//�����ļ����ݵ��ڴ�	
		fscanf(fp, "%s%s%f%f%f\n", (stu[index].number), (stu[index].name), &stu[index].dailyScore,&stu[index].expScore, &stu[index].finalScore);

		//���������ѧ����Ϣ
		printf("* ѧ�ţ�%s	����:%s		ƽʱ�ɼ���%4.2f��	ʵ��ɼ���%4.2f��	��ĩ�ɼ�:%4.2f��\n", (stu[index].number), (stu[index].name), stu[index].dailyScore, stu[index].expScore, stu[index].finalScore);

		index++;
	}

	getchar();

	fclose(fp);

	return stu;
}

//2.����N��ѧ�����Ե������ɼ�
void calcuScore(SS stu[], int N)
{


	printf("\n\n------�ڶ���: ����ÿ��ѧ���������ɼ�--------\n\n");

	for (int i = 0; i < N; i++)
	{

		stu[i].generalScore = 0.2*stu[i].dailyScore + 0.2*stu[i].expScore + 0.6*stu[i].finalScore;
		printf("* ѧ�ţ�%s	����:%s		�ܳɼ�:%4.2f��\n", (stu[i].number), (stu[i].name), stu[i].generalScore);

	}

	getchar();
}


//3.���������ɼ�����
int cmpBigtoSmall(const void *a, const void *b)
{

	SS *aa = (SS *)(a);
	SS *bb = (SS *)(b);



	if ((*aa).generalScore < (*bb).generalScore)  return 1;

	else if ((*aa).generalScore > (*bb).generalScore)  return -1;

	else
		return 0;

}

void sortScore(SS stu[], int N)
{

	qsort(&(stu[0]), N, sizeof(stu[0]), cmpBigtoSmall);

}

//4.����һ���ĸ�ʽ���N��ѧ������Ϣ
void printOut(SS stu[], int N)
{

	printf("\n------������: �����ܳɼ����ѧ��������Ϣ!------\n\n");

	for (int i = 0; i < N; i++)
	{

		printf("��%d����Ϣ ѧ�ţ�%s	����:%s		�ܳɼ�:%4.2f��\n", i + 1, &(stu[i].number[0]), &(stu[i].name[0]), stu[i].generalScore);
	}

	getchar();

}
//5.����ѧ�Ų�ѯ�ɼ�
void findScore(SS stu[], int N)
{
	printf("\n-------���Ĳ�����������Ҫ��ѯѧ����ѧ��--------\n\n");
	char b[11];
	scanf("%s", b);
	int i;
	for (i = 0; i < N; i++)
	{
		if (strcmp(b, stu[i].number) == 0)
			printf("* ѧ�ţ�%s	����:%s		ƽʱ�ɼ���%4.2f��	ʵ��ɼ���%4.2f��	��ĩ�ɼ�:%4.2f��\n", (stu[i].number), (stu[i].name), stu[i].dailyScore, stu[i].expScore, stu[i].finalScore);
		break;
	}if ((strcmp(b, stu[N - 1].number) > 0) || (strcmp(b, stu[N - 1].number) < 0) && (i== N))printf("��ѯ������ѧ������Ϣ\n");
}
//6.����ѧ���ɼ���Ϣ
void anaScore(SS stu[], int N)
{
	float aver, vari, add1 = 0, add2 = 0;
	for (int i = 0; i < N; i++)
	{
		add1 = add1 + stu[i].finalScore;
	}
	aver = add1 / N;
	for (int i = 0; i < N; i++)
	{
		add2 = add2 + (stu[i].finalScore - aver)*(stu[i].finalScore - aver);
	}
	vari = add2 / N;
	printf("��ֵΪ%f������Ϊ%f\n", aver,vari);
	if (vari > 25)printf("�ɼ�������");
	else printf("�ɼ��Ͼ���");
}