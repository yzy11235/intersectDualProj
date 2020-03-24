# 运行说明

### 目录结构说明

```
intersectDualProj/
├── bin    //cmd可执行文件
│   ├── intersect.exe
│   └── dll和lib文件
├── README.md
├── src
│   //核心计算模块源代码
└── test
│   //核心计算模块源代码
└── GUI
    ├── exeFiles
    |    //GUI可执行文件
    └── src
        //GUI源码

```



### cmd运行说明

将bin中的三个文件放在同一目录下

命令行运行指令为：

`intersect.exe -i input.txt -o output.txt`

### GUI运行说明

将`GUI/exeFiles`中的文件全部放于同一目录下，运行 exe

注意：GUI的画布中最大的x坐标为10，图形太大时会超过画布无法显示绘制。



### 附加题

与我们对接的组的仓库链接为https://github.com/zwx980624/IntersectProject

只需更换可执行文件夹中的 `calcInterface.lib``calcInterface.dll`即可完成对接

由于我们一开始就商量好了接口，所以没有为对接改动太多

