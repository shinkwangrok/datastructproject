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
}words;

void words_init(words* self) {
	strcpy_s(self->string, 40, ("none"));
	self->number = 0;
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
	word* wordpointer;
	struct adj* friendpointer;
}user;

void user_init(user* self) {
	strcpy_s(self->id, 40, ("none"));
	strcpy_s(self->name, 40, ("none"));
	self->friendnumber = 0;
	self->wordnumber = 0;
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

	scanf_s("%d", &menu);
	switch (menu) {
	case 0:
		printf("Total users: %d\n", usernum);
		printf("Total friendship records: %d\n", totalfriends());
		printf("Total tweets: %d\n", tweetnum);
		break;
	case 1:
		a = totalfriends();
		printf("Average number of friends: %f\n", (float)a/(float)usernum);
		for (a = 0; a<5000; a++)
		{
			if ((vertices[a].friendnumber < minfriend) && (strcmp(vertices[a].id,("none")))!=0)
			{
				minfriend = vertices[a].friendnumber;
			}
		}
		printf("Minimum friends: %d\n", minfriend);
		for (a = 0; a<5000; a++)
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

	default: break;
	}
	getchar();
	getchar();
}