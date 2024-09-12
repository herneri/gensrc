/*
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

#ifndef PARAM_PARSE_H
#define PARAM_PARSE_H

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
	During initial parsing of a param file, 
	params will be added to this queue and
	a total count will be kept.

	The queue will then be dequeued to a hash
	table, which will be of size count.
*/
struct param_queue {
	int count;
	struct param_node *head;
};

#endif /* PARAM_PARSE_H */