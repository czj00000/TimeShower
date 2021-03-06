# 时间显示
* 此应用可以在屏幕上指定显示时间，可以防止某些拖堂行为 ~~(没有卵用)~~
---
## 重要消息: 本仓库即日起永久迁移至Gitee, GitHub停止更新
---
## 更新日志
### v1.0
* 第一个版本...
### v1.0.1
* 修复了恢复默认设置时会直接追加而不是重写的BUG
* 增加了自动对齐网格功能，可以通过将settings.txt中`doAutoAlign`的值改为`0`来禁用 
* ~~_修改了版本号_~~
### v1.0.2
* 修复了当`size`的值不为`1`时自动对齐无法正常工作的BUG
* 修复了移动至屏幕右边缘时侧边栏被遮挡的BUG
* 将图标分类到fluentStyle下，方便添加新的图标风格
* ~~_修改了版本号_~~
### v1.1
* (BUG修复)
* 将图标格式改为svg
* 将所有常量等转移到同一个文件中，优化文档结构
* 加入了更好看的对话框(半成品)
* ~~_修改了版本号_~~
### v1.1.1
* 修复了对话框文字显示不全的问题 ~~(其实就是忘了适配DPI)~~ 
* 修改了主界面的字体颜色
* 将对话框正文字体修改为楷体
* ~~_修改了版本号_~~
### v1.1.2
* 真正修复了v1.1.1未能修复的BUG
* ~~_修改了版本号_~~
### v1.1.3
* 解决了对话框底部的按钮问题
* ~~_修改了版本号_~~
### v1.2
* 将关闭按钮替换为最小化按钮
* 加入系统托盘图标和菜单
* 正式加入了时间表（时间表的编写范例在example.json中）
* 修改了窗口大小的控制机制，现在支持任意大小
* 加入了更加详细亿点的日志
* 美化了对话框
* 加入自建的关机前摇
* 可以更方便地更改关机前摇（在settings.txt中修改`shutDownPrerock`的值即可）
* ~~_修改了版本号_~~
### v1.2.1
* 修复了BUG:关机事件不调用自建提示，而是系统提供的
* 修复了BUG:关机前摇的时间似乎不能自定义
* ~~_修改了版本号_~~
### v1.2.2
* 修复了BUG:当程序打开时间晚于第一个事件的执行时间时，所有事件都不会执行
* 修复了BUG:上一版本中“关于”对话框显示的版本号还是1.2
* ~~_修改了版本号_~~
### v1.2.3
* 下方当前事件栏实装
* 修改了Dpi的计算机制（未做完）
* 将设置改为Json
* 日志中的事件现在精确到毫秒
* 加入了更多~~没用~~的日志
* 现在应用会实时监测设置的改变
* ~~_修改了版本号_~~
### v1.3
* 修复了BUG:关机前摇消失，没有提示直接关机
* 进行了代码结构的优化
* 加入了半成品（~~刚刚开始做~~）的设置界面，默认不启用，如果真的想看的话把settings.json里的`enableSettingsWidget`改成`true`
* 现在支持拖拽加载时间表（可以不用翻目录了，好耶ヽ(✿ﾟ▽ﾟ)ノ）
* ~~_修改了版本号_~~
### v1.3.1
* 修复了BUG:日志中多次重复同一内容导致日志过长
* 修复了BUG:关机窗口出现后点击任何按钮都会导致应用崩溃
* 由于上一点提到的玄学BUG，目前自制的关机前摇无法使用。已将其替换为系统提供的
* 暂时移除了设置窗口，未来会加入
* ~~_修改了版本号_~~
