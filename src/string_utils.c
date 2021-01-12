#include "string_utils.h"

#include <string.h>
#include <malloc.h>

char *merge_str(const char *A, const char *B) {
	size_t A_len = strlen(A), B_len = strlen(B), len = A_len + B_len;

	char *out = (char*)malloc(len + 1);
	strncpy(out, A, A_len);
	strncpy(out + A_len, B, B_len);

	return out;
}
