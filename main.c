#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <jansson.h>

void debug(const char *fmt, ...)
{
	int size = 0;
	char *p = NULL;
	va_list ap;

	/* Determine required size */

	va_start(ap, fmt);
	size = vsnprintf(p, size, fmt, ap);
	va_end(ap);

	if (size < 0)
		return;

	size++;             /* For '\0' */
	p = malloc(size);
	if (p == NULL)
		return;

	va_start(ap, fmt);
	size = vsnprintf(p, size, fmt, ap);
	if (size < 0) {
		free(p);
		return;
	}
	va_end(ap);

	fprintf(stderr, "%s", p);
	free(p);
}

int bin2int(unsigned char *bytes) {
	int val = bytes[0] \
			  | ( (int)bytes[1] << 8 ) \
			  | ( (int)bytes[2] << 16 ) \
			  | ( (int)bytes[3] << 24 );

	return val;
}

const char *receive_message() {

}

int main(int argc, char **argv) {
	unsigned char buf[4] = {0};

	fread(buf, sizeof(buf[0]), sizeof(buf), stdin);
	unsigned int len = bin2int(buf);
	debug("%d\n", len);

	char *text = calloc(len + 1, sizeof(char));
	if (!text) {
		debug("calloc() failed\n");
		exit(1);
	}

	fread(text, sizeof(text[0]), len, stdin);
	debug("text: %s\n", text);

	json_t *root;
	json_error_t error;

	root = json_loads(text, 0, &error);
	free(text);

    if(!root) {
		debug("error: on line %d: %s\n", error.line, error.text);
		return 1;
	}

    if(!json_is_array(root)) {
		debug("error: root is not an array\n");
		json_decref(root);
		return 1;
	}

    json_t *data = json_array_get(root, 0);
    if(json_is_string(data) &&
            strcmp(json_string_value(data), "ping") == 0) {
        debug("we got string\n");
    }

	json_decref(root);

	return 0;
}




