/*********************************************************************
 *
 * $Id: yjson.c 7646 2012-09-13 15:05:29Z mvuilleu $
 *
 * Simple JSON parser (actually a slightly enhanced lexer)
 *
 * - - - - - - - - - License information: - - - - - - - - - 
 *
 * Copyright (C) 2011 and beyond by Yoctopuce Sarl, Switzerland.
 *
 * 1) If you have obtained this file from www.yoctopuce.com,
 *    Yoctopuce Sarl licenses to you (hereafter Licensee) the
 *    right to use, modify, copy, and integrate this source file
 *    into your own solution for the sole purpose of interfacing
 *    a Yoctopuce product with Licensee's solution.
 *
 *    The use of this file and all relationship between Yoctopuce 
 *    and Licensee are governed by Yoctopuce General Terms and 
 *    Conditions.
 *
 *    THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 *    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING 
 *    WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS 
 *    FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO
 *    EVENT SHALL LICENSOR BE LIABLE FOR ANY INCIDENTAL, SPECIAL,
 *    INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, 
 *    COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR 
 *    SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT 
 *    LIMITED TO ANY DEFENSE THEREOF), ANY CLAIMS FOR INDEMNITY OR
 *    CONTRIBUTION, OR OTHER SIMILAR COSTS, WHETHER ASSERTED ON THE
 *    BASIS OF CONTRACT, TORT (INCLUDING NEGLIGENCE), BREACH OF
 *    WARRANTY, OR OTHERWISE.
 *
 * 2) If your intent is not to interface with Yoctopuce products,
 *    you are not entitled to use, read or create any derived 
 *    material from this source file.
 *
 *********************************************************************/
#define __FILE_ID__  "yjson"
#include <string.h>
#include "yjson.h"

#ifdef MICROCHIP_API
#define atoi      parseUInt
#else
#include <stdio.h>
#include <stdlib.h>
#ifdef WINDOWS_API
#include <Windows.h>
#endif
#endif

#ifdef DEBUG_JSON_PARSE
const char* yJsonStateStr[] = {
    "YJSON_HTTP_START",       // about to parse HTTP header, up to first space before return code
    "YJSON_HTTP_READ_CODE",   // reading HTTP return code
    "YJSON_HTTP_READ_MSG",    // reading HTTP return message
    "YJSON_HTTP_SKIP",        // skipping rest of HTTP header until double-CRLF
    "YJSON_START",            // about to parse JSON reply
    "YJSON_PARSE_ANY",        // parsing anything to come
    "YJSON_PARSE_SYMBOL",     // parsing a symbol (boolean)
    "YJSON_PARSE_NUM",        // parsing a number
    "YJSON_PARSE_STRING",     // parsing a quoted string
    "YJSON_PARSE_STRINGQ",    // parsing a quoted string, within quoted character
    "YJSON_PARSE_STRINGCONT", // parsing the continuation of a quoted string
    "YJSON_PARSE_STRINGCONTQ",// parsing the continuation of a quoted string, within quoted character
    "YJSON_PARSE_ARRAY",      // parsing an unnamed array
    "YJSON_PARSE_STRUCT",     // parsing a named structure
    "YJSON_PARSE_MEMBSTART",  // parsing a structure member (before name)
    "YJSON_PARSE_MEMBNAME",   // parsing a structure member name
    "YJSON_PARSE_MEMBCOL",    // parsing the colon between member name and value
    "YJSON_PARSE_DONE",       // parse completed, end of input data (or end of container)
    "YJSON_PARSE_ERROR"       // dead end, parse error encountered
};
#endif

