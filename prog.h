#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

struct Student {
	char* Name;
	int Group;
	double Rating;
	int isElder;
};

void quick_sortG(struct Student**, int, int);
void quick_sortR(struct Student**, int, int);
int progItSelf(const char* fileName, struct Student*** ans, int* k1);
int AutoTest();