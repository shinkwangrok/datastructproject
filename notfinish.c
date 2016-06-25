#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define ID_SIZE 40
#define NAME_SIZE 40
#define STRING_SIZE 40

typedef struct adj {
	char id[ID_SIZE];
	struct adj* nextadj;
}adj;

typedef struct words{
	char string[STRING_SIZE];
	int number;
	int color;
}words;

void words_init(words* self) {
	strcpy_s(self->string, 40, ("none"));
	self->number = 0;
	self->color = 0;
}

typedef struct word{
	char string[40];
	words* wordspointer;
	struct word* nextword;
}word;


typedef struct user{
	char id[ID_SIZE];
	char name[NAME_SIZE];
	int friendnumber;
	int wordnumber;
	int color;
	word* wordpointer;
	struct adj* friendpointer;
}user;

void user_init(user* self) {
	strcpy_s(self->id, 40, ("none"));
	strcpy_s(self->name, 40, ("none"));
	self->friendnumber = 0;
	self->wordnumber = 0;
	self->color = 0;
	self->wordpointer = NULL;
	self->friendpointer = NULL;
}

void user_add(user* self, user* v) {
	adj* a = (adj *)malloc(sizeof(adj));
	strcpy_s(a->id, 20, v->id);
	a->nextadj = self->friendpointer;
	self->friendpointer = a;
	self->friendnumber++;  
}

int totaluser(user vertices)
{
	int num=0;
	if (strcmp(vertices.id, ("none")) == 0)
	{
		return 0;
	}
	return 1;
}

int totalfriends()
{
	int num=0;
	char hope[40];
	FILE* fp;
	fopen_s(&fp, "friend.txt", "rt");
	while (feof(fp) == 0)
	{
		fgets(hope, sizeof(hope), fp);
		fgets(hope, sizeof(hope), fp);
		fgets(hope, sizeof(hope), fp);
		num++;
	}
	return num;
}

int totaltweets(user* vertices)
{
	int num = 0;
	word* v = vertices->wordpointer;
	while (v != NULL)
	{
		v = v->nextword;
		num++;
	}
	return num;
}


