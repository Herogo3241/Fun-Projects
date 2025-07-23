#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *temp = fopen("hello.txt", "w");
    fprintf(temp, "This is a temporary file.\n");
    fclose(temp);


    char *q = "#include <stdio.h>%c#include <stdlib.h>%c#ifdef _WIN32%c#include <windows.h>%c#else%c#include <unistd.h>%c#endif%c%cint main() {%c    printf(%cWaiting 5 seconds...\\n%c);%c#ifdef _WIN32%c    Sleep(5000);%c#else%c    sleep(5);%c#endif%c%c    remove(%chello.txt%c);%c remove(%cout.c%c);%c    return 0;%c}%c";

    FILE *f = fopen("out.c", "w");
    // debugging
    // printf(q, 10, 10, 10, 10, 10, 10, 10, 10,
    //     10, 34, 34, 10,
    //     10, 10, 10, 10, 10, 10,
    //     34, 34, 10, 34, 34, 10,
    //     10, 10);
    fprintf(f, q, 10, 10, 10, 10, 10, 10, 10, 10,
        10, 34, 34, 10,
        10, 10, 10, 10, 10, 10,
        34, 34, 10, 34, 34, 10,
        10, 10);
    fclose(f);


    system("gcc out.c -o out && out.exe");
    remove("out.exe");

    return 0;
}
