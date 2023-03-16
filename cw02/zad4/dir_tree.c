#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ftw.h>

static long long sizes_sum = 0;

int print_file_info(const char *file_path, const struct stat*file_info, int typeflag) {
    if (typeflag == FTW_F) { 
        printf("Size: %ld Filename: %s \n", file_info->st_size, file_path);
        sizes_sum += file_info->st_size;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Too many arguments!\n");
        return(1);
    }

    if (ftw(argv[1], print_file_info, 10) == -1) {
        fprintf(stderr, "Excepction in ftw function!\n");
        return(1);
    }

    printf("Total size: %lld\n", sizes_sum);
    return 0;
}