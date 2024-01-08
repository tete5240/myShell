#include <stdio.h>
#include <dirent.h>

int main(void) {
    DIR *d;
    struct dirent *dir;
    d = opendir("."); // 현재 디렉토리를 연다.

    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s  ", dir->d_name); // 파일 또는 디렉토리 이름을 출력
        }
        printf("\n");
        closedir(d); // 디렉토리를 닫는다.
    } else {
        perror("opendir"); // opendir 실패 시 에러 메시지 출력
        return 1;
    }

    return 0;
}
