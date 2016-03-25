/*beatmania IIDX config switch by dxnoob

give -1 on argv[2] for 3rd - 8th style switch
give -2 on argv[2] for 9th - 16th style switch
give -3 on argv[2] disables allow 8bit textures

based on PCSX2 v1.2.1 - newer revisions just lag like hell :/
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>

void error(char *error) {
	printf("%s\n", error);
	Sleep(1000);
	exit(1);

}

void filecopy(char *in, char *out) {
	FILE *file, *file2;
	if ((file = fopen(in, "rb")) == NULL) {
		perror("input error");
		exit(1);
	}
	if ((file2 = fopen(out, "wb")) == NULL) {
		perror("output error");
		exit(1);
	}
	//check file size
	fseek(file, 0L, SEEK_END);
	long size = ftell(file);
	fseek(file, 0L, SEEK_SET);
	//printf("%ld", size);
	//copy file
	int n = 0;
	//char buffer[size];
	char *buffer = (char *)calloc(size, sizeof(char));
	while ((fread(buffer, sizeof(char), size, file))>0) {
		//printf("%d\n", n++);
		fwrite(buffer, sizeof(char), size, file2);
	}
	fclose(file);
	fclose(file2);
}


int main(int argc, char **argv) {
	char pre[1024] = { 0 };
	char address[1024] = { 0 };
	char address2[1024] = { 0 };
	char buffer[1024] = { 0 };
	char buffer2[1024] = { 0 };

	FILE *file = NULL;
	FILE *file2 = NULL;
	int i = 0;
	int flag = 0;
	long flength = 0;

	char* temp = NULL;

	if (argc == 1) {
		error("nothing specified. i need a directory of ini folder");
	}
	else if (argc == 2) {
		error("requires both ini folder directory and option\n"
			"for option, \"-1\" for 3rd - 8th style\n"
			"\"-2\" for 9th - 16th style\n");
	
	}
	if (argv[1]) strcpy(pre, argv[1]);
	else error("what");

	printf("beatmania IIDX 3rd - 8th style config switch\n"
		"for pcsx2 v1.2.1 and older revs\n"
		"made by dxnoob\n"
		"have fun!\n"
		);

	//flag
	switch(argv[2][1]) {
	case '1':
		flag = 1; break;
	case '2':
		flag = 2; break;
	case '3':
		flag = 3; break;
	default:
		error("invalid option!");
	
	}


	//PCSX2_vm.ini
	strcpy(address, pre);
	strcat(address, "/PCSX2_vm.ini");
	strcpy(address2, address);
	strcat(address2, ".bak");

	if (file = fopen(address2, "r")) {
		fclose(file); //file exists revert
		filecopy(address2, address);
		remove(address2);
		printf("changed back.\n");

	}
	else {

		filecopy(address, address2); //backup



		file = fopen(address2, "r");
		if (!file) error("something happened");

		file2 = fopen(address, "w");
		if (!file2) error("something happened");

		fseek(file, 0L, SEEK_END);
		flength = ftell(file); //tell filesize
		fseek(file, 0L, SEEK_SET); //goto first
		switch (flag) {
		case 1:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				if (!strcmp(strtok(buffer2, " ="), "FramerateNTSC")) {

					fputs("FramerateNTSC=59.82\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "VUCycleSteal")) {

					fputs("VUCycleSteal=0\n", file2);
				}
				else {
					fputs(buffer, file2);
				}
			}
			break;
		case 2:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				if (!strcmp(strtok(buffer2, " ="), "VUCycleSteal")) {

					fputs("VUCycleSteal=0\n", file2);
				}
				else {
					fputs(buffer, file2);
				}
			}
			break;
		case 3:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				if (!strcmp(strtok(buffer2, " ="), "VUCycleSteal")) {
					temp = strtok(NULL, " =");
					if (temp[0] - '0' > 0) {
						fprintf(file2, "VUCycleSteal=%d\n", temp[0] - '0' - 1); //light stealing
					}
					else {
						fprintf(file2, "VUCycleSteal=0\n");
					
					}
				}
				else {
					fputs(buffer, file2);
				}
			}
			break;
		default:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				fputs(buffer, file2);
			}
		}

		fflush(file);
		fclose(file);

		fflush(file2);
		fclose(file2);

		printf("applied!\n");
	}


	//GSdx.ini
	strcpy(address, pre);
	strcat(address, "/GSdx.ini");
	strcpy(address2, address);
	strcat(address2, ".bak");

	if (file = fopen(address2, "r")) {
		fclose(file); //file exists revert
		filecopy(address2, address);
		remove(address2);
		printf("changed back.\n");
	}
	else {

		filecopy(address, address2); //backup



		file = fopen(address2, "r");
		if (!file) error("something happened");

		file2 = fopen(address, "w");
		if (!file2) error("something happened");

		fseek(file, 0L, SEEK_END);
		flength = ftell(file); //tell filesize
		fseek(file, 0L, SEEK_SET); //goto first

		switch (flag) {
		case 1:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				if (!strcmp(strtok(buffer2, " ="), "Renderer")) {

					fputs("Renderer=4\n", file2);
				}
				else {
					fputs(buffer, file2);
				}
			}
			break;
		case 2:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				if (!strcmp(strtok(buffer2, " ="), "Renderer")) {

					fputs("Renderer=4\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "Interlace")) {

					fputs("Interlace=3\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "paltex")) {

					fputs("paltex=1\n", file2);
				}
				else {
					fputs(buffer, file2);
				}
			}
			break;
		default:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				fputs(buffer, file2);
			}
		}
		fflush(file);
		fclose(file);

		fflush(file2);
		fclose(file2);

		printf("applied!\n");
	}
end:
	Sleep(1000);
	exit(0);

	return 0;
}