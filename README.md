
jsmn-extras
===========
jsmn-extras is minimalistic addon for awesome lightweight [jsmn-parser](https://github.com/zserge/jsmn) by [zserge](https://github.com/zserge/).
It's included [JSONPath](http://goessner.net/articles/JsonPath/) path parser, which helps to navigate in JSON's branchs.

It's only support dot–notation like this:

```
$.path.to.array[1].or.element
```

code:

```c
#define JSMN_PARENT_LINKS
#include "jsmn_extras.h"
const char object[]="{\"sensors\":{\"temperature\":{\"onewire\":[{\"serial\":\"28:3A:CF:7B:04:00:00:D3\",\"name\":\"air\",\"place\":\"room\"},{\"serial\":\"10:86:85:9E:02:08:00:77\",\"name\":\"air\",\"place\":\"kitchen\"},{\"serial\":\"28:A7:74:7c:04:00:00:91\",\"name\":\"hot water\",\"place\":\"bath room\"}],\"analog\":[]},\"humidity\":{\"onewire\":[{\"id\":\"12345\",\"name\":\"Humidity\",\"place\":\"living room\"}]},\"inputs\":{\"analog\":[{\"serial\":\"34:51:0D:31:32:39:32:00\",\"name\":\"water level\",\"place\":\"bath\"}],\"digital\":[{\"serial\":\"34:51:0D:31:32:39:32:05\",\"name\":\"bath is full\",\"place\":\"bath\"}],\"dimmer\":[{\"serial\":\"34:51:0D:31:32:39:32:04\",\"name\":\"light dimmer\",\"place\":\"bedroom\"}],\"sequential\":[{\"serial\":\"34:51:0D:31:32:39:32:06\",\"name\":\"door is opened\",\"place\":\"room\"}]}},\"comment\":\"serial is hexademical: 00, 01..09, 0a,0b..0f\"}";
char path[]="$.sensors.temperature.onewire[0].serial";
#define CONFIG_JSMN_NUM_TOKENS 128
#define STRLEN(s) (sizeof(s)/sizeof(s[0]))
static jsmn_parser jSMNparser;
static jsmntok_t jSMNtokens[CONFIG_JSMN_NUM_TOKENS];

int toknum;
jsmnerr_t resultCode;
jsmn_init(&jSMNparser);
resultCode = jsmn_parse(&jSMNparser, &object[0], STRLEN(object), &jSMNtokens[0], CONFIG_JSMN_NUM_TOKENS);
toknum = jsmn_find_value(&object[0], &jSMNtokens[0], resultCode, &path);
```

```c
toknum
```
will contain number of token, specified by 
```c
path
```
Licensing
----------

This software is distributed under [MIT license](http://www.opensource.org/licenses/mit-license.php),
 so feel free to integrate it in your commercial products.
 
