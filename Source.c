#define _CRT_SECURE_NO_DEPRECATE﻿
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#define MAX_EVENTS 120
typedef struct {
	int h;
	int m;
	int node;
	int requests;
	int failures;
} Event;
int parseEvent(const char* line, Event* e);
int addEvent(Event buffer[], int* count, const Event* e);
int to_minutes(int h, int m);
int is_duplicate(Event a, Event b);
int filter_duplicates(Event buffer[], int* count, const Event new_events[], int new_count);
int readEventsFromFile(const char* filename, Event events[], int max_events);
int main() {
    Event buffer[MAX_EVENTS];
	int count;
	setlocale(LC_ALL, "RUS");
	printf("\tЗдравствуй, пользователь!\n");
	printf("Данная программа создана студентом первого курса ВГТУ ФИТКБ бТИИ-261 Серебряков А.Г.\n");
	printf("для формирования и анализа архива событий DNS-сервера (фильтрация дубликатов и архивация по регламенту)\n");
	count = readEventsFromFile("../Events.txt", buffer, MAX_EVENTS);
		if (count == -1) {
			return -1;
		}
	for (int i = 0; i < count; i++) {
		printf("%d. %02d:%02d %d %d %d\n", i + 1 , buffer[i].h, buffer[i].m, buffer[i].node, buffer[i].requests, buffer[i].failures);
	}
}
int parseEvent(const char* line, Event* e) {
	int parsed = sscanf(line, "%d:%d %d %d %d", &e->h, &e->m, &e->node, &e->requests, &e->failures);
		if (parsed == 5 && e->h >= 0 && e->h < 24 && e->m >= 0 && e->m < 60 && e->node >= 0 && e->requests >= 0 && e->failures >= 0) {
			return 1;
		}
		else {
			return 0;
		}
}
int addEvent(Event buffer[], int* count, Event* e) {
	if (*count >= MAX_EVENTS) {
		return 0;
	}
	buffer[*count] = *e;
	(*count)++;
	return 1;
}
int to_minutes(int h, int m) {
	int mh = h * 60 + m;
	return mh;
}
int is_duplicate(Event a, Event b) {
	if (a.node == b.node && a.requests == b.requests && abs(to_minutes(a.h, a.m) - to_minutes(b.h, b.m) <= 10)) {
		return 1;
	}
	else {
		return 0;
	}
}
int filter_duplicates(Event buffer[], int* count, const Event new_events[], int new_count) {
	int dup_count = 0;
	for (int i = 0; i < new_count; i++) {
		int is_dub = 0;
		for (int j = 0; j < *count ; j++) {
			if (is_duplicate(buffer[j], new_events[i]) == 1) {
				is_dub = 1;
				break;
			}
		}
		if (is_dub == 1) {
			dup_count++;
		}
		else {
			addEvent(buffer, count, &new_events[i]);
		}
	}
	return dup_count;
}
int readEventsFromFile(const char* filename, Event events[], int max_events) {
	int count = 0;
	char line[256];
	FILE* f = fopen(filename, "r");
	if (f == NULL) {
		return -1;
	}
	while(fgets(line, sizeof(line), f)!= NULL ) {
		if (count == max_events) {
			break;
		}
		if (parseEvent(line, &events[count]) == 1) {
			count++;
		}
		
	}
	fclose(f);
	return count;

}

