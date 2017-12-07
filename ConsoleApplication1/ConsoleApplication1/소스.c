#include <stdio.h>
#include <string.h>
#include <io.h>
#include <conio.h>
#include <stdlib.h>

//���� ��� �� 3���� ��������� ��!(Specify the path to the folder you want to search!)
//line 55, line 92, line 413

typedef struct hello
{
	char filename[30]; //�ش� ������ �̸�
	int yescount; //�ܾ �ִ� ��� ��� �ִ���
	int contain; //�ܾ ��� �����ϴ���
	int coin; //�� ���ڰ� ��ġ�ϴ���
	int nocount; //��ġ�ϴ� ��� ��� �ִ���
}bello;

typedef struct yes //�ܾ� �ִ� ���
{
	char yesname[30];
	int yescount;
}Yes;

typedef struct include //���µ� �����ϴ� ���
{
	char inname[30];
	int contain;
}In;

typedef struct coincide //���µ� �ձ��� ��ġ ����(���絵)
{
	char coinname[30];
	int coin;
	int coincount;
}Co;

int filecounter();
void lastchecker(char st[100]);
void frontchecker(char strr[100]);

int main()
{
	char str[100], word[100], b1[100], b2[100];
	int count = 0, size, i, num = 0, j, m, n, k, h;
	int include = 0; // ����ڰ� �Է��� �ܾ ������ �ܾ ���ԵǴ� ���
	int noword = 0; //����ڰ� �Է��� �ܾ ������ �ܾ �պκп� �Ϻ� ���� ��
	int nowordmax = 2; // ���� ������ ��� �� ���� ū ���(���ڼ��� ���� ���� ��ġ�� ���)
	int nowordmaxc = 0;
	struct _finddata_t fd;
	long handle;
	int result = 1;
	int filecount = 0;
	char filename[30];
	char ChangeDir[60] = { "c:dataset-2nd\\" }; //��� ���� 1.(Setting path 1)
	int rank;

	bello *score;
	Yes *have;
	In *in;
	Co *coin;

	Yes temp1;
	In temp2;
	Co temp3;


	if ((score = (bello*)malloc(sizeof(bello)*filecounter())) == NULL)
	{
		printf("score�� �ڸ�����!");
		exit(1);
	}

	if ((have = (Yes*)malloc(sizeof(Yes)*filecounter())) == NULL)
	{
		printf("have�� �ڸ�����!");
		exit(1);
	}

	if ((in = (In*)malloc(sizeof(In)*filecounter())) == NULL)
	{
		printf("in�� �ڸ�����!");
		exit(1);
	}

	if ((coin = (Co*)malloc(sizeof(Co)*filecounter())) == NULL)
	{
		printf("coin�� �ڸ�����!");
		exit(1);
	}

	handle = _findfirst("c:dataset-2nd\\*.*", &fd); //��� ���� 2(Setting path 2)
	if (handle == -1)return;
	while (result != -1)
	{
		if ((strcmp(".", fd.name)) != 0 && (strcmp("..", fd.name)) != 0)
		{
			strcpy(score[filecount].filename, fd.name);
			filecount++;
		}
		result = _findnext(handle, &fd);
	}
	_findclose(handle);

	printf("���ϴ� �ܾ �Է��Ͻÿ�. : ");
	scanf("%s", str);

	size = strlen(str);

	if (96 < str[0] && str[0] < 123) //str�� �ҹ��ڷθ� ������ ��� -> �빮�ڰ� ���� �� ��쿡�� �˻� �����ؾ� �ϹǷ�.
	{
		strcpy(b1, str);
		b1[0] = str[0] - 32;  //str�� ���� ù��° ���ڸ� �빮�ڷ� �ٲ��ش�.
		strcpy(b2, str);
		strupr(b2);//str�� ���� �빮�ڷ� �ٲ��ش�.
	}

	else if (64 < str[0] && str[0] < 91) //ù ���ڰ� �빮���϶�
	{
		if (64 < str[1] && str[1] < 91) // �ι�° ���ڵ� �빮���ΰ��
		{
			strcpy(b1, str);
			strlwr(b1);
			b1[0] = b1[0] - 32;//str�� ù��° ���ڸ� �����ϰ� ���� �ҹ��ڷ� �ٲ��ش�.
			strcpy(b2, str);
			strlwr(b2); //str�� ���� �ҹ��ڷ� �ٲ��ش�.
		}

		else if (96 < str[1] && str[1] < 123) // �ι�° ���ڰ� �ҹ����� ���
		{
			strcpy(b1, str);
			b1[0] = str[0] + 32;  //ù��° ���ڸ� �ҹ��ڷ� �ٲ��ش�.
			strcpy(b2, str);
			strupr(b2); //str�� ���� �빮�ڷ� �ٲ��ش�.
		}
	}

	if (chdir(ChangeDir) == 0) //�۾� ���丮 �ٲ���
	{
		for (i = 0; i < filecount; i++)
		{
			count = 0;
			include = 0;
			nowordmax = 2;
			nowordmaxc = 0;
			FILE *fp = fopen(score[i].filename, "rt");

			if (fp == NULL)
			{
				printf("�� ������ ����ֽ��ϴ�!");
				return 1;
			}
			do
			{
				fscanf(fp, "%s", word);
				frontchecker(word);
				lastchecker(word);
				frontchecker(word);
				lastchecker(word);

				if (strlen(word) == size) // strstr���� at�� �Է��ߴµ� that�� at���� �ν��ϴ� ��츦 ���� ����.
				{
					if (strstr(word, str) != NULL) // �Է��� �ܾ�� ��ġ�ϴ� ���
						count++;
					else if (strstr(word, b1) != NULL) //�Է��� �ܾ �ҹ����϶� �빮�ڷ� ���� ù ���ڸ� �ٲ� ���
						count++;
					else if (strstr(word, b2) != NULL) // �Է��� �ܾ �ҹ����϶� ��� �빮�ڷ� �ٲ� ���
						count++;
				}
				else
					continue;
			} while (!feof(fp));

			(score + i)->yescount = count;

			if ((score + i)->yescount == 0) //�ܾ ���� ���
			{
				fseek(fp, 0L, SEEK_SET); //���� ���� ������ �̵�.
				do
				{
					fscanf(fp, "%s", word);
					frontchecker(word);
					lastchecker(word);
					frontchecker(word);
					lastchecker(word);

					if (size < strlen(word)) // ���Ͽ��� ������ �ܾ ����ڰ� �Է��� �ܾ ���ԵǴ� ���
					{
						if (strstr(word, str) != NULL) // �Է��� �ܾ�� ��ġ�ϴ� ���
							include++;
						else if (strstr(word, b1) != NULL) //�Է��� �ܾ �ҹ����϶� �빮�ڷ� ���� ù ���ڸ� �ٲ� ���
							include++;
						else if (strstr(word, b2) != NULL) // �Է��� �ܾ �ҹ����϶� ��� �빮�ڷ� �ٲ� ���
							include++; //���Ե� Ƚ�� ���°���.
					}
					else
						continue;
				} while (!feof(fp));
				(score + i)->contain = include;
			}

			if ((score + i)->yescount == 0 && (score + i)->contain == 0)
			{
				fseek(fp, 0L, SEEK_SET); //���� ���� ������ �̵�.
				do
				{
					fscanf(fp, "%s", word);
					frontchecker(word);
					lastchecker(word);
					frontchecker(word);
					lastchecker(word);
					noword = 0;

					if (strncmp(str, word, 2) == 0)
					{
						noword = 2; //�̹� 2�� ��ġ�ϹǷ�
						for (num = 2; num < size; num++)
						{
							if (str[num] == word[num])
								noword++;
							else
								break;
						}
					}

					else if (strncmp(b1, word, 2) == 0)
					{
						noword = 2; //�̹� 2�� ��ġ�ϹǷ�
						for (num = 2; num < size; num++)
						{
							if (str[num] == word[num])
								noword++;
							else
								break;
						}
					}

					else if ((strncmp(b2, word, 2)) == 0)
					{
						noword = 2; //�̹� 2�� ��ġ�ϹǷ�
						for (num = 2; num < size; num++)
						{
							if (str[num] == word[num])
								noword++;
							else
								break;
						}
					}

					if (noword > nowordmax)
					{
						nowordmax = noword;
						nowordmaxc = 1; //max���� �ٲ����ϱ�
					}
					else if (noword == nowordmax)
					{
						nowordmaxc++; //���� ��찡 ���� ���� �տ�
					}

				} while (!feof(fp));
				(score + i)->coin = nowordmax;
				(score + i)->nocount = nowordmaxc;
			}
			fclose(fp);
		}
	}

	printf("\n\n-------------------------���----------------------\n\n");

	j = 0, n = 0, m = 0;
	for (i = 0; i < filecount; i++)
	{
		if ((score + i)->yescount > 0)
		{
			strcpy((have + j)->yesname, (score + i)->filename);
			(have + j)->yescount = (score + i)->yescount;
			j++;
		}

		if ((score + i)->contain > 0)
		{
			strcpy(in[n].inname, (score + i)->filename);
			(in + n)->contain = (score + i)->contain;
			n++;
		}

		if ((score + i)->nocount > 0)
		{
			strcpy((coin + m)->coinname, (score + i)->filename);
			(coin + m)->coin = (score + i)->coin;
			(coin + m)->coincount = (score + i)->nocount;
			m++;
		}
	}

	for (k = 0; k < filecount - 1; k++)
	{
		for (h = 0; h < filecount - k - 1; h++)
		{
			if ((have + h)->yescount < (have + h + 1)->yescount)
			{
				temp1 = have[h];
				have[h] = have[h + 1];
				have[h + 1] = temp1;
			}
			else if (!(have[h].yescount > 0))
				break;
		}
	}


	for (i = 0; i < filecount; i++)
	{
		if ((in + i)->contain > 0)
		{
			for (k = 0; k < filecount - 1; k++)
			{
				for (h = 0; h < filecount - k - 1; h++)
				{
					if ((in + h)->contain < (in + h + 1)->contain)
					{
						temp2 = in[h];
						in[h] = in[h + 1];
						in[h + 1] = temp2;
					}
				}
			}
		}
	}

	for (i = 0; i < filecount; i++)
	{
		if ((coin + i)->coincount > 0)
		{
			for (k = 0; k < filecount - 1; k++)
			{
				for (h = 0; h < filecount - k - 1; h++)
				{
					if ((coin + h)->coin < (coin + h + 1)->coin)
					{
						temp3 = coin[h];
						coin[h] = coin[h + 1];
						coin[h + 1] = temp3;
					}
					else if ((coin + h)->coin == (coin + h + 1)->coin)
					{
						if ((coin + h)->coincount < (coin + h + 1)->coincount)
						{
							temp3 = coin[h];
							coin[h] = coin[h + 1];
							coin[h + 1] = temp3;
						}
					}
				}
			}
		}
	}

	rank = 1;
	printf("------------�ܾ� �ִ� ���----------- \n");
	for (i = 0; i < filecount; i++)
	{
		if ((have + i)->yescount > 0)
		{
			printf(" [����%d] - %s, %d��\n", rank, (have + i)->yesname, (have + i)->yescount);
			rank++;
		}
	}

	printf("------------�ܾ�� ������ �����ϴ� ���----------- \n");
	for (i = 0; i < filecount; i++)
	{
		if ((in + i)->contain > 0)
		{
			printf(" [����%d] - %s, %d��\n", rank, (in + i)->inname, (in + i)->contain);
			rank++;
		}
	}

	printf("------------�ܾ ������ ������ �ܾ�� �ִ� ���----------- \n");
	for (i = 0; i < filecount; i++)
	{
		if ((coin + i)->coincount > 0)
		{
			printf(" [����%d] - %s %d���� %d��\n", rank, (coin + i)->coinname, (coin + i)->coin, (coin + i)->coincount);
			rank++;
		}
	}

	printf("------------�����ϰų� ������ �ܾ������� ���� ���----------- \n");
	for (i = 0; i < filecount; i++)
	{
		if (!((score + i)->yescount > 0) && !((score + i)->contain > 0))
		{
			if (!((score + i)->nocount > 0))
			{
				printf(" [����%d] - %s\n", rank, (score + i)->filename);
				rank++;
			}
		}
	}

	free(score);
	free(have);
	free(in);
	free(coin);

	getchar();//�ܼ�â �ٷ� ������ �� ����
	getchar();//�ܼ�â �ٷ� ������ �� ����

	return 0;
}

