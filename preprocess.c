#include "param.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

bool gensrc_preprocess(struct param_node **table, const int table_size, const char *input_path, const char *output_path) {
	FILE *template_file = NULL;
	FILE *processed_file = NULL;
	char c;

	bool potential_param = false;
	bool is_param = false;
	bool closing_param = false;
	bool end_param = false;

	const int MAX_LEN = 255;
	int param_name_index = 0;

	char *param_name = (char *) calloc(MAX_LEN, sizeof(char));

	template_file = fopen(input_path, "r");
	if (template_file == NULL) {
		fprintf(stderr, "gensrc: Failed to open template file\n");
		return false;
	}

	processed_file = fopen(output_path, "w");
	if (processed_file == NULL) {
		fprintf(stderr, "gensrc: Failed to open output file\n");
		return false;
	}

	while ((c = fgetc(template_file)) != EOF) {
		if (end_param == true) {
			unsigned int hash = gensrc_hash_key(param_name, table_size);

			while (strcmp(table[hash]->name, param_name) != 0) {
				hash = gensrc_handle_hash_collision(param_name, hash, table_size);
			}

			fprintf(processed_file, "%s", table[hash]->value);

			free(param_name);
			param_name = (char *) calloc(MAX_LEN, sizeof(char));
			param_name_index = 0;

			end_param = false;
		}

		if (c != '*' && is_param == true && closing_param == false) {
			param_name[param_name_index] = c;
			param_name_index++;
		}

		switch (c) {
		case '<':
			if (potential_param == false) {
				potential_param = true;
			}

			break;
		case '>':
			if (end_param == false) {
				end_param = true;
				is_param = false;
				potential_param = false;
				closing_param = false;
			}

			break;
		case '*':
			if (potential_param == false || closing_param == true) {
				fputc(c, processed_file);
				break;
			}

			if (is_param == false) {
				is_param = true;
			} else if (closing_param == false) {
				closing_param = true;
			}
			
			break;
		default:
			if (is_param == false) {
				fputc(c, processed_file);
			}
		}
	}

	return true;
}
