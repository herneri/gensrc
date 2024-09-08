/*
	gensrc: Generate boilerplate source files in several languages

    Copyright 2024 Eric Hernandez

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        https://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

const char *extensions[] = {".c", ".cpp", ".java", ".html"};
const char *GENSRC_DIR = "/.gensrc/";

enum extension_num {
	C, CPP, JAVA, HTML
};

int main(int argc, char *argv[]) {
	FILE *source_file;
	FILE *output_file;

	char source_name[255];
	char *file_name;
	char *extension;
	char buffer[255];

	bool is_custom = false;

	if (argc == 2 && strcmp(argv[1], "--help") || argc < 3) {
		printf("usage: gensrc [option] [file_name]\n-g\tCustom template\n-c\tC Source\n-p\tC++ Source\n-j\tJava Source\n-h\tHTML Source\n");
		return 1;
	}

	switch (argv[1][1]) {
	case 'g':
		is_custom = true;

		if (argc < 4) {
			fprintf(stderr, "gensrc: Not enough arguments to create from a custom template \n");
			return 1;
		}

		break;
	case 'c':
		extension = (char *) extensions[C];
		break;
	case 'p':
		extension = (char *) extensions[CPP];
		break;
	case 'j':
		extension = (char *) extensions[JAVA];
		break;
	case 'h':
		extension = (char *) extensions[HTML];
		break;
	default:
		fprintf(stderr, "gensrc: Invalid source file type \n");
		return 1;
	}

	strcpy(source_name, getenv("HOME"));
	strcat(source_name, GENSRC_DIR);

	if (is_custom == false) {
		strcat(source_name, "basic");
		strcat(source_name, extension);
	} else {
		strcat(source_name, argv[2]);
	}

	source_file = fopen(source_name, "r");
	if (source_file == NULL) {
		fprintf(stderr, "gensrc: Failed to find source file\n");
		return 1;
	}

	if (is_custom == false)
		file_name = strncat(argv[2], extension, 255);
	else
		file_name = argv[3];

	output_file = fopen(file_name, "w");
	if (output_file == NULL) {
		fprintf(stderr, "gensrc: Unable to create file \n");
		return 1;
	}

	while (fgets(buffer, 255, source_file) != NULL) {
		fprintf(output_file, "%s", buffer);
	}

	fclose(source_file);
	fclose(output_file);
	return 0;
}
