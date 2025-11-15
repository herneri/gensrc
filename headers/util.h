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

#ifndef UTIL_H
#define UTIL_H

enum READ_STDIN_RETURN_CODES {
	STDIN_OK, STDIN_ALLOC_FAIL, STDIN_REALLOC_FAIL
};

/*
**	Read params from stdin into a dynamic char array
**	until EOF is read. This is meant for use in main.
*/
int gensrc_read_stdin(char **param_data);

#endif /* UTIL_H */
