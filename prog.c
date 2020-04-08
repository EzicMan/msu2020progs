#include "prog.h"

void quick_sortG(struct Student** arr, int low, int high) {
	int i = low, j = high;
	struct Student* t, * x = arr[(low + high) / 2];
	do {
		while (arr[i]->Group < x->Group) {
			i++;
		}
		while (arr[j]->Group > x->Group) {
			j--;
		}
		if (i <= j) {
			if (i < j) {
				t = arr[i];
				arr[i] = arr[j];
				arr[j] = t;
			}
			i++;
			j--;
		}
	} while (i <= j);
	if (i < high) {
		quick_sortG(arr, i, high);
	}
	if (j > low) {
		quick_sortG(arr, low, j);
	}
}

void quick_sortR(struct Student** arr, int low, int high) {
	int i = low, j = high;
	struct Student* t, * x = arr[(low + high) / 2];
	do {
		while (arr[i]->Rating < x->Rating) {
			i++;
		}
		while (arr[j]->Rating > x->Rating) {
			j--;
		}
		if (i <= j) {
			if (i < j) {
				t = arr[i];
				arr[i] = arr[j];
				arr[j] = t;
			}
			i++;
			j--;
		}
	} while (i <= j);
	if (i < high) {
		quick_sortR(arr, i, high);
	}
	if (j > low) {
		quick_sortR(arr, low, j);
	}
}

int progItSelf(const char* fileName, struct Student*** ans, int* k1) {
	struct Student** info;
	FILE* input;
	int k = 0;
	int* a1;
	int off = 0;
	int temp;
	int n = 1;
	if ((input = fopen(fileName, "r")) == NULL) {
		printf("Error while opening file!");
		return 1;
	}
	while (!feof(input)) {
		char c = 32;
		int bespoleznyiNigger = 0;
		while (c != '\n') {
			c = fgetc(input);
			if (feof(input)) {
				break;
			}
			bespoleznyiNigger++;
		}
		if (bespoleznyiNigger == 1) {
			continue;
		}
		if (bespoleznyiNigger == 0 && feof(input)) {
			fclose(input);
			return 0;
		}
		k++;
	}
	if (k == 0) {
		fclose(input);
		return 0;
	}
	fseek(input, 0, 0);
	if ((info = (struct Student**)malloc(sizeof(struct Student*) * k)) == NULL) {
		free(info);
		fclose(input);
		printf("Error while allocating info");
		return 1;
	}
	for (int i = 0; i < k; i++) {
		char c = 0;
		int bespoleznyiNigger = 0;
		while (c != ' ' && c != '\n') {
			c = fgetc(input);
			bespoleznyiNigger++;
		}
		if (c == '\n') {
			continue;
		}
		if ((info[i] = (struct Student*) malloc(sizeof(struct Student))) == NULL) {
			for (int h = 0; h <= i; h++) {
				free(info[h]->Name);
				free(info[h]);
			}
			free(info);
			fclose(input);
			printf("Error while allocating Student");
			return 1;
		}
		if ((info[i]->Name = (char*)malloc(sizeof(char) * bespoleznyiNigger)) == NULL) {
			for (int h = 0; h <= i; h++) {
				free(info[h]->Name);
				free(info[h]);
			}
			free(info);
			fclose(input);
			printf("Error while allocating Name");
			return 1;
		}
		fseek(input, -bespoleznyiNigger, SEEK_CUR);
		for (int j = 0; j < bespoleznyiNigger - 1; j++) {
			info[i]->Name[j] = fgetc(input);
		}
		info[i]->Name[bespoleznyiNigger - 1] = '\0';
		if (fscanf(input, "%d", &info[i]->Group) != 1) {
			for (int h = 0; h <= i; h++) {
				free(info[h]->Name);
				free(info[h]);
			}
			free(info);
			fclose(input);
			printf("Error while reading Group");
			return 1;
		}
		if (fscanf(input, "%lf", &info[i]->Rating) != 1) {
			for (int h = 0; h <= i; h++) {
				free(info[h]->Name);
				free(info[h]);
			}
			free(info);
			fclose(input);
			printf("Error while reading Rating");
			return 1;
		}
		if (fscanf(input, "%d", &info[i]->isElder) != 1) {
			for (int h = 0; h <= i; h++) {
				free(info[h]->Name);
				free(info[h]);
			}
			free(info);
			fclose(input);
			printf("Error while reading isElder");
			return 1;
		}
		fscanf(input, "%*c");
	}
	quick_sortG(info, 0, k - 1);
	temp = info[0]->Group;
	for (int i = 0; i < k; i++) {
		if (info[i]->Group != temp) {
			n++;
			temp = info[i]->Group;
		}
	}
	if ((a1 = (int*)malloc(sizeof(int) * n)) == NULL) {
		for (int h = 0; h < k; h++) {
			free(info[h]->Name);
			free(info[h]);
		}
		free(info);
		fclose(input);
		printf("Error while allocating a1");
		return 1;
	}
	temp = info[0]->Group;
	for (int i = 0; i < k; i++) {
		if (info[i]->Group != temp) {
			temp = info[i]->Group;
			a1[off] = i - 1;
			off++;
		}
		info[i]->isElder = 0;
	}
	a1[off] = k - 1;
	quick_sortR(info, 0, a1[0]);
	for (int i = 1; i < n; i++) {
		quick_sortR(info, a1[i - 1] + 1, a1[i]);
	}
	if ((a1[0] + 1) % 2 == 0) {
		info[(a1[0] + 1) / 2 - 1]->isElder = 1;
	}
	else {
		info[(a1[0] + 1) / 2]->isElder = 1;
	}
	for (int i = 1; i < n; i++) {
		if ((a1[i] - a1[i - 1]) % 2 == 0) {
			info[(a1[i] - a1[i - 1]) / 2 + a1[i - 1]]->isElder = 1;
		}
		else {
			info[(a1[i] - a1[i - 1]) / 2 + a1[i - 1] + 1]->isElder = 1;
		}
	}
	fclose(input);
	free(a1);
	*k1 = k;
	*ans = info;
	return 0;
}

int AutoTest() {
	struct Student** info;
	int k;
	if (progItSelf("autotest.txt", &info, &k)) {
		return 1;
	}
	if (!(info[0]->isElder == 1 && info[0]->Rating == 3.0)) {
		printf("Autotest not passed!");
		for (int h = 0; h < k; h++) {
			free(info[h]->Name);
			free(info[h]);
		}
		free(info);
		return 1;
	}
	for (int h = 0; h < k; h++) {
		free(info[h]->Name);
		free(info[h]);
	}
	free(info);
	return 0;
}