#include "prog.h"

int progItSelf(struct node* firstLine, int* mI1) {
	printf("Enter 'a x1 y1 x2 y2' to add line, 'd index' to delete line, 'l' for list of lines, 'e' to exit\n>");
	char code = 0;
	int mI = *mI1;
	while (1) {
		double x1, y1, x2, y2;
		struct node* cur;
		struct node* toDel;
		int i;
		scanf("%c", &code);
		switch (code)
		{
		case 'a':
			if (scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2) != 4) {
				printf("Error with your request!\n");
			}
			else {
				double k, b;
				if (x1 == x2) {
					printf("Can't add line which consists only of one point!\n");
				}
				if (mI == 0) {
					firstLine = malloc(sizeof(struct node));
					firstLine->x1 = x1;
					firstLine->y1 = y1;
					firstLine->x2 = x2;
					firstLine->y2 = y2;
					firstLine->nextNode = firstLine;
					firstLine->k = (y2 - y1) / (x2 - x1);
					firstLine->b = y2 - firstLine->k * x2;
					firstLine->index = 1;
					mI++;
					firstLine->toDelete = 0;
					break;
				}
				k = (y2 - y1) / (x2 - x1);
				b = y2 - k * x2;
				firstLine->toDelete = 0;
				if (firstLine->k == k && firstLine->b == b && (firstLine->x1 > x1&& firstLine->x1 < x2 || firstLine->x2 > x1&& firstLine->x2 < x2)) {
					if (firstLine->x2 <= x2 && firstLine->x1 >= x1) {
						firstLine->toDelete = 1;
					}
					else {
						if (firstLine->x2 > x2) {
							x2 = firstLine->x2;
							y2 = firstLine->y2;
							firstLine->toDelete = 1;
						}
						if (firstLine->x1 < x1) {
							x1 = firstLine->x1;
							y1 = firstLine->y1;
							firstLine->toDelete = 1;
						}
					}
				}
				cur = firstLine->nextNode;
				while (cur != firstLine) {
					cur->toDelete = 0;
					if (cur->k == k && cur->b == b && (cur->x1 > x1&& cur->x1 < x2 || cur->x2 > x1&& cur->x2 < x2)) {
						if (cur->x2 <= x2 && cur->x1 >= x1) {
							cur->toDelete = 1;
						}
						else {
							if (cur->x2 > x2) {
								x2 = cur->x2;
								y2 = cur->y2;
								cur->toDelete = 1;
							}
							if (cur->x1 < x1) {
								x1 = cur->x1;
								y1 = cur->y1;
								cur->toDelete = 1;
							}
						}
					}
					cur = cur->nextNode;
				}
				if (mI == 1 && firstLine->toDelete) {
					free(firstLine);
					mI = 0;
				}
				else {
					while (firstLine->nextNode->toDelete == 1 && mI != 0) {
						if (mI == 1 && firstLine->toDelete) {
							free(firstLine);
							mI = 0;
							break;
						}
						else {
							struct node* nex = firstLine->nextNode;
							firstLine->nextNode = nex->nextNode;
							if (nex == firstLine) {
								firstLine = nex->nextNode;
							}
							mI--;
							free(nex);
						}
					}
					if (mI != 0) {
						cur = firstLine->nextNode;
						while (cur != firstLine) {
							while (cur->nextNode->toDelete == 1 && mI != 0) {
								if (mI == 1 && cur->toDelete) {
									free(cur);
									mI = 0;
									break;
								}
								else {
									struct node* nex = cur->nextNode;
									if (nex == firstLine) {
										firstLine = nex->nextNode;
									}
									cur->nextNode = nex->nextNode;
									mI--;
									free(nex);
								}
							}
							cur = cur->nextNode;
						}
					}
				}
				if (mI == 0) {
					firstLine = malloc(sizeof(struct node));
					firstLine->x1 = x1;
					firstLine->y1 = y1;
					firstLine->x2 = x2;
					firstLine->y2 = y2;
					firstLine->nextNode = firstLine;
					firstLine->k = (y2 - y1) / (x2 - x1);
					firstLine->b = y2 - firstLine->k * x2;
					firstLine->index = 1;
					mI++;
					firstLine->toDelete = 0;
					break;
				}
				cur = firstLine;
				i = 1;
				while (cur->nextNode != firstLine) {
					cur->index = i;
					cur = cur->nextNode;
					i++;
				}
				cur->index = i;
				i++;
				toDel = malloc(sizeof(struct node));
				toDel->x1 = x1;
				toDel->y1 = y1;
				toDel->x2 = x2;
				toDel->y2 = y2;
				toDel->nextNode = cur->nextNode;
				cur->nextNode = toDel;
				toDel->k = (y2 - y1) / (x2 - x1);
				toDel->b = y2 - toDel->k * x2;
				toDel->index = i;
				mI = i;
				toDel->toDelete = 0;
			}
			break;
		case 'd':
			if (scanf("%d", &i) != 1 || i < 0 || i > mI) {
				printf("Error with your request!\n");
			}
			else {
				cur = firstLine;
				while (cur->nextNode->index != i) {
					cur = cur->nextNode;
				}
				toDel = cur->nextNode;
				cur->nextNode = toDel->nextNode;
				mI--;
				if (toDel->index == 1 && mI != 0) {
					firstLine = toDel->nextNode;
					cur = firstLine->nextNode;
					firstLine->index--;
					while (cur != firstLine) {
						cur->index--;
						cur = cur->nextNode;
					}
				}
				else if (mI != 0) {
					cur = cur->nextNode;
					while (cur != firstLine) {
						cur->index--;
						cur = cur->nextNode;
					}
				}
				free(toDel);
				printf("Delete succesfull!\n");
			}
			break;
		case 'l':
			if (mI == 0) {
				printf("No lines\n>");
				break;
			}
			printf("%d: %lf %lf %lf %lf\n",firstLine->index, firstLine->x1, firstLine->y1, firstLine->x2, firstLine->y2);
			cur = firstLine->nextNode;
			while (cur != firstLine) {
				printf("%d: %lf %lf %lf %lf\n", cur->index , cur->x1, cur->y1, cur->x2, cur->y2);
				cur = cur->nextNode;
			}
			break;
		case 'e':
			*mI1 = mI;
			return 0;
			break;
		default:
			printf(">");
			break;
		}
	}
}

int AutoTest() {
	
}