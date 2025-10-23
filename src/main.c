/*
	Copyright 2024, 2025 Eric Hernandez

	This file is part of gensrc.

	gensrc is free software: you can redistribute it and/or modify it under the terms of the GNU General
	Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

	gensrc is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
	the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along with gensrc. If not, see <https://www.gnu.org/licenses/>.
*/

#include "../headers/param.h"
#include "../headers/preprocess.h"

#include <stdio.h>
#include <stdlib.h>

#include <stdbool.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

const char *GENSRC_DIR = "/.gensrc/";

enum gensrc_return_codes {
	GENOK, ARGERR, FSFAIL
};

int main(int argc, char *argv[]) {
	const int MAX_LEN = 125;

	const char *HELP_MESSAGE = "usage: gensrc [OPTION] [OPERANDS]\n\
-g [TEMPLATE_NAME]\tSpecify the name of the template to preprocess\n\
-o [OUTPUT_FILE]\tName the output file, default is genout\n\
-p [PARAM_FILE]\tThe param file to set values from, otherwise stdin is used\n";

	char output_file_name[MAX_LEN];
	strncpy(output_file_name, "genout", MAX_LEN);

	char template_name[MAX_LEN];
	template_name[0] = '\0';

	struct param_queue *param_key_values = malloc(sizeof(struct param_queue));
	param_key_values->head = NULL;
	struct stat param_file_metadata;

	char *param_file_data = NULL;
	char param_file[MAX_LEN];
	strncpy(param_file, "stdin", MAX_LEN);

	int param_file_descriptor;
	int param_table_size = 0;

	bool seeking_operand = false;
	bool read_stdin = true;

	if (argc == 2 && (strcmp(argv[1], "--help") || strcmp(argv[1], "-h")) || argc < 3) {
		fprintf(stderr, "%s\n", HELP_MESSAGE);
		return GENOK;
	}

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-' && seeking_operand == false) {
			if (i + 1 >= argc) {
				fprintf(stderr, "gensrc: An option must have an operand after it \n");
				return ARGERR;
			}

			seeking_operand = true;
		} else if (argv[i][0] == '-' && seeking_operand == true) {
			fprintf(stderr, "gensrc: An operand must come after an option \n");
			return ARGERR;
		}

		switch (argv[i][1]) {
		case 'p':
			strncpy(param_file, argv[i + 1], MAX_LEN);
			read_stdin = false;
			i += 1;
			break;
		case 'o':
			strncpy(output_file_name, argv[i + 1], MAX_LEN);
			i += 1;
			break;
		case 'g':
			strncpy(template_name, argv[i + 1], MAX_LEN);
			i += 1;
			break;
		default:
			fprintf(stderr, "gensrc: Invalid option: %s \n", argv[i]);
			fprintf(stderr, "Use -h or --help for proper options \n");
			return ARGERR;
		}

		seeking_operand = false;
	}

	if (strnlen(template_name, MAX_LEN) == 0) {
		fprintf(stderr, "gensrc: A template name is required, use -g to set it \n");
		return ARGERR;
	}

	if (read_stdin == false) {
		param_file_descriptor = open(param_file, O_RDONLY, 0444);
		stat(param_file, &param_file_metadata);

		if (param_file_descriptor == -1) {
			fprintf(stderr, "gensrc: Failed to read param file \n");
			return FSFAIL;
		}

		param_file_data = mmap(NULL, param_file_metadata.st_size, PROT_READ, MAP_SHARED, param_file_descriptor, 0);
	} else {
		return 1; // TODO: Delete this and get params from stdin
	}

	gensrc_param_parse(&param_key_values, param_file_data, param_file_metadata.st_size);
	param_table_size = param_key_values->count;

	struct param_node *param_table[param_table_size];
	gensrc_table_initialization(param_table, param_table_size);
	gensrc_queue_transfer(param_table, &param_key_values);

	gensrc_preprocess(param_table, param_table_size, template_name, output_file_name);

	if (read_stdin == false) {
		munmap(param_file_data, param_file_metadata.st_size);
		close(param_file_descriptor);
	}

	gensrc_param_table_free(param_table, param_table_size);
	return GENOK;
}
