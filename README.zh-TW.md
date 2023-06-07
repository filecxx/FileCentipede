[英語](./README.md)\|[簡體中文](./README.zh-CN.md)\|[繁體中文](./README.zh-TW.md)\|[韓國人](./README.ko.md)\|[沒有](./README.hi.md)\|[阿拉伯](./README.ar.md)\|[法語](./README.fr.md)\|[俄語](./README.ru.md)\|[拉丁](./README.la.md)\|[日本人](./README.ja.md)\|[意大利語](./README.it.md)\|[德語](./README.de.md)\|[西班牙語](./README.es.md)\|[瑞典](./README.sv.md)

![image](https://user-images.githubusercontent.com/100348948/165334090-0b1a6f28-554e-484b-9946-1ffef010fa78.png)

# 

[![Join the chat at https://gitter.im/filecxx/FileCentipede](https://badges.gitter.im/filecxx/FileCentipede.svg)](https://gitter.im/filecxx/FileCentipede?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

<a href="http://filecxx.com" target="_blank">
  <img src="./style/images/logo_128.png" width="128" alt="File Centipede Icon" />
</a>

文件蜈蚣是一個多合一的互聯網文件上傳/下載管理器，BitTorrent 客戶端，WebDAV 客戶端，FTP 客戶端和 SSH 客戶端。

它旨在快速、可定制且用戶友好。

它支持多協議並包含許多有用的輔助工具，例如 HTTP 請求器、文件合併和編碼器。

通過瀏覽器集成，您可以從網站下載音頻和視頻，甚至是加密視頻。

（它是免費的，沒有廣告）

網站：<http://filecxx.com>

儀表板：<https://w.filecxx.com>

贊助商：<http://www.filecxx.com/en_US/sponsors.html>

## 截屏

#### 檔案蜈蚣

![File Centipede](images/screenshot_software.png)![File Centipede](images/screenshot_software2.png)![File Centipede](images/screenshot_software_file_browser_webdav.png)![File Centipede](images/screenshot_software_file_browser_ssh.png)![File Centipede](images/screenshot_software_file_browser_ftp.png)![File Centipede](images/screenshot_software_file_browser_add.png)![File Centipede](images/screenshot_software_file_browser_log.png)

#### 添加任務

![Add task](images/screenshot_add_task.png)![Add task](images/screenshot_add_task2.png)![Add task](images/screenshot_add_task3.png)![Add task](images/screenshot_add_task4.png)

#### 編輯任務

![Edit task](images/screenshot_edit_task.png)![Edit task](images/screenshot_edit_task2.png)

#### 確認對話框

![torrent confirm](images/screenshot_torrent_confirm.png)![http confirm](images/screenshot_http_confirm.png)![links confirm](images/screenshot_links_confirm.png)

#### 添加目錄

![add catalog](images/screenshot_add_catalog.png)

#### 設置

![settings](images/screenshot_settings.png)

#### 代理設置

![proxy](images/screenshot_proxy.png)

#### 網站規則

![Site rules](images/screenshot_site_rule.png)![Site rules](images/screenshot_site_rule2.png)

#### 篩選

![filter](images/screenshot_filter.png)

#### 刷新地址

![${refresh_address}](images/screenshot_refresh_address.png)

#### 創建種子

![create_torrent](images/screenshot_create_torrent.png)

#### 速度極限

![Speed limit](images/screenshot_download_speed_limit.png)

#### 翻譯工具

![Translate tool](images/screenshot_translate.png)

#### HTTP工具

![HTTP tool](images/screenshot_http_tool.png)

#### 校驗和工具

![Checksum tool](images/screenshot_checksum_tool.png)

## 瀏覽器擴展截圖

#### 視頻欄

![Video bar](images/extension_video_bar.png)

#### 視頻面板

![videos panel](images/extension_videos.png)

#### 音頻面板

![Audios panel](images/extension_audios.png)

## 特徵

-   HTTP、HTTPS協議（gzip、斷點續傳、多連接等基本特性不再列舉）1.0
-   FTP、FTPS協議1.0
-   磁鐵，HASH地址1.0
-   比特流 1.0
-   其他自定義協議如迅雷、快車、qqdl 1.0
-   JSON格式地址1.0
-   m3u8流任務1.0
-   流任務AES-128解密（暫不支持SAMPLE-AES解密）1.0
-   帶有用戶自定義 1.0 的 HTTP cookie、標頭、用戶代理
-   種子種子限制 1.0
-   動態編輯傳輸任務配置 1.0
-   防螞蟥1.0
-   刷新過期地址 1.0
-   目錄 1.0
-   限制下載、上傳速度1.0
-   創建自定義地址(filec, fileu) 1.0
-   代理管理1.0
-   過濾器定制1.0
-   追踪器管理1.0
-   任務詳情 1.0
-   從任務 1.0 導出種子
-   多國語言1.0
-   隊列或無限並發設置 1.0
-   Chrome 瀏覽器集成 1.0
-   Firefox 瀏覽器集成 1.0
-   從網頁抓取視頻、音頻 1.0
-   從網頁 1.0 中查找所有磁鐵
-   翻譯工具 1.0
-   HTTP 工具 1.0
-   URI編碼/解碼工具1.0
-   Base64編解碼工具1.0
-   正則表達式測試工具 1.0
-   創建洪流 1.0
-   Torrent 轉磁力工具 1.0
-   磁力轉種子工具 1.0
-   文件合併工具1.0
-   統計 1.0
-   從網頁1.6下載所有鏈接
-   SSH、SFTP協議2.0
-   curl、wget、aria2、axel 命令行 2.0
-   WebDAV 協議 2.0
-   上傳文件 2.0
-   上傳目錄2.0
-   下載目錄2.0
-   全功能 WebDAV(s) 文件管理器 2.0
-   全功能 FTP(s) 文件管理器 2.0
-   全功能 SSH(sftp) 文件管理器 2.0
-   文件瀏覽器持久緩存 2.0
-   網站規則 2.1
-   校驗和工具 2.3
-   遠程下載2.6

## 源代碼

FileU 的完整源代碼可以在“source_code”目錄中找到。

僅供演示，項目中使用的依賴庫均未開源。

事實證明，在不降低性能的情況下，用 C++ 編寫用戶界面比用 HTML 和 JavaScript 編寫用戶界面要容易得多。

（如“UI”目錄中的 .sml 文件所示）。

## 翻譯

如果您喜歡這款軟件，您可以使用軟件中提供的翻譯工具將其翻譯成其他語言。

這將使使用軟件最初編寫語言以外的其他語言的人更容易訪問該軟件。非常感謝您的貢獻。

## 語言文件

-   網站：“lang/website/\*.lang”
-   軟件：“lang/software/\*.lang”
-   瀏覽器擴展：“lang/browser_extension/\*.lang”

#### 如何翻譯網站？

![translate](images/document/how_to_translate_this_website.png)

| 語言    | @                                                                                        |
| :---- | :--------------------------------------------------------------------------------------- |
| 俄語    | [@vanja-san](https://github.com/vanja-san)[@Den1704](https://github.com/Den1704)         |
| 繁體中文  | [@bear0316](https://github.com/bear0316)[@postman1year](https://github.com/postman1year) |
| 法語    | [@卡西克](https://github.com/XIAA25)                                                        |
| 荷蘭語   | [@卡西克](https://github.com/XIAA25)                                                        |
| 韓國人   | [@維納斯女孩](https://github.com/VenusGirl)                                                   |
| 越南語   | [@vuongtuha](https://github.com/vuongtuha)                                               |
| 土耳其   | [@geeeede](https://github.com/geeede)                                                    |
| 印度尼西亞 | [@gigglylo](https://github.com/gigglylo)                                                 |

## 開源庫

[促進](https://www.boost.org)[Qt](https://qt.io/)[libtorrent](https://www.libtorrent.org)
