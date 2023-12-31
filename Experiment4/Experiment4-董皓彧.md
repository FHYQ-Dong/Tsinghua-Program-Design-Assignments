# Experiment4-董皓彧
环境: 
```txt
gcc.exe (x86_64-win32-seh-rev0, Built by MinGW-W64 project) 8.1.0
Visual Stdio Code 1.83.1
```
作业仓库地址: 
[https://github.com/FHYQ-Dong/Tsinghua-Program-Design-Assignments/tree/main/Experiment4](https://github.com/FHYQ-Dong/Tsinghua-Program-Design-Assignments/tree/main/Experiment4)
## 必做题
### Experiment4-1
题目: 
```txt
输入函数参数x, (x, y), 计算函数值并输出
```
代码: 
```c
#include<stdio.h>
#include<math.h>
#define pi acos(-1)

void print_exp() {
    double x = 0;
    scanf("%lf", &x);
    double tmp = exp(-0.5 * x * x);
    printf("f(x) = %lf\n", (1/sqrt(2 * pi)) * tmp);
    return;
}

void printf_sin_cos() {
    double x = 0, y = 0;
    scanf("%lf %lf", &x, &y);
    printf("f(x, y) = %lf\n", (double)(1)/3 * sin(x*x + y*y) * cos(x+y));
    return;
}

int main() {
    print_exp();
    printf_sin_cos();
    return 0;
}
```
输入1: 
```txt
1
1 1
```
输出1: 
```txt
f(x) = 0.241971
f(x, y) = -0.126134
```

### Experiment4-2
题目: 
```txt
写出下列C表达式的值并输出
```
代码: 
```c
#include<stdio.h>
#include<stdlib.h>

int main() {
    printf("(!x && x!=0) == false\n");
    printf("(!(x==a) && (y==b) && 0) == false\n");
    printf("(-10<a<5 && b==c) == false\n");
    printf("(5>3 && 2 || 8<4-!0) == true\n");
    printf("(!4<y<5 && 5<b<6) == true\n");
    printf("(!x || x!=0) == true\n");
    printf("(3<x<5 || y>3 && y<2) == true\n");
    return 0;
}
```
输入1: 
```txt

```
输出1: 
```txt
(!x && x!=0) == false
(!(x==a) && (y==b) && 0) == false
(-10<a<5 && b==c) == false
(5>3 && 2 || 8<4-!0) == true
(!4<y<5 && 5<b<6) == true
(!x || x!=0) == true
(3<x<5 || y>3 && y<2) == true
```

### Experiment4-3
题目: 
```txt
判断谁是发帖者: 
甲说：乙发的；
乙说：丙发的；
丙说：乙说谎。
```
代码: 
```c
#include<stdio.h>
#include<stdlib.h>
#define true 1
#define false 0
typedef int bool;

bool a = false, b = false, c = false; // false: 不是泄密者

bool argument_a(bool b, bool honest) { // b: a的谈论对象, honest: a说的话的真假
    return honest ? b==1 : b==0;
}
bool argument_b(bool c, bool honest) { // c: b的谈论对象, honest: b说的话的真假
    return honest ? c==1 : c==0;
}
bool argument_c(bool argv_b, bool honest) { // argv_b: b的谈论对象, honest: c说的话的真假
    return honest ? argument_b(argv_b, false) : argument_b(argv_b, true);
}

void init(int x) {
    a = x == 1;
    b = x == 2;
    c = x == 3;
    return;
}

bool check() {
    for(int ha=0; ha<=1; ++ha) {
        for(int hb=0; hb<=1; ++hb) {
            for(int hc=0; hc<=1; ++hc) {
                if (argument_a(b, ha) && argument_b(c, hb) && argument_c(c, hc)) {
                    printf("若甲说%s话, 乙说%s话, 丙说%s话, 则:\n", ha?"真":"假", hb?"真":"假", hc?"真":"假");
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    bool flag = false;
    for(int i=1; i<=3; ++i) {
        init(i);
        if(check()) {
            printf("可能的泄密者是%s\n", i==1?"甲":i==2?"乙":"丙");
            flag = true;
        }
    }
    if(!flag) printf("没有泄密者\n");
    return 0;
}
```
输入1: 
```txt

```
输出1: 
```txt
若甲说假话, 乙说假话, 丙说真话, 则:
可能的泄密者是甲
若甲说真话, 乙说假话, 丙说真话, 则:
可能的泄密者是乙
若甲说假话, 乙说真话, 丙说假话, 则:
可能的泄密者是丙
```

## 选做题
### Optional-Experiment4-1
题目: 
```txt
某食堂管理员带1000元人民币去市场买鸡，市场价每只小鸡5元，每只公鸡10元，每只母鸡15元。该管理员打算正好买100只鸡，每种鸡的数目都要大于零，并且尽可能多买母鸡。请编程序，替他制定采购方案。
```
代码: 
```c
#include<stdio.h>
#include<stdlib.h>

typedef int bool;
#define true 1
#define false 0

int cnt15, cnt10, cnt5;
bool flag;

int main() {
    for(cnt15=98; cnt15>0; --cnt15) {
        for(cnt10=99-cnt15; cnt10>0; --cnt10) {
            cnt5 = 100 - cnt15 - cnt10;
            if(cnt15*15 + cnt10*10 + cnt5*5 == 1000) {
                flag = true;
                goto end;
            }
        }
    }
end:
    if(flag) printf("%d只母鸡, %d只公鸡, %d只小鸡\n", cnt15, cnt10, cnt5);
    else printf("无解\n");
    return 0;
}

```
输入1: 
```txt

```
输出1: 
```txt
49只母鸡, 2只公鸡, 49只小鸡
```

