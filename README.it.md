[Inglese](./README.md)\|[Cinese semplificato](./README.zh-CN.md)\|[cinese tradizionale](./README.zh-TW.md)\|[coreano](./README.ko.md)\|[No](./README.hi.md)\|[Arabo](./README.ar.md)\|[Francese](./README.fr.md)\|[russo](./README.ru.md)\|[latino](./README.la.md)\|[giapponese](./README.ja.md)\|[Italiano](./README.it.md)\|[Tedesco](./README.de.md)\|[spagnolo](./README.es.md)\|[svedese](./README.sv.md)

![image](https://user-images.githubusercontent.com/100348948/165334090-0b1a6f28-554e-484b-9946-1ffef010fa78.png)

# 

[![Join the chat at https://gitter.im/filecxx/FileCentipede](https://badges.gitter.im/filecxx/FileCentipede.svg)](https://gitter.im/filecxx/FileCentipede?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

<a href="http://filecxx.com" target="_blank">
  <img src="./style/images/logo_128.png" width="128" alt="File Centipede Icon" />
</a>

File Centipede è un gestore di caricamento/download di file Internet all-in-one, client BitTorrent, client WebDAV, client FTP e client SSH.

È progettato per essere veloce, personalizzabile e facile da usare.

Supporta multiprotocolli e contiene molti utili strumenti ausiliari come HTTP requester, file merge e codificatori.

Con l'integrazione del browser, puoi scaricare audio e video da siti Web, persino video crittografati.

(È gratuito senza pubblicità)

Sito web:<http://filecxx.com>

Pannello di controllo:<https://w.filecxx.com>

Sponsor:<http://www.filecxx.com/en_US/sponsors.html>

## Screenshots

#### File Centipede

![File Centipede](images/screenshot_software.png)![File Centipede](images/screenshot_software2.png)![File Centipede](images/screenshot_software_file_browser_webdav.png)![File Centipede](images/screenshot_software_file_browser_ssh.png)![File Centipede](images/screenshot_software_file_browser_ftp.png)![File Centipede](images/screenshot_software_file_browser_add.png)![File Centipede](images/screenshot_software_file_browser_log.png)

#### Aggiungi attività

![Add task](images/screenshot_add_task.png)![Add task](images/screenshot_add_task2.png)![Add task](images/screenshot_add_task3.png)![Add task](images/screenshot_add_task4.png)

#### Modifica attività

![Edit task](images/screenshot_edit_task.png)![Edit task](images/screenshot_edit_task2.png)

#### Schermata di conferma

![torrent confirm](images/screenshot_torrent_confirm.png)![http confirm](images/screenshot_http_confirm.png)![links confirm](images/screenshot_links_confirm.png)

#### Aggiungi catalogo

![add catalog](images/screenshot_add_catalog.png)

#### Impostazioni

![settings](images/screenshot_settings.png)

#### Impostazioni proxy

![proxy](images/screenshot_proxy.png)

#### Regole del sito

![Site rules](images/screenshot_site_rule.png)![Site rules](images/screenshot_site_rule2.png)

#### Filtro

![filter](images/screenshot_filter.png)

#### Aggiorna indirizzo

![${refresh_address}](images/screenshot_refresh_address.png)

#### Crea torrent

![create_torrent](images/screenshot_create_torrent.png)

#### Limite di velocità

![Speed limit](images/screenshot_download_speed_limit.png)

#### Strumento di traduzione

![Translate tool](images/screenshot_translate.png)

#### Strumento HTTP

![HTTP tool](images/screenshot_http_tool.png)

#### Strumento di somma di controllo (checksum)

![Checksum tool](images/screenshot_checksum_tool.png)

## Screenshot dell'estensione del browser

#### Videobar

![Video bar](images/extension_video_bar.png)

#### Pannello video

![videos panel](images/extension_videos.png)

#### Pannello audio

![Audios panel](images/extension_audios.png)

## Caratteristiche

-   HTTP, protocollo HTTPS (funzionalità di base come gzip, ripristino, connessioni multiple non saranno elencate.) 1.0
-   FTP, protocollo FTPS 1.0
-   Magnet, indirizzo HASH 1.0
-   BitTorrent 1.0
-   Altri protocolli personalizzati come thunder, flashget, qqdl 1.0
-   Indirizzo in formato JSON 1.0
-   attività flusso m3u8 1.0
-   Decrittografia AES-128 dell'attività di flusso (la decrittografia SAMPLE-AES non è ancora supportata) 1.0
-   Cookie HTTP, header, user-agent con personalizzazione dell'utente 1.0
-   Limite seeding torrent 1.0
-   Modifica dinamicamente la configurazione dell'attività di trasferimento 1.0
-   Anti leeches 1.0
-   Aggiorna indirizzo scaduto 1.0
-   Cataloghi 1.0
-   Limita download, velocità di caricamento 1.0
-   Crea indirizzo personalizzato (filec, fileu) 1.0
-   Gestione proxy 1.0
-   Filtro personalizza 1.0
-   Gestione del tracker 1.0
-   Dettagli attività 1.0
-   Esporta torrent dall'attività 1.0
-   Multilingue 1.0
-   Impostazione coda o concorrenza illimitata 1.0
-   Integrazione del browser Chrome 1.0
-   Integrazione del browser Firefox 1.0
-   Cattura video, audio dalla pagina web 1.0
-   Trova tutti i magnet dalla pagina web 1.0
-   Strumento di traduzione 1.0
-   Strumento HTTP 1.0
-   Strumento di codifica/decodifica URI 1.0
-   Strumento di codifica/decodifica Base64 1.0
-   Strumento di test Regex 1.0
-   Crea torrent 1.0
-   Strumento da torrent a magnet 1.0
-   Strumento da magnet a torrent 1.0
-   Strumento di unione file 1.0
-   Statistiche 1.0
-   Scarica tutti i link dalla pagina web 1.6
-   SSH, protocollo SFTP 2.0
-   curl, wget, aria2, riga di comando axel 2.0
-   Protocollo WebDAV 2.0
-   Carica file 2.0
-   Carica cartella 2.0
-   Scarica cartella 2.0
-   File manager WebDAV completo 2.0
-   File manager FTP(s) completo 2.0
-   File manager SSH (sftp) completo 2.0
-   File browser cache persistenti 2.0
-   Regole del sito 2.1
-   Strumento di somma di controllo 2.3
-   Download remoto 2.6

## Codice sorgente

Il codice sorgente completo di FileU può essere trovato nella directory "source_code".

È solo a scopo dimostrativo, le librerie dipendenti utilizzate nel progetto non sono open source.

È dimostrato che la scrittura di interfacce utente in C++ potrebbe essere notevolmente più semplice rispetto a HTML e JavaScript, senza ridurre le prestazioni.

(come visto nei file .sml nella directory "UI").

## Come tradurre

Se ti piace questo software, puoi aiutare utilizzando lo strumento di traduzione fornito nel software per tradurlo in altre lingue.

Ciò renderà il software più accessibile alle persone che parlano lingue diverse da quella in cui è stato originariamente scritto. Il tuo contributo sarebbe molto apprezzato.

## File di lingua

-   Sito web: "lang/website/*.lang"
-   Software: "lang/software/*.lang"
-   Estensione del browser: "lang/browser_extension/*.lang"

#### Come tradurre il sito web?

![translate](images/document/how_to_translate_this_website.png)

| Lingua              | @                                                                                         |
| :------------------ | :---------------------------------------------------------------------------------------- |
| russo               | [@vanja-san](https://github.com/vanja-san)[@Den1704](https://github.com/Den1704)          |
| cinese tradizionale | [@orso0316](https://github.com/bear0316)[@ postino1anno](https://github.com/postman1year) |
| Francese            | [@kasikh](https://github.com/XIAA25)                                                      |
| Olandese            | [@XIAA25](https://github.com/XIAA25)                                                      |
| coreano             | [@VenereGirl](https://github.com/VenusGirl)                                               |
| vietnamita          | [@vuongtuha](https://github.com/vuongtuha)                                                |
| Turco               | [@geeeee](https://github.com/geeede)                                                      |
| indonesiano         | [@gigglylo](https://github.com/gigglylo)                                                  |

## Librerie Opensource

[boost](https://www.boost.org) [Qt](https://qt.io/) [libtorrent](https://www.libtorrent.org)
