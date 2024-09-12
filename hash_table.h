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

#ifndef GEN_TABLE_H
#define GEN_TABLE_H

struct param {
	char *name;
	char *value;
};

/* Hash function made to perform on strings in large hash tables */
unsigned int hash(char *string, const int table_size);

#endif /* GEN_TABLE_H */
