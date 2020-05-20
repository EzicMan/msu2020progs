#include "prog.h"

int main(void) {
	struct node* firstLine = NULL;
	struct node* cur = NULL;
	struct node* temp;
	int curindex = 0;
	firstLine = progItSelf(&curindex);
	cur = firstLine;
	for (int i = 0; i < curindex; i++) {
		temp = cur;
		cur = cur->nextNode;
		free(temp);
	}
	return 0;
}