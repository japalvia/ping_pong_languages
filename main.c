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

unsigned char *int2bin(unsigned int n) {
	unsigned char *bytes;
	bytes = calloc(4, sizeof(*bytes));

	bytes[0] = n & 0xFF;
	bytes[1] = (n >> 8) & 0xFF;
	bytes[2] = (n >> 16) & 0xFF;
	bytes[3] = (n >> 24) & 0xFF;

	return bytes;
}

char *receive_message() {
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
	return text;
}

void send_message() {
	debug("send_message\n");
	json_t *array = json_array();
	json_array_append_new(array, json_string("pong"));

	char *data = json_dumps(array, 0);
	json_decref(array);

	size_t len = strlen(data);
	debug("str: %s, len: %d\n", data, len);
	unsigned char *bytes = int2bin(len);
	fwrite(bytes, sizeof(*bytes), 4, stdout);
	free(bytes);

	fwrite(data, sizeof(*data), len, stdout);
	free(data);
}

int main(int argc, char **argv) {

	char *text = receive_message();
	debug("text: %s\n", text);

	json_t *root;
	json_error_t error;

	root = json_loads(text, 0, &error);
	free(text);

	// Look for 'ping', ignore unexpected json
	// but ensure still crash safety.
	if(root) {
		if(json_is_array(root)) {
			json_t *data = json_array_get(root, 0);
			if(json_is_string(data)) {
				if(strcmp(json_string_value(data), "ping") == 0) {
					send_message();
				}
			}
		}
		json_decref(root);
	}
	return 0;
}




