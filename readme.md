# WOL 工具

## 使用说明
```shell
wol  MAC地址  [IP地址] [端口号]
```
不传递端口号的时候,默认端口号为 9 

例程:
```shell
$ ./wol 00:0B:CD:39:2D:E9
$ ./wol 00:0B:CD:39:2D:E9 192.168.1.36 
$ ./wol 00:0B:CD:39:2D:E9 192.168.1.36  5000
```

## 编译说明:
进入 src 目录,输入 make 即可,手工编译 
```shell
gcc -Wall -o wol wol.cpp main.cpp
```

