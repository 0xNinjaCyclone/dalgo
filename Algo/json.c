/*
    Json Parser Implementation
    
    Author      => Abdallah Mohamed Elsharif
    Date        => 06-07-2024
*/


#include "json.h"

int g_nDepth = 0;

bool json_parse_obj(Json *pJson, JsonItem *pItem, JsonBuffer *pBuffer)
{
    JsonItem *pTemp;

#ifndef USE_DALGO_STRUCTURES
    JsonItem *pHead, *pCurr;
#else
    Hash *pObj;
    Item *pObjItem;
    Key *pObjName;
#endif

    if ( !JSON_ISOBJECT(pBuffer) )
        return false;

    JSON_WALK(pBuffer, 1);
    JSON_SKIP(pBuffer);

    if ( JSON_ISOBJECTEND(pBuffer) ) {
        JSON_WALK(pBuffer, 1);
        JSON_SKIP(pBuffer);
        return true;
    }

#if !defined(USE_DALGO_STRUCTURES)
    pHead = pCurr = NULL;
#else
    if ( !(pObj = hash_new(JSON_OBJECT_MAX_ENTRIES, CHAINING)) )
        return false;
#endif
    
    do {
        if ( JSON_CANREAD(pBuffer, 1) && *pBuffer->data == JSON_COMMA ) {
            JSON_WALK(pBuffer, 1);
            JSON_SKIP(pBuffer);
        }

        if ( !(pTemp = json_item_new()) ) {
            goto FAIL;
        }

        if ( !json_parse_str(pJson, pTemp, pBuffer) ) {
            json_item_delete( &pTemp );
            goto FAIL;
        }

#ifndef USE_DALGO_STRUCTURES
        if ( !pHead )
            pHead = pCurr = pTemp;

        else {
            pCurr->pNext = pTemp;
            pCurr = pCurr->pNext;
        }

        pCurr->cpName = (char *) pCurr->pValue;

#else
        pObjName = key_new(pTemp->pValue, strlen(pTemp->pValue)+1, StrPrintA, StrCmpA);
        free( pTemp->pValue );

        if ( !pObjName ) {
            goto FAIL;
        }
#endif
        pTemp->pValue = NULL;
        pJson->nItems--; // The object name is not a new item (json_parse_str() doesn't know that)
        
        JSON_SKIP(pBuffer);

        if ( !(JSON_CANREAD(pBuffer, 1) && *pBuffer->data == JSON_COLON) ) {
#ifdef USE_DALGO_STRUCTURES
            key_destroy( &pObjName );
#endif
            goto FAIL;
        }

        JSON_WALK(pBuffer, 1);
        JSON_SKIP(pBuffer);

        if ( !json_parse_val(pJson, pTemp, pBuffer) ) {
#ifdef USE_DALGO_STRUCTURES
            key_destroy( &pObjName );
#endif
            goto FAIL;
        }

#ifdef USE_DALGO_STRUCTURES
        pObjItem = item_new(pTemp, sizeof(JsonItem), malloc, json_item_free, NULL, NULL);
        free( pTemp );

        if ( !pObjItem || !hash_insert(pObj, pObjName, pObjItem) ) {
            goto FAIL;
        }
        
#endif

        JSON_SKIP(pBuffer);

    } while ( JSON_CANREAD(pBuffer, 1) && *pBuffer->data == JSON_COMMA );


    if ( !JSON_ISOBJECTEND(pBuffer) ) {
        goto FAIL;
    }

    JSON_WALK(pBuffer, 1);
#ifndef USE_DALGO_STRUCTURES
    pItem->pChild = pHead;
#else
    pItem->pValue = pObj;
#endif
    pJson->nItems++;
    return true;

FAIL:
#ifndef USE_DALGO_STRUCTURES
    if ( pHead ) {
        json_item_delete( &pHead );
    }
#else
    hash_destroy( &pObj );
#endif
    
    return false;

}

