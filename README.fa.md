[انگلیسی](./README.md) | [چینی ساده شده](./README.zh-CN.md) | [چینی سنتی](./README.zh-TW.md) | [کره‌ای](./README.ko.md) | [هندی](./README.hi.md) | [عربی](./README.ar.md) | [فرانسوی](./README.fr.md) | [روسی](./README.ru.md) | [لاتین](./README.la.md) | [ژاپنی](./README.ja.md) | [ایتالیایی](./README.it.md) | [آلمانی](./README.de.md) | [اسپانیولی](./README.es.md) | [سوئدی](./README.sv.md) | [فارسی](./README.fa.md)

![image](https://user-images.githubusercontent.com/100348948/165334090-0b1a6f28-554e-484b-9946-1ffef010fa78.png)
#

[![Join the chat at https://gitter.im/filecxx/FileCentipede](https://badges.gitter.im/filecxx/FileCentipede.svg)](https://gitter.im/filecxx/FileCentipede?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

<a href="http://filecxx.com" target="_blank">
  <img src="./style/images/logo_128.png" width="128" alt="File Centipede Icon" />
</a>



 این یک برنامه مدیریت دانلود/ آپلود همه کاره است که  کلاینت های BitTorrent و WebDAV و FTP و SSH را در اختیار شما قرار میدهد.
 
 این برنامه به گونه‌ای طراحی شده است که سریع، قابل شخصی سازی و کاربرپسند باشد.


این برنامه نه تنها از پروتکل های مخلتف پشتیبانی میکند بلکه بسیاری ابزار کاربردی دیگر مانند HTTP requester و به هم چسباندن فایل ها و انکودر و دیکودر در اختیار شما قرار میدهد.

با استفاده از افزونه‌ی مرورگر این برنامه می‌توانید فایل صوتی و ویدیویی و حتی ویدیوهای رمز گذاری شده را از پخش آنلاین وبسایت‌ها دانلود کنید.

(این برنامه کاملا رایگان است و هیچ تبلیغی  ندارد)

وب سایت برنامه: [http://filecxx.com](http://filecxx.com)

داشبورد: [https://w.filecxx.com](https://w.filecxx.com)


لیست حامی‌های مالی: [http://www.filecxx.com/en_US/sponsors.html](http://www.filecxx.com/en_US/sponsors.html)


## تصاویر محیط برنامه


#### File Centipede

![File Centipede](images/screenshot_software.png)
![File Centipede](images/screenshot_software2.png)
![File Centipede](images/screenshot_software_file_browser_webdav.png)
![File Centipede](images/screenshot_software_file_browser_ssh.png)
![File Centipede](images/screenshot_software_file_browser_ftp.png)
![File Centipede](images/screenshot_software_file_browser_add.png)
![File Centipede](images/screenshot_software_file_browser_log.png)


#### اضافه کردن ماموریت

![Add task](images/screenshot_add_task.png)
![Add task](images/screenshot_add_task2.png)
![Add task](images/screenshot_add_task3.png)
![Add task](images/screenshot_add_task4.png)


#### تنظیم ماموریت

![Edit task](images/screenshot_edit_task.png)
![Edit task](images/screenshot_edit_task2.png)


#### تاییدیه قبل اجرا

![torrent confirm](images/screenshot_torrent_confirm.png)
![http confirm](images/screenshot_http_confirm.png)
![links confirm](images/screenshot_links_confirm.png)


#### اضافه کردن کاتالوگ

![add catalog](images/screenshot_add_catalog.png)


#### تنظیمات برنامه

![settings](images/screenshot_settings.png)


#### تنظیمات پراکسی

![proxy](images/screenshot_proxy.png)


#### تنظیمات رول برای سایت ها

![Site rules](images/screenshot_site_rule.png)
![Site rules](images/screenshot_site_rule2.png)


#### اعمال فیلتر

![filter](images/screenshot_filter.png)


#### تازه سازی آدرس

![${refresh_address}](images/screenshot_refresh_address.png)


#### ساخت تورنت

![create_torrent](images/screenshot_create_torrent.png)


#### محدودیت سرعت

![Speed limit](images/screenshot_download_speed_limit.png)


#### ابزار ترجمه

![Translate tool](images/screenshot_translate.png)


#### HTTP ابزار

![HTTP tool](images/screenshot_http_tool.png)


#### Checksum ابزار

![Checksum tool](images/screenshot_checksum_tool.png)

تصاویر افزونه‌ی مرورگر برنامه
-----------------------------------


#### نوار ویدیو

![Video bar](images/extension_video_bar.png)


#### پنل ویدیو

![videos panel](images/extension_videos.png)


#### پنل فایل صوتی

![Audios panel](images/extension_audios.png)


## قابلیت‌ها

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


## کد منبع

کد منبع کامل FileU را میتوانید در مسیر "source_code" پیدا کنید.

این برنامه تنها برای نمونه و اهداف آزمایشی طراحی شده است وگرنه کتابخانه‌های مورد استفاده در برنامه منبع باز نیستند.

ثابت شده است که نوشتن رابط های کاربری در ++C می تواند به طور قابل توجهی ساده تر از HTML و جاوا اسکریپت باشد، بدون اینکه کارایی کاهش یابد.

(همانطور که در فایل های .sml در دایرکتوری "UI" مشاهده می شود).


## ترجمه 

اگر این نرم افزار مورد پسند شما واقع شد، می توانید با استفاده از ابزار ترجمه ارائه شده در نرم افزار به ترجمه آن به زبان های دیگر کمک کنید.

این امر باعث می شود که نرم افزار برای افرادی که به زبان هایی غیر از زبانی که در ابتدا به آن نوشته شده صحبت می کنند قابل دسترس تر باشد. کمک شما  مورد قدردانی ما خواهد بود.


## فایل های زبان

* وبسایت:  "lang/website/*.lang"
* نرم افزار: "lang/software/*.lang"
* افزونه‌ی مرورگر: "lang/browser_extension/*.lang"


#### چگونه وبسایت را ترجمه کنیم؟

![translate](images/document/how_to_translate_this_website.png)


| زبان            |مشارکت‌کنندگان|
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
| فارسی     | [@bananbenbadr](https://github.com/bananbenbadr)


## کتابخانه‌های منبع باز
[boost](https://www.boost.org)
[Qt](https://qt.io/)
[libtorrent](https://www.libtorrent.org)