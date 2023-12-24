[![Open Source Love](https://badges.frapsoft.com/os/v1/open-source.svg?style=flat)](https://github.com/ellerbrock/open-source-badges/)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg?logo=github&color=%23F7DF1E)](https://opensource.org/licenses/MIT)
![GitHub last commit](https://img.shields.io/github/last-commit/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things)
![Project](https://img.shields.io/badge/Project-Bot%20of%20Things-light.svg?style=flat&logo=arduino&logoColor=white&color=%23F7DF1E)

# Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things
<strong>Tugas Akhir IoT Master Class Indobot 2022</strong><br>
Proyek ini sangat erat kaitannya dengan teknologi pertanian, dimana alat ini digunakan untuk melakukan penyiraman secara otomatis dan memantau perubahan kondisi yang ada di lingkungan sekitar tanaman Echeveria Peacockii secara real time dari jarak jauh kapanpun dan dimanapun. Alat ini dilengkapi dengan antarmuka berbasis Bot of Things (BoT) yang bertujuan untuk memudahkan pengguna dalam merawat tanaman hias tersebut. Echeveria Peacockii merupakan jenis tanaman yang memiliki kekerabatan dengan kaktus, namun pada tubuh tanaman ini tidak dijumpai adanya duri, sehingga sangat diminati oleh para pecinta tanaman hias.

<br><br>

## Fitur / Kerangka Kerja / Peralatan
| Media | Deskripsi |
| --- | --- |
| Papan Pengembangan | DOIT ESP32 DEVKIT V1 |
| Editor Kode | Arduino IDE |
| Driver | USB-Serial CP210X |
| Platform IoT | Blynk & ThingsBoard |
| Protokol IoT | MQTT & TCP/IP |
| Arsitektur | 3 Lapisan |
| Telegram | API Bot Telegram |
| Pustaka Arduino | WiFi, WiFiClient, PubSubClient, BlynkSimpleEsp32, ArduinoJson, Wire, ESP32_FC28, CTBot, DHT, & LiquidCrystal I2C |
| Aktuator | Submersible pump |
| Sensor | FC-28 (Kelembaban Tanah Resistif), LDR (Cahaya), DHT22 (Suhu & Kelembaban Udara) |
| Layar | LCD I2C |
| Saklar | Electrical relay 2 channel |
| Komponen Lainnya | ESP32 Expansion Board, Breadboard/Projectboard, Adaptor DC, Resistor, & Casing box |

<br><br>

## Unduh & Instal
1. Arduino IDE

   ```
   https://www.arduino.cc/en/software
   ```
<br>

2. USB-Serial CP210X

   ```
   https://bit.ly/CP210X_Driver
   ```
   
<br><br>

## Pengaturan
1. Buka ``` Arduino IDE ``` terlebih dahulu, lalu masuk ke ``` Boards Manager Url ``` dengan cara menyalin tautan berikut:
   
   ```bash
   https://dl.espressif.com/dl/package_esp32_index.json
   ```
<br>

2. ``` Pengaturan Board ``` di Arduino IDE<br><br>
   • Cara: klik ``` Boards Manager ``` -> ``` ESP32 Arduino ``` -> ``` DOIT ESP32 DEVKIT V1 ```.
   <br><br><br>
3. ``` Pengaturan Port ``` di Arduino IDE<br><br>
   • Cara: klik ``` Port ``` -> Pilih sesuai dengan port perangkat Anda ``` (Anda dapat melihatnya di Device Manager) ```.
   <br><br><br>
4. ``` Instal pustaka ``` di Arduino IDE<br><br>
   • Cara: klik ``` Tools ``` -> ``` Manage Libraries ``` -> ``` Install Library ``` sesuai dengan kebutuhan proyek.

<br><br>

## Persyaratan Proyek
<table>
<tr>
<th colspan="2">Desain Perangkat Keras</th>
</tr>
<tr>
<td width="420"><img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/5b54e9a0-2972-46b9-a06b-d8a093266ee9" alt="pictorial-diagram"></td>
<td width="420"><img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/3fffa52b-5e16-465a-987a-fba5074de658" alt="schematic-diagram"></td>
</tr>
</table>
<table>
<tr>
<th colspan="2">Desain Perangkat Lunak</th>
</tr>
<tr>
<td width="420"><img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/3c6af705-8d0b-4291-9825-d633338e1f67" alt="flowchart-blynk"></td>
<td width="420"><img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/45c85d49-59ff-4f20-98ce-9405e0c07fe5" alt="flowchart-thingsboard"></td>
</tr>
</table>

<br><br>

## Memulai
1. Pastikan anda memiliki komponen elektronik yang diperlukan.
   
2. Pastikan komponen anda telah dirancang sesuai dengan diagram.
   
3. Pastikan komponen terhubung dengan baik ``` (Sesuaikan pengaturan Board dan Port) ```.
   
4. Disarankan untuk ``` membuat akun Platform IoT ``` sekaligus dengan layanannya.
    
5. Pastikan untuk mengubah kode program arduino di bagian ``` Router ``` sesuai dengan perangkat yang anda gunakan.
    
6. Jika anda tidak menerapkan poin 1 dan 2 untuk keperluan pengembangan proyek itu tidak masalah, tetapi harap dicatat bahwa beberapa hal perlu diubah agar dapat berfungsi dengan baik.

7. Pastikan perangkat terhubung ke internet.

8. Pastikan semua Things telah dibuat.

9. Unduh dan ekstrak repositori ini.
   
10. Selamat menikmati [Selesai].

<br><br>

## Sorotan
<table>
<tr>
<th width="840">Produk</th>
</tr>
<tr>
<td><img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/88b94f07-953e-4cdb-84f8-a4849ff031e8" alt="product"></td>
</tr>
</table>
<table>
<tr>
<th colspan="3">Antarmuka Bot Telegram</th>
<th colspan="1">Pemantauan melalui Blynk Mobile</th>
</tr>
<tr>
<td width="210"><img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/d57ba0a1-895b-4d49-99b0-22931c8f99bb" alt="interfacebot-1"></td>
<td width="210"><img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/37cef7d6-f2b2-4e94-8ed6-d696780e13a5" alt="interfacebot-2"></td>
<td width="210"><img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/ce29156a-5f1b-4231-a1d9-4ba03e28bea5" alt="interfacebot-3"></td>
<td width="210"><img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/e3d0fb05-4668-4e33-a186-002f538d8ddb" alt="blynk-mobile"></td>
</tr>
</table>
<table>
<tr>
<th width="840">Pemantauan melalui Thingsboard</th>
</tr>
<tr>
<td><img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/48380dd7-cb7c-4c7d-ae1c-e637bf9adacf" alt="thingsboard"></td>
</tr>
</table>

<br><br>

## Penafian
Aplikasi ini dibuat dengan menyertakan sumber-sumber dari pihak ketiga. Pihak ketiga di sini adalah penyedia layanan, yang layanannya berupa pustaka, kerangka kerja, dan lain-lain. Saya ucapkan terima kasih banyak atas layanannya. Telah terbukti sangat membantu dan dapat diimplementasikan.

<br><br>

## LISENSI
LISENSI MIT - Hak Cipta (c) 2023 - Devan C. M. Wijaya, S.Kom

Dengan ini diberikan izin tanpa biaya kepada siapa pun yang mendapatkan salinan perangkat lunak ini dan file dokumentasi terkait perangkat lunak untuk menggunakannya tanpa batasan, termasuk namun tidak terbatas pada hak untuk menggunakan, menyalin, memodifikasi, menggabungkan, mempublikasikan, mendistribusikan, mensublisensikan, dan/atau menjual salinan Perangkat Lunak ini, dan mengizinkan orang yang menerima Perangkat Lunak ini untuk dilengkapi dengan persyaratan berikut:

Pemberitahuan hak cipta di atas dan pemberitahuan izin ini harus menyertai semua salinan atau bagian penting dari Perangkat Lunak.

DALAM HAL APAPUN, PENULIS ATAU PEMEGANG HAK CIPTA DI SINI TETAP MEMILIKI HAK KEPEMILIKAN PENUH. PERANGKAT LUNAK INI DISEDIAKAN SEBAGAIMANA ADANYA, TANPA JAMINAN APAPUN, BAIK TERSURAT MAUPUN TERSIRAT, OLEH KARENA ITU JIKA TERJADI KERUSAKAN, KEHILANGAN, ATAU LAINNYA YANG TIMBUL DARI PENGGUNAAN ATAU URUSAN LAIN DALAM PERANGKAT LUNAK INI, PENULIS ATAU PEMEGANG HAK CIPTA TIDAK BERTANGGUNG JAWAB, KARENA PENGGUNAAN PERANGKAT LUNAK INI TIDAK DIPAKSAKAN SAMA SEKALI, SEHINGGA RISIKO ADALAH MILIK ANDA SENDIRI.
