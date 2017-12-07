#include <stdio.h>
#include <string.h>
#include <io.h>
#include <conio.h>
#include <stdlib.h>

//폴더 경로 총 3군데 지정해줘야 함!(Specify the path to the folder you want to search!)
//line 55, line 92, line 413

typedef struct hello
{
	char filename[30]; //해당 파일의 이름
	int yescount; //단어가 있는 경우 몇번 있는지
	int contain; //단어를 몇번 포함하는지
	int coin; //몇 글자가 일치하는지
	int nocount; //일치하는 경우 몇번 있는지
}bello;

typedef struct yes //단어 있는 경우
{
	char yesname[30];
	int yescount;
}Yes;

typedef struct include //없는데 포함하는 경우
{
	char inname[30];
	int contain;
}In;

typedef struct coincide //없는데 앞글자 일치 정도(유사도)
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
	int include = 0; // 사용자가 입력한 단어가 파일의 단어에 포함되는 경우
	int noword = 0; //사용자가 입력한 단어가 파일의 단어에 앞부분에 일부 있을 때
	int nowordmax = 2; // 위의 숫자의 경우 중 제일 큰 경우(글자수가 가장 많이 일치할 경우)
	int nowordmaxc = 0;
	struct _finddata_t fd;
	long handle;
	int result = 1;
	int filecount = 0;
	char filename[30];
	char ChangeDir[60] = { "c:dataset-2nd\\" }; //경로 설정 1.(Setting path 1)
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
		printf("score에 자리없음!");
		exit(1);
	}

	if ((have = (Yes*)malloc(sizeof(Yes)*filecounter())) == NULL)
	{
		printf("have에 자리없음!");
		exit(1);
	}

	if ((in = (In*)malloc(sizeof(In)*filecounter())) == NULL)
	{
		printf("in에 자리없음!");
		exit(1);
	}

	if ((coin = (Co*)malloc(sizeof(Co)*filecounter())) == NULL)
	{
		printf("coin에 자리없음!");
		exit(1);
	}

	handle = _findfirst("c:dataset-2nd\\*.*", &fd); //경로 설정 2(Setting path 2)
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

	printf("원하는 단어를 입력하시오. : ");
	scanf("%s", str);

	size = strlen(str);

	if (96 < str[0] && str[0] < 123) //str이 소문자로만 구성될 경우 -> 대문자가 포함 된 경우에도 검색 가능해야 하므로.
	{
		strcpy(b1, str);
		b1[0] = str[0] - 32;  //str의 제일 첫번째 글자를 대문자로 바꿔준다.
		strcpy(b2, str);
		strupr(b2);//str을 전부 대문자로 바꿔준다.
	}

	else if (64 < str[0] && str[0] < 91) //첫 글자가 대문자일때
	{
		if (64 < str[1] && str[1] < 91) // 두번째 글자도 대문자인경우
		{
			strcpy(b1, str);
			strlwr(b1);
			b1[0] = b1[0] - 32;//str을 첫번째 문자를 제외하고 전부 소문자로 바꿔준다.
			strcpy(b2, str);
			strlwr(b2); //str을 전부 소문자로 바꿔준다.
		}

		else if (96 < str[1] && str[1] < 123) // 두번째 글자가 소문자인 경우
		{
			strcpy(b1, str);
			b1[0] = str[0] + 32;  //첫번째 문자를 소문자로 바꿔준다.
			strcpy(b2, str);
			strupr(b2); //str을 전부 대문자로 바꿔준다.
		}
	}

	if (chdir(ChangeDir) == 0) //작업 디렉토리 바꿔줌
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
				printf("이 파일은 비어있습니다!");
				return 1;
			}
			do
			{
				fscanf(fp, "%s", word);
				frontchecker(word);
				lastchecker(word);
				frontchecker(word);
				lastchecker(word);

				if (strlen(word) == size) // strstr에서 at을 입력했는데 that도 at으로 인식하는 경우를 막기 위해.
				{
					if (strstr(word, str) != NULL) // 입력한 단어와 일치하는 경우
						count++;
					else if (strstr(word, b1) != NULL) //입력한 단어가 소문자일때 대문자로 제일 첫 글자를 바꾼 경우
						count++;
					else if (strstr(word, b2) != NULL) // 입력한 단어가 소문자일때 모두 대문자로 바꾼 경우
						count++;
				}
				else
					continue;
			} while (!feof(fp));

			(score + i)->yescount = count;

			if ((score + i)->yescount == 0) //단어가 없을 경우
			{
				fseek(fp, 0L, SEEK_SET); //파일 제일 앞으로 이동.
				do
				{
					fscanf(fp, "%s", word);
					frontchecker(word);
					lastchecker(word);
					frontchecker(word);
					lastchecker(word);

					if (size < strlen(word)) // 파일에서 가져온 단어에 사용자가 입력한 단어가 포함되는 경우
					{
						if (strstr(word, str) != NULL) // 입력한 단어와 일치하는 경우
							include++;
						else if (strstr(word, b1) != NULL) //입력한 단어가 소문자일때 대문자로 제일 첫 글자를 바꾼 경우
							include++;
						else if (strstr(word, b2) != NULL) // 입력한 단어가 소문자일때 모두 대문자로 바꾼 경우
							include++; //포함된 횟수 세는거임.
					}
					else
						continue;
				} while (!feof(fp));
				(score + i)->contain = include;
			}

			if ((score + i)->yescount == 0 && (score + i)->contain == 0)
			{
				fseek(fp, 0L, SEEK_SET); //파일 제일 앞으로 이동.
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
						noword = 2; //이미 2개 일치하므로
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
						noword = 2; //이미 2개 일치하므로
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
						noword = 2; //이미 2개 일치하므로
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
						nowordmaxc = 1; //max값이 바꼈으니까
					}
					else if (noword == nowordmax)
					{
						nowordmaxc++; //같은 경우가 많을 수록 앞에
					}

				} while (!feof(fp));
				(score + i)->coin = nowordmax;
				(score + i)->nocount = nowordmaxc;
			}
			fclose(fp);
		}
	}

	printf("\n\n-------------------------결과----------------------\n\n");

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
	printf("------------단어 있는 경우----------- \n");
	for (i = 0; i < filecount; i++)
	{
		if ((have + i)->yescount > 0)
		{
			printf(" [순위%d] - %s, %d번\n", rank, (have + i)->yesname, (have + i)->yescount);
			rank++;
		}
	}

	printf("------------단어는 없지만 포함하는 경우----------- \n");
	for (i = 0; i < filecount; i++)
	{
		if ((in + i)->contain > 0)
		{
			printf(" [순위%d] - %s, %d번\n", rank, (in + i)->inname, (in + i)->contain);
			rank++;
		}
	}

	printf("------------단어가 없지만 유사한 단어는 있는 경우----------- \n");
	for (i = 0; i < filecount; i++)
	{
		if ((coin + i)->coincount > 0)
		{
			printf(" [순위%d] - %s %d글자 %d번\n", rank, (coin + i)->coinname, (coin + i)->coin, (coin + i)->coincount);
			rank++;
		}
	}

	printf("------------포함하거나 유사한 단어조차도 없는 경우----------- \n");
	for (i = 0; i < filecount; i++)
	{
		if (!((score + i)->yescount > 0) && !((score + i)->contain > 0))
		{
			if (!((score + i)->nocount > 0))
			{
				printf(" [순위%d] - %s\n", rank, (score + i)->filename);
				rank++;
			}
		}
	}

	getchar();//콘솔창 바로 꺼지는 것 방지
	getchar();//콘솔창 바로 꺼지는 것 방지

	return 0;
}

int filecounter()
{
	struct _finddata_t fd1;
	long handle;
	int result = 1;
	int filecount = 0;

	handle = _findfirst("c:dataset-2nd\\*.*", &fd1); //경로 설정 3(Setting path 3)
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
	int size; //st의 크기
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