[英語](./README.md)\|[簡體中文](./README.zh-CN.md)\|[繁體中文](./README.zh-TW.md)\|[韓國語](./README.ko.md)\|[印度](./README.hi.md)\|[阿拉伯](./README.ar.md)\|[法語](./README.fr.md)\|[俄文](./README.ru.md)\|[拉丁](./README.la.md)\|[日本語](./README.ja.md)\|[義大利語](./README.it.md)\|[德文](./README.de.md)\|[西班牙語](./README.es.md)\|[瑞典](./README.sv.md)\|[波斯語](./README.fa.md)\|[土耳其](./README.tr-TR.md)

![image](https://user-images.githubusercontent.com/100348948/165334090-0b1a6f28-554e-484b-9946-1ffef010fa78.png)

# 

[![Join the chat at https://gitter.im/filecxx/FileCentipede](https://badges.gitter.im/filecxx/FileCentipede.svg)](https://gitter.im/filecxx/FileCentipede?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

<a href="http://filecxx.com" target="_blank">
  <img src="./style/images/logo_128.png" width="128" alt="File Centipede Icon" />
</a>

File centipede 是一款一體化網際網路檔案上傳/下載管理器、BitTorrent 用戶端、WebDAV 用戶端、FTP 用戶端和 SSH 用戶端。

它被設計為快速、可自訂且使用者友善。

它支援多協議，並包含許多有用的輔助工具，例如 HTTP 請求器、文件合併和編碼器。

透過瀏覽器整合，您可以從網站下載音訊和影片，甚至加密的影片。

（免費且無廣告）

網站：<http://filecxx.com>

儀表板：<https://w.filecxx.com>

贊助商：<http://www.filecxx.com/en_US/sponsors.html>

## 螢幕截圖

#### File Centipede

![File Centipede](images/screenshot_software.png)![File Centipede](images/screenshot_software2.png)![File Centipede](images/screenshot_software_file_browser_webdav.png)![File Centipede](images/screenshot_software_file_browser_ssh.png)![File Centipede](images/screenshot_software_file_browser_ftp.png)![File Centipede](images/screenshot_software_file_browser_add.png)![File Centipede](images/screenshot_software_file_browser_log.png)

#### 新增任務

![Add task](images/screenshot_add_task.png)![Add task](images/screenshot_add_task2.png)![Add task](images/screenshot_add_task3.png)![Add task](images/screenshot_add_task4.png)

#### 編輯任務

![Edit task](images/screenshot_edit_task.png)![Edit task](images/screenshot_edit_task2.png)

#### 確認對話框

![torrent confirm](images/screenshot_torrent_confirm.png)![http confirm](images/screenshot_http_confirm.png)![links confirm](images/screenshot_links_confirm.png)

#### 新增目錄

![add catalog](images/screenshot_add_catalog.png)

#### 設定

![settings](images/screenshot_settings.png)

#### 代理設定

![proxy](images/screenshot_proxy.png)

#### 網站規則

![Site rules](images/screenshot_site_rule.png)![Site rules](images/screenshot_site_rule2.png)

#### 篩選

![filter](images/screenshot_filter.png)

#### 重新整理地址

![${refresh_address}](images/screenshot_refresh_address.png)

#### 建立種子

![create_torrent](images/screenshot_create_torrent.png)

#### 速度極限

![Speed limit](images/screenshot_download_speed_limit.png)

#### 翻譯工具

![Translate tool](images/screenshot_translate.png)

#### HTTP 工具

![HTTP tool](images/screenshot_http_tool.png)

#### 校驗和工具

![Checksum tool](images/screenshot_checksum_tool.png)

## 瀏覽器擴充截圖


#### Video bar

![Video bar](images/extension_video_bar.png)

#### Videos panel

![videos panel](images/extension_videos.png)

#### Audios panel

![Audios panel](images/extension_audios.png)

#### Custom files panel

![Custom files panel](images/extension_popup_custom.png)

#### Resource explorer - images

![Resource explorer - images](images/extension_res_explorer_images.png)


#### Resource explorer - scripts

![Resource explorer - scripts](images/extension_res_explorer_scripts.png)

#### Videos preview

![Videos preview](images/extension_preview.png)


#### Videos collector

![Videos collector](images/extension_collector_videos.png)


#### Audios collector

![Audios collector](images/extension_collector_audios.png)

#### Settings

![Settings](images/extension_settings.png)

## 功能特色

-   HTTP、HTTPS 通訊協定（不列出基本功能如 gzip、可續傳、多重連線等）1.0
-   FTP、FTPS 通訊協定 1.0
-   Magnet、HASH 位址 1.0
-   BitTorrent 1.0
-   其他自訂通訊協定如迅雷、快車、QQ 下載 1.0
-   JSON 格式位址 1.0
-   m3u8 串流任務 1.0
-   串流任務 AES-128 解密（尚未支援 SAMPLE-AES 解密）1.0
-   HTTP Cookie、標頭、使用者代理程式可自訂 1.0
-   Torrent 做種限制 1.0
-   動態編輯傳輸任務設定 1.0
-   防止吸血蟲 1.0
-   更新過期位址 1.0
-   分類目錄 1.0
-   限制下載、上傳速度 1.0
-   建立自訂位址（filec、fileu）1.0
-   Proxy 管理 1.0
-   自訂篩選器 1.0
-   Tracker 管理 1.0
-   任務詳細資訊 1.0
-   從任務匯出 Torrent 1.0
-   多國語言 1.0
-   佇列或無限併發設定 1.0
-   Chrome 瀏覽器整合 1.0
-   Firefox 瀏覽器整合 1.0
-   從網頁擷取影音 1.0
-   從網頁尋找所有磁力連結 1.0
-   翻譯工具 1.0
-   HTTP 工具 1.0
-   URI 編碼/解碼工具 1.0
-   Base64 編碼/解碼工具 1.0
-   正規表示式測試工具 1.0
-   建立 Torrent 1.0
-   Torrent 轉磁力連結工具 1.0
-   磁力連結轉 Torrent 工具 1.0
-   檔案合併工具 1.0
-   統計資料 1.0
-   下載網頁所有連結 1.6
-   SSH、SFTP 通訊協定 2.0
-   curl、wget、aria2、axel 命令列 2.0
-   WebDAV 通訊協定 2.0
-   上傳檔案 2.0
-   上傳資料夾 2.0
-   下載資料夾 2.0
-   完整功能 WebDAV(s) 檔案管理器 2.0
-   完整功能 FTP(s) 檔案管理器 2.0
-   完整功能 SSH(sftp) 檔案管理器 2.0
-   檔案瀏覽器持續性快取 2.0
-   網站規則 2.1
-   校驗工具 2.3
-   遠端下載 2.6

## 原始碼

FileU 的完整原始碼可在「source_code」目錄中找到。

此為展示用途，專案中使用的相依程式庫並非開放原始碼。

這證明了使用 C++ 撰寫使用者介面可以比 HTML 和 JavaScript 容易許多，而且不會降低效能。

（如「UI」目錄中的 .sml 檔案所示）。

## 翻譯

如果您喜歡這個軟體，您可以使用軟體提供的翻譯工具協助將其翻譯成其他語言。

這將使軟體更容易被使用其他語言的人使用。我們非常感謝您的貢獻。

## 語言檔案

-   網址：“lang/website/\*.lang”
-   軟體：“lang/software/\*.lang”
-   瀏覽器擴充套件：“lang/browser_extension/\*.lang”

#### 如何翻譯網站？

![translate](images/document/how_to_translate_this_website.png)

| 語言   | @                                                                                     |
| :--- | :------------------------------------------------------------------------------------ |
| 俄文   | [@vanja-san](https://github.com/vanja-san)[@Den1704](https://github.com/Den1704)      |
| 繁體中文 | [@熊0316](https://github.com/bear0316)[@postman1year](https://github.com/postman1year) |
| 法語   | [@Ksahikh](https://github.com/XIAA25)                                                 |
| 荷蘭語  | [@Ksahikh](https://github.com/XIAA25)                                                 |
| 韓國語  | [@維納斯女孩](https://github.com/VenusGirl)                                                |
| 越南語  | [@vuongtuha](https://github.com/vuongtuha)                                            |
| 土耳其  | [@geeeede](https://github.com/geeede)[@saurane](https://github.com/saurane)           |
| 印尼   | [@吉格利洛](https://github.com/gigglylo)                                                  |
| 德文   | [@Vulcanraven91](https://github.com/Vulcanraven91)                                    |
| 日本語  | [@wany-哦](https://github.com/wany-oh)                                                 |
| 波蘭語   | [@魯諾霍克](https://github.com/RunoHawk)                                                  |

## 開源函式庫

[Boost](https://www.boost.org)
[Qt](https://qt.io/)
[libtorrent](https://www.libtorrent.org)
