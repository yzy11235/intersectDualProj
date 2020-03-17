# intersectDualProj
BUAA Software Engineering

## Learning & Design

### step 2 命令行&GUI的IO设计
- 新增IO class

### step 3 异常处理
- 新增自定义异常处理
#### 异常处理程序知识
- [参考](https://www.runoob.com/cplusplus/cpp-exceptions-handling.html)
  - `try... catch...` `throw`
  - [自定义异常](https://www.cnblogs.com/narjaja/p/10905516.html)

#### 异常处理设计
- 几种异常
  1. 命令行输入异常（参数、文件名）
  2. 输入文件内容异常（输入曲线不符合格式，输入线段数目，“乱码”输入）
  3. 运行时异常（曲线输入文件无法打开，坐标范围超限，直线定义中两点重合，有无穷多交点）

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
# 线
## 输入两点重合
L 0 1 0 1 

## 直线输入错误
R 0 43 9 -3 98

S 0 28 2

# 圆
## 输入圆半径小于1
C 0 0 0

C 84 72 -23

# 输入几何对象参数含有前导0
S 09 12 45 89

# 输入超范围
R 100000 0 0 0
L -100000 4897 278 1
S -100005 3784 942 61
```

2.2. 输入线段数目异常

```shell
# 输入线段 < 1
0
-94

# 输入线段与实际线段数不同
1
L 0 10 8 83
R 91 46 2 0

4
L 56 28 82 4
R 19 41 34 56
C 56 168 5 
```

2.3. 乱码输入

```shell
# -后不接数字
L - - - -

# 错误数字
L 98-736 92 0 82

# 多个字母
S S 3 2 1 

# 只有数字
3 1 5 2 76

# 字母数字乱序
5 L 1 4 6
```


3.1.曲线输入文件无法打开

3.2.有无穷多交点
```shell
# 正确情况
3
S 1 1 3 3
S 5 5 100 100
R 0 0 -55 -55


# 异常
2
S 0 1 7 8
R -4 -3 -3 -2

2
S 0 1 7 8
L 9 10 100 101

2
R -4 -5 0 -1
L -99 -100 -50 -49
```

### Step 4
- GUI采用MFC开发
  - [MFC VS配置及基本编写](https://www.cnblogs.com/gemuxiaoshe/p/12054099.html)
  - [dll是啥](https://www.cnblogs.com/code1992/p/9585853.html)
  - [dll咋写](https://blog.csdn.net/hlx371240/article/details/51507025)



## Test
- Point (finished)
  - all function tests
- Line (finished)
  - all function tests
- Circle (finished)
  - all function tests
- Calculator (partly finished)
  - finished: `xmult` `pOnline` `pInCircle` `isParallel`
  - unfinished: haveIntersection，原有个人项目的直线相关测试全部保留，需要完善射线与线段的测试；circle之间的交点无需变更，采用回归测试即可。

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
