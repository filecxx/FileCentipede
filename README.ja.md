[英語 English](./README.md) | [中国語（簡体字） 简体中文](./README.zh-CN.md) | [中国語（繁体字） 繁體中文](./README.zh-TW.md) | [韓国語 한국어](./README.ko.md) | [ヒンディー語 Hindi](./README.hi.md) | [アラビア語 Arabic](./README.ar.md) | [フランス語 Français](./README.fr.md) | [ロシア語 Русский](./README.ru.md) | [ラテン語 Latin](./README.la.md) | [日本語](./README.ja.md)| [イタリア語 Italian](./README.it.md) | [ドイツ語 Deutsch](./README.de.md) | [スペイン語 Español](./README.es.md) | [スウェーデン語 svenska](./README.sv.md) | [ペルシャ語 فارسی](./README.fa.md)

![image](https://user-images.githubusercontent.com/100348948/165334090-0b1a6f28-554e-484b-9946-1ffef010fa78.png)

#

[![Join the chat at https://gitter.im/filecxx/FileCentipede](https://badges.gitter.im/filecxx/FileCentipede.svg)](https://gitter.im/filecxx/FileCentipede?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

<a href="http://filecxx.com" target="_blank">
  <img src="./style/images/logo_128.png" width="128" alt="File Centipede Icon" />
</a>

File centipede は、オールインワンのインターネットファイルアップロード・ダウンロードマネージャー、およびBitTorrentクライアント、WebDAVクライアント、FTPクライアント、SSHクライアントです。

高速で、カスタマイズ可能で、使いやすいように設計されています。

マルチプロトコルをサポートし、HTTPリクエスター、ファイルマージツール、エンコーダーなどの便利な補助ツールが多数含まれています。

ブラウザ統合機能により、Webサイトから音声ファイルや動画ファイル、さらには暗号化動画ファイルもダウンロードできます。

（広告は無く、無料で使用できます）

Webサイト：[http://filecxx.com](http://filecxx.com)

ダッシュボード：[https://w.filecxx.com](https://w.filecxx.com)

スポンサー：[http://www.filecxx.com/en_US/sponsors.html](http://www.filecxx.com/en_US/sponsors.html)

## スクリーンショット

#### File Centipede

![File Centipede](images/screenshot_software.png)
![File Centipede](images/screenshot_software2.png)
![File Centipede](images/screenshot_software_file_browser_webdav.png)
![File Centipede](images/screenshot_software_file_browser_ssh.png)
![File Centipede](images/screenshot_software_file_browser_ftp.png)
![File Centipede](images/screenshot_software_file_browser_add.png)
![File Centipede](images/screenshot_software_file_browser_log.png)

#### タスクの追加

![Add task](images/screenshot_add_task.png)
![Add task](images/screenshot_add_task2.png)
![Add task](images/screenshot_add_task3.png)
![Add task](images/screenshot_add_task4.png)

#### タスクの編集

![Edit task](images/screenshot_edit_task.png)
![Edit task](images/screenshot_edit_task2.png)

#### 確認ダイアログ

![torrent confirm](images/screenshot_torrent_confirm.png)
![http confirm](images/screenshot_http_confirm.png)
![links confirm](images/screenshot_links_confirm.png)

#### カタログの追加

![add catalog](images/screenshot_add_catalog.png)

#### 設定

![settings](images/screenshot_settings.png)

#### プロキシ設定

![proxy](images/screenshot_proxy.png)

#### サイトルール

![Site rules](images/screenshot_site_rule.png)
![Site rules](images/screenshot_site_rule2.png)

#### フィルター

![filter](images/screenshot_filter.png)

#### アドレスの更新

![${refresh_address}](images/screenshot_refresh_address.png)

#### トレントの作成

![create_torrent](images/screenshot_create_torrent.png)

#### 制限速度

![Speed limit](images/screenshot_download_speed_limit.png)

#### 翻訳ツール

![Translate tool](images/screenshot_translate.png)

#### HTTPツール

![HTTP tool](images/screenshot_http_tool.png)

#### チェックサムツール

![Checksum tool](images/screenshot_checksum_tool.png)

## ブラウザ拡張機能のスクリーンショット

---

#### 動画用フローティングバー

![Video bar](images/extension_video_bar.png)

#### 動画パネル

![videos panel](images/extension_videos.png)

#### 音声パネル

![Audios panel](images/extension_audios.png)

## 機能・特徴

- HTTP、HTTPSプロトコル（gzip、再開可能、複数接続などの基本機能はこのリストから省略） 1.0
- FTP、FTPSプロトコル 1.0
- マグネット、ハッシュアドレス 1.0
- BitTorrent 1.0
- Thunder、FlashGet、QQDLやその他のカスタムプロトコル 1.0
- JSON形式のアドレス 1.0
- m3u8ストリームのタスク 1.0
- ストリームタスク AES-128 復号化（SAMPLE-AES復号化はまだサポートされていません） 1.0
- HTTP Cookieやヘッダを含むカスタマイズ可能なユーザー・エージェント 1.0
- torrent(シード)制限 1.0
- 動的編集可能な転送タスク構成 1.0
- リーチャー対策 1.0
- 期限切れアドレスの更新 1.0
- カタログ機能 1.0
- ダウンロード・アップロード速度制限 1.0
- カスタムアドレスの作成（filec、fileu） 1.0
- プロキシ管理 1.0
- フィルターのカスタマイズ 1.0
- トラッカー管理 1.0
- タスクの詳細 1.0
- タスクからtorrentをエクスポート 1.0
- 多言語対応 1.0
- キューまたは無制限の同時実行設定 1.0
- Chromeブラウザ統合 1.0
- Firefoxブラウザ統合 1.0
- ウェブページから動画・音声ファイルをキャプチャ 1.0
- ウェブページからすべてのマグネットリンクを検索 1.0
- 翻訳ツール 1.0
- HTTPツール 1.0
- URIエンコーダー・デコーダー 1.0
- Base64エンコーダー・デコーダー 1.0
- 正規表現テストツール 1.0
- torrentの作成 1.0
- torrentからマグネットへの変換ツール 1.0
- マグネットからtorrentへの変換ツール 1.0
- ファイルマージツール 1.0
- 統計 1.0
- ウェブページ からすべてのリンクをダウンロード 1.6
- SSH、SFTPプロトコル 2.0
- curl、wget、aria2、axelコマンドライン 2.0
- WebDAVプロトコル 2.0
- ファイルのアップロード 2.0
- ディレクトリのアップロード 2.0
- ディレクトリのダウンロード 2.0
- 完全なWebDAVファイルマネージャー 2.0
- 完全なFTPファイルマネージャー 2.0
- 完全なSSH(sftp)ファイルマネージャー 2.0
- ファイルブラウザの永続キャッシュ 2.0
- サイト別ルール 2.1
- チェックサムツール 2.3
- リモートダウンロード 2.6

## ソースコード

FileUの完全なソースコードは、[`source_code`](./source_code/) ディレクトリに配置しています。

これはデモンストレーションのみを目的としており、プロジェクト内で使用されている依存ライブラリはオープンソースではありません。

C++によるUIの作成は、パフォーマンスを低下させることなく、HTMLやJavaScriptよりもはるかに簡単であることが確認できました。

（UIディレクトリ内の`.sml`ファイルを参照）。

## 翻訳

このソフトウェアが気に入った場合は、ソフトウェアに同梱されている翻訳ツールを使用して他の言語に翻訳することができます。

これにより、ソフトウェアの元言語とは異なる言語を話す人々にとっても、より使いやすくなります。ご協力をお待ちしております。

## 言語ファイル

- ウェブサイト：`lang/website/\*.lang`
- ソフトウェア：`lang/software/\*.lang`
- ブラウザ拡張機能：`lang/browser_extension/\*.lang`

#### ウェブサイトを翻訳するには

![translate](images/document/how_to_translate_this_website.png)


| 言語             | @                                                                                         |
| :--------------- | :---------------------------------------------------------------------------------------- |
| ロシア語         | [@vanja-san](https://github.com/vanja-san) [@Den1704](https://github.com/Den1704)         |
| 中国語（繁体字） | [@bear0316](https://github.com/bear0316) [@postman1year](https://github.com/postman1year) |
| フランス語       | [@XIAA25](https://github.com/XIAA25)                                                      |
| オランダ語       | [@XIAA25](https://github.com/XIAA25)                                                      |
| 韓国語           | [@VenusGirl](https://github.com/VenusGirl)                                                |
| ベトナム語       | [@vuongtuha](https://github.com/vuongtuha)                                                |
| トルコ語         | [@geeede](https://github.com/geeede)                                                      |
| インドネシア語   | [@gigglylo](https://github.com/gigglylo)                                                  |
| ドイツ語         | [@Vulcanraven91](https://github.com/Vulcanraven91)                                        |
| 日本語           | [@wany-oh](https://github.com/wany-oh)                                                    |

## オープンソース ライブラリ

- [boost](https://www.boost.org)
- [Qt](https://qt.io/)
- [libtorrent](https://www.libtorrent.org)
