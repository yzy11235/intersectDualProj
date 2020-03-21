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