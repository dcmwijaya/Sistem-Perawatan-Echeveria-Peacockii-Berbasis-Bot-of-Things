[![Open Source Love](https://badges.frapsoft.com/os/v1/open-source.svg?style=flat)](https://github.com/ellerbrock/open-source-badges/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)
![GitHub last commit](https://img.shields.io/github/last-commit/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things)
![Project](https://img.shields.io/badge/Project-Bot%20of%20Things-light.svg?style=flat&logo=github&logoColor=white&color=bcbcbc)
![Platform-IoT-Blynk-Thingsboard](https://img.shields.io/badge/Platform-Blynk-%2DThingsboard-light.svg?style=flat&logo=GoogleChrome&logoColor=white&color=bcbcbc)
![Bot-IoT](https://img.shields.io/badge/Based-Telegram%20Bot-light.svg?style=flat&logo=telegram&logoColor=white&color=bcbcbc)
![Arduino](https://img.shields.io/badge/Tools-Arduino%20IDE-light.svg?style=flat&logo=arduino&logoColor=white&color=bcbcbc)

# Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things
<strong>Tugas Akhir IoT Master Class Indobot 2022</strong><br>
Proyek ini sangat erat kaitannya dengan teknologi pertanian, dimana alat ini digunakan untuk melakukan penyiraman secara otomatis dan memantau perubahan kondisi yang ada di lingkungan sekitar tanaman Echeveria Peacockii secara real time dari jarak jauh kapanpun dan dimanapun. Alat ini dilengkapi dengan antarmuka berbasis Bot of Things (BoT) yang bertujuan untuk memudahkan pengguna dalam merawat tanaman hias tersebut. Echeveria Peacockii merupakan jenis tanaman yang memiliki kekerabatan dengan kaktus, namun pada tubuh tanaman ini tidak dijumpai adanya duri, sehingga sangat diminati oleh para pecinta tanaman hias.

<br>

## Fitur / Kerangka Kerja / Peralatan
| Media | Deskripsi |
| --- | --- |
| Platform IoT | Blynk & ThingsBoard |
| Papan Pengembangan | DOIT ESP32 DEVKIT V1 |
| Pustaka Arduino | WiFi, WiFiClient, PubSubClient, BlynkSimpleEsp32, ArduinoJson, Wire, ESP32_FC28, CTBot, DHT, & LiquidCrystal I2C |
| Telegram | API Bot Telegram |
| Aktuator | Submersible pump |
| Sensor | FC-28 (Kelembaban Tanah Resistif), LDR (Cahaya), DHT22 (Suhu & Kelembaban Udara) |
| Layar | LCD I2C |
| Saklar | Electrical relay 2 channel |
| Komponen Lainnya | ESP32 Expansion Board, Breadboard/Projectboard, Adaptor DC, Resistor, & Casing box |

<br>

## Unduh & Instal
Unduh Arduino IDE :
```bash
https://www.arduino.cc/en/software
```

<br>

## Settings
1. Buka Arduino IDE terlebih dahulu, lalu masuk ke Boards Manager Url dengan cara menyalin tautan berikut:
```bash
https://dl.espressif.com/dl/package_esp32_index.json
```
2. Pengaturan Board di Arduino IDE
   <ul>
      <li>Cara: klik Boards Manager -> ESP32 Arduino -> DOIT ESP32 DEVKIT V1.</li>
   </ul>
3. Pengaturan Port di Arduino IDE
   <ul>
      <li>Cara: klik Port -> Pilih sesuai dengan port perangkat Anda (Anda dapat melihatnya di Device Manager).</li>
   </ul>
4. Instal pustaka di Arduino IDE
   <ul>
      <li>Cara: klik Tools -> Manage Libraries -> Install Library sesuai dengan kebutuhan proyek.</li>
   </ul>

<br>

## Perancangan Perangkat Keras
<img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/5b54e9a0-2972-46b9-a06b-d8a093266ee9"><br><br>
<img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/3fffa52b-5e16-465a-987a-fba5074de658">

<br><br>

## Perancangan Perangkat Lunak
<img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/3c6af705-8d0b-4291-9825-d633338e1f67"><br><br>
<img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/45c85d49-59ff-4f20-98ce-9405e0c07fe5">


<br>

## Menjalankan
1. Unduh Repositori ini.
2. Pastikan Anda memiliki komponen elektronik yang diperlukan.
3. Pastikan komponen Anda telah dirancang sesuai dengan diagram.
4. Pastikan komponen terhubung dengan baik (Sesuaikan pengaturan Board dan Port).
5. Disarankan untuk membuat akun Broker sekaligus dengan layanannya.
6. Pastikan untuk mengubah kode program arduino di bagian "Router" sesuai dengan perangkat yang Anda gunakan.
7. Jika Anda tidak menerapkan poin 2 dan 3 untuk keperluan pengembangan proyek itu tidak masalah, tetapi harap dicatat bahwa beberapa hal perlu diubah agar dapat berfungsi dengan baik.
8. Selesai, semoga berhasil.

<br>

## Preview: Produk
<img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/88b94f07-953e-4cdb-84f8-a4849ff031e8">

<br>

## Preview: Antarmuka Bot Telegram
<img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/d57ba0a1-895b-4d49-99b0-22931c8f99bb" width=230 height=500>&emsp;&emsp;
<img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/37cef7d6-f2b2-4e94-8ed6-d696780e13a5" width=230 height=500>&emsp;&emsp;
<img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/ce29156a-5f1b-4231-a1d9-4ba03e28bea5" width=230 height=500>

<br>

## Preview: Blynk & ThingsBoard
<img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/e3d0fb05-4668-4e33-a186-002f538d8ddb" width=150 height=300>&emsp;
<img src="https://github.com/devancakra/Sistem-Perawatan-Echeveria-Peacockii-Berbasis-Bot-of-Things/assets/54527592/48380dd7-cb7c-4c7d-ae1c-e637bf9adacf" width=600 height=300>

<br>

Notes: This project requires internet and electricity supply to run the application.

<br><br>

## LISENSI
LISENSI MIT - Hak Cipta (c) 2023 - Devan C. M. Wijaya, S.Kom

Dengan ini diberikan izin tanpa biaya kepada siapa pun yang mendapatkan salinan perangkat lunak ini dan file dokumentasi terkait perangkat lunak untuk menggunakannya tanpa batasan, termasuk namun tidak terbatas pada hak untuk menggunakan, menyalin, memodifikasi, menggabungkan, mempublikasikan, mendistribusikan, mensublisensikan, dan/atau menjual salinan Perangkat Lunak ini, dan mengizinkan orang yang menerima Perangkat Lunak ini untuk dilengkapi dengan persyaratan berikut:

Pemberitahuan hak cipta di atas dan pemberitahuan izin ini harus menyertai semua salinan atau bagian penting dari Perangkat Lunak.

DALAM HAL APAPUN, PENULIS ATAU PEMEGANG HAK CIPTA DI SINI TETAP MEMILIKI HAK KEPEMILIKAN PENUH. PERANGKAT LUNAK INI DISEDIAKAN SEBAGAIMANA ADANYA, TANPA JAMINAN APAPUN, BAIK TERSURAT MAUPUN TERSIRAT, OLEH KARENA ITU JIKA TERJADI KERUSAKAN, KEHILANGAN, ATAU LAINNYA YANG TIMBUL DARI PENGGUNAAN ATAU URUSAN LAIN DALAM PERANGKAT LUNAK INI, PENULIS ATAU PEMEGANG HAK CIPTA TIDAK BERTANGGUNG JAWAB, KARENA PENGGUNAAN PERANGKAT LUNAK INI TIDAK DIPAKSAKAN SAMA SEKALI, SEHINGGA RISIKO ADALAH MILIK ANDA SENDIRI.