bool json_parse_arr(Json *pJson, JsonItem *pItem, JsonBuffer *pBuffer)
{
    JsonItem *pTemp;
#ifndef USE_DALGO_STRUCTURES
    JsonItem *pHead, *pCurr;
#else
    List *pArrItem;
    int nInserted;
#endif

    if ( !JSON_ISARRAY(pBuffer) )
        return false;

    JSON_WALK(pBuffer, 1);
    JSON_SKIP(pBuffer);
    
    if ( JSON_ISARRAYEND(pBuffer) ) {
        JSON_WALK(pBuffer, 1);
        JSON_SKIP(pBuffer);
        return true;
    }

#ifndef USE_DALGO_STRUCTURES
    pHead = pCurr = NULL;
#else
    if ( !(pArrItem = llist_init()) )
        return false;
#endif
    
    do {
        if ( JSON_CANREAD(pBuffer, 1) && *pBuffer->data == JSON_COMMA ) {
            JSON_WALK(pBuffer, 1);
            JSON_SKIP(pBuffer);
        }

        if ( !(pTemp = json_item_new()) ) {
            goto FAIL;
        }

#ifndef USE_DALGO_STRUCTURES
        if ( !pHead )
            pHead = pCurr = pTemp;

        else {
            pCurr->pNext = pTemp;
            pCurr = pCurr->pNext;
        }
#endif

        if ( !json_parse_val(pJson, pTemp, pBuffer) ) {
#ifdef USE_DALGO_STRUCTURES
            json_item_delete( &pTemp );
#endif
            goto FAIL;
        }

#ifdef USE_DALGO_STRUCTURES
        nInserted = llist_insert(pArrItem, pTemp, sizeof(JsonItem), malloc, json_item_free, NULL, NULL);
        free( pTemp );

        if ( !nInserted )
            goto FAIL;

#endif

        JSON_SKIP(pBuffer);

    } while ( JSON_CANREAD(pBuffer, 1) && *pBuffer->data == JSON_COMMA );

    if ( !JSON_ISARRAYEND(pBuffer) ) {
        goto FAIL;
    }

    JSON_WALK(pBuffer, 1);
#ifndef USE_DALGO_STRUCTURES
    pItem->pChild = pHead;
#else
    pItem->pValue = pArrItem;
#endif
    pJson->nItems++;
    return true;

FAIL:
#ifndef USE_DALGO_STRUCTURES
    if ( pHead ) {
        json_item_delete( &pHead );
    }
#else
    llist_cleanup( &pArrItem );
#endif   
    
    return false;
}

bool utf16_to_utf8(char *cpHex, char **cppOutput)
{
    iconv_t cd;
    char *cpInput;
    size_t ulInSize, ulOutSize;
    unsigned short wHex;
    bool bSuccess;

    wHex = 0;

    /* Convert the hex value from string to numerical */
    for ( int i = 0; i < 4; i++ )
    {
        if ( cpHex[i] >= 0x30 && cpHex[i] <= 0x39 )
            wHex += (unsigned short) cpHex[i] - 0x30;

        else if ( cpHex[i] >= 0x61 && cpHex[i] <= 0x66 )
            wHex += (unsigned short) cpHex[i] + 0x0a - 0x61;

        else if ( cpHex[i] >= 0x41 && cpHex[i] <= 0x46 )
            wHex += (unsigned short) cpHex[i] + 0x0a - 0x41;

        else {
            return false;
        }

        // Make place for the next nibble
        if ( i != 3 )
            wHex <<= 4;
    }
    
    if ( (cd = iconv_open("UTF8", "UTF16")) == (iconv_t)-1 )
        return false;

    cpInput = (char *) &wHex;
    ulInSize = 2;
    ulOutSize = 4;
    bSuccess = false;

    if ( ~iconv(cd, &cpInput, &ulInSize, cppOutput, &ulOutSize) )
        bSuccess = true;

    iconv_close( cd );

    return bSuccess;
}

