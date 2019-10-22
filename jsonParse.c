#include "jsmn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * A small example of jsmn parsing when JSON structure is known and number of
 * tokens is predictable.
 */

//static const char *JSON_STRING =
  //  "{\"type\": \"shooter\", \"action\": motorOn}";

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}



int parseAction(char* JSON_STRING, char* myType, char* myAction)
{
  int i;
  int r;
  jsmn_parser p;
  jsmntok_t t[128]; /* We expect no more than 128 tokens */
  jsmn_init(&p);
  r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t, sizeof(t) / sizeof(t[0]));
  if (r < 0) {
    printf("Failed to parse JSON: %d\n", r);
    return -1;
  }

  /* Assume the top-level element is an object */
  if (r < 1 || t[0].type != JSMN_OBJECT) {
    printf("Object expected\n");
    return -1;
  }

  /* Loop over all keys of the root object */
  for (i = 1; i < r; i++) {
    if (jsoneq(JSON_STRING, &t[i], "type") == 0) {
      /* We may use strndup() to fetch string value */
		//printf(JSON_STRING + i);
		//printf("- type: %.*s\n", t[i + 1].end - t[i + 1].start, JSON_STRING + t[i + 1].start);

		jsmntok_t key = t[i+1];
		unsigned int length = key.end - key.start;
		memcpy(myType, &JSON_STRING[key.start], length);
      i++;
    } else if (jsoneq(JSON_STRING, &t[i], "action") == 0) {
      /* We may additionally check if the value is either "true" or "false" */
      //printf(JSON_STRING)
	  printf("- action: %.*s\n", t[i + 1].end - t[i + 1].start, JSON_STRING + t[i + 1].start);
		jsmntok_t key = t[i+1];
		unsigned int length = key.end - key.start;
		memcpy(myAction, &JSON_STRING[key.start], length);
		
      i++;
    } 
	else {
      printf("Unexpected key: %.*s\n", t[i].end - t[i].start,
             JSON_STRING + t[i].start);
    }
  }
  return EXIT_SUCCESS;
}

//
//int main()
//{
//	char* myString = "{\"type\": \"shooter\", \"action\": motorOn}";
//	char* myType = malloc(sizeof(char)*10 + 1);
//	char* myAction = malloc(sizeof(char)*10 + 1);
//	memset(myType, '\0', sizeof(myType));
//	memset(myAction, '\0', sizeof(myAction));
//
//	parseAction(myString, myType, myAction);
//	printf("the type: ");
//	printf(myType);
//	printf("\nthe action: ");
//	printf(myAction);
//}
