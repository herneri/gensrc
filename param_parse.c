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

#include "param_parse.h"

struct param_queue *param_enqueue(struct param_queue *queue, struct param_node *node) {
	if (queue->head == NULL) {
		queue->head = node;
		return queue;
	}

	struct param_node *temp = queue->head;
	while (temp != NULL)
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