bool json_parse_str(Json *pJson, JsonItem *pItem, JsonBuffer *pBuffer)
{
    char *cpStr, *cpStrEnd, cSeq;
    int nStrLen, nBuffLen;

    if ( !JSON_ISSTRING(pBuffer) )
        return false;
    
    JSON_WALK(pBuffer, 1);
    nStrLen = 0;
    cpStrEnd = pBuffer->data;
    nBuffLen = pBuffer->nLength;

    while ( --nBuffLen && *cpStrEnd != JSON_DQUOTE )
    {
        if ( *cpStrEnd == JSON_BACKSLASH )
        {
            if ( --nBuffLen <= 0 )
                return false;

            cpStrEnd++;

            if ( *cpStrEnd == 'u' )
                nStrLen++; // We include '\u' in the result when we fail to convert into utf8
        }

        cpStrEnd++;
        nStrLen++;
    }

    if ( *cpStrEnd != JSON_DQUOTE )
        return false;

    if ( !(cpStr = (char *) malloc(nStrLen + 1)) )
        return false;

    pItem->pValue = (void *) cpStr;

    while ( pBuffer->data < cpStrEnd )
    {
        if ( *pBuffer->data == JSON_BACKSLASH )
        {
            cSeq = *( pBuffer->data + 1 );

            switch ( cSeq )
            {
            case 'b':
                *cpStr++ = JSON_BACKSPACE;
                break;
            case 'f':
                *cpStr++ = JSON_FORMAT;
                break;
            case 'n':
                *cpStr++ = JSON_LF;
                break;
            case 'r':
                *cpStr++ = JSON_CR;
                break;
            case 't':
                *cpStr++ = JSON_TAB;
                break;
            case JSON_DQUOTE:
            case JSON_BACKSLASH:
            case JSON_SLASH:
                *cpStr++ = cSeq;
                break;

            /* UTF-16 literal */
            case 'u':
                if ( !utf16_to_utf8(pBuffer->data+2, &cpStr) ) {
                    strncpy( cpStr, pBuffer->data, 6 );
                    cpStr += 6;
                }

                JSON_WALK(pBuffer, 4);
                break;

            default:
                free( pItem->pValue );
                pItem->pValue = NULL;
                return false;
            }

            JSON_WALK(pBuffer, 2);
        }

        else 
        {
            *cpStr++ = *pBuffer->data;
            JSON_WALK(pBuffer, 1);
        }
    }

    JSON_WALK(pBuffer, 1);
    *cpStr = JSON_NUL;
    pJson->nItems++;
    return true;
}

bool json_parse_num(Json *pJson, JsonItem *pItem, JsonBuffer *pBuffer)
{
    unsigned char cNumber[JSON_NUMBER_MAX_LENGTH] = { 0 };
    unsigned char *pEnd = NULL;
    double dNumber;
    int nIdx;

    if ( !JSON_ISNUMBER(pBuffer) )
        return false;

    for ( nIdx = 0; nIdx < JSON_NUMBER_MAX_LENGTH; nIdx++ )
    {
        if (
            *pBuffer->data != JSON_DECPOINT && 
            *pBuffer->data != JSON_NEGSIGN &&
            *pBuffer->data != JSON_POSSIGN &&
            *pBuffer->data != 'e' &&
            *pBuffer->data != 'E' &&
            !JSON_ISNUMBER(pBuffer)
        )
            break;

        cNumber[ nIdx ] = *pBuffer->data;
        JSON_WALK(pBuffer, 1);
    }

    dNumber = strtod( (const char *)cNumber, (char **)&pEnd );

    if ( pEnd == cNumber )
        return false;

    if ( !(pItem->pValue = malloc(sizeof(double))) )
        return false;
        
    memcpy( pItem->pValue, (const void *)&dNumber, sizeof(double) );
    pJson->nItems++;
    return true;
}

bool json_parse_val(Json *pJson, JsonItem *pItem, JsonBuffer *pBuffer)
{
    if ( JSON_ISNULL(pBuffer) ) {
        pItem->nType = JSON_NULL;
        JSON_WALK(pBuffer, 4);
        pJson->nItems++;
        return true;
    }

    else if ( JSON_ISTRUE(pBuffer) ) {
        pItem->nType = JSON_TRUE;
        JSON_WALK(pBuffer, 4);
        pJson->nItems++;
        return true;
    }

    else if ( JSON_ISFALSE(pBuffer) ) {
        pItem->nType = JSON_FALSE;
        JSON_WALK(pBuffer, 5);
        pJson->nItems++;
        return true;
    }

    else if ( JSON_ISNUMBER(pBuffer) ) {
        pItem->nType = JSON_NUMBER;
        return json_parse_num(pJson, pItem, pBuffer);
    }

    else if ( JSON_ISSTRING(pBuffer) ) {
        pItem->nType = JSON_STRING;
        return json_parse_str(pJson, pItem, pBuffer);
    }

    else if ( JSON_ISARRAY(pBuffer) ) {
        pItem->nType = JSON_ARRAY;
        return json_parse_arr(pJson, pItem, pBuffer);
    }

    else if ( JSON_ISOBJECT(pBuffer) ) {
        pItem->nType = JSON_OBJECT;
        return json_parse_obj(pJson, pItem, pBuffer);
    }

    else {
        pItem->nType = JSON_NONE;
        return false;
    }
}

