#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>

#define MAX_LINE 80
int input(char* str);
int str_to_args(char* str, char* args[], int str_num);
void display_history(int history_front, int history_rear);
void add_history(char* str, int* front, int* rear);

char history[10][MAX_LINE];

int input(char* str){
    char c;
    int i = 0;
    while((c = getchar())!='\n' && i<MAX_LINE){
        str[i] = c;
        i++;
    }
    if(i == MAX_LINE && c != '\n'){
        printf("over maximum length!");
        return 0;
    }
    else{
        str[i] = 0;
        return i;
    }
}

int str_to_args(char* str, char* args[], int str_num){
    const char s[2] = " ";
    int i = 0;
    char* temp;

    temp = strtok(str, s);
    while(temp != NULL){
        args[i] = (char*)malloc(strlen(temp));
        strcpy(args[i], temp);
        i++;
        temp = strtok(NULL, s);
    }
    args[i] = 0;
    return i;
}

void display_history(int history_front, int history_rear){
    if(history_front == history_rear){
        printf("No commands in history.\n");
    }else{
        int i;
        for(i = history_front; i < history_rear; i++){
            printf("%d.\t%s\n", history_rear - i, history[i%10]);
        }
    }
}

void add_history(char* str, int* front, int* rear){
    strcpy(history[*rear%10], str);
    *rear = *rear+1;
    if(*rear - *front > 10){
        *front++;
    }
}

int main(void){
    char* args[MAX_LINE/2+1];
    int should_run = 1;
    int args_num = 0;

    char str[MAX_LINE];
    int str_num;

    int history_front = 0;
    int history_rear = 0;

    int i = 0;
    int concurrentFlag = 0;
    int pid_status;

    while(should_run){
        printf("osh>");
        fflush(stdout);

        str_num = input(str);

        if(str_num == 0){
            continue;
        }
        
        if(strcmp(str, "exit") == 0){
            should_run = 0;
            return 0;
        }

        if(strcmp(str, "!!") == 0){
            if(history_rear != 0){
                strcpy(str, history[(history_rear-1)%10]);
                str_num = strlen(str);
            }
            else{
                printf("No commands in history.\n");
            }
        }
        
        if(strcmp(str, "history") == 0){
            display_history(history_front, history_rear);
        }

        if(strcmp(str, "!!") != 0 && strcmp(str, "history") != 0){
            add_history(str, &history_front, &history_rear);
        }

        args_num = str_to_args(str, args, str_num);

        if(strcmp(args[args_num-1], "&") == 0){
            concurrentFlag = 1;
            args_num--;
            args[args_num] = NULL;
        }

        pid_t pid = fork();
        if(pid == 0){
            pid_status = execvp(args[0], args);
        }
        else{
            if(concurrentFlag == 1){
                printf("%d is running in background %s \n", pid, str);
            }else{
                wait(&pid_status);
            }
        }
        concurrentFlag = 0;
    }
    return 0;
}