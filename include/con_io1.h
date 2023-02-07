#define con_io1 1

#define _COUNT 10
#define _LENGTH 50
#include <cstdio>
#include <cstring>
typedef struct Console_Text {
    bool active[_COUNT];        // 该行是否激活
    bool new_line[_COUNT];      // 是否需要换行
    char text[_COUNT][_LENGTH]; // 文本串
    int count;                  // 进行至的数目
} Con_Tex;

int contex_paint(Con_Tex *Cp, int per);                   // 输出
int contex_read(Con_Tex *Cp, FILE *fp);                   // 读取
int file_gets(char *cp, int count, FILE *fp, short mode); // 读取的内部函数
int contex_init(Con_Tex *Cp, int act, int new_l);         // 初始化