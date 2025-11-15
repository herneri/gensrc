/*
**	Copyright 2024, 2025 Eric Hernandez
**
**	This file is part of gensrc.
**
**	gensrc is free software: you can redistribute it and/or modify it under the terms of the GNU General
**	Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
**
**	gensrc is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
**	the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License along with gensrc. If not, see <https://www.gnu.org/licenses/>.
*/

#include "../headers/util.h"

#include <stdio.h>
#include <stdlib.h>

int gensrc_read_stdin(char **param_data) {
	int data_index = 0;
	int data_size = 125;
	int growth_factor = 20;

	char user_input = 0;

	*param_data = malloc(data_size);
	char *new_param_data = NULL;

	if (param_data == NULL) {
		return STDIN_ALLOC_FAIL;
	}

	while ((user_input = getchar()) != EOF) {
		(*param_data)[data_index] = user_input;
		data_index++;

		if (data_index >= data_size) {
			data_size += growth_factor;
			new_param_data = realloc((*param_data), data_size);

			if (new_param_data == NULL) {
				/* For memory safe use in strlen. */
				(*param_data)[data_index] = '\0';
				return STDIN_REALLOC_FAIL;
			}

			(*param_data) = new_param_data;
		}
	}

	/* For memory safe use in strlen. */
	(*param_data)[data_index] = '\0';
	return STDIN_OK;
}
