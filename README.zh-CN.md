[英语](./README.md)\|[简体中文](./README.zh-CN.md)\|[繁体中文](./README.zh-TW.md)\|[韩国语](./README.ko.md)\|[印度](./README.hi.md)\|[阿拉伯](./README.ar.md)\|[法语](./README.fr.md)\|[俄语](./README.ru.md)\|[拉丁](./README.la.md)\|[日本语](./README.ja.md)\|[意大利语](./README.it.md)\|[德语](./README.de.md)\|[西班牙语](./README.es.md)\|[瑞典](./README.sv.md)\|[波斯语](./README.fa.md)\|[土耳其](./README.tr-TR.md)

![image](https://user-images.githubusercontent.com/100348948/165334090-0b1a6f28-554e-484b-9946-1ffef010fa78.png)

# 

[![Join the chat at https://gitter.im/filecxx/FileCentipede](https://badges.gitter.im/filecxx/FileCentipede.svg)](https://gitter.im/filecxx/FileCentipede?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

<a href="http://filecxx.com" target="_blank">
  <img src="./style/images/logo_128.png" width="128" alt="File Centipede Icon" />
</a>

File centipede 是一款一体化互联网文件上传/下载管理器、BitTorrent 客户端、WebDAV 客户端、FTP 客户端和 SSH 客户端。

它被设计为快速、可定制且用户友好。

它支持多协议，并包含许多有用的辅助工具，例如 HTTP 请求器、文件合并和编码器。

通过浏览器集成，您可以从网站下载音频和视频，甚至加密的视频。

（免费无广告）

网站：[http://filecxx.com](http://filecxx.com)

仪表板：[https://w.filecxx.com](https://w.filecxx.com)

赞助商：[http://www.filecxx.com/en_US/sponsors.html](http://www.filecxx.com/en_US/sponsors.html)

## 截屏

#### 文件蜈蚣

![File Centipede](images/screenshot_software.png)![File Centipede](images/screenshot_software2.png)![File Centipede](images/screenshot_software_file_browser_webdav.png)![File Centipede](images/screenshot_software_file_browser_ssh.png)![File Centipede](images/screenshot_software_file_browser_ftp.png)![File Centipede](images/screenshot_software_file_browser_add.png)![File Centipede](images/screenshot_software_file_browser_log.png)

#### 添加任务

![Add task](images/screenshot_add_task.png)![Add task](images/screenshot_add_task2.png)![Add task](images/screenshot_add_task3.png)![Add task](images/screenshot_add_task4.png)

#### 编辑任务

![Edit task](images/screenshot_edit_task.png)![Edit task](images/screenshot_edit_task2.png)

#### 确认对话框

![torrent confirm](images/screenshot_torrent_confirm.png)![http confirm](images/screenshot_http_confirm.png)![links confirm](images/screenshot_links_confirm.png)

#### 添加目录

![add catalog](images/screenshot_add_catalog.png)

#### 设置

![settings](images/screenshot_settings.png)

#### 代理设置

![proxy](images/screenshot_proxy.png)

#### 网站规则

![Site rules](images/screenshot_site_rule.png)![Site rules](images/screenshot_site_rule2.png)

#### 过滤器

![filter](images/screenshot_filter.png)

#### 刷新地址

![${refresh_address}](images/screenshot_refresh_address.png)

#### 创建种子

![create_torrent](images/screenshot_create_torrent.png)

#### 速度限制

![Speed limit](images/screenshot_download_speed_limit.png)

#### 翻译工具

![Translate tool](images/screenshot_translate.png)

#### HTTP工具

![HTTP tool](images/screenshot_http_tool.png)

#### 校验和工具

![Checksum tool](images/screenshot_checksum_tool.png)

## 浏览器扩展截图

#### 视频栏

![Video bar](images/extension_video_bar.png)

#### 视频面板

![videos panel](images/extension_videos.png)

#### 音频面板

![Audios panel](images/extension_audios.png)

## 特征

-   HTTP、HTTPS协议（gzip、断点续传、多连接等基本功能不再列出） 1.0
-   FTP、FTPS协议 1.0
-   magnet、HASH 地址 1.0
-   BT 1.0
-   其他自定义协议如迅雷、快车、qqdl 1.0
-   JSON 格式的地址 1.0
-   m3u8 流任务 1.0
-   流任务 AES​​-128 解密（尚不支持SAMPLE-AES解密）1.0
-   HTTP cookie、标头、用户代理以及用户自定义 1.0
-   torrent 种子限制 1.0
-   动态编辑传输任务配置 1.0
-   防蛭 1.0
-   刷新过期地址 1.0
-   目录 1.0
-   限制下载、上传速度 1.0
-   创建自定义地址（filec、fileu）1.0
-   代理管理 1.0
-   过滤器定制 1.0
-   追踪器管理 1.0
-   任务详情 1.0
-   从任务导出 torrent 1.0 
-   多语言 1.0
-   队列或无限并发设置 1.0
-   Chrome 浏览器集成 1.0
-   火狐浏览器集成1.0
-   抓取网页视频、音频 1.0
-   从网页中查找所有的 magnets 1.0
-   翻译工具 1.0
-   HTTP 工具 1.0
-   URI 编码/解码工具 1.0
-   Base64 编码/解码工具 1.0
-   正则表达式测试工具 1.0
-   创建种子 1.0
-   torrent 转 magnet 工具 1.0
-   magnet 转 torrent 工具 1.0
-   文件合并工具 1.0
-   统计 1.0
-   下载网页的所有链接 1.6
-   SSH、SFTP协议 2.0
-   curl、wget、aria2、axel 命令行 2.0
-   WebDAV 协议 2.0
-   上传文件 2.0
-   上传目录 2.0
-   下载目录 2.0
-   全功能 WebDAV 文件管理器 2.0
-   全功能 FTP 文件管理器 2.0
-   全功能 SSH(sftp) 文件管理器 2.0
-   文件浏览器持久缓存 2.0
-   网站规则 2.1
-   校验和工具 2.3
-   远程下载 2.6

## 源代码

FileU 的完整源代码可以在“source_code”目录中找到。

仅用于演示目的，项目中使用的依赖库不是开源的。

事实证明，用 C++ 编写用户界面比 HTML 和 JavaScript 容易得多，而且不会降低性能。

（如“UI”目录中的 .sml 文件所示）。

## 翻译

如果您喜欢这个软件，您可以使用软件中提供的翻译工具将其翻译成其他语言。

这将使使用该软件最初编写的语言以外的语言的人更容易使用该软件。我们将非常感谢您的贡献。

## 语言文件

-   网站：“lang/website/\*.lang”
-   软件：“lang/software/\*.lang”
-   浏览器扩展名：“lang/browser_extension/\*.lang”

#### 如何翻译网站？

![translate](images/document/how_to_translate_this_website.png)

| 语言    | @                                                                                     |
| :---- | :------------------------------------------------------------------------------------ |
| 俄语    | [@vanja-san](https://github.com/vanja-san)[@Den1704](https://github.com/Den1704)      |
| 繁体中文  | [@熊0316](https://github.com/bear0316)[@postman1year](https://github.com/postman1year) |
| 法语    | [@Ksahikh](https://github.com/XIAA25)                                                 |
| 荷兰语   | [@Ksahikh](https://github.com/XIAA25)                                                 |
| 韩国语   | [@维纳斯女孩](https://github.com/VenusGirl)                                                |
| 越南语   | [@vuongtuha](https://github.com/vuongtuha)                                            |
| 土耳其   | [@geeeede](https://github.com/geeede)[@saurane](https://github.com/saurane)           |
| 印度尼西亚 | [@吉格利洛](https://github.com/gigglylo)                                                  |
| 德语    | [@Vulcanraven91](https://github.com/Vulcanraven91)                                    |
| 日本语   | [@wany-哦](https://github.com/wany-oh)                                                 |
| 波兰语    | [@鲁诺霍克](https://github.com/RunoHawk)                                                  |

## 开源库

[boost](https://www.boost.org) [Qt](https://qt.io/) [libtorrent](https://www.libtorrent.org)