void main()
{
	char time[100];
	char enter[100];
	char id1[ID_SIZE];
	char id2[ID_SIZE];
	char words[40];
	int a = 0;
	int b = 0;
	int menu;
	int usernum = 0;
	int minfriend = 5000;
	int maxfriend = 0;
	int tweetnum = 0;
	int mintweet = 5000;
	int maxtweet = 0;
	struct words v;
	user u;
	word *w =(word*)malloc(sizeof(word));
	word *w1;
	adj* f;
	user vertices[5000];
	for (a = 0; a < 5000; a++) {
		user_init(&vertices[a]);
	}
	a = 0;
	FILE* fp;
	fopen_s(&fp, "user.txt", "rt");
	while (feof(fp) == 0) {
		fgets(vertices[a].id, sizeof(vertices[a].id), fp);
		fgets(time, sizeof(time), fp);
		fgets(vertices[a].name, sizeof(vertices[a].name), fp);
		fgets(enter, sizeof(enter), fp);
		a++;
	}
	a = 0;
	fclose(fp);
	fopen_s(&fp, "friend.txt", "rt");
	while (feof(fp) == 0) {
		fgets(id1, sizeof(id1), fp);
		fgets(id2, sizeof(id2), fp);
		fgets(enter, sizeof(enter), fp);
		for (a = 0; a < 5000; a++) {
			if (strcmp(vertices[a].id, id1) == 0) {
				for (b = 0; b < 5000; b++) {
					if (strcmp(vertices[b].id, id2) == 0) {
						user_add(&vertices[a], &vertices[b]);
					}
				}
			}
		}
	}
	fclose(fp);

	fopen_s(&fp, "word.txt", "rt");
	while (feof(fp) == 0)
	{
		
		fgets(id1, sizeof(id1), fp);
		for (a = 0; a < 5000; a++)
		{
			if (strcmp(vertices[a].id, id1) == 0)
			{
				
				fgets(time, sizeof(time), fp);
				word *w = (word*)malloc(sizeof(word));
				fgets(w->string, STRING_SIZE, fp);
				w->nextword = vertices[a].wordpointer;
				vertices[a].wordpointer = w;
				vertices[a].wordnumber++;
				fgets(enter, sizeof(enter), fp);
			}
		}
	}
	fclose(fp);
	for (a = 0; a < 5000; a++)
	{
		usernum += totaluser(vertices[a]);
	}
	for (a = 0; a < 5000; a++)
	{
		tweetnum += totaltweets(&vertices[a]);
		if ((totaltweets(&vertices[a]) < mintweet) && (strcmp(vertices[a].id, ("none"))!=0))
		{
			mintweet = totaltweets(&vertices[a]);
		}
		if ((totaltweets(&vertices[a]) > maxtweet) && (strcmp(vertices[a].id, ("none")) != 0))
		{
			maxtweet = totaltweets(&vertices[a]);
		}
	}
	
	struct words wordvertices[5000];
	for (a = 0; a < 5000; a++)
	{
		words_init(&wordvertices[a]);
	}
	a = 0;
	fopen_s(&fp, "word.txt", "rt");
	while (feof(fp) == 0)
	{
		fgets(id1, sizeof(id1), fp);
		fgets(time, sizeof(time), fp);
		fgets(wordvertices[a].string, 40, fp);
		fgets(enter, sizeof(enter), fp);
		a++;
	}
	fclose(fp);
	word *x = (word *)malloc(sizeof(word));
	for (a = 0; a<5000; a ++)
	{
		x = vertices[a].wordpointer;
		while (x != NULL)
		{
			for (b = 0; b < 5000; b++)
			{
				if (strcmp(wordvertices[b].string, x->string) == 0)
				{
					x->wordspointer = &wordvertices[b];
					wordvertices[b].number = wordvertices[b].number +1;
				}
			}
			x = x->nextword;
		}
	}
	for (;;)
	{
		system("cls");
		printf("0. Read data files\n");
		printf("1. display statistics\n");
		printf("2. Top 5 most tweeted words\n");
		printf("3. Top 5 most tweeted users\n");
		printf("4. Find users who tweeted a word\n");
		printf("5. Find all people who are friends of the above users\n");
		printf("6. Delete all mentions of a word\n");
		printf("7. Delete al users who mentioned a word\n");
		printf("8. Find strongly connected components\n");
		printf("9. Find shortest path from a given user\n");
		printf("99. Quit\n");
		printf("Select Menu: ");
		scanf_s("%d", &menu);
	
		switch (menu) {
		case 0:
			printf("Total users: %d\n", usernum);
			printf("Total friendship records: %d\n", totalfriends());
			printf("Total tweets: %d\n", tweetnum);
			break;
		case 1:
			a = totalfriends();
			printf("Average number of friends: %f\n", (float)a / (float)usernum);
			for (a = 0; a < 5000; a++)
			{
				if ((vertices[a].friendnumber < minfriend) && (strcmp(vertices[a].id, ("none"))) != 0)
				{
					minfriend = vertices[a].friendnumber;
				}
			}
			printf("Minimum friends: %d\n", minfriend);
			for (a = 0; a < 5000; a++)
			{
				if ((vertices[a].friendnumber > maxfriend) && (strcmp(vertices[a].id, ("none"))) != 0)
				{
					maxfriend = vertices[a].friendnumber;
				}
			}
			printf("Maximum number of friends: %d\n", maxfriend);
			printf("Average tweets per user: %f\n", (float)tweetnum / (float)usernum);
			printf("Minimum tweets per user:%d\n", mintweet);
			printf("Maximum tweets per user:%d\n", maxtweet);
			break;
		case 2:
			for (b = 0; b < 5; b++)
			{
				words_init(&v);
				for (a = 0; a < 5000; a++)
				{
					if ((v.number < wordvertices[a].number) && (wordvertices[a].color == 0))
					{
						v = wordvertices[a];
					}
				}
				v.color = 1;
				for (a = 0; a < 5000; a++)
				{
					if (v.number == wordvertices[a].number)
					{
						wordvertices[a].color = 1;
					}
				}
				printf("%s", v.string);
			}
			break;
		case 3:
			for (b = 0; b < 5; b++)
			{
				user_init(&u);
				for (a = 0; a < 5000; a++)
				{
					if ((u.wordnumber < vertices[a].wordnumber) && (vertices[a].color == 0))
					{
						u = vertices[a];
					}
				}
				for (a = 0; a < 5000; a++)
				{
					if (u.wordnumber == vertices[a].wordnumber)
					{
						vertices[a].color = 1;
					}
				}
				printf("%s", u.id);
			}
			break;
		case 4:
			scanf_s("%s", words, sizeof(words));
			for (a = 0; a < 5000; a++)
			{
				w = vertices[a].wordpointer;
				while (w != NULL)
				{
					if (strcmp(w->string, words) == 0)
					{
						vertices[a].color = 2;
					}
					w = w->nextword;
				}
				if (vertices[a].color == 2)
				{
					printf("%s", vertices[a].id);
				}
			}
			break;
		case 5:
			for (a = 0; a < 5000; a++)
			{
				f = vertices[a].friendpointer;
				if (vertices[a].color == 2)
				{
					while (f != NULL)
					{
						printf("%s", f->id);
						f = f->nextadj;
					}
				}
			}
		case 6:
			scanf_s("%s", words, sizeof(words));
			for (a = 0; a < 5000; a++)
			{
				while (strcmp(words, vertices[a].wordpointer->string) == 0)
				{
					vertices[a].wordpointer = vertices[a].wordpointer->nextword;
					vertices[a].wordnumber--;
				}
				w = vertices[a].wordpointer;
				while (w != NULL)
				{
					if (strcmp(words, w->nextword->string) == 0)
					{
						w->nextword = w->nextword->nextword;
						vertices[a].wordnumber--;
					}
					else
					{
						w = w->nextword;
					}
				}
			}
			for (a = 0; a < 5000; a++)
			{
				if (strcmp(wordvertices[a].string, words) == 0)
				{
					wordvertices[a].number = 0;
				}
			}
			break;
		case 7:
			for (a = 0; a < 5000; a++)
			{
				w = vertices[a].wordpointer;
				w1 = vertices[a].wordpointer;
				while (w != NULL)
				{
					if (strcmp(words, w->string) == 0)
					{
						while (w1 != NULL)
						{
							w1->wordspointer->number--;
							w1 = w1->nextword;
						}
						user_init(&vertices[a]);

						while (strcmp(vertices[b].friendpointer->id, words) == 0)
						{
							vertices[b].friendpointer = vertices[b].friendpointer->nextadj;
						}
						f = vertices[b].friendpointer;
						while (f != NULL)
						{
							if (strcmp(f->nextadj->id, words) == 0)
							{
								f->nextadj = f->nextadj->nextadj;
							}
							f = f->nextadj;
						}
					}
					w = w->nextword;
				}
			}
			printf("%d", vertices[0].friendnumber);
			break;
		case 99:
			exit(-1);
		default: break;
		}
		getchar();
		getchar();
	}
	
}