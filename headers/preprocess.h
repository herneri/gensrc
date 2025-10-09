#ifndef VAL_WRITE_H
#define VAL_WRITE_H

#include <stdbool.h>

/*
	Preprocess a template file, substituting params with their assigned values
	and writing the result to an output file.
*/
bool gensrc_preprocess(struct param_node **table, const int table_size, const char *input_path, const char *output_path);

#endif /* VAL_WRITE_H */
