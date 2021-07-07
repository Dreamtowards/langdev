//
// Created by Dreamtowards on 2021/5/20.
//

#include <printf.h>
#include <libc.h>

struct STRUC {
    int i1;
    int i2;
};

void call(int i) {
    int is[i];

}

int main() {

    struct STRUC s1 = {1, 2};
    struct STRUC s2 = {1, 2};

    int i;
    int i2;
    int i3;

//    printf("size of STRUCT %d\n", sizeof s1);
    printf("%p \n", &s1);
    printf("%p \n", &s2);
    printf("%p \n", &i);
    printf("%p \n", &i2);
    printf("%p \n", &i3);

    void* mem = malloc(10);

    memset(mem, 0, 0);



}

