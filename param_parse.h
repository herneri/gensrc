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

/* Parsing for param values with intermediary */
struct param_node **param_parse(struct param_node **table, char *line);

#endif /* PARAM_PARSE_H */
