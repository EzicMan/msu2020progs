#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

struct node {
	double x1;
	double y1;
	int inc1;
	double x2;
	double y2;
	int inc2;
	int index;
	double k;
	double b;
	int toDelete;
	struct node* nextNode;
};

struct node* progItSelf(int*);