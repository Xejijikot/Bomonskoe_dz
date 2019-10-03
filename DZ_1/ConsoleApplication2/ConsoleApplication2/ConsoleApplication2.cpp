#include "stdafx.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MAKESTRING(p1, p2)     pNew->p1 = (char*)malloc(strlen(p2)+1);\
    strncpy(pNew->p1, p2, strlen(p2)+1);

typedef struct TAG_LIST
{
	struct TAG_LIST *next;
	char *word;
} list_t;

int Compare(char *str1, char *str2) {
	for (int i = 0; str1[i] != '\0' || str2[i] != '\0'; i++) {
		if (str1[i] != str2[i])
			return 0;
	}
	return 1;
}

int get_word_from_console(char **ppCWord)
{
	char c;
	int malloc_size = 10;
	int real_size = 0;
	char *pCWord = (char *)malloc(malloc_size);
	pCWord[real_size] = '\0';
	while ((c = getchar()) != '\n')
	{
		if (real_size + 2 > malloc_size)
		{
			malloc_size *= 2;
			pCWord = (char *)realloc(pCWord, malloc_size);
			if (pCWord == NULL)
				return -1;
		}
		pCWord[real_size++] = c;
		pCWord[real_size] = '\0';
	}
	*ppCWord = pCWord;
	return 1;
}

void push(list_t **pHead, char *pWord)
{
	list_t *pNew = (list_t*)malloc(sizeof(list_t));

	MAKESTRING(word, pWord);

	pNew->next = (*pHead);
	*pHead = pNew;
}

int Remove_volume(list_t **pHead, char *pWord)

{
	list_t *pCheck;
	pCheck = *pHead;
	list_t *pHelp = pCheck;
	if (Compare(pCheck->word, pWord))
	{
		(*pHead) = pCheck->next;
		free(pCheck);
		return 1;
	}
	pCheck = pCheck->next;
	while (pCheck != NULL)
	{
		if (Compare(pCheck->word, pWord))
		{
			pHelp->next = pCheck->next;
			free(pCheck);
			return 1;
		}
		else
		{
			pHelp = pCheck;
			pCheck = pCheck->next;
		}
	}
	return 0;
}

void print(list_t **pHead) {
	list_t *help;
	help = (*pHead);
	while (help != NULL) {
		printf("%s  ", help->word);
		help = help->next;
	}
}

int main()
{
	system("chcp 1251");
	system("cls");

	list_t *list1 = NULL;
	list_t *list2 = NULL;

	printf("Введите количество символов 1 множества:");

	int N;
	scanf("%d", &N);
	getchar();

	for (int i = 0; i<N; i++) 
	{
		
		char *c;
		get_word_from_console(&c);
		push(&list1, c);
	}

	printf("Введите количество символов 2 множества:");

	scanf("%d", &N);
	getchar();


	for (int i = 0; i<N; i++)
	{

		char *c;
		get_word_from_console(&c);
		push(&list2, c);
	}
	int pointer;
	int pointer2;

	while (1)
	{
		printf("Выберите пункт:\n1.Вывести элементы множеств\n2.Добавить элемент множества\n3.Удалить элемент множества\n4.Завершение работы");
		scanf("%d", &pointer);
		getchar();
		switch (pointer)
		{
			case 1:
			{
				printf("\nЭлементы 1 множества:  ");
				print(&list1);
				printf("\nЭлементы 2 множества:  ");
				print(&list2);
				break;
			}
			case 2:
			{
				printf("Введите номер множества:");
				scanf("%d", &pointer2);
				getchar();
				switch (pointer2)
				{
				case 1:
				{
					printf("Введите элемент 1 множества");
					char *c;
					get_word_from_console(&c);
					push(&list1, c);
					break;
				}
				case 2:
				{
					printf("Введите элемент 2 множества");
					char *c;
					get_word_from_console(&c);
					push(&list1, c);
					break;
				}
				default:
					printf("Неверный номер");
					break;
				}
				break;
			}
			case 3:
			{
				printf("Введите номер множества:");
				scanf("%d", &pointer2);
				getchar();
				switch (pointer2)
				{
				case 1:
				{
					printf("Введите элемент 1 множества");
					char *c;
					get_word_from_console(&c);
					Remove_volume(&list1, c);
					break;
				}
				case 2:
				{
					printf("Введите элемент 2 множества");
					char *c;
					get_word_from_console(&c);
					Remove_volume(&list2, c);
					break;
				}
				default:
					printf("Неверный номер");
					break;
				}
				break;
			}
			case 4:
				exit(0);
		}
		getchar();
	}
    return 0;
}

