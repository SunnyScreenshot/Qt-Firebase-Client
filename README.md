





使用 Qt5 写一个 QWdiget ，调用  firebase_cpp_sdk 移动端的库，一个使用示范。



## 简介

1. 下载 [Firebase C++ SDK](https://firebase.google.com/download/cpp?hl=zh-cn)，然后将 SDK 解压缩到方便的位置。

2. 解压后，将 `include`、`libs` 两个文件夹拷贝到 `Qt-Firebase-Client\tripartite` 下即可

3. 在 main.cpp 中即可编译和与运行

   ```cpp
   #include "widget.h"
   #include <QApplication>
   //#include "analytics.h"           # 此两种方式，均可找到头文件
   #include "firebase/analytics.h"
   
   int main(int argc, char *argv[])
   {
       QApplication a(argc, argv);
       Widget w;
       w.show();
       return a.exec();
   }
   ```

4. 但本项目中，已将 firebase_cpp sdk 的头文件直接上传，故只用拷贝 `libs`  文件夹即可。









1. 在创建 [firebase ](https://console.firebase.google.com/?hl=zh-cn) 创建项目
