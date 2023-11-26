[English](./README.md) | [简体中文](./README.zh-CN.md) | [繁體中文](./README.zh-TW.md) | [한국어](./README.ko.md) | [Hindi](./README.hi.md) | [Arabic](./README.ar.md) | [Français](./README.fr.md) | [Русский](./README.ru.md) | [Latin](./README.la.md) | [日本語](./README.ja.md)| [Italian](./README.it.md) | [Deutsch](./README.de.md) | [Español](./README.es.md) | [svenska](./README.sv.md) | [فارسی](./README.fa.md)) | [Türkçe](./README.tr-TR.md)

![image](https://user-images.githubusercontent.com/100348948/165334090-0b1a6f28-554e-484b-9946-1ffef010fa78.png)
#

[![Join the chat at https://gitter.im/filecxx/FileCentipede](https://badges.gitter.im/filecxx/FileCentipede.svg)](https://gitter.im/filecxx/FileCentipede?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

<a href="http://filecxx.com" target="_blank">
  <img src="./style/images/logo_128.png" width="128" alt="File Centipede Icon" />
</a>


File centipede, hepsi bir arada bulunan bir internet dosya yükleme/indirme yöneticisi, BitTorrent, WebDAV, FTP ve SSH istemcisidir.

Hızlı, özelleştirilebilir ve kullanıcı dostu olacak şekilde tasarlanmıştır.

Çoklu protokolleri destekler ve HTTP istekçi, dosya birleştirme ve şifreleme/şifre çözme gibi birçok yararlı yardımcı araç içerir.

Tarayıcı desteği ile web sitelerinden ses ve video, hatta şifrelenmiş videoları bile indirebilirsiniz.

(Reklamsız ve ücretsiz)


Web site: [http://filecxx.com](http://filecxx.com)

Ana sayfa: [https://w.filecxx.com](https://w.filecxx.com)

Sponsorlar: [http://www.filecxx.com/en_US/sponsors.html](http://www.filecxx.com/en_US/sponsors.html)

## Ekran görüntüsü

#### File Centipede

![File Centipede](images/screenshot_software.png)
![File Centipede](images/screenshot_software2.png)
![File Centipede](images/screenshot_software_file_browser_webdav.png)
![File Centipede](images/screenshot_software_file_browser_ssh.png)
![File Centipede](images/screenshot_software_file_browser_ftp.png)
![File Centipede](images/screenshot_software_file_browser_add.png)
![File Centipede](images/screenshot_software_file_browser_log.png)

#### Görev ekleme

![Add task](images/screenshot_add_task.png)
![Add task](images/screenshot_add_task2.png)
![Add task](images/screenshot_add_task3.png)
![Add task](images/screenshot_add_task4.png)

#### Görev düzenleme

![Edit task](images/screenshot_edit_task.png)
![Edit task](images/screenshot_edit_task2.png)


#### İletişim kutusu onayı

![torrent confirm](images/screenshot_torrent_confirm.png)
![http confirm](images/screenshot_http_confirm.png)
![links confirm](images/screenshot_links_confirm.png)

#### Katalog ekleme

![add catalog](images/screenshot_add_catalog.png)

#### Ayarlar

![settings](images/screenshot_settings.png)

#### Proxy ayarları

![proxy](images/screenshot_proxy.png)

#### Site kuralları

![Site rules](images/screenshot_site_rule.png)
![Site rules](images/screenshot_site_rule2.png)

#### Filtre

![filter](images/screenshot_filter.png)

#### Adres yenileme

![${refresh_address}](images/screenshot_refresh_address.png)

#### Torrent oluşturma

![create_torrent](images/screenshot_create_torrent.png)

#### Hız sınırlama

![Speed limit](images/screenshot_download_speed_limit.png)

#### Çeviri aracı

![Translate tool](images/screenshot_translate.png)

#### HTTP aracı

![HTTP tool](images/screenshot_http_tool.png)

#### Sağlama aracı

![Checksum tool](images/screenshot_checksum_tool.png)

Tarayıcı uzantısının ekran görüntüleri
-----------------------------------

#### Video çubuğu

![Video bar](images/extension_video_bar.png)

#### Video paneli

![videos panel](images/extension_videos.png)

#### Ses paneli

![Audios panel](images/extension_audios.png)


## özellikler
* HTTP, HTTPS protokolü (gzip, devam ettirilebilir, çoklu bağlantılar gibi temel özellikler listelenmeyecektir).	1.0
* FTP, FTPS protokolü	1.0
* Mıknatıs, HASH adresi	1.0
* BitTorrent	1.0
* Thunder, flashget, qqdl gibi diğer özel protokoller	1.0
* JSON biçimli adres	1.0
* m3u8 akış görevi	1.0
* Akış görevi AES-128 şifre çözme (SAMPLE-AES şifre çözme henüz desteklenmiyor)	1.0
* HTTP çerezi, üst bilgi, kullanıcı özelleştirmeli user-agent aracı	1.0
* Torrent gönderim sınırlayıcı	1.0
* İndirme görevi yapılandırmasını dinamik olarak düzenleyici	1.0
* Gönderim önleyici	1.0
* Süresi dolan adresi yenileyici	1.0
* Kataloglar	1.0
* İndirme ve gönderme hızını sınırlayıcı	1.0
* Özel adres oluşturucu (filec, fileu)	1.0
* Proxy yönetici	1.0
* Filtre özelleştirici	1.0
* İzleyici yönetimi	1.0
* Görev ayrıntıları	1.0
* Torrent'i görevden dışa aktarma	1.0
* Çoklu dil	1.0
* Kuyruk veya sınırsız eş zamanlılık ayarı	1.0
* Chrome tarayıcı desteği	1.0
* Firefox tarayıcı desteği	1.0
* Web sayfasından video, ses yakalama	1.0
* Web sayfasından tüm mıknatısları bulma	1.0
* Çeviri aracı	1.0
* HTTP aracı	1.0
* URI şifreleme/şifre çözme aracı	1.0
* Base64 şifreleme/şifre çözme aracı	1.0
* Regex deneme aracı	1.0
* Torrent oluşturucu	1.0
* Torrentten mıknatısa dönüştürme aracı	1.0
* Mıknatıstan torrente dönüştürme aracı	1.0
* Dosya birleştirme aracı	1.0
* İstatistikler	1.0
* Web sayfasındaki tüm bağlantıları indirici	1.6
* SSH, SFTP protokolü	2.0
* curl, wget, aria2, axel komut satırı	2.0
* WebDAV protokolü	2.0
* Dosya gönderici	2.0
* Dizin gönderici	2.0
* Dizin indirici	2.0
* Tam özellikli WebDAV dosya yöneticisi	2.0
* Tam özellikli FTP dosya yöneticisi	2.0
* Tam özellikli SSH(sftp) dosya yöneticisi	2.0
* Dosya tarayıcısının kalıcı önbellek özelliği	2.0
* Site kuralları	2.1
* Sağlama aracı	2.3
* Uzaktan indirici	2.6

## Kaynak kodu

FileU yazılımının tam kaynak kodu "source_code" dizininde bulunur.

Sadece tanıtım amaçlıdır, projede kullanılan bağımlı kütüphaneler açık kaynak değildir.

C++ dilinde kullanıcı arayüzü yazmanın, performansı düşürmeden HTML ve JavaScript dilinden büyük oranda daha kolay olabileceğini kanıtlamıştır.

("UI" dizinindeki .sml dosyalarında görüldüğü üzere).


## Çeviri
Bu yazılımı beğendiyseniz, diğer dillere çevirmek için yazılımda bulunan çeviri aracını kullanarak yardımcı olabilirsiniz.

Bu, yazılımın orijinal olarak yazıldığı dilden farklı dilleri konuşan kişiler için daha erişilebilir olmasını sağlayacaktır. Katkınız büyük ölçüde takdir edilecektir.


## Dil dosyaları
* Web site:  "lang/website/*.lang"
* Yazılım: "lang/software/*.lang"
* Tarayıcı uzantısı: "lang/browser_extension/*.lang"

#### Web sitesi nasıl çevrilir?
![translate](images/document/how_to_translate_this_website.png)


| Dil            |@|
|:--------------------|:-------------|
| Русский             | [@vanja-san](https://github.com/vanja-san) [@Den1704](https://github.com/Den1704)
| 繁體中文             | [@bear0316](https://github.com/bear0316) [@postman1year](https://github.com/postman1year)
| Français           | [@XIAA25](https://github.com/XIAA25)
| Nederlands         | [@XIAA25](https://github.com/XIAA25)
| 한국어         | [@VenusGirl](https://github.com/VenusGirl)
| Tiếng Việt | [@vuongtuha](https://github.com/vuongtuha)
| Türkçe     | [@saurane](https://github.com/saurane)
| Indonesian     | [@gigglylo](https://github.com/gigglylo)
| Deutsch     | [@Vulcanraven91](https://github.com/Vulcanraven91)
| 日本語     | [@wany-oh](https://github.com/wany-oh)
| polski     | [@RunoHawk](https://github.com/RunoHawk)


## Açık kaynak kütüphaneler
[boost](https://www.boost.org)
[Qt](https://qt.io/)
[libtorrent](https://www.libtorrent.org)
