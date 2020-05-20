#include "prog.h"

struct node* progItSelf(int* mI1) {
	printf("Enter 'a x1 y1 x2 y2' to add line, 'd ' to delete line, 'l' for list of lines, 'e' to exit\n>");
	char code = 0;
	struct node* firstLine = NULL;
	int mI = *mI1;
	while (1) {
		double x1, y1, x2, y2;
		int inc1 = 1;
		int inc2 = 1;
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
				if (x1 > x2) {
					double temp;
					temp = x1;
					x1 = x2;
					x2 = temp;
					temp = y1;
					y1 = y2;
					y2 = temp;
				}
				if (mI == 0) {
					firstLine = malloc(sizeof(struct node));
					firstLine->x1 = x1;
					firstLine->y1 = y1;
					firstLine->inc1 = 1;
					firstLine->x2 = x2;
					firstLine->y2 = y2;
					firstLine->inc2 = 1;
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
				if (firstLine->k == k && firstLine->b == b && (firstLine->x1 >= x1&& firstLine->x1 <= x2 || firstLine->x2 >= x1&& firstLine->x2 <= x2)) {
					if (firstLine->x2 <= x2 && firstLine->x1 >= x1) {
						firstLine->toDelete = 1;
					}
					else {
						if (firstLine->x2 > x2) {
							x2 = firstLine->x2;
							y2 = firstLine->y2;
							if (firstLine->inc2) {
								inc2 = 1;
							}
							firstLine->toDelete = 1;
						}
						if (firstLine->x1 < x1) {
							x1 = firstLine->x1;
							y1 = firstLine->y1;
							if (firstLine->inc1) {
								inc1 = 1;
							}
							firstLine->toDelete = 1;
						}
					}
				}
				cur = firstLine->nextNode;
				while (cur != firstLine) {
					cur->toDelete = 0;
					if (cur->k == k && cur->b == b && (cur->x1 >= x1&& cur->x1 <= x2 || cur->x2 >= x1&& cur->x2 <= x2)) {
						if (cur->x2 <= x2 && cur->x1 >= x1) {
							cur->toDelete = 1;
						}
						else {
							if (cur->x2 > x2) {
								x2 = cur->x2;
								y2 = cur->y2;
								if (cur->inc2) {
									inc2 = 1;
								}
								cur->toDelete = 1;
							}
							if (cur->x1 < x1) {
								x1 = cur->x1;
								y1 = cur->y1;
								if (cur->inc1) {
									inc1 = 1;
								}
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
					firstLine->inc1 = inc1;
					firstLine->x2 = x2;
					firstLine->y2 = y2;
					firstLine->inc2 = inc2;
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
				toDel->inc1 = inc1;
				toDel->x2 = x2;
				toDel->y2 = y2;
				toDel->inc2 = inc2;
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
			if (scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2) != 4) {
				printf("Error with your request!\n");
			}
			else {
				double k = (y2 - y1) / (x2 - x1);
				double b = y2 - k * x2;
				if (x1 > x2) {
					double temp;
					temp = x1;
					x1 = x2;
					x2 = temp;
					temp = y1;
					y1 = y2;
					y2 = temp;
				}
				if (firstLine->k == k && firstLine->b == b) {
					if (!(x2 < firstLine->x1 || x1 > firstLine->x2)) {
						if (x2 < firstLine->x2 && x1 > firstLine->x1) {
							struct node* add = malloc(sizeof(struct node));
							add->x1 = x2;
							add->y1 = y2;
							add->inc1 = 0;
							add->x2 = firstLine->x2;
							add->y2 = firstLine->y2;
							add->inc2 = 1;
							add->nextNode = firstLine->nextNode;
							add->index = 0;
							add->k = firstLine->k;
							add->b = firstLine->b;
							add->toDelete = 0;
							firstLine->x2 = x1;
							firstLine->y2 = y1;
							firstLine->inc2 = 0;
							firstLine->nextNode = add;
							mI++;
						}
						else if (x2 >= firstLine->x2 && x1 <= firstLine->x1) {
							firstLine->toDelete = 1;
						}
						else if (x2 >= firstLine->x2) {
							firstLine->x2 = x1;
							firstLine->y2 = y1;
							firstLine->inc2 = 0;
						}
						else if (x1 <= firstLine->x1) {
							firstLine->x1 = x2;
							firstLine->y1 = y2;
							firstLine->inc1 = 0;
						}
					}
				}
				else if (k != firstLine->k) {
					double xp = (b - firstLine->b) / (firstLine->k - k);
					if (xp >= x1 && xp <= x2 && xp >= firstLine->x1 && xp <= firstLine->x2) {
						if (xp == firstLine->x1) {
							firstLine->inc1 = 0;
						}
						else if (xp == firstLine->x2) {
							firstLine->inc2 = 0;
						}
						else {
							struct node* add = malloc(sizeof(struct node));
							add->x1 = xp;
							add->y1 = k*xp + b;
							add->inc1 = 0;
							add->x2 = firstLine->x2;
							add->y2 = firstLine->y2;
							add->inc2 = 1;
							add->nextNode = firstLine->nextNode;
							add->index = 0;
							add->k = firstLine->k;
							add->b = firstLine->b;
							add->toDelete = 0;
							firstLine->x2 = xp;
							firstLine->y2 = k * xp + b;
							firstLine->inc2 = 0;
							firstLine->nextNode = add;
							mI++;
						}
					}
				}
				cur = firstLine->nextNode;
				while (cur != firstLine) {
					if (cur->k == k && cur->b == b) {
						if (!(x2 < cur->x1 || x1 > cur->x2)) {
							if (x2 < cur->x2 && x1 > cur->x1) {
								struct node* add = malloc(sizeof(struct node));
								add->x1 = x2;
								add->y1 = y2;
								add->inc1 = 0;
								add->x2 = cur->x2;
								add->y2 = cur->y2;
								add->inc2 = 1;
								add->nextNode = cur->nextNode;
								add->index = 0;
								add->k = cur->k;
								add->b = cur->b;
								add->toDelete = 0;
								cur->x2 = x1;
								cur->y2 = y1;
								cur->inc2 = 0;
								cur->nextNode = add;
								mI++;
							}
							else if (x2 >= cur->x2 && x1 <= cur->x1) {
								cur->toDelete = 1;
							}
							else if (x2 >= cur->x2) {
								cur->x2 = x1;
								cur->y2 = y1;
								cur->inc2 = 0;
							}
							else if (x1 <= cur->x1) {
								cur->x1 = x2;
								cur->y1 = y2;
								cur->inc1 = 0;
							}
						}
					}
					else if (k != cur->k) {
						double xp = (b - cur->b) / (cur->k - k);
						if (xp >= x1 && xp <= x2 && xp >= cur->x1 && xp <= cur->x2) {
							if (xp == cur->x1) {
								cur->inc1 = 0;
							}
							else if (xp == cur->x2) {
								cur->inc2 = 0;
							}
							else {
								struct node* add = malloc(sizeof(struct node));
								add->x1 = xp;
								add->y1 = k * xp + b;
								add->inc1 = 0;
								add->x2 = cur->x2;
								add->y2 = cur->y2;
								add->inc2 = 1;
								add->nextNode = cur->nextNode;
								add->index = 0;
								add->k = cur->k;
								add->b = cur->b;
								add->toDelete = 0;
								cur->x2 = xp;
								cur->y2 = k * xp + b;
								cur->inc2 = 0;
								cur->nextNode = add;
								mI++;
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
				if (mI != 0) {
					cur = firstLine;
					i = 1;
					while (cur->nextNode != firstLine) {
						cur->index = i;
						cur = cur->nextNode;
						i++;
					}
					cur->index = i;
					i++;
				}
			}
			break;
		case 'l':
			if (mI == 0) {
				printf("No lines\n>");
				break;
			}
			printf("%d: ", firstLine->index);
			if (firstLine->inc1) {
				printf("[ (%lf %lf);", firstLine->x1, firstLine->y1);
			}
			else {
				printf("( (%lf %lf);", firstLine->x1, firstLine->y1);
			}
			if (firstLine->inc2) {
				printf("(%lf %lf) ]\n", firstLine->x2, firstLine->y2);
			}
			else {
				printf("(%lf %lf) )\n", firstLine->x2, firstLine->y2);
			}
			cur = firstLine->nextNode;
			while (cur != firstLine) {
				printf("%d: ", cur->index);
				if (cur->inc1) {
					printf("[ (%lf %lf);", cur->x1, cur->y1);
				}
				else {
					printf("( (%lf %lf);", cur->x1, cur->y1);
				}
				if (cur->inc2) {
					printf("(%lf %lf) ]\n", cur->x2, cur->y2);
				}
				else {
					printf("(%lf %lf) )\n", cur->x2, cur->y2);
				}
				cur = cur->nextNode;
			}
			break;
		case 'e':
			*mI1 = mI;
			return firstLine;
			break;
		default:
			printf(">");
			break;
		}
	}
}