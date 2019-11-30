## 十速创新嵌入式课程

>十速科技与韩山师范学院合作建设的嵌入式课程，本课程采用十速科技的 51核 8位单片机，课程力求基础理论阐述清晰的同时，强化产品开发工程能力的培养。本课程包含 8位 MCU、嵌入式 C51、git 协作技能、嵌入式常规仪器使用和常规器件特性等基础知识。课程中还包含两个完整的嵌入式项目，其中一个项目是市场中实际的产品。以此来展现真实产品的开发流程和工程实践。

### 一、课程前的准备

1. 下载安装 IDE 工具 [keil C51](https://www.keil.com/download/product/)，[十速的keil 插件](http://www.tenx.com.tw/product_tools_detail.aspx?ToolsID=100)。
2. 下载安装 [vscode](https://code.visualstudio.com/)，课程使用 vscode 编辑。
3. 下载安装 git 客户端 [sourcetree](https://www.sourcetreeapp.com/)，课程使用 sourcetree 和 [github](http://www.github.com) 作为项目管理和协作系统。
4. git 入门请读 [Git教程](https://www.liaoxuefeng.com/wiki/896043488029600)，进阶请阅读 [git 权威指南](https://gitee.com/progit/) 或其[英文版](https://git-scm.com/book/en/v2)。

### 二、课程目录结构

  1. textbook 内含课程教材。
  2. guide 内含使用 MCU 工程开发**注意事项**文档，请反复仔细阅读。
  3. datasheets 包含常规器件的详细**数据手册**，普通教学中不会涉及，但本课程特别强调工程实践中对数据书册的理解。比如电阻的使用，可以参见 res 目录中的手册。
  4. prj1 包含一块直流供电的实验开发板的原理设计和代码开发的完整材料。
  5. prj2 包含一个产品（茶艺壶）的设计、布板和代码开发的全部材料，从中可以学习市场中真实产品的开发流程。
  6. 3rdPartCode 包含从网络收集，经课程组整理修订的各类常用模块和代码。
  7. tools 包含学生的大胆尝试-自动代码框架生成工具，期望提高开发效率和可靠代码的复用性。

### 三、课程重点内容

>请课程的使用者特别关注以下几点：

1. 基于Git 分布式版本管理系统的协作能力。
2. MarKDown 文档的写作能力，请阅读 [MarkDown 写作指南](https://shd101wyy.github.io/markdown-preview-enhanced/#/zh-cn/)。
3. 嵌入式 C 语言中的 volatile、const、interrupt 等几个关键词后面的理论含义。
4. 形成自己的编程风格和规范，课程中会给出一种风格规范。
5. 嵌入式常规仪器（万用表，逻辑分析仪，示波器等）的使用能力训练，嵌入式程序员易忽略此点。
6. 产品创新和规划能力，培养工程师的商业敏锐度。

> 使用课程时有任何问题和建议，请及时与我们联系，请 pull request 。
