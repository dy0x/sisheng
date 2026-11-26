
#include <assert.h>
#include <string.h>
#include "../src/pinyin.h"
#include <stdio.h>

static int success=0,fail = 0;

static void check(const char *label, const char *name, int tone, const char *expected){
    Pinyin test = {0};
    char out[32];
    out[0]='\0';
    tone -=1; // i.e: 3rd tone is in array pos 2

    snprintf(test.name, sizeof(test.name),"%s",name);
    int result = format_syllable(test,tone,out,sizeof(out));
    if(result!=0 || strcmp(out,expected) !=0){
        printf("FAIL %s! Expected: %s, Got: %s\n", label, expected, out);
        fail +=1;
        return;
    }

    printf("PASS %s is %s\n", label, expected);
    success+=1;
}

int main(void){
    check("a: hao1",    "hao1",    1, "hāo");
    check("a: hao2",    "hao2",    2, "háo");
    check("a: hao3",    "hao3",    3, "hǎo");
    check("a: hao4",    "hao4",    4, "hào");
    check("a: ai4",     "ai4",     4, "ài");
    check("a: xiao4",   "xiao4",   4, "xiào");
    check("a: xiang3",  "xiang3",  3, "xiǎng");
    check("a: zhang2",  "zhang2",  2, "zháng");

    check("e: xie2",    "xie2",    2, "xié");
    check("e: xue4",    "xue4",    4, "xuè");

    check("ou: zhou1",  "zhou1",   1, "zhōu");
    check("ou: dou3",   "dou3",    3, "dǒu");

    check("last: niu1",    "niu1",    1, "niū");
    check("last: liu2",    "liu2",    2, "liú");
    check("last: gui4",    "gui4",    4, "guì");
    check("last: nong2",   "nong2",   2, "nóng");
    check("last: xiong2",  "xiong2",  2, "xióng");

    check("v: lv4",     "lv4",     4, "lǜ");
    check("v: nv3",     "nv3",     3, "nǚ");

    check("neutral: ma5", "ma5",   5, "ma");
    check("neutral: ne5", "ne5",   5, "ne");

    printf("%d/%d passed\n",success, success+fail);

    return fail > 0;
}