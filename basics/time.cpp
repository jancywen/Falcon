#include <stdio.h>
#include <time.h>

using namespace std;

int main()
{
    time_t rawtime;
    struct tm *info;
    
    char buffer[80];
    time(&rawtime);

    printf("%ld\n", rawtime);

    printf("当前时间: %s\n", ctime(&rawtime));

    info = localtime(&rawtime);

    printf("%d-%d-%d %d:%d:%d\n", info->tm_year, info->tm_mon, info->tm_mday, info->tm_hour, info->tm_min, info->tm_sec);
    printf("%s\n", asctime(info));

    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", info);
    printf("%s\n", buffer);
    


    return 0;
}