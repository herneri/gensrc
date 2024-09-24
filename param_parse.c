/*
	param_parse.c: Parsing algorithm and queue for param files

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

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <stdio.h>

#include "param_parse.h"

/*
    Max length of strings, including
    buffers, keys, and values.
*/
const int MAX_LEN = 255;

struct param_queue *param_enqueue(struct param_queue *queue, char *key, char *value) {
	struct param_node *node = (struct param_node *) malloc(sizeof(struct param_node));
	node->name = key;
	node->value = value;

	if (queue->head == NULL) {
		queue->head = node;
		queue->count = 1;
		return queue;
	}

	struct param_node *temp = queue->head;
	while (temp->link != NULL)
		temp = temp->link;

	temp->link = node;
	queue->count++;
	return queue;
}

struct param_queue *param_dequeue(struct param_queue *queue) {
	if (queue->head == NULL) {
		return NULL;
	}

	struct param_node *temp = queue->head; 
	queue->head = temp->link;
	free(temp);

	queue->count--;
	return queue;
}

struct param_node *param_peek(struct param_queue *queue) {
	if (queue == NULL) {
		return NULL;
	}

	return queue->head;
}

struct param_queue *param_parse(struct param_queue *queue, char *line) {
	int length = strnlen(line, MAX_LEN);
	int mode = SEEK_MODE;

	char *key = (char *) calloc(0, MAX_LEN);
	char *value = (char *) calloc(0, MAX_LEN);
	int buffer_index = 0;

	for (int i = 0; i < length; i++) {
		char c = line[i];

		if (isspace(c) && mode != VALUE_MODE) {
			continue;
		}

		if (c == '=' && mode == KEY_MODE) {
			mode = OPR_MODE;
			buffer_index = 0;
			continue;
		}

		if (c == '"') {
			if (mode == OPR_MODE && value[0] == 0) {
				mode = VALUE_MODE;
				continue;
			} else if (mode == VALUE_MODE) {
				mode = SEEK_MODE;
				buffer_index = 0;

				queue = param_enqueue(queue, key, value);

				key = (char *) calloc(0, MAX_LEN);
				value = (char *) calloc(0, MAX_LEN);
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
	return queue;
}
