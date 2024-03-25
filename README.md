[English](./README.md) | [简体中文](./README.zh-CN.md) | [繁體中文](./README.zh-TW.md) | [한국어](./README.ko.md) | [Hindi](./README.hi.md) | [Arabic](./README.ar.md) | [Français](./README.fr.md) | [Русский](./README.ru.md) | [Latin](./README.la.md) | [日本語](./README.ja.md)| [Italian](./README.it.md) | [Deutsch](./README.de.md) | [Español](./README.es.md) | [svenska](./README.sv.md) | [فارسی](./README.fa.md) | [Türkçe](./README.tr-TR.md)

![image](https://user-images.githubusercontent.com/100348948/165334090-0b1a6f28-554e-484b-9946-1ffef010fa78.png)
#

[![Join the chat at https://gitter.im/filecxx/FileCentipede](https://badges.gitter.im/filecxx/FileCentipede.svg)](https://gitter.im/filecxx/FileCentipede?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

<a href="http://filecxx.com" target="_blank">
  <img src="./style/images/logo_128.png" width="128" alt="File Centipede Icon" />
</a>


File centipede is an All-In-One internet file upload/download manager, BitTorrent Client, WebDAV client, FTP client, and SSH client.

It is designed to be fast, customizable, and user-friendly.

It supports multi-protocols and contains many useful auxiliary tools such as HTTP requester, file merge, and encoders.

With the browser integration, you can download audio and videos from websites, even encrypted videos.

(It's free with no ads)


Website: [http://filecxx.com](http://filecxx.com)

Dashboard: [https://w.filecxx.com](https://w.filecxx.com)

Sponsors: [http://www.filecxx.com/en_US/sponsors.html](http://www.filecxx.com/en_US/sponsors.html)

## Screenshot

#### File Centipede

![File Centipede](images/screenshot_software.png)
![File Centipede](images/screenshot_software2.png)
![File Centipede](images/screenshot_software_file_browser_webdav.png)
![File Centipede](images/screenshot_software_file_browser_ssh.png)
![File Centipede](images/screenshot_software_file_browser_ftp.png)
![File Centipede](images/screenshot_software_file_browser_add.png)
![File Centipede](images/screenshot_software_file_browser_log.png)

#### Add task

![Add task](images/screenshot_add_task.png)
![Add task](images/screenshot_add_task2.png)
![Add task](images/screenshot_add_task3.png)
![Add task](images/screenshot_add_task4.png)

#### Edit task

![Edit task](images/screenshot_edit_task.png)
![Edit task](images/screenshot_edit_task2.png)


#### Confirm dialog

![torrent confirm](images/screenshot_torrent_confirm.png)
![http confirm](images/screenshot_http_confirm.png)
![links confirm](images/screenshot_links_confirm.png)

#### Add catalog

![add catalog](images/screenshot_add_catalog.png)

#### Settings

![settings](images/screenshot_settings.png)

#### Proxy settings

![proxy](images/screenshot_proxy.png)

#### Site rules

![Site rules](images/screenshot_site_rule.png)
![Site rules](images/screenshot_site_rule2.png)

#### Filter

![filter](images/screenshot_filter.png)

#### Refresh address

![${refresh_address}](images/screenshot_refresh_address.png)

#### Create torrent

![create_torrent](images/screenshot_create_torrent.png)

#### Speed limit

![Speed limit](images/screenshot_download_speed_limit.png)

#### Translate tool

![Translate tool](images/screenshot_translate.png)

#### HTTP tool

![HTTP tool](images/screenshot_http_tool.png)

#### Checksum tool

![Checksum tool](images/screenshot_checksum_tool.png)

Browser extension screenshots
-----------------------------------

#### Video bar

![Video bar](images/extension_video_bar.png)

#### Videos panel

![videos panel](images/extension_videos.png)

#### Audios panel

![Audios panel](images/extension_audios.png)


## features
* HTTP,HTTPS protocol (basic features like gzip, resumable, multi-connections will not be listed.)	1.0
* FTP, FTPS protocol	1.0
* Magnet, HASH address	1.0
* BitTorrent	1.0
* Other custom protocol like thunder, flashget, qqdl	1.0
* JSON formatted address	1.0
* m3u8 stream task	1.0
* Stream task AES-128 decryption (SAMPLE-AES decryption is not supported yet)	1.0
* HTTP cookie, header, user-agent with user customize	1.0
* Torrent seeding limit	1.0
* Dynamically edit transfer-task config	1.0
* Anti leeches	1.0
* Refresh expired address	1.0
* Catalogs	1.0
* Limit download, upload speed	1.0
* Create custom address (filec, fileu)	1.0
* Proxy management	1.0
* Filter customize	1.0
* Tracker management	1.0
* Task details	1.0
* Export torrent from task	1.0
* Multi languages	1.0
* Queue or Unlimited concurrency setting	1.0
* Chrome Browser integration	1.0
* Firefox Browser integration	1.0
* Capture videos, audios from web page	1.0
* Find all magnets from web page	1.0
* Translate tool	1.0
* HTTP tool	1.0
* URI encode/decode tool	1.0
* Base64 encode/decode tool	1.0
* Regex test tool	1.0
* Create torrent	1.0
* Torrent to magnet tool	1.0
* Magnet to torrent tool	1.0
* File merge tool	1.0
* Statistics	1.0
* Download all links from webpage	1.6
* SSH, SFTP protocol	2.0
* curl, wget, aria2, axel command line	2.0
* WebDAV protocol	2.0
* Upload file	2.0
* Upload directory	2.0
* Download directory	2.0
* Full-featured WebDAV(s) file manager	2.0
* Full-featured FTP(s) file manager	2.0
* Full-featured SSH(sftp) file manager	2.0
* File browser persistent caches	2.0
* Site rules	2.1
* Checksum tool	2.3
* Remote download	2.6

## Source code

The full source code of FileU can be found in the "source_code" directory.

It's for demonstration purposes only, the dependent libraries used in the project are not open source.

It has proved that writing user interfaces in C++ could be significantly easier than HTML and JavaScript, without reducing performance.

(as seen in the .sml files in the "UI" directory).


## Translate
If you like this software, you can help by using the translation tool provided in the software to translate it into other languages.

This will make the software more accessible to people who speak languages other than the one it was originally written in. Your contribution would be greatly appreciated.


## Language files
* Website:  "lang/website/*.lang"
* Software: "lang/software/*.lang"
* Browser extension: "lang/browser_extension/*.lang"

#### How to translate the website?
![translate](images/document/how_to_translate_this_website.png)


| Language            |@|
|:--------------------|:-------------|
| Русский             | [@vanja-san](https://github.com/vanja-san) [@Den1704](https://github.com/Den1704)
| 繁體中文             | [@bear0316](https://github.com/bear0316) [@postman1year](https://github.com/postman1year)
| Français           | [@XIAA25](https://github.com/XIAA25)
| Nederlands         | [@XIAA25](https://github.com/XIAA25)
| 한국어         | [@VenusGirl](https://github.com/VenusGirl)
| Tiếng Việt | [@vuongtuha](https://github.com/vuongtuha)
| Türkçe     | [@geeede](https://github.com/geeede) [@saurane](https://github.com/saurane)
| Indonesian     | [@gigglylo](https://github.com/gigglylo) Rangga S. Nugraha
| Deutsch     | [@Vulcanraven91](https://github.com/Vulcanraven91)
| 日本語     | [@wany-oh](https://github.com/wany-oh)
| polski     | [@RunoHawk](https://github.com/RunoHawk)


## Opensource libraries
[boost](https://www.boost.org)
[Qt](https://qt.io/)
[libtorrent](https://www.libtorrent.org)
