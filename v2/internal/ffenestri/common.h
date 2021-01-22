//
// Created by Lea Anthony on 6/1/21.
//

#ifndef COMMON_H
#define COMMON_H

#define OBJC_OLD_DISPATCH_PROTOTYPES 1
#include <objc/objc-runtime.h>
#include <CoreGraphics/CoreGraphics.h>

#include <stdio.h>
#include <stdarg.h>
#include "string.h"
#include "hashmap.h"
#include "vec.h"
#include "json.h"

#define STREQ(a,b) strcmp(a, b) == 0
#define STREMPTY(string) strlen(string) == 0
#define STRCOPY(str) (str == NULL ? NULL : concat(str, ""))
#define STR_HAS_CHARS(input) input != NULL && strlen(input) > 0
#define MEMFREE(input) if(input != NULL) { free((void*)input); input = NULL; }
#define FREE_AND_SET(variable, value) if( variable != NULL ) { MEMFREE(variable); } variable = value
#define NEW(struct) malloc(sizeof(struct));

#define HASHMAP_INIT(hashmap, initialSize, name) \
    if( 0 != hashmap_create((const unsigned)initialSize, &hashmap)) { \
        ABORT("Not enough memory to allocate %s!\n", name);          \
    }

#define HASHMAP_PUT(hashmap, key, value) hashmap_put(&hashmap, key, strlen(key), value);
#define HASHMAP_GET(hashmap, key) hashmap_get(&hashmap, key, strlen(key));
#define HASHMAP_DESTROY(hashmap) hashmap_destroy(&hashmap);
#define HASHMAP_SIZE(hashmap) hashmap_num_entries(&hashmap)
#define HASHMAP_ITERATE(hashmap, function, context) if( hashmap_num_entries(&hashmap) > 0 ) { \
        if (0!=hashmap_iterate_pairs(&hashmap, function, context)) { \
            ABORT("failed to iterate hashmap entries!"); \
        } \
    }
#define JSON_ADD_STRING(jsonObject, key, value) if( value != NULL ) { json_append_member(jsonObject, (char*)key, json_mkstring(value)); }
#define JSON_ADD_NUMBER(jsonObject, key, value) json_append_member(jsonObject, (char*)key, json_mknumber(value));
#define JSON_ADD_OBJECT(jsonObject, key, value) if( value != NULL ) { json_append_member(jsonObject, (char*)key, value); }
#define JSON_ADD_BOOL(jsonObject, key, value) json_append_member(jsonObject, (char*)key, json_mkbool(value));
#define JSON_ADD_ELEMENT(jsonObject, value) json_append_element(jsonObject, value);

// Credit: https://stackoverflow.com/a/8465083
char* concat(const char *string1, const char *string2);
void ABORT(const char *message, ...);
int freeHashmapItem(void *context, struct hashmap_element_s *e);
const char* getJSONString(JsonNode *item, const char* key);
const char* getJSONStringDefault(JsonNode *item, const char* key, const char* defaultValue);
const char* mustJSONString(JsonNode *node, const char* key);
JsonNode* getJSONObject(JsonNode* node, const char* key);
JsonNode* mustJSONObject(JsonNode *node, const char* key);

bool getJSONBool(JsonNode *item, const char* key);
bool getJSONInt(JsonNode *item, const char* key, int *result);
int mustJSONInt(JsonNode *node, const char* key);
JsonNode* mustParseJSON(const char* JSON);

#endif //ASSETS_C_COMMON_H
