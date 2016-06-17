/*beatmania IIDX config switch by dxnoob

give -1 on argv[2] for 3rd - 8th style switch
give -2 on argv[2] for 9th - 16th style switch
give -3 on argv[2] for one lower vu stealing level
give -4 on argv[2] hd rendering
give -5 on argv[2] for pop'n music switch
give -6 on argv[2] for 9th - 16th style HD alternative
give -7 on argv[2] for ogl render + hwdepth
give -8 on argv[2] for vuThread(boost katamari games)
give -9 on argv[2] for kingdom hearts HD rendering(lighter speedhack)

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
		error("nothing specified. i need a directory of ini folder\n"
			"parameter:\n"
			"\"-1\" for 3rd - 8th style\n"
			"\"-2\" for 9th - 16th style\n"
			"\"-3\" for one lower vu stealing level\n"
			"\"-4\" for hd resolution\n"
			"\"-5\" for pop'n music games\n"
			"\"-6\" for 9th - 16th style HD alternative\n"
			"\"-7\" for ogl render + hwdepth\n"
			"\"-8\" for vuThread(boost katamari games)\n"
			"\"-9\" for kingdom hearts HD rendering(lighter speedhack)"
			);
	}
	else if (argc == 2) {
		error("requires option below\n"
			"parameter:\n"
			"\"-1\" for 3rd - 8th style\n"
			"\"-2\" for 9th - 16th style\n"
			"\"-3\" for one lower vu stealing level\n"
			"\"-4\" for hd resolution\n"
			"\"-5\" for pop'n music games\n"
			"\"-6\" for 9th - 16th style HD alternative\n"
			"\"-7\" for ogl render + hwdepth\n"
			"\"-8\" for vuThread(boost katamari games)\n"
			"\"-9\" for kingdom hearts HD rendering(lighter speedhack)"
			);
	
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
	case '4':
		flag = 4; break;
	case '5':
		flag = 5; break;
	case '6':
		flag = 6; break;
	case '7':
		flag = 7; break;
	case '8':
		flag = 8; break;
	case '9':
		flag = 9; break;
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
				//disable speedhacks
				else if (!strcmp(strtok(buffer2, " ="), "EECycleRate")) {

					fputs("EECycleRate=0\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "VUCycleSteal")) {

					fputs("VUCycleSteal=0\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "IntcStat")) {

					fputs("IntcStat=disabled\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "WaitLoop")) {

					fputs("WaitLoop=disabled\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "vuFlagHack")) {

					fputs("vuFlagHack=disabled\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "vuThread")) {

					fputs("vuThread=disabled\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "VsyncEnable")) {

					fputs("VsyncEnable=disabled\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "ManagedVsync")) {

					fputs("ManagedVsync=disabled\n", file2);
				}
				else {
					fputs(buffer, file2);
				}
			}
			break;
		case 2:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				//disable speedhacks
				if (!strcmp(strtok(buffer2, " ="), "EECycleRate")) {

					fputs("EECycleRate=0\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "VUCycleSteal")) {

					fputs("VUCycleSteal=0\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "IntcStat")) {

					fputs("IntcStat=disabled\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "WaitLoop")) {

					fputs("WaitLoop=disabled\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "vuFlagHack")) {

					fputs("vuFlagHack=disabled\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "vuThread")) {

					fputs("vuThread=disabled\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "VsyncEnable")) {

					fputs("VsyncEnable=disabled\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "ManagedVsync")) {

					fputs("ManagedVsync=disabled\n", file2);
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
						fprintf(file2, "VUCycleSteal=%d\n", temp[0] - '0' - 1); //lighter stealing
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
		case 5:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				//disable speedhacks
				if (!strcmp(strtok(buffer2, " ="), "EECycleRate")) {

					fputs("EECycleRate=0\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "VUCycleSteal")) {

					fputs("VUCycleSteal=0\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "IntcStat")) {

					fputs("IntcStat=disabled\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "WaitLoop")) {

					fputs("WaitLoop=disabled\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "vuFlagHack")) {

					fputs("vuFlagHack=disabled\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "vuThread")) {

					fputs("vuThread=disabled\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "VsyncEnable")) {

					fputs("VsyncEnable=disabled\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "ManagedVsync")) {

					fputs("ManagedVsync=disabled\n", file2);
				}
				else {
					fputs(buffer, file2);
				}
			}
			break;
		case 6:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				//disable speedhacks
				if (!strcmp(strtok(buffer2, " ="), "EECycleRate")) {

					fputs("EECycleRate=0\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "VUCycleSteal")) {

					fputs("VUCycleSteal=0\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "IntcStat")) {

					fputs("IntcStat=disabled\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "WaitLoop")) {

					fputs("WaitLoop=disabled\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "vuFlagHack")) {

					fputs("vuFlagHack=disabled\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "vuThread")) {

					fputs("vuThread=disabled\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "VsyncEnable")) {

					fputs("VsyncEnable=disabled\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "ManagedVsync")) {

					fputs("ManagedVsync=disabled\n", file2);
				}
				else {
					fputs(buffer, file2);
				}
			}
			break;
		case 8:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				//enable vuThread
				if (!strcmp(strtok(buffer2, " ="), "VUCycleSteal")) {

					fputs("VUCycleSteal=0\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "vuThread")) {

					fputs("vuThread=enabled\n", file2);
				}
				else {
					fputs(buffer, file2);
				}
			}
			break;
		case 9:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				if (!strcmp(strtok(buffer2, " ="), "VUCycleSteal")) {
					temp = strtok(NULL, " =");
					if (temp[0] - '0' > 0) {
						fprintf(file2, "VUCycleSteal=%d\n", temp[0] - '0' - 1); //lighter stealing
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

	//PCSX2_ui.ini
	strcpy(address, pre);
	strcat(address, "/PCSX2_ui.ini");
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
				if (!strcmp(strtok(buffer2, " ="), "EnableSpeedHacks")) {

					fputs("EnableSpeedHacks=disabled\n", file2);
				}
				else {
					fputs(buffer, file2);
				}
			}
			break;
		case 2:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				if (!strcmp(strtok(buffer2, " ="), "EnableSpeedHacks")) {

					fputs("EnableSpeedHacks=disabled\n", file2);
				}
				else {
					fputs(buffer, file2);
				}
			}
			break;
		case 5:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				if (!strcmp(strtok(buffer2, " ="), "EnableSpeedHacks")) {

					fputs("EnableSpeedHacks=disabled\n", file2);
				}
				else {
					fputs(buffer, file2);
				}
			}
			break;
		case 6:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				if (!strcmp(strtok(buffer2, " ="), "EnableSpeedHacks")) {

					fputs("EnableSpeedHacks=disabled\n", file2);
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

	//SPU2-X.ini
	strcpy(address, pre);
	strcat(address, "/SPU2-X.ini");
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
				if (!strcmp(strtok(buffer2, " ="), "Synch_Mode")) {

					fputs("Synch_Mode=2\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "Latency")) {

					fputs("Latency=3\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "Output_Module")) {

					fputs("Output_Module=dsound\n", file2);
				}
				else {
					fputs(buffer, file2);
				}
			}
			break;
		case 2:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				if (!strcmp(strtok(buffer2, " ="), "Synch_Mode")) {

					fputs("Synch_Mode=2\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "Latency")) {

					fputs("Latency=3\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "Output_Module")) {

					fputs("Output_Module=dsound\n", file2);
				}
				else {
					fputs(buffer, file2);
				}
			}
			break;
		case 5:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				if (!strcmp(strtok(buffer2, " ="), "Synch_Mode")) {

					fputs("Synch_Mode=2\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "Latency")) {

					fputs("Latency=3\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "Output_Module")) {

					fputs("Output_Module=dsound\n", file2);
				}
				else {
					fputs(buffer, file2);
				}
			}
			break;
		case 6:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				if (!strcmp(strtok(buffer2, " ="), "Synch_Mode")) {

					fputs("Synch_Mode=2\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "Latency")) {

					fputs("Latency=3\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "Output_Module")) {

					fputs("Output_Module=dsound\n", file2);
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
				else if (!strcmp(strtok(buffer2, " ="), "filter")) {

					fputs("filter=2\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "Interlace")) {

					fputs("Interlace=7\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "shaderfx")) {

					fputs("shaderfx=0\n", file2);
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

					fputs("Renderer=3\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "filter")) {

					fputs("filter=2\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "Interlace")) {

					fputs("Interlace=3\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "paltex")) {

					fputs("paltex=1\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "shaderfx")) {

					fputs("shaderfx=0\n", file2);
				}
				else {
					fputs(buffer, file2);
				}
			}
			break;
		case 4:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				if (!strcmp(strtok(buffer2, " ="), "upscale_multiplier")) {

					fputs("upscale_multiplier=2\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "filter")) {

					fputs("filter=1\n", file2);
				}
				else {
					fputs(buffer, file2);
				}
			}

			break;
		case 5:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				if (!strcmp(strtok(buffer2, " ="), "Renderer")) {

					fputs("Renderer=4\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "filter")) {

					fputs("filter=2\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "Interlace")) {

					fputs("Interlace=7\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "paltex")) {

					fputs("paltex=1\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "shaderfx")) {

					fputs("shaderfx=0\n", file2);
				}
				else {
					fputs(buffer, file2);
				}
			}
			break;
		case 6:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				if (!strcmp(strtok(buffer2, " ="), "Renderer")) {

					fputs("Renderer=3\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "filter")) {

					fputs("filter=2\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "Interlace")) {

					fputs("Interlace=3\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "paltex")) {

					fputs("paltex=1\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "upscale_multiplier")) {

					fputs("upscale_multiplier=2\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "shaderfx")) {

					fputs("shaderfx=0\n", file2);
				}
				else {
					fputs(buffer, file2);
				}
			}
			break;
		case 7:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				if (!strcmp(strtok(buffer2, " ="), "Renderer")) {

					fputs("Renderer=12\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "texture_cache_depth")) {

					fputs("texture_cache_depth=1\n", file2);
				}
				else {
					fputs(buffer, file2);
				}
			}
			break;
		case 9:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				if (!strcmp(strtok(buffer2, " ="), "upscale_multiplier")) {

					fputs("upscale_multiplier=2\n", file2);
				}
				else if (!strcmp(strtok(buffer2, " ="), "filter")) {

					fputs("filter=1\n", file2);
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

	//LilyPad.ini
	strcpy(address, pre);
	strcat(address, "/LilyPad.ini");
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
				if (!strcmp(strtok(buffer2, "="), "Keyboard Mode")) { //no spaces please

					fputs("Keyboard Mode=3\n", file2);
				}
				else {
					fputs(buffer, file2);
				}
			}
			break;
		case 2:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				if (!strcmp(strtok(buffer2, "="), "Keyboard Mode")) { //no spaces please

					fputs("Keyboard Mode=3\n", file2);
				}
				else {
					fputs(buffer, file2);
				}
			}
			break;
		case 5:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				if (!strcmp(strtok(buffer2, "="), "Keyboard Mode")) { //no spaces please

					fputs("Keyboard Mode=1\n", file2);
				}
				else {
					fputs(buffer, file2);
				}
			}
			break;
		case 6:
			for (; fgets(buffer, 1024, file); i++) {
				strcpy(buffer2, buffer);
				if (!strcmp(strtok(buffer2, "="), "Keyboard Mode")) { //no spaces please

					fputs("Keyboard Mode=3\n", file2);
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