JsonItem *json_item_new()
{
    JsonItem *pItem;

    if ( pItem = (JsonItem *) malloc(sizeof(JsonItem)) )
    {
        pItem->nType = JSON_NONE;
        pItem->pValue = NULL;
#ifndef USE_DALGO_STRUCTURES
        pItem->pChild = NULL;
        pItem->cpName = NULL;
        pItem->pNext = NULL;
#endif
    }

    return pItem;
}

void json_item_delete(JsonItem **ppItem)
{
    JsonItem *pItem, *pTemp;
    
    pItem = *ppItem;

#ifndef USE_DALGO_STRUCTURES
    while ( pItem )
    {
        if ( pItem->pChild )
            json_item_delete( &pItem->pChild );

        if ( pItem->cpName )
            free( pItem->cpName );

        if ( pItem->pValue )
            free( pItem->pValue );

        pTemp = pItem->pNext;
        free( pItem );
        pItem = pTemp;
    }
#else
    if ( pItem->pValue ) {
        switch ( pItem->nType )
        {
        case JSON_ARRAY:
            llist_cleanup( (List **) &pItem->pValue );
            break;
        
        case JSON_OBJECT:
            hash_destroy( (Hash **) &pItem->pValue );
            break;

        case JSON_STRING:
        case JSON_NUMBER:
            free( pItem->pValue );

        default:
            break;
        }
    }

    free( pItem );
#endif
    
    *ppItem = NULL;
}

#ifdef USE_DALGO_STRUCTURES
void json_item_free(void *pItem)
{
    json_item_delete( (JsonItem **) &pItem );
}
#endif

Json *json_init()
{
    Json *pJson;

    if ( pJson = (Json *) malloc(sizeof(Json)) )
    {
        pJson->pHeadItem = NULL;
        pJson->nItems = 0;
    }

    return pJson;
}

bool json_parse(Json *pJson, char *data)
{
    JsonBuffer buf;
    int nLen;

    if ( !(data && (nLen = strlen(data)) >= 2) )
        return false;

    buf.data = data;
    buf.nLength = nLen;
    
    return json_parsebuffer( pJson, &buf );
}

bool json_parsefile(Json *pJson, char *cpFileName)
{
    FILE *fp;
    char *cpJsonData;
    bool bSuccess;
    JsonBuffer buf;

    bSuccess = false;

    if ( fp = fopen(cpFileName, "r") )
    {
        fseek( fp, 0L, SEEK_END );
        buf.nLength = ftell( fp );
        fseek( fp, 0L, SEEK_SET );

        if ( buf.nLength && (buf.data = cpJsonData = (char *) malloc(buf.nLength)) )
        {
            fread( buf.data, buf.nLength, 1, fp );
            bSuccess = json_parsebuffer( pJson, &buf );
            free( cpJsonData );
        }

        fclose( fp );
    }

    return bSuccess;
}

bool json_parsebuffer(Json *pJson, JsonBuffer *pBuffer)
{

    if ( pJson->pHeadItem = json_item_new() ) {
        JSON_SKIP(pBuffer);
        return json_parse_val(pJson, pJson->pHeadItem, pBuffer);
    }

    return false;
}

void json_print_num(JsonItem *pItem)
{
    double dNum;
    int nNum;

    dNum = *(double *) pItem->pValue;
    nNum = (int) dNum;

    if ( dNum == (double)nNum )
        printf("%d", nNum);

    else {
        printf("%0.2f", dNum);
    }
}

