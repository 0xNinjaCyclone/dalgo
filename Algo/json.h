#ifndef _dalgo_json
#define _dalgo_json


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <iconv.h>

#if defined(USE_DALGO_STRUCTURES)
#include "hash.h"
#include "llist.h"
#include "helpers.h"
#endif


/* JSON Types */
#define JSON_NONE   ( 0 ) // Invalid
#define JSON_NULL   ( 1 << 0 )
#define JSON_FALSE  ( 1 << 1 )
#define JSON_TRUE   ( 1 << 2 )
#define JSON_NUMBER ( 1 << 3 )
#define JSON_STRING ( 1 << 4 )
#define JSON_ARRAY  ( 1 << 5 )
#define JSON_OBJECT ( 1 << 6 )

#define JSON_WHITESPACE ' '
#define JSON_BACKSPACE '\b'
#define JSON_FORMAT '\f'
#define JSON_CR '\r'
#define JSON_LF '\n'
#define JSON_TAB '\t'
#define JSON_NUL '\0'
#define JSON_DQUOTE '"'
#define JSON_SLASH '/'
#define JSON_BACKSLASH '\\'
#define JSON_COMMA ','
#define JSON_COLON ':'
#define JSON_DECPOINT '.'
#define JSON_NEGSIGN '-'
#define JSON_POSSIGN '+'
#define JSON_OPENBRACKET '['
#define JSON_CLOSEBRACKET ']'
#define JSON_OPENCBRACKET '{'
#define JSON_CLOSECBRACKET '}'
#define JSON_NUMBER_MAX_LENGTH 64
#if defined(USE_DALGO_STRUCTURES)
#define JSON_OBJECT_MAX_ENTRIES 32
#endif

/* Macros */
#define JSON_PARSABLE(pBuffer) ( pBuffer->nLength && *pBuffer->data != JSON_NUL )

#define JSON_CANREAD(pBuffer, nLen) ( pBuffer->nLength >= nLen )

#define JSON_SKIP(pBuffer) while ( \
    JSON_CANREAD(pBuffer, 1) && \
    *pBuffer->data <= 0x20  && \
    pBuffer->data++ && pBuffer->nLength-- \
)

#define JSON_WALK(pBuffer, n) pBuffer->data += n; pBuffer->nLength -= n 

#define JSON_ISNULL(pBuffer)      ( JSON_CANREAD(pBuffer, 4) && strncmp(pBuffer->data, "null", 4) == 0 )
#define JSON_ISTRUE(pBuffer)      ( JSON_CANREAD(pBuffer, 4) && strncmp(pBuffer->data, "true", 4) == 0 )
#define JSON_ISFALSE(pBuffer)     ( JSON_CANREAD(pBuffer, 5) && strncmp(pBuffer->data, "false", 5) == 0 )
#define JSON_ISNUMBER(pBuffer)    ( JSON_CANREAD(pBuffer, 1) && (*pBuffer->data == JSON_NEGSIGN || (*pBuffer->data >= 0x30 && *pBuffer->data <= 0x39)) )
#define JSON_ISOBJECT(pBuffer)    ( JSON_CANREAD(pBuffer, 1) && *pBuffer->data == JSON_OPENCBRACKET )
#define JSON_ISOBJECTEND(pBuffer) ( JSON_CANREAD(pBuffer, 1) && *pBuffer->data == JSON_CLOSECBRACKET )
#define JSON_ISARRAY(pBuffer)     ( JSON_CANREAD(pBuffer, 1) && *pBuffer->data == JSON_OPENBRACKET )
#define JSON_ISARRAYEND(pBuffer)  ( JSON_CANREAD(pBuffer, 1) && *pBuffer->data == JSON_CLOSEBRACKET )
#define JSON_ISSTRING(pBuffer)    ( JSON_CANREAD(pBuffer, 1) && *pBuffer->data == JSON_DQUOTE )

#define JSON_TYPE_ISNULL(pItem)   ( pItem->nType & JSON_NULL )
#define JSON_TYPE_ISTRUE(pItem)   ( pItem->nType & JSON_TRUE )
#define JSON_TYPE_ISFALSE(pItem)  ( pItem->nType & JSON_FALSE )
#define JSON_TYPE_ISNUMBER(pItem) ( pItem->nType & JSON_NUMBER )
#define JSON_TYPE_ISOBJECT(pItem) ( pItem->nType & JSON_OBJECT )
#define JSON_TYPE_ISARRAY(pItem)  ( pItem->nType & JSON_ARRAY )
#define JSON_TYPE_ISSTRING(pItem) ( pItem->nType & JSON_STRING )

typedef struct _JsonItem JsonItem;

struct _JsonItem {
    __int8_t nType;
    void *pValue;
#if !defined(USE_DALGO_STRUCTURES)
    char *cpName;
    JsonItem *pChild;
    JsonItem *pNext;
#endif
};

typedef struct {
    JsonItem *pHeadItem;
    int nItems;
} Json;

typedef struct {
    char *data;
    int nLength;
} JsonBuffer;

JsonItem *json_item_new();
void json_item_delete(JsonItem **ppItem);
#if defined(USE_DALGO_STRUCTURES)
void json_item_free(void *pItem);
#endif

Json *json_init();
bool json_parse(Json *pJson, char *data);
bool json_parsefile(Json *pJson, char *cpFileName);
bool json_parsebuffer(Json *pJson, JsonBuffer *pBuffer);
bool json_parse_val(Json *pJson, JsonItem *pItem, JsonBuffer *pBuffer);
bool json_parse_num(Json *pJson, JsonItem *pItem, JsonBuffer *pBuffer);
bool json_parse_str(Json *pJson, JsonItem *pItem, JsonBuffer *pBuffer);
bool json_parse_arr(Json *pJson, JsonItem *pItem, JsonBuffer *pBuffer);
bool json_parse_obj(Json *pJson, JsonItem *pItem, JsonBuffer *pBuffer);
void json_print(Json *pJson);
void json_print_item(JsonItem *pItem);
void json_print_num(JsonItem *pItem);
void json_print_arr(JsonItem *pItem);
void json_print_obj(JsonItem *pItem);
void json_destroy(Json **ppJson);

#endif