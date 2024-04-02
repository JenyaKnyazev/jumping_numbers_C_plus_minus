#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int digits,exercises,rounds,sum,sum2,correct,wrong,pm;
HANDLE h;
COORD c;
clock_t start,end;
void clean(){
    SetConsoleCursorPosition(h,c);
    puts("                                                                        ");
    SetConsoleCursorPosition(h,c);
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
void jump_num(){
    int n=rand()%30,k=gen_num();
    while(n--){
        putchar(' ');
    }
    sum+=k;
    printf("%d",k);
    Sleep(1000);
    clean();
}
void round_(){
    int e=exercises;
    sum=0;
    printf("Ready press any key");
    getchar();
    clean();
    while(e--){
        jump_num();
    }
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
        Sleep(5000);
        clean();
        printf("again enter 0 other exit: ");
        scanf("%d",&again);
        getchar();
        clean();
    }while(!again);
    printf("Good Bay");
    Sleep(5000);
}
int main(){
    srand(time(NULL));
    c.X=c.Y=0;
    h=GetStdHandle(-11);
    play();
    return 0;
}