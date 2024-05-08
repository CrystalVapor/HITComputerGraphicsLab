# HITComputerGraphicsLab
A possible implementation version for HIT's Computer Graphics Lab / 哈工大图形学与虚拟现实课程实验的一个可能实现版本

## 项目编译
**本项目使用了第三方开源库作为子模块，因此在克隆本项目时请使用`git clone --recursive`命令以同时克隆子模块。**

**或者在克隆后使用`git submodule update --init --recursive`命令来初始化子模块。**

**本项目使用CMake作为构建工具，因此在编译前请确保已经安装了CMake。**

可以执行以下命令来编译项目：
```bash
git clone --recursive https://github.com/CrystalVapor/HITComputerGraphicsLab.git
cd HITComputerGraphicsLab
mkdir build
cd build
cmake ..
cmake --build .
```

编译后的文件将生成于`.\bin`目录下。

## 实验一文件使用方法

usage: `.\bin\lab1.exe [vertex_shader_path] [fragment_shader_path]`