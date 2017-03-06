#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>

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

	fprintf(stderr, "%s\n", p);
	free(p);
}

int bin2int(unsigned char *bytes) {
	int val = bytes[0] \
			  | ( (int)bytes[1] << 8 ) \
			  | ( (int)bytes[2] << 16 ) \
			  | ( (int)bytes[3] << 24 );

	return val;
}

int main(int argc, char **argv) {
	unsigned char buf[4] = {0};

	fread(buf, sizeof(buf[0]), sizeof(buf), stdin);
	unsigned int len = bin2int(buf);
	debug("%d", len);

	char *data = calloc(len + 1, sizeof(char));
	if (!data) {
		debug("calloc() failed");
		exit(1);
	}

    fread(data, sizeof(data[0]), len, stdin);
    debug("data: %s\n", data);


    free(data);

	return 0;
}



