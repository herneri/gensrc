/*
    Copyright 2024, 2025 Eric Hernandez

	This file is part of gensrc.

	gensrc is free software: you can redistribute it and/or modify it under the terms of the GNU General
	Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

	gensrc is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
	the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along with gensrc. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef PARAM_PARSE_H
#define PARAM_PARSE_H

/*
	Indicators of what mode is
	currently active during parsing.

	The modes consist of searching
	for a key, value, or the assignment
	operator.
*/
enum modes {
	KEY_MODE, VALUE_MODE,
	OPR_MODE, SEEK_MODE
};

/* 
	A param node in a queue will
	be a temporary storage for
	params during parsing.
*/
struct param_node {
	char *name;
	char *value;
	struct param_node *link;
};

/*
	During initial parsing of a param file, params will be
	added to this queue and a total count will be kept.

	The queue will be dequeued to a hash table, which will
	be of size count.

	This is necessary because:
	1. A static table size is
	   needed for consistent hashing.
	2. The table size must be known before
	   declaring the array for the table.

	It also avoids memory fragmentation when
	reallocating memory for the table.
*/
struct param_queue {
	int count;
	struct param_node *head;
};

/* Hash function made to perform on strings in large hash tables */
unsigned int gensrc_hash_key(char *string, const int table_size);

/* A hash function different to gensrc_hash_key() that's based on the previous hash code. */
unsigned int gensrc_handle_hash_collision(const char *key, const unsigned int hash_code, const int table_size);

/* Allocates and enqueues a param node. */
void gensrc_enqueue(struct param_queue **queue, const char *key, const char *value);

/*
	Dequeues a param node without freeing it. Freeing of a node is
	to be done after the hash table is done being used.
*/
void gensrc_dequeue(struct param_queue **queue);

/* Retrieve the param node at the front of the queue. */
struct param_node *gensrc_queue_peek(struct param_queue *queue);

/* Parsing for param values with intermediary */
void gensrc_param_parse(struct param_queue **queue, char *line, const unsigned int line_length);

/*
	Set each table element to NULL. This must be ran prior to the
	param table being used.
*/
void gensrc_table_initialization(struct param_node *table[], int table_size);

/* Assign the nodes from the param queue to the hash table for preprocessing. */
int gensrc_queue_transfer(struct param_node *table[], struct param_queue **queue);

/*
	Free all heap memory from a param hash table. This includes the param keys,
	values, and structs themselves.
*/
void gensrc_param_table_free(struct param_node *table[], int table_size);

#endif /* PARAM_PARSE_H */
