// simple demo of reading JSON
#include <stdio.h>
#include <string.h>

#include "jsmn.h"

#define count 128

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}

int main(int argc, char **argv) {

if(argc < 2) {
  fprintf(stderr, "please specify JSON filename to parse");
  return 1;
}

int i;
int r;
jsmn_parser p;
jsmntok_t t[128]; /* We expect no more than 128 tokens */

// read

FILE *fp = fopen(argv[1], "rt");
if(fp == NULL) {
  fprintf(stderr, "failed to open %s", argv[1]);
  return 1;
}

char raw[count];

int numread = fread(raw, sizeof(char), count, fp);
fclose(fp);

// parse
jsmn_init(&p);
r = jsmn_parse(&p, raw, strlen(raw), t,
                sizeof(t) / sizeof(t[0]));
if (r < 0) {
  fprintf(stderr, "Failed to parse JSON: %d\n", r);
  return 1;
}

/* Assume the top-level element is an object */
if (r < 1 || t[0].type != JSMN_OBJECT) {
  fprintf(stderr, "Object expected\n");
  return 1;
}

/* Loop over all keys of the root object */
for (i = 1; i < r; i++) {
  if (jsoneq(raw, &t[i], "instrument") == 0) {
    /* We may use strndup() to fetch string value */
    printf("- Instrument: %.*s\n", t[i + 1].end - t[i + 1].start,
            raw + t[i + 1].start);
    i++;
  } else if (jsoneq(raw, &t[i], "power") == 0) {
    /* We may want to do strtol() here to get numeric value */
    printf("- Power: %.*s\n", t[i + 1].end - t[i + 1].start,
            raw + t[i + 1].start);
    i++;
  } else {
    printf("Unexpected key: %.*s\n", t[i].end - t[i].start,
            raw + t[i].start);
  }
}

return 0;
}
