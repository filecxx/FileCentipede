[engelsk](./README.md)\|[Förenklad kinesiska](./README.zh-CN.md)\|[traditionell kinesiska](./README.zh-TW.md)\|[koreanska](./README.ko.md)\|[Nej](./README.hi.md)\|[arabiska](./README.ar.md)\|[franska](./README.fr.md)\|[ryska](./README.ru.md)\|[latin](./README.la.md)\|[japanska](./README.ja.md)\|[italienska](./README.it.md)\|[tysk](./README.de.md)\|[spanska](./README.es.md)\|[svenska](./README.sv.md)

![image](https://user-images.githubusercontent.com/100348948/165334090-0b1a6f28-554e-484b-9946-1ffef010fa78.png)

# 

[![Join the chat at https://gitter.im/filecxx/FileCentipede](https://badges.gitter.im/filecxx/FileCentipede.svg)](https://gitter.im/filecxx/FileCentipede?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

<a href="http://filecxx.com" target="_blank">
  <img src="./style/images/logo_128.png" width="128" alt="File Centipede Icon" />
</a>

Fil tusenfoting är en allt-i-ett-hanterare för internetuppladdning/nedladdning, BitTorrent-klient, WebDAV-klient, FTP-klient och SSH-klient.

Den är designad för att vara snabb, anpassningsbar och användarvänlig.

Den stöder flera protokoll och innehåller många användbara hjälpverktyg som HTTP-begärare, filsammanfogning och kodare.

Med webbläsarintegrationen kan du ladda ner ljud och videor från webbplatser, till och med krypterade videor.

(Det är gratis utan annonser)

Hemsida:<http://filecxx.com>

Instrumentbräda:<https://w.filecxx.com>

Sponsorer:<http://www.filecxx.com/en_US/sponsors.html>

## Skärmdump

#### Arkiv tusenfoting

![File Centipede](images/screenshot_software.png)![File Centipede](images/screenshot_software2.png)![File Centipede](images/screenshot_software_file_browser_webdav.png)![File Centipede](images/screenshot_software_file_browser_ssh.png)![File Centipede](images/screenshot_software_file_browser_ftp.png)![File Centipede](images/screenshot_software_file_browser_add.png)![File Centipede](images/screenshot_software_file_browser_log.png)

#### Lägg till uppgift

![Add task](images/screenshot_add_task.png)![Add task](images/screenshot_add_task2.png)![Add task](images/screenshot_add_task3.png)![Add task](images/screenshot_add_task4.png)

#### Redigera uppgift

![Edit task](images/screenshot_edit_task.png)![Edit task](images/screenshot_edit_task2.png)

#### Bekräfta dialogrutan

![torrent confirm](images/screenshot_torrent_confirm.png)![http confirm](images/screenshot_http_confirm.png)![links confirm](images/screenshot_links_confirm.png)

#### Lägg till katalog

![add catalog](images/screenshot_add_catalog.png)

#### inställningar

![settings](images/screenshot_settings.png)

#### Proxyinställningar

![proxy](images/screenshot_proxy.png)

#### Webbplatsregler

![Site rules](images/screenshot_site_rule.png)![Site rules](images/screenshot_site_rule2.png)

#### Filtrera

![filter](images/screenshot_filter.png)

#### Uppdatera adress

![${refresh_address}](images/screenshot_refresh_address.png)

#### Skapa torrent

![create_torrent](images/screenshot_create_torrent.png)

#### Hastighetsbegränsning

![Speed limit](images/screenshot_download_speed_limit.png)

#### Översättningsverktyg

![Translate tool](images/screenshot_translate.png)

#### HTTP-verktyg

![HTTP tool](images/screenshot_http_tool.png)

#### Kontrollsumma verktyg

![Checksum tool](images/screenshot_checksum_tool.png)

## Skärmdumpar för webbläsartillägg

#### Video bar

![Video bar](images/extension_video_bar.png)

#### Videopanel

![videos panel](images/extension_videos.png)

#### Ljudpanel

![Audios panel](images/extension_audios.png)

## Funktioner

-   HTTP,HTTPS-protokoll (grundläggande funktioner som gzip, resumable, multi-connections kommer inte att listas.) 1.0
-   FTP, FTPS-protokoll 1.0
-   Magnet, HASH-adress 1.0
-   BitTorrent 1.0
-   Andra anpassade protokoll som thunder, flashget, qqdl 1.0
-   JSON-formaterad adress 1.0
-   m3u8 stream uppgift 1.0
-   Strömuppgift AES-128-dekryptering (SAMPLE-AES-dekryptering stöds inte ännu) 1.0
-   HTTP-cookie, rubrik, användaragent med användaranpassning 1.0
-   Torrent sådd gräns 1.0
-   Redigera dynamiskt transfer-task config 1.0
-   Anti iglar 1.0
-   Uppdatera utgången adress 1.0
-   Kataloger 1.0
-   Begränsa nedladdning, uppladdningshastighet 1.0
-   Skapa anpassad adress (filec, fileu) 1.0
-   Proxyhantering 1.0
-   Filter anpassa 1.0
-   Tracker management 1.0
-   Uppgiftsdetaljer 1.0
-   Exportera torrent från uppgift 1.0
-   Flerspråk 1.0
-   Inställning för kö eller obegränsad samtidighet 1.0
-   Chrome-webbläsarintegration 1.0
-   Firefox webbläsarintegration 1.0
-   Fånga videor, ljud från webbsida 1.0
-   Hitta alla magneter från webbsida 1.0
-   Översättningsverktyg 1.0
-   HTTP-verktyg 1.0
-   URI-kodnings-/avkodningsverktyg 1.0
-   Base64 koda/avkoda verktyg 1.0
-   Regex testverktyg 1.0
-   Skapa torrent 1.0
-   Torrent till magnetverktyg 1.0
-   Magnet till torrent-verktyg 1.0
-   Filsammanfogningsverktyg 1.0
-   Statistik 1.0
-   Ladda ner alla länkar från webbsida 1.6
-   SSH, SFTP-protokoll 2.0
-   curl, wget, aria2, axel kommandorad 2.0
-   WebDAV-protokoll 2.0
-   Ladda upp fil 2.0
-   Ladda upp katalog 2.0
-   Ladda ner katalog 2.0
-   Fullständig WebDAV(s) filhanterare 2.0
-   Fullständig FTP(er) filhanterare 2.0
-   Fullständig SSH(sftp) filhanterare 2.0
-   Filläsares beständiga cacheminne 2.0
-   Webbplatsregler 2.1
-   Kontrollsummaverktyg 2.3
-   Fjärrnedladdning 2.6

## Källkod

Den fullständiga källkoden för FileU finns i katalogen "source_code".

Det är endast för demonstrationsändamål, de beroende biblioteken som används i projektet är inte öppen källkod.

It has proved that writing user interfaces in C++ could be significantly easier than HTML and JavaScript, without reducing performance.

(som ses i .sml-filerna i "UI"-katalogen).

## Översätt

Om du gillar den här programvaran kan du hjälpa till genom att använda översättningsverktyget i programvaran för att översätta den till andra språk.

Detta kommer att göra programvaran mer tillgänglig för personer som talar andra språk än det den ursprungligen skrevs i. Ditt bidrag skulle uppskattas mycket.

## Språkfiler

-   Webbplats: "lang/website/\*.lang"
-   Programvara: "lang/software/\*.lang"
-   Webbläsartillägg: "lang/browser_extension/\*.lang"

#### Hur översätter man webbplatsen?

![translate](images/document/how_to_translate_this_website.png)

| Språk                  | @                                                                                       |
| :--------------------- | :-------------------------------------------------------------------------------------- |
| ryska                  | [@vanja-san](https://github.com/vanja-san)[@Den1704](https://github.com/Den1704)        |
| traditionell kinesiska | [@björn0316](https://github.com/bear0316)[@postman1år](https://github.com/postman1year) |
| franska                | [@kasikh](https://github.com/XIAA25)                                                    |
| holländska             | [@kasikh](https://github.com/XIAA25)                                                    |
| koreanska              | [@VenusGirl](https://github.com/VenusGirl)                                              |
| vietnamesiska          | [@vuongtuha](https://github.com/vuongtuha)                                              |
| turkiska               | [@geeede](https://github.com/geeede)                                                    |
| indonesiska            | [@gigglylo](https://github.com/gigglylo)                                                |

## Bibliotek med öppen källkod

[lyft](https://www.boost.org)[Qt](https://qt.io/)[libtorrent](https://www.libtorrent.org)