yJsonRetCode yJsonParse(yJsonStateMachine *j)
{
    yJsonRetCode    res;
    yJsonState      st = j->st;
    const char      *src = j->src;
    const char      *end = j->end;
    char            *pt = j->pt;
    char            *ept = j->token + sizeof(j->token) - 1;
    char            c=0;

skip:
    res = YJSON_NEED_INPUT;
    if(st == YJSON_HTTP_START || st == YJSON_START || st == YJSON_PARSE_ANY) {
        j->next = -1;
    } else if(j->next != -1) {
        st = j->next;
        j->next = -1;
    }
    
    while(1) {
        switch(st) {
            case YJSON_HTTP_START:       // about to parse HTTP header, up to first space before return code
                while(src < end && (c = *src) != ' ' && c != 'O' && c != '\r') src++;
                if(src >= end) goto done;
                if(c == ' ') src++; // skip space
                pt = j->token;
                st = YJSON_HTTP_READ_CODE;
                // fall through
            case YJSON_HTTP_READ_CODE:   // reading HTTP return code
                while(src < end && pt < ept && (c = *src) != ' ' && c != 'O' && c != '\r') {
                    if(c < '0' || c > '9') goto push_error;
                    *pt++ = c;
                    src++;
                }
                if(src >= end) goto done;
                if(pt >= ept) goto push_error;
                if(c == ' ') src++; // skip space
                else if(c == 'O' && pt == j->token) {
                    // Handle short status "OK" as "HTTP/1.1 200 OK"
                    *pt++ = '2';*pt++ = '0';*pt++ = '0';
                }
                *pt = 0;
                pt = j->token;
                j->next = YJSON_HTTP_READ_MSG;
                res = YJSON_PARSE_AVAIL;
                goto done;
            case YJSON_HTTP_READ_MSG:    // reading HTTP return message
                while(src < end && pt < ept && (c = *src) != '\r' && c != '\n') {
                    *pt++ = c;
                    src++;
                }
                if(src >= end) goto done;
                *pt = 0;
                pt = j->token;
                j->next = YJSON_HTTP_SKIP;
                res = YJSON_PARSE_AVAIL;
                goto done;                
            case YJSON_HTTP_SKIP:        // skipping rest of HTTP header until double-CRLF
                while(src < end && pt < j->token+2) {
                    c = *src++;
                    if(c == '\n') *pt++ = '\n';
                    else if(c != '\r') pt = j->token; 
                }
                if(src >= end) goto done;
                st = YJSON_START;
                // fall through
            case YJSON_START:            // about to parse JSON reply
                j->depth = 0;
                j->skipcnt = 0;
                j->skipdepth = YJSON_MAX_DEPTH;
                // fall through
            case YJSON_PARSE_ANY:        // parsing anything to come
                while(src < end && ((c = *src) == ' ' || c == '\r' || c == '\n')) src++;
                if(src >= end) goto done;
                pt = j->token;
                if(c == '{') { src++; st = YJSON_PARSE_STRUCT; }
                else if(c == '[') { src++; st = YJSON_PARSE_ARRAY; }
                else if(c == '"') { src++; st = YJSON_PARSE_STRING; }
                else if(c=='-' || (c >= '0' && c <= '9')) { st = YJSON_PARSE_NUM; }
                else if(c >= 'A' && c <= 'z') { st = YJSON_PARSE_SYMBOL; }
                else if(j->depth > 0 && c == ']') { st = YJSON_PARSE_DONE; }
                else goto push_error;
                // continue into the selected state
                continue;
            case YJSON_PARSE_SYMBOL:     // parsing a symbol (boolean)
                while(src < end && pt < ept && (c = *src) >= 'A' && c <= 'z') {
                    *pt++ = c;
                    src++;
                }
                if(src >= end) goto done;
                if(pt >= ept) goto push_error;
            token_done:
                *pt = 0;
                j->next = YJSON_PARSE_DONE;
                res = YJSON_PARSE_AVAIL;
                goto done;                
            case YJSON_PARSE_NUM:        // parsing a number
                while(src < end && pt < ept && ( (c = *src)=='-' || (c >= '0' && c <= '9') ))  {
                    *pt++ = c;
                    src++;
                }
                if(src >= end) goto done;
                if(pt >= ept) goto push_error;
                goto token_done;
            case YJSON_PARSE_STRING:     // parsing a quoted string
            case YJSON_PARSE_STRINGCONT: // parsing the continuation of a quoted string
                while(src < end && pt < ept && (c = *src) != '"' && c != '\\') {
                    *pt++ = c;
                    src++;
                }
                if(src >= end) goto done;
                if(pt >= ept) {
                    *pt = 0;
                    pt = j->token;
                    j->next = YJSON_PARSE_STRINGCONT;
                    res = YJSON_PARSE_AVAIL;
                    goto done;
                }
                src++; // skip double-quote or backslash
                if(c == '"') goto token_done;
                st++;
                // fall through
            case YJSON_PARSE_STRINGQ:    // parsing a quoted string, within quoted character
            case YJSON_PARSE_STRINGCONTQ:// parsing the continuation of a quoted string, within quoted character
                if(src >= end) goto done;
                c = *src++;
                switch(c) {
                    case 'r': *pt++ = '\r'; break;
                    case 'n': *pt++ = '\n'; break;
                    case 't': *pt++ = '\t'; break;
                    default: *pt++ = c;
                }
                st--; // continue string parsing;
                continue;
            case YJSON_PARSE_ARRAY:      // parsing an unnamed array
                while(src < end && (*src == ' ' || *src == '\r' || *src == '\n')) src++;
                if(src >= end) goto done;
                if(*src == ']') {
                    j->next = YJSON_PARSE_DONE;
                }else{
                    j->next = YJSON_PARSE_ANY;
                }
                goto nest;
            case YJSON_PARSE_STRUCT:     // parsing a named structure
                j->next = YJSON_PARSE_MEMBSTART;
            nest:
                if(j->depth >= YJSON_MAX_DEPTH) goto push_error;
                j->stack[j->depth++] = st;
                *pt++ = c;
                *pt = 0;
                res = YJSON_PARSE_AVAIL;
                goto done;
            case YJSON_PARSE_MEMBSTART:  // parsing a structure member (before name)
                while(src < end && ((c = *src) == ' ' || c == '\r' || c == '\n')) src++;
                if(src >= end) goto done;
                if(c == '}') {
                    st = YJSON_PARSE_DONE;
                    continue;
                }
                if(c != '"') goto push_error;
                src++;
                pt = j->token;
                st = YJSON_PARSE_MEMBNAME;
                // fall through
            case YJSON_PARSE_MEMBNAME:   // parsing a structure member name
                while(src < end && pt < ept && (c = *src) != '"') {
                    *pt++ = c;
                    src++;
                }
                if(src >= end) goto done;
                if(pt >= ept) goto push_error;
                src++;
                *pt = 0;
                j->next = YJSON_PARSE_MEMBCOL;
                res = YJSON_PARSE_AVAIL;
                goto done;
            case YJSON_PARSE_MEMBCOL:    // parsing the colon between member name and value
                while(src < end && ((c = *src) == ' ' || c == '\r' || c == '\n')) src++;
                if(src >= end) goto done;
                if(c != ':') goto push_error;
                src++;
                st = YJSON_PARSE_ANY;
                continue; // continue parse
            case YJSON_PARSE_DONE:       // parse completed, end of input data
                while(src < end && ((c = *src) == ' ' || c == '\r' || c == '\n')) src++;
                pt = j->token;
                if(j->depth > 0) {
                    if(src >= end) goto done;
                    if(j->stack[j->depth-1] == YJSON_PARSE_STRUCT) {
                        if(c == ',') { src++; st = YJSON_PARSE_MEMBSTART; }
                        else if(c == '}') goto un_nest; 
                        else goto push_error;
                    } else { // YJSON_PARSE_ARRAY
                        if(c == ',') { src++; st = YJSON_PARSE_ANY; }
                        else if(c == ']') {
            un_nest:
                            *pt++ = *src++; 
                            st = j->stack[--(j->depth)]; 
                            goto token_done; 
                        } 
                        else goto push_error;
                    }
                    continue; // continue to parse nested block
                }
                if(src < end) goto push_error; // unexpected content at end of JSON data
                *pt = 0;
                res = YJSON_SUCCESS;
                goto done;
                // save current state if possible, and trigger an error
            push_error:
                if(j->depth < YJSON_MAX_DEPTH)
                    j->stack[j->depth++] = st;
                st = YJSON_PARSE_ERROR;
                // fall through
            case YJSON_PARSE_ERROR:      // dead end, parse error encountered
                res = YJSON_FAILED;
                goto done;
        }
    }
done:
    if(st >= YJSON_START  && res == YJSON_PARSE_AVAIL) {
        if(j->skipdepth <= j->depth) {
            if(j->skipdepth == j->depth) {
                j->skipdepth = YJSON_MAX_DEPTH;
            }
            goto skip;
        }
        if(j->skipcnt > 0) {
            if(st == YJSON_PARSE_STRUCT || st == YJSON_PARSE_ARRAY) {
                j->skipdepth = j->depth-1;
            }
            j->skipcnt--;
            goto skip;
        }
    }
    j->st = st;
    j->src = src;
    j->pt = pt;
    return res;
}

void yJsonSkip(yJsonStateMachine *j, int nitems)
{
    j->skipcnt += nitems;
}

