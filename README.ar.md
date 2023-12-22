[إنجليزي](./README.md)\|[الصينية المبسطة](./README.zh-CN.md)\|[الصينية التقليدية](./README.zh-TW.md)\|[الكورية](./README.ko.md)\|[لا](./README.hi.md)\|[عربي](./README.ar.md)\|[فرنسي](./README.fr.md)\|[الروسية](./README.ru.md)\|[اللاتينية](./README.la.md)\|[اليابانية](./README.ja.md)\|[ايطالي](./README.it.md)\|[ألماني](./README.de.md)\|[الأسبانية](./README.es.md)\|[السويدية](./README.sv.md)\|[الفارسية](./README.fa.md)\|[اللغة التركية](./README.tr-TR.md)

![image](https://user-images.githubusercontent.com/100348948/165334090-0b1a6f28-554e-484b-9946-1ffef010fa78.png)

# 

[![Join the chat at https://gitter.im/filecxx/FileCentipede](https://badges.gitter.im/filecxx/FileCentipede.svg)](https://gitter.im/filecxx/FileCentipede?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

<a href="http://filecxx.com" target="_blank">
  <img src="./style/images/logo_128.png" width="128" alt="File Centipede Icon" />
</a>

File Centipede هو مدير تحميل/تنزيل ملفات الإنترنت متعدد الإمكانات، وعميل BitTorrent، وعميل WebDAV، وعميل FTP، وعميل SSH.

لقد تم تصميمه ليكون سريعًا وقابلاً للتخصيص وسهل الاستخدام.

وهو يدعم البروتوكولات المتعددة ويحتوي على العديد من الأدوات المساعدة المفيدة مثل طالب HTTP ودمج الملفات وأجهزة التشفير.

من خلال تكامل المتصفح، يمكنك تنزيل الصوت ومقاطع الفيديو من مواقع الويب، وحتى مقاطع الفيديو المشفرة.

(إنه مجاني بدون إعلانات)

موقع إلكتروني:[حطب://فيلسكسكس.كوم](http://filecxx.com)

لوحة القيادة:[هتبص://و.فيلسكسكس.كوم](https://w.filecxx.com)

الرعاة:[حطب://وو.فيلسكسكس.كوم/إنس/سبنسرس.هتمل](http://www.filecxx.com/en_US/sponsors.html)

## لقطة شاشة

#### ملف حريش

![File Centipede](images/screenshot_software.png)![File Centipede](images/screenshot_software2.png)![File Centipede](images/screenshot_software_file_browser_webdav.png)![File Centipede](images/screenshot_software_file_browser_ssh.png)![File Centipede](images/screenshot_software_file_browser_ftp.png)![File Centipede](images/screenshot_software_file_browser_add.png)![File Centipede](images/screenshot_software_file_browser_log.png)

#### إضافة مهمة

![Add task](images/screenshot_add_task.png)![Add task](images/screenshot_add_task2.png)![Add task](images/screenshot_add_task3.png)![Add task](images/screenshot_add_task4.png)

#### تحرير المهمة

![Edit task](images/screenshot_edit_task.png)![Edit task](images/screenshot_edit_task2.png)

#### تأكيد الحوار

![torrent confirm](images/screenshot_torrent_confirm.png)![http confirm](images/screenshot_http_confirm.png)![links confirm](images/screenshot_links_confirm.png)

#### إضافة كتالوج

![add catalog](images/screenshot_add_catalog.png)

#### إعدادات

![settings](images/screenshot_settings.png)

#### إعدادات الوكيل

![proxy](images/screenshot_proxy.png)

#### قواعد الموقع

![Site rules](images/screenshot_site_rule.png)![Site rules](images/screenshot_site_rule2.png)

#### منقي

![filter](images/screenshot_filter.png)

#### تحديث العنوان

![${refresh_address}](images/screenshot_refresh_address.png)

#### إنشاء سيل

![create_torrent](images/screenshot_create_torrent.png)

#### الحد الأقصى للسرعة

![Speed limit](images/screenshot_download_speed_limit.png)

#### أداة الترجمة

![Translate tool](images/screenshot_translate.png)

#### أداة HTTP

![HTTP tool](images/screenshot_http_tool.png)

#### أداة المجموع الاختباري

![Checksum tool](images/screenshot_checksum_tool.png)

## لقطات من ملحق المتصفح

#### شريط الفيديو

![Video bar](images/extension_video_bar.png)

#### لوحة الفيديوهات

![videos panel](images/extension_videos.png)

#### لوحة صوتيات

![Audios panel](images/extension_audios.png)

## سمات

-   بروتوكول HTTP وHTTPS (لن يتم إدراج الميزات الأساسية مثل gzip والقابلة للاستئناف والاتصالات المتعددة.) 1.0
-   بروتوكول نقل الملفات، بروتوكول FTPS 1.0
-   مغناطيس، عنوان التجزئة 1.0
-   بت تورنت 1.0
-   بروتوكول مخصص آخر مثل الرعد، برنامج Flashget، QQDL 1.0
-   العنوان المنسق JSON 1.0
-   مهمة دفق m3u8 1.0
-   فك تشفير مهمة الدفق AES-128 (فك تشفير SAMPLE-AES غير مدعوم حتى الآن) 1.0
-   ملف تعريف ارتباط HTTP، والرأس، ووكيل المستخدم مع تخصيص المستخدم 1.0
-   حد البذر سيل 1.0
-   تحرير تكوين مهمة النقل 1.0 ديناميكيًا
-   مكافحة العلق 1.0
-   تحديث العنوان منتهي الصلاحية 1.0
-   الكتالوجات 1.0
-   الحد من التنزيل وسرعة التحميل 1.0
-   إنشاء عنوان مخصص (ملف، ملف) 1.0
-   إدارة الوكيل 1.0
-   تخصيص الفلتر 1.0
-   إدارة التتبع 1.0
-   تفاصيل المهمة 1.0
-   تصدير سيل من المهمة 1.0
-   متعدد اللغات 1.0
-   قائمة الانتظار أو إعداد التزامن غير المحدود 1.0
-   التكامل مع متصفح كروم 1.0
-   التكامل مع متصفح فايرفوكس 1.0
-   التقاط مقاطع الفيديو والتسجيلات الصوتية من صفحة الويب 1.0
-   ابحث عن جميع المغناطيسات من صفحة الويب 1.0
-   أداة الترجمة 1.0
-   أداة HTTP 1.0
-   أداة تشفير/فك تشفير URI 1.0
-   أداة التشفير وفك التشفير Base64 1.0
-   أداة اختبار Regex 1.0
-   إنشاء تورنت 1.0
-   أداة التورنت إلى المغناطيس 1.0
-   أداة المغناطيس للتورنت 1.0
-   أداة دمج الملفات 1.0
-   الإحصائيات 1.0
-   تنزيل جميع الروابط من صفحة الويب 1.6
-   SSH، بروتوكول SFTP 2.0
-   حليقة، wget، aria2، سطر الأوامر أكسل 2.0
-   بروتوكول WebDAV 2.0
-   تحميل الملف 2.0
-   تحميل الدليل 2.0
-   تحميل الدليل 2.0
-   مدير ملفات WebDAV (برامج) كامل المواصفات 2.0
-   مدير ملفات FTP (ملفات) كامل المواصفات 2.0
-   مدير ملفات SSH(sftp) كامل المواصفات 2.0
-   ذاكرة التخزين المؤقت المستمرة لمتصفح الملفات 2.0
-   قواعد الموقع 2.1
-   أداة المجموع الاختباري 2.3
-   التحميل عن بعد 2.6

## مصدر الرمز

يمكن العثور على كود المصدر الكامل لـ FileU في دليل "source_code".

إنه لأغراض العرض التوضيحي فقط، والمكتبات التابعة المستخدمة في المشروع ليست مفتوحة المصدر.

لقد أثبت أن كتابة واجهات المستخدم بلغة C++ يمكن أن تكون أسهل بكثير من HTML وJavaScript، دون تقليل الأداء.

(كما هو موضح في ملفات .sml في دليل "UI").

## يترجم

إذا أعجبك هذا البرنامج، فيمكنك المساعدة باستخدام أداة الترجمة المتوفرة في البرنامج لترجمته إلى لغات أخرى.

وهذا سيجعل البرنامج في متناول الأشخاص الذين يتحدثون لغات أخرى غير تلك التي تمت كتابتها بها في الأصل. وستكون مساهمتك موضع تقدير كبير.

## ملفات اللغة

-   موقع الويب: "lang/website/\*.lang"
-   البرنامج: "lang/software/\*.lang"
-   ملحق المتصفح: "lang/browser_extension/\*.lang"

#### كيفية ترجمة الموقع؟

![translate](images/document/how_to_translate_this_website.png)

| لغة               | @                                                                                        |
| :---------------- | :--------------------------------------------------------------------------------------- |
| الروسية           | [@فانجا-سان](https://github.com/vanja-san)[@دن1704](https://github.com/Den1704)          |
| الصينية التقليدية | [@bear0316](https://github.com/bear0316)[@postman1year](https://github.com/postman1year) |
| فرنسي             | [@كسائخ](https://github.com/XIAA25)                                                      |
| هولندي            | [@كسائخ](https://github.com/XIAA25)                                                      |
| الكورية           | [@فينوسجيرل](https://github.com/VenusGirl)                                               |
| الفيتنامية        | [@vuongtuha](https://github.com/vuongtuha)                                               |
| اللغة التركية     | [@geeeede](https://github.com/geeede)[@سوران](https://github.com/saurane)                |
| الاندونيسية       | [@gigglylo](https://github.com/gigglylo)                                                 |
| ألماني            | [@فولكانرافين91](https://github.com/Vulcanraven91)                                       |
| اليابانية         | [@wany-أوه](https://github.com/wany-oh)                                                  |
| تلميع             | [@رونوهوك](https://github.com/RunoHawk)                                                  |

## المكتبات مفتوحة المصدر

[يعزز](https://www.boost.org)[كيو تي](https://qt.io/)[com.libtorrent](https://www.libtorrent.org)
