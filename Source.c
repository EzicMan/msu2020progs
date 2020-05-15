#include "prog.h"

int main(void) {
	FILE* input;
	struct node* firstLine = NULL;
	struct node* lastLine = NULL;
	struct node* cur = NULL;
	struct node* temp;
	int curindex = 1;
	if ((input = fopen("input.txt","r")) == NULL) {
		printf("Can't open file!");
		return 1;
	}
	while (!feof(input)) {
		cur = malloc(sizeof(struct node));
		if (fscanf(input, "%lf %lf %lf %lf", &cur->x1, &cur->y1, &cur->x2, &cur->y2) != 4){
			printf("Can't read data from file!\n");
			cur = firstLine;
			fclose(input);
			for (int i = 0; i < curindex - 1; i++) {
				temp = cur;
				cur = cur->nextNode;
				free(temp);
			}
			return 1;
		}
		cur->index = curindex;
		if (cur->x2 == cur->x1) {
			cur = firstLine;
			printf("Can't add line which consists only of one point!\n");
			while (cur != NULL) {
				temp = cur;
				cur = cur->nextNode;
				free(temp);
			}
			fclose(input);
			return 1;
		}
		cur->k = (cur->y2 - cur->y1) / (cur->x2 - cur->x1);
		cur->b = cur->y2 - cur->k * cur->x2;
		curindex++;
		if (firstLine == NULL) {
			firstLine = cur;
		}
		else {
			lastLine->nextNode = cur;
		}
		lastLine = cur;
	}
	lastLine->nextNode = firstLine;
	curindex--;
	progItSelf(firstLine, &curindex);
	cur = firstLine;
	fclose(input);
	for (int i = 0; i < curindex; i++) {
		temp = cur;
		cur = cur->nextNode;
		free(temp);
	}
	return 0;
}