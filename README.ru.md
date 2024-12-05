[Английский](./README.md)\|[Упрощенный китайский](./README.zh-CN.md)\|[традиционный китайский](./README.zh-TW.md)\|[Корейский](./README.ko.md)\|[Неа](./README.hi.md)\|[арабский](./README.ar.md)\|[Французский](./README.fr.md)\|[Русский](./README.ru.md)\|[латинский](./README.la.md)\|[Японский](./README.ja.md)\|[итальянский](./README.it.md)\|[Немецкий](./README.de.md)\|[испанский](./README.es.md)\|[Шведский](./README.sv.md)\|[фарси](./README.fa.md)\|[турецкий](./README.tr-TR.md)

![image](https://user-images.githubusercontent.com/100348948/165334090-0b1a6f28-554e-484b-9946-1ffef010fa78.png)

# 

[![Join the chat at https://gitter.im/filecxx/FileCentipede](https://badges.gitter.im/filecxx/FileCentipede.svg)](https://gitter.im/filecxx/FileCentipede?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

<a href="http://filecxx.com" target="_blank">
  <img src="./style/images/logo_128.png" width="128" alt="File Centipede Icon" />
</a>

File centipede — это универсальный менеджер загрузки/выгрузки файлов в Интернете, BitTorrent-клиент, клиент WebDAV, FTP-клиент и SSH-клиент.

Он разработан, чтобы быть быстрым, настраиваемым и удобным для пользователя.

Он поддерживает несколько протоколов и содержит множество полезных вспомогательных инструментов, таких как HTTP-реквестер, слияние файлов и кодировщики.

Благодаря интеграции с браузером вы можете загружать аудио и видео с веб-сайтов, даже зашифрованные видео.

(Это бесплатно, без рекламы)

Веб-сайт:[хттп://филеккс.ком](http://filecxx.com)

Панель приборов:[хттпс://в.филеккс.ком](https://w.filecxx.com)

Спонсоры:[хттп://ввв.филеккс.ком/ен\_УС/спонсорс.хтмл](http://www.filecxx.com/en_US/sponsors.html)

## Скриншот

#### Файловая многоножка

![File Centipede](images/screenshot_software.png)![File Centipede](images/screenshot_software2.png)![File Centipede](images/screenshot_software_file_browser_webdav.png)![File Centipede](images/screenshot_software_file_browser_ssh.png)![File Centipede](images/screenshot_software_file_browser_ftp.png)![File Centipede](images/screenshot_software_file_browser_add.png)![File Centipede](images/screenshot_software_file_browser_log.png)

#### Добавить задачу

![Add task](images/screenshot_add_task.png)![Add task](images/screenshot_add_task2.png)![Add task](images/screenshot_add_task3.png)![Add task](images/screenshot_add_task4.png)

#### Изменить задачу

![Edit task](images/screenshot_edit_task.png)![Edit task](images/screenshot_edit_task2.png)

#### Диалоговое окно подтверждения

![torrent confirm](images/screenshot_torrent_confirm.png)![http confirm](images/screenshot_http_confirm.png)![links confirm](images/screenshot_links_confirm.png)

#### Добавить каталог

![add catalog](images/screenshot_add_catalog.png)

#### Настройки

![settings](images/screenshot_settings.png)

#### Настройки прокси

![proxy](images/screenshot_proxy.png)

#### Правила сайта

![Site rules](images/screenshot_site_rule.png)![Site rules](images/screenshot_site_rule2.png)

#### Фильтр

![filter](images/screenshot_filter.png)

#### Обновить адрес

![${refresh_address}](images/screenshot_refresh_address.png)

#### Создать торрент

![create_torrent](images/screenshot_create_torrent.png)

#### Ограничение скорости

![Speed limit](images/screenshot_download_speed_limit.png)

#### Инструмент перевода

![Translate tool](images/screenshot_translate.png)

#### HTTP-инструмент

![HTTP tool](images/screenshot_http_tool.png)

#### Инструмент контрольной суммы

![Checksum tool](images/screenshot_checksum_tool.png)

## Скриншоты расширения для браузера

#### Видеобар


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

## функции

-   Протокол HTTP, HTTPS (базовые функции, такие как gzip, возобновление, множественные соединения, не будут перечислены.) 1.0
-   FTP, протокол FTPS 1.0
-   Магнит, HASH-адрес 1.0
-   БитТоррент 1.0
-   Другие пользовательские протоколы, такие как Thunder, flashget, qqdl 1.0.
-   Адрес в формате JSON 1.0
-   Потоковая задача m3u8 1.0
-   Расшифровка потоковой задачи AES-128 (расшифровка SAMPLE-AES пока не поддерживается) 1.0
-   HTTP cookie, заголовок, пользовательский агент с пользовательской настройкой 1.0
-   Лимит раздачи торрентов 1.0
-   Динамическое редактирование конфигурации задачи передачи 1.0
-   Анти пиявки 1.0
-   Обновить просроченный адрес 1.0
-   Каталоги 1.0
-   Ограничить загрузку, скорость отдачи 1.0
-   Создать собственный адрес (filec, fileu) 1.0
-   Управление прокси 1.0
-   Настройка фильтра 1.0
-   Управление трекером 1.0
-   Детали задачи 1.0
-   Экспортировать торрент из задачи 1.0
-   Мультиязычность 1.0
-   Настройка очереди или неограниченного параллелизма 1.0
-   Интеграция браузера Chrome 1.0
-   Интеграция браузера Firefox 1.0
-   Захват видео и аудио с веб-страницы 1.0.
-   Найдите все магниты на веб-странице 1.0.
-   Инструмент перевода 1.0
-   HTTP-инструмент 1.0
-   Инструмент кодирования/декодирования URI 1.0
-   Инструмент кодирования/декодирования Base64 1.0
-   Инструмент тестирования регулярных выражений 1.0
-   Создать торрент 1.0
-   Инструмент Torrent to Magnetic 1.0
-   Магнит для торрент-инструмента 1.0
-   Инструмент слияния файлов 1.0
-   Статистика 1.0
-   Скачать все ссылки с веб-страницы 1.6.
-   SSH, протокол SFTP 2.0
-   Curl, wget, aria2, командная строка axel 2.0
-   Протокол WebDAV 2.0
-   Загрузить файл 2.0
-   Загрузить каталог 2.0
-   Каталог загрузки 2.0
-   Полнофункциональный файловый менеджер WebDAV(s) 2.0.
-   Полнофункциональный файловый менеджер FTP(ов) 2.0
-   Полнофункциональный файловый менеджер SSH(sftp) 2.0.
-   Постоянные кэши файлового браузера 2.0
-   Правила сайта 2.1
-   Инструмент контрольной суммы 2.3
-   Удаленная загрузка 2.6

## Исходный код

Полный исходный код FileU можно найти в каталоге «source_code».

Это только для демонстрационных целей, зависимые библиотеки, используемые в проекте, не имеют открытого исходного кода.

Было доказано, что написание пользовательских интерфейсов на C++ может быть значительно проще, чем на HTML и JavaScript, без снижения производительности.

(как показано в файлах .sml в каталоге «UI»).

## Переводить

Если вам нравится это программное обеспечение, вы можете помочь, используя инструмент перевода, входящий в состав программного обеспечения, для перевода его на другие языки.

Это сделает программное обеспечение более доступным для людей, говорящих на языках, отличных от того, на котором оно было изначально написано. Ваш вклад будет очень признателен.

## Языковые файлы

-   Веб-сайт: "lang/website/\*.lang"
-   Программное обеспечение: "lang/software/\*.lang"
-   Расширение браузера: «lang/browser_extension/\*.lang»

#### Как перевести сайт?

![translate](images/document/how_to_translate_this_website.png)

| Язык                   | @                                                                                        |
| :--------------------- | :--------------------------------------------------------------------------------------- |
| Русский                | [@ванья-сан](https://github.com/vanja-san)[@Den1704](https://github.com/Den1704)         |
| традиционный китайский | [@bear0316](https://github.com/bear0316)[@postman1year](https://github.com/postman1year) |
| Французский            | [@Ксахих](https://github.com/XIAA25)                                                     |
| Голландский            | [@Ксахих](https://github.com/XIAA25)                                                     |
| Корейский              | [@VenusGirl](https://github.com/VenusGirl)                                               |
| вьетнамский            | [@vuongtuha](https://github.com/vuongtuha)                                               |
| турецкий               | [@geeeede](https://github.com/geeede)[@saurane](https://github.com/saurane)              |
| индонезийский          | [@gigglylo](https://github.com/gigglylo)                                                 |
| Немецкий               | [@Vulcanraven91](https://github.com/Vulcanraven91)                                       |
| Японский               | [@wany-ох](https://github.com/wany-oh)                                                   |
| Польский               | [@RunoHawk](https://github.com/RunoHawk)                                                 |

## Библиотеки с открытым исходным кодом

[способствовать росту](https://www.boost.org)[Qt](https://qt.io/)[libtorrent](https://www.libtorrent.org)
