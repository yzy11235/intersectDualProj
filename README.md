# intersectDualProj
BUAA Software Engineering

## Learning & Design

### step 2 命令行&GUI的IO设计
- 新增IO class
```c++
int guiProcess(std::vector<std::pair<double, double>>* points, std::vector<string> msg);
void cmdProcess(int argc, char* argv[]);
```
- guiProcess之后作为ddl供图像界面调用的接口
- cmdProcess在main中供cmd调用


### step 3 异常处理
- 新增自定义异常处理
#### 异常处理程序知识
- [参考](https://www.runoob.com/cplusplus/cpp-exceptions-handling.html)
  - `try... catch...` `throw`
  - [自定义异常](https://www.cnblogs.com/narjaja/p/10905516.html)

#### 异常处理设计
- 几种异常
  1. 命令行输入异常（参数、文件名）
  2. 输入文件异常（输入曲线不符合格式，输入线段数目，“乱码”输入）
  3. 直线异常
  4. 曲线异常

#### 异常处理单元测试
- 测试方式[参考](https://www.jianshu.com/p/f19e75bf490a)

1.1. 命令行输入——参数异常

```shell
intersect.exe -n 
intersect.exe -i input.txt -o output.txt -h
```

1.2. 命令行输入——文件名异常

```shell
intersect.exe -i test.txt -o output.txt
intersect.exe -i input.txt -o out.txt
```
2.1. 输入文件内容——输入曲线不符合格式

```shell
## 1. 直线输入错误
R 0 43 9 -3 98

# 2. 输入几何对象参数含有前导0
S 09 12 45 89

# 3.  多个字母
S S 3 2 1 

# 4. 只有数字
3 1 5 2 76

# 5. 字母数字乱序
5 L 1 4 6

# 6. -后不接数字
L - - - -

# 7. 错误数字
L 98-736 92 0 82
```

2.2. 输入线段数目异常

```shell
# 1. 输入线段 < 1
0
-94

# 2. 输入线段与实际线段数不同
1
L 0 10 8 83
R 91 46 2 0

4
L 56 28 82 4
R 19 41 34 56
C 56 168 5 
```

2.3.曲线输入文件无法打开

3.1. 直线不符合标准

```shell
## 1. 输入两点重合
L 0 1 0 1 

## 2. 输入数字超范围
R 100000 0 0 0
L -100000 4897 278 1
S -100005 3784 942 61
```

3.2.有无穷多交点
```shell
#1.  正确情况
3
S 1 1 3 3
S 5 5 100 100
R 0 0 -55 -55


# 2. 异常
2
S 0 1 7 8
R -4 -3 -3 -2

2
S 0 1 7 8
L 9 10 100 101

2
R -4 -5 0 -1
L -99 -100 -50 -51

2 
S 1 0 3 0
S 2 0 4 0 

2
S 1 0 3 0
S 2 0 3 0 

2 
S 1 0 3 0
S 1 0 5 0 

2
S 1 0 3 0
S 0 0 5 0
```

4.1. 圆不符合标准
```shell
## 1. 输入圆半径小于1
C 0 0 0

C 84 72 -23

## 2. 输入数字超范围
C -100000 4897 278
```



### Step 4
- VS dll导出
- dll异常处理和gui互联


## Push Record 
- 2020

- 0313: init
  1. 计算类、图形类、基础函数类分离
  2. 加入一些TODO标记
    - 命令行错误处理
    - 直线boundary
    - 时间分析
    - 更换数据结构以优化性能 

- 0315.11:00: add design
  - 确定Point, Line, Circle, Calculator主要的class及其接口
  - 确定实现的主要算法    

- 0315.22:00：debug & update tests
  - 完成部分的基础测试
  - 新增测试和大规模覆盖性测试尚未进行

- 0316.22:00: test & design update
  - 完成第一部分的测试编写，开始debug
  - 完成2、3部分的设计与第四部分的工具选择

- 0317 
  - 12:00 code & tests for step 1 finished
  - 20:00 untested code for step 2

- 0318
  - 20：00 step 2 code&test pushed

- 0320
  - 10：50 step 3 code & tests pushed
  - 19：30 dll pushed