void json_print_obj(JsonItem *pItem)
{
    JsonItem *pNextItem;
#ifdef USE_DALGO_STRUCTURES
    Hash *pObj;
    Item *pObjItem = NULL;
    Key *pObjKey = NULL;
    size_t ulPos = 0;
#endif
    char *cpName;
    putchar( JSON_OPENCBRACKET );
#ifndef USE_DALGO_STRUCTURES
    pItem = pItem->pChild;
#else
    if ( pObj = (Hash *) pItem->pValue ) {
        if ( !hash_next( pObj, &ulPos, &pObjKey, &pObjItem ) ) {
            pItem = NULL;
        }
        else {
            pItem = (JsonItem *) pObjItem->data;
        }
    }
    else {
        pItem = NULL;
    }
#endif
    g_nDepth++;

    while ( pItem )
    {
        putchar( JSON_LF );

#ifndef USE_DALGO_STRUCTURES
        cpName = pItem->cpName;
#else
        cpName = (char *) pObjKey->data;
#endif
        for ( int i = 0; i < g_nDepth; i++ )
            putchar( JSON_TAB );
            
        printf("%s: ", cpName);
        json_print_item( pItem );

#ifndef USE_DALGO_STRUCTURES
        pNextItem = pItem->pNext;
#else
        if ( !hash_next( (Hash *) pObj, &ulPos, &pObjKey, &pObjItem ) )
            pNextItem = NULL;
        else 
            pNextItem = (JsonItem *) pObjItem->data;
#endif

        if ( pNextItem ) {
            putchar( JSON_COMMA );
            putchar( JSON_WHITESPACE );
        }

        pItem = pNextItem;
        
    }

    putchar( JSON_LF );
    for ( int i = 0; i < g_nDepth-1; i++ )
        putchar( JSON_TAB );
    putchar( JSON_CLOSECBRACKET );
    g_nDepth--;
}

void json_print_arr(JsonItem *pItem)
{
    JsonItem *pNextItem;
#ifdef USE_DALGO_STRUCTURES
    List *pArr;
    size_t lIdx = 0;
#endif

    putchar( JSON_OPENBRACKET );

#ifndef USE_DALGO_STRUCTURES
    pItem = pItem->pChild;
#else
    pArr = (List *) pItem->pValue;
    pItem = ( pArr ) ? (JsonItem *) llist_getitemAt( pArr, lIdx++ ) : NULL;
#endif
    
    while ( pItem )
    {
        json_print_item( pItem );
        
#ifndef USE_DALGO_STRUCTURES
        pNextItem = pItem->pNext;
#else
        pNextItem = (JsonItem *) llist_getitemAt( pArr, lIdx++ );
#endif
        if ( pNextItem ) {
            putchar( JSON_COMMA );
            putchar( JSON_WHITESPACE );
        }

        pItem = pNextItem;
    }

    putchar( JSON_CLOSEBRACKET );
}

void json_print_item(JsonItem *pItem)
{
    
    if ( JSON_TYPE_ISNULL(pItem) ) {
        printf("Null");
    }

    else if ( JSON_TYPE_ISTRUE(pItem) ) {
        printf("True");
    }

    else if ( JSON_TYPE_ISFALSE(pItem) ) {
        printf("False");
    }

    else if ( JSON_TYPE_ISSTRING(pItem) ) {
        printf("'%s'", (char *) pItem->pValue);
    }

    else if ( JSON_TYPE_ISNUMBER(pItem) ) {
        json_print_num(pItem);
    }

    else if ( JSON_TYPE_ISARRAY(pItem) ) {
        json_print_arr(pItem);
    }

    else if ( JSON_TYPE_ISOBJECT(pItem) ) {
        json_print_obj(pItem);
    }

    else {
        printf("Invalid");
    }
}

void json_print(Json *pJson)
{
    if ( pJson->pHeadItem )
        json_print_item( pJson->pHeadItem );
}

void json_destroy(Json **ppJson)
{
    if ( (*ppJson)->pHeadItem )
        json_item_delete( &(*ppJson)->pHeadItem );

    free( *ppJson );
    *ppJson = NULL;
}