#include "prog.h"

int main(void) {
	if (AutoTest()) {
		return 1;
	}
	FILE* input;
	struct Student** info;
	int k;
	if (progItSelf("input.txt", &info, &k)) {
		return 1;
	}
	if ((input = fopen("output.txt", "w")) == NULL) {
		for (int h = 0; h < k; h++) {
			free(info[h]->Name);
			free(info[h]);
		}
		free(info);
		printf("Error while opening file");
		return 1;
	}
	for (int i = 0; i < k; i++) {
		fprintf(input, "%s %d %lf %d\n", info[i]->Name, info[i]->Group, info[i]->Rating, info[i]->isElder);
	}
	fclose(input);
	for (int h = 0; h < k; h++) {
		free(info[h]->Name);
		free(info[h]);
	}
	free(info);
	return 0;
}