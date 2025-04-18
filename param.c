/*
	param_parse.c: Parsing algorithm and hash table for params

	Copyright 2024, 2025 Eric Hernandez

	This file is part of gensrc.

	gensrc is free software: you can redistribute it and/or modify it under the terms of the GNU General
	Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

	gensrc is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
	the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along with gensrc. If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <stdio.h>

#include "param.h"

/*
    Max length of strings, including
    buffers, keys, and values.
*/
const int MAX_LEN = 255;

unsigned int gensrc_hash_key(char *string, const int table_size) {
    int length = strlen(string);
    unsigned int hash = length * string[0];

    for (int i = 0; i < length; i++) {
        hash *= string[i];
        hash = string[i] * string[0];
    }

    hash *= string[length / 2];
    hash ^= string[length - 1];

    return hash % table_size;
}

struct param_node **gensrc_param_insert(struct param_node **table, char *key, char *value, int *length) {
	struct param_node *node = (struct param_node *) malloc(sizeof(struct param_node));

	node->name = key;
	node->value = value;

	if (*length > 1) {
		table = realloc(table, (*length)++);
	}

	unsigned int hash_code = gensrc_hash_key(key, *length);
	table[hash_code] = node;
	return table;
}

void gensrc_enqueue(struct param_queue **queue, const char *key, const char *value) {
	struct param_node *node = (struct param_node *) malloc(sizeof(struct param_node));
	node->name = (char *) key;
	node->value = (char *) value;

	if ((*queue)->head == NULL) {
		(*queue)->head = node;
		(*queue)->count = 1;
		return;
	}


	struct param_node *temp = (*queue)->head;
	while (temp->link != NULL) {
		temp = temp->link;
	}

	temp->link = node;
	(*queue)->count++;
	return;
}

void gensrc_dequeue(struct param_queue **queue) {
	if ((*queue)->head == NULL) {
		return;
	}

	struct param_node *temp = (*queue)->head;
	(*queue)->head = temp->link;

	(*queue)->count--;
	return;
}

struct param_node *gensrc_queue_peek(struct param_queue *queue) {
	return queue->head;
}

void gensrc_param_parse(struct param_queue **queue, char *line) {
	int length = strnlen(line, MAX_LEN);
	int mode = SEEK_MODE;

	char *key = (char *) calloc(MAX_LEN, sizeof(char));
	char *value = (char *) calloc(MAX_LEN, sizeof(char));
	int buffer_index = 0;

	for (int i = 0; i < length; i++) {
		char c = line[i];

		if (isspace(c) && mode != VALUE_MODE) {
			continue;
		}

		if (c == '=' && mode == KEY_MODE) {
			mode = OPR_MODE;
			key[buffer_index + 1] = '\0';
			buffer_index = 0;
			continue;
		}

		if (c == '"') {
			if (mode == OPR_MODE && value[0] == 0) {
				mode = VALUE_MODE;
				continue;
			} else if (mode == VALUE_MODE) {
				mode = SEEK_MODE;
				value[buffer_index + 1] = '\0';
				buffer_index = 0;

				gensrc_enqueue(queue, key, value);

				key = (char *) calloc(MAX_LEN, sizeof(char));
				value = (char *) calloc(MAX_LEN, sizeof(char));
				continue;
			}
		}

		if (mode == SEEK_MODE && key[0] == 0) {
			mode = KEY_MODE;
		}

		if (mode == KEY_MODE) {
			key[buffer_index] = c;
			buffer_index++;
			continue;
		}

		if (mode == VALUE_MODE) {
			value[buffer_index] = c;
			buffer_index++;
			continue;
		}
	}

	free(key);
	free(value);
	return;
}