int filecounter()
{
	struct _finddata_t fd1;
	long handle;
	int result = 1;
	int filecount = 0;

	handle = _findfirst("c:dataset-2nd\\*.*", &fd1); //��� ���� 3(Setting path 3)
	if (handle == -1)return;
	while (result != -1)
	{
		if ((strcmp(".", fd1.name)) != 0 && (strcmp("..", fd1.name)) != 0)
		{
			filecount++;
		}
		result = _findnext(handle, &fd1);
	}
	_findclose(handle);

	return filecount;
}

void lastchecker(char st[100])
{
	int size; //st�� ũ��
	char last;

	size = strlen(st);

	last = st[size - 1];

	switch (last)
	{
	case ',':
		st[size - 1] = '\0';
		break;
	case '-':
		st[size - 1] = '\0';
		break;
	case '.':
		st[size - 1] = '\0';
		break;
	case ')':
		st[size - 1] = '\0';
		break;
	case '!':
		st[size - 1] = '\0';
		break;
	case '~':
		st[size - 1] = '\0';
		break;
	case '?':
		st[size - 1] = '\0';
		break;
	case '\"':
		st[size - 1] = '\0';
		break;
	case '\'':
		st[size - 1] = '\0';
		break;
	default:
		break;
	}
}

void frontchecker(char strr[100])
{
	int size, i;
	char front;

	size = strlen(strr);

	front = strr[0];

	switch (front)
	{
	case '(':
		for (i = 0; i < size - 1; i++)
			strr[i] = strr[i + 1];
		strr[size - 1] = '\0';
		break;
	case '-':
		for (i = 0; i < size - 1; i++)
			strr[i] = strr[i + 1];
		strr[size - 1] = '\0';
		break;
	case '\"':
		for (i = 0; i < size - 1; i++)
			strr[i] = strr[i + 1];
		strr[size - 1] = '\0';
		break;
	case '\'':
		for (i = 0; i < size - 1; i++)
			strr[i] = strr[i + 1];
		strr[size - 1] = '\0';
		break;
	default:
		break;
	}
}