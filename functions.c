#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <limits.h>

int mapIndex(FILE*file, int index, int len) {
    int res = 0;
    long ptr = ftell(file);
    rewind(file);
    for (int j = index + 1; j > 0 ; j--) {
        int temp = INT_MIN;
        for (; temp <= 0 && res < len; res++) fread(&temp, sizeof(int), 1, file);
        if (res > len) return -1;

    }
    fseek(file, ptr, SEEK_SET);
    return res - 1;
}
void readNum(FILE** file, int pos, int* num)
{
    fseek(*file, pos * (int)sizeof(int), SEEK_SET);
    fread(num, sizeof(int), 1, *file);
}

void writeNum(FILE** file, int pos, int* num)
{
    fseek(*file, pos * (int)sizeof(int), SEEK_SET);
    fwrite(num, sizeof(int), 1, *file);
}

void swapInFile(FILE* file, int i, int j) {
    int num1, num2;

    readNum(&file, i, &num1);
    readNum(&file, j, &num2);

    writeNum(&file, i, &num2);
    writeNum(&file, j, &num1);
}

int fileSize(FILE* file) {
    fseek(file, 0, SEEK_END);
    int size = (int)ftell(file) / (int)sizeof(int);
    rewind(file);
    return size;
}

void sortBinaryFile(char * filename,int n) {

    FILE* file;
    fopen_s(&file, filename, "r+b");
    int num1, num2;
    int posCount = 0;
    rewind(file);
    for (int i = 0; i < n; i++)
    {
        int temp;
        fread(&temp, sizeof(int), 1, file);
        if (temp > 0) posCount++;
    }
    rewind(file);
    for (int i = 0; i < posCount - 1; ++i) {
        for (int j = i + 1; j < posCount; ++j) {
            int _i = mapindex(file, i, n);
            int _j = mapindex(file, j, n);

            readNum(&file, _i, &num1);
            readNum(&file, _j, &num2);
            if (num1 > num2) {
                swapInFile(file, _i, _j);
            }
        }
    }
    printf("\n");
    fclose(file);
}


void SearchMaxMin(int count, int* min, int* max,char * filename)
{
    FILE* file;
    fopen_s(&file, filename, "rb");
    int n;
    rewind(file);
    fread(&n, sizeof(int), 1, file);
    *min = n;
    *max = n;
    for (int i = 1; i < count; i++)
    {
        fread(&n, sizeof(int), 1, file);
        if (n > *max)
            *max = n;
        if (n < *min)
           * min = n;

    }
    fclose(file);
}

int valid_int(int min, int max) {
    int value;
    while (1) {
        int result = scanf_s("%d", &value);
        char check;
        int is_valid = 1;
        while ((check = getchar()) != '\n') {
            if (check < '0' || check > '9')
                is_valid = 0;
        }
        if (is_valid == 1 && value >= min && value <= max)
            return value;
        else
            printf("Ошибка.Введите целое число в диапозоне от %d до %d:\n", min, max);
    }
}

void ChangeMinMax(char *filename,int count,int max,int min,int * count_max)
{
    FILE* file;
    fopen_s(&file, filename, "r+b");
    rewind(file);
    for (int i = 0; i < count; i++)
    {
        int num;
        fread(&num, sizeof(int), 1, file);
            if (max == num) {
            (*count_max)++;
            fseek(file, -(long)sizeof(int), SEEK_CUR);
            fwrite(&min, sizeof(int), 1, file);
            fflush(file);
            }
    }
    fclose(file);
}+

void OutputFile(int count,char * filename)
{
    int num;
    FILE* file;
    fopen_s(&file, filename, "rb");
    
    rewind(file);
    for (int i = 0; i < count; i++)
    {
        fread(&num, sizeof(int), 1, file);
        printf("%d\n", num);

    }
    fclose(file);
}

void FillFile(int *count,char * filename)
{
    int num;
    FILE* file;
    fopen_s(&file, filename, "wb");
    printf("Введите количество чисел:\n");
    (*count) = valid_int(1, 100);
    printf("\n");

    printf("Введите числа:\n");
    for (int i = 0; i < (*count); i++) {
        num = valid_int(-100, 100);
        fwrite(&num, sizeof(int), 1, file);
    }
    fclose(file);
}
