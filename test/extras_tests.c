#include "../jsmn_extras.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

static const char *JSON_STRING =
	"{\"user\": \"johndoe\", \"admin\": false, \"uid\": 1000,\n  "
	"\"groups\": [\"users\", \"wheel\", \"audio\", \"video\"]}";

#define CONFIG_JSMN_NUM_TOKENS 128
#define string_path "$.user"
#define bool_path "$.admin"
#define array_path "$.groups[1]"
#define wrong_path "$.none.existing.path"

jsmntok_t jSMNtokens[CONFIG_JSMN_NUM_TOKENS];
jsmn_parser jSMNparser;
jsmnParserStruct jsmnParser;

int main(void) {
    int toknum;
    int resultCode;
    char value[64];
    int boolValue=0;

    value[0]='\0';
    jsmnParser.jSMNparser = &jSMNparser;
    jsmnParser.jSMNtokens = &jSMNtokens[0];
    jsmnParser.numOfTokens = CONFIG_JSMN_NUM_TOKENS;
    jsmnParser.data = JSON_STRING;
    jsmnParser.lengthOfData = strlen(jsmnParser.data);

    jsmn_init(jsmnParser.jSMNparser);
    xjsmn_parse(&jsmnParser);
    
    printf("Object: %s\r\n", jsmnParser.data);
    printf("Length: %zu\r\n", jsmnParser.lengthOfData);
    printf("Tokens in object: %d\r\n", jsmnParser.resultCode);

    printf("Path 1: "string_path"\r\n");
    if (jsmn_get_string(&jsmnParser, string_path, &value[0], 64) >= 0)
    {
        printf("Test passed.\r\n");
        printf("Value 1: %s\r\n", value);
    }
    else
    {
        printf("Test failed.\r\n");
    }

    printf("Path 2: "bool_path"\r\n");
    if (jsmn_get_bool(&jsmnParser, bool_path, &boolValue) >= 0)
    {
        printf("Test passed.\r\n");
        printf("Value 2: %s\r\n", (boolValue?"true":"false"));
    }
    else
    {
        printf("Test failed.\r\n");
    }

    printf("Path 3: "wrong_path"\r\n");
    if (jsmn_get_string(&jsmnParser, wrong_path, &value[0], 64) <0)
    {
        printf("Test passed.\r\n");
    }
    else
    {
        printf("Test failed.\r\n");
        printf("Value 4: %s\r\n", value);
    }

    return (0);
}