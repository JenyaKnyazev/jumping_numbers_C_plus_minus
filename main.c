#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define GREEN FOREGROUND_GREEN
#define RED FOREGROUND_RED
#define BLUE FOREGROUND_BLUE
#define WHITE BLUE|RED|GREEN
int digits,exercises,rounds,sum,sum2,correct,wrong,pm,delay;
HANDLE h;
COORD c;
clock_t start,end;
int colors[] = {GREEN,RED,BLUE,RED|GREEN,RED|BLUE,BLUE|GREEN};
void clean(){
    SetConsoleCursorPosition(h,c);
    puts("                                                                        ");
    SetConsoleCursorPosition(h,c);
}
int change_num_color(int prev_color) {
    int color;
    while ((color = colors[rand() % 6]) == prev_color);
    SetConsoleTextAttribute(h, color);
    return color;
}
void input(){
    do{
        printf("enter 1 for simple, enter 2 for interesting: ");
        scanf("%d",&pm);
        getchar();
        clean();
    }while(pm>2||pm<1);
    printf("enter amount of digits: ");
    scanf("%d",&digits);
    getchar();
    clean();
    printf("enter amount of exercises: ");
    scanf("%d",&exercises);
    getchar();
    clean();
    printf("enter amount of rounds: ");
    scanf("%d",&rounds);
    getchar();
    clean();
}
int gen_num(){
    int d=digits;
    int n=rand()%9+1;
    while(--d){
        n*=10;
        n+=rand()%10;
    }
    if(pm==2&&rand()%2)
        return n*-1;
    return n;
}
int jump_num(int color,int *prev_n){
    int n,k=gen_num();
    while ((n = rand() % 40) >= (*prev_n)-digits&& n <= (*prev_n)+digits);
    (*prev_n) = n;
    while(n--){
        putchar(' ');
    }
    sum+=k;
    color=change_num_color(color);
    printf("%d",k);
    Sleep(delay);
    clean();
    return color;
}
void round_(){
    int e=exercises;
    int color = -1;
    int prev_jump_location=-1;
    sum=0;
    printf("Ready press any key");
    getchar();
    clean();
    while(e--){
        color=jump_num(color,&prev_jump_location);
    }
    SetConsoleTextAttribute(h, WHITE);
    printf("enter the sum: ");
    scanf("%d",&sum2);
    getchar();
    clean();
    if(sum2==sum){
        printf("CORRECT!");
        correct++;
    }else{
        printf("WRONG!");
        wrong++;
    }
    Sleep(5000);
    clean();
}
void play(){
    int again,t;
    printf("Enter delay in miliseconds: ");
    scanf("%d", &delay);
    getchar();
    clean();
    do{
        input();
        start=clock()/CLOCKS_PER_SEC;
        correct=wrong=0;
        while(rounds--){
            round_();
        }
        end=clock()/CLOCKS_PER_SEC;
        t=end-start;
        printf("correct: %d, wrong: %d, total: %d,time %d:%d",correct,wrong
        ,correct+wrong,t/60,t%60);
        Sleep(10000);
        clean();
        printf("again enter 0 other exit: ");
        scanf("%d",&again);
        getchar();
        clean();
    }while(!again);
    printf("Good Bay");
    Sleep(10000);
}
int main(){
    srand(time(NULL));
    c.X=c.Y=0;
    h=GetStdHandle(-11);
    play();
    return 0;
}