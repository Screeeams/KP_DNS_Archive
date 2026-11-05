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
int main() {




	return 0;
}
int parseEvent(const char* line, Event* e) {
	int parsed = sscanf(line, "%d:%d %d %d %d", &e->h, &e->m, &e->node, &e->requests, &e->failures);
		if (parsed == 5 && &e->h >= 0 && &e->h < 24 && &e->m >= 0 && &e->m < 60 && &e->node >= 0 && &e->requests >= 0 && &e->failures >= 0) {
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
