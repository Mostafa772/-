//
// Created by mostafa on 20.09.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct EndAndBeginning {
    char* begin;
    char* end;
};

typedef struct EndAndBeginning EndAndBeginning;

void Swap(EndAndBeginning* a, EndAndBeginning* b)
{
    EndAndBeginning t;
    t = *a;
    *a = *b;
    *b = t;
}

bool CompEndBeginning(EndAndBeginning a, EndAndBeginning b, bool comparison_operator) {
    /// if comparison operator TRUE then it is meant to be: a.begin > b.begin
    /// comparing the beginnings
    if (comparison_operator) {
        return  *a.begin > *b.begin;
    } else {
        /// comparing from the end
        return *a.end > *b.end;
    }

}

EndAndBeginning SelectPivot(const EndAndBeginning vec[], size_t left) {
    return vec[left];
}

size_t Partition(EndAndBeginning vec[], int left, size_t right, bool comparison_operation) {

    EndAndBeginning pivot = SelectPivot(vec, left);
    int partition = left;

    for (size_t j = left + 1; j < right; j++) {

        if (CompEndBeginning(vec[j], pivot, comparison_operation)) {
            partition = partition + 1;
            Swap(&vec[partition], &vec[j]);
        }
    }
    Swap(&vec[left], &vec[partition]);
    return partition;
}

void QuickSort(EndAndBeginning vec[], int left, int right, bool comparison_operation) {
    if (left < right) {
        int q = Partition(vec, left, right, comparison_operation);
        QuickSort(vec, left, q, comparison_operation);
        QuickSort(vec, q + 1, right, comparison_operation);
    }
}



size_t GetSizeFile (FILE* file, int* counter2) {
    int count = 0;  // Line counter (result)
    char c;
    for (c = getc(file); c != EOF; c = getc(file)) {\
        ++*counter2;
        if (c == '\n') { // Increment count if this character is newline{
            count = count + 1;
        }
    }
    return count;
}

char* OpenFile(FILE* fptr, int size_of_file) {
    fseek(fptr, 0, SEEK_SET);
    printf("size1_of_file: %d\n", size_of_file);

    char* c;
    c = static_cast<char*>(calloc( size_of_file + 1, 1));

    if( !static_cast<bool>(c) ) {
        fclose(fptr),fputs("memory alloc fails",stderr),exit(1);
    }

    /* copy the file into the buffer */
    if( 1!=fread( c , size_of_file, 1 , fptr) ) {
        fclose(fptr),free(c),fputs("entire read fails",stderr),exit(1);
    }

    //printf("pointer: %p , value: %c\n ", &c[1], c[1]);
    fclose(fptr);
    return c;
}

int WriteInFile (EndAndBeginning strings[], int* num_of_lines, bool same_string, char* string) {
    
    FILE *fp = fopen("Output.txt","r+");
    
    fseek(fp, 0 ,SEEK_END);

    if (fp == nullptr)
    {
        printf("Error opening the file Output.txt");

        return -1;
    }
    
    // write to the text file
    if(!same_string) {
        for (size_t i = 0; i < *num_of_lines ; ++i) {
            for(int j = 0; ;++j){
                if(strings[i].begin +j == strings[i].end){
                    break;
                }
                fputc(*(strings[i].begin+j), fp);
            }
            fprintf(fp,"\n");
        }
    } else {
        fputs(string, fp);
    }
    
    fprintf(fp, "\n\n************************ END OF THIS WRITING SESSION ***********************************\n\n");
    
    fclose(fp);

    return 1;
}

void Sort(char* text, int* size, int* num_of_lines) {

    EndAndBeginning pointers_strings[*num_of_lines];
    pointers_strings[0].begin = &text[0];

    char* x = strchr(text, '\n');

    for (size_t i = 1; i <= *num_of_lines; ++i){
        
        x = strchr(x, '\n') + 1;
        
        pointers_strings[i].begin = x;
        
        pointers_strings[i - 1].end = x - 1;
        
    }
    
    pointers_strings[*num_of_lines - 1].end = &text[*size - 1];

    QuickSort(pointers_strings, 0, *num_of_lines, true);
    WriteInFile(pointers_strings, num_of_lines, false, text);

    QuickSort(pointers_strings, 0, *num_of_lines, false);
    WriteInFile(pointers_strings, num_of_lines, false, text);

    WriteInFile(pointers_strings, num_of_lines, true, text);

}

int main() {

    FILE* fptr = fopen("hamlet.txt", "r");
    if (fptr == nullptr)
    {
        printf("Cannot open file \n");
        exit(0);
    }

        int num_of_lines = 0;
    int size = 0;

    num_of_lines = GetSizeFile(fptr, &size);

    char* text = OpenFile(fptr, size);

    Sort(text, &size, &num_of_lines);

    printf("num_of_lines: %d size: %d", num_of_lines, size);

    return 0;
}
