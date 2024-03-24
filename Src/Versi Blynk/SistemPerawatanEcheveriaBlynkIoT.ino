// Blynk
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "YOUR_BLYNK_TEMPLATE_ID"
#define BLYNK_DEVICE_NAME "YOUR_BLYNK_DEVICE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"
BlynkTimer timer;

// Pustaka yang digunakan
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <CTBot.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <ESP_FC28.h>

// Koneksi
#define WIFI_SSID "YOUR_WIFI_NAME"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#define BOTtoken "YOUR_API_BOT_TOKEN"
#define KodeBot "ECHEVERIA2022"
#define SERIAL_DEBUG_BAUD 115200
unsigned long lastTime = 0;
unsigned long timerDelay = 1000;

// Sensor
#define LDR_PIN 35 // Pin Antarmuka Sensor LDR
#define FC28_PIN 34 // Pin Antarmuka Sensor FC-28
FC28Sensor fc28(FC28_PIN); // Konstruktor FC28Sensor -> fc28
#define DHT_PIN 13 // Pin Antarmuka Sensor DHT
#define DHT_TYPE DHT22 // Tipe Sensor DHT -> DHT22
DHT dht(DHT_PIN, DHT_TYPE); // Konstruktor DHT -> dht

// Aktuator
#define RPOMPA1_PIN 2 // Pin Antarmuka Pompa Air 1
#define RPOMPA2_PIN 4 // Pin Antarmuka Pompa Air 2

// Layar
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variabel untuk keperluan bot telegram
CTBot myBot; CTBotInlineKeyboard InlineKey, InlineOption, InlineKeyNULL;
#define InlineMenu1 "InlineMonitoringSuhuUdara"
#define InlineMenu2 "InlineMonitoringKelembabanUdara"
#define InlineMenu3 "InlineMonitoringKelembabanTanah"
#define InlineMenu4 "InlineMonitoringIntensitasCahaya"
#define InlineMenu5 "InlineControllingPenyiramanAir"
bool viewTombol;
String sendMsg, msg1, msg2; 

// Variabel untuk keperluan aktuator
bool relayON = HIGH; bool relayOFF = LOW; // Silakan cek terlebih dahulu apakah relay anda itu Active High / Low, kalau relay saya Active High
int kontrolair; // Variabel ini difungsikan untuk menampung perintah yaitu antara 1 (ON) dan 0 (OFF) yang di dapat dari Blynk

// Variabel untuk keperluan sensor
const float GAMMA = 0.7, RL10 = 50; int analogLDR; float volt, resistance, cahaya; String statusSinar, info_intensitascahaya; // LDR
int kelembaban_udara; float suhu_udara; String statusUdara, info_suhuudara, info_kelembabanudara; // DHT
int kelembaban_tanah; String statusTanah, info_kelembabantanah; // FC-28

// Kontrol air untuk menyiram tanaman echeveria
BLYNK_WRITE(V6) {
  kontrolair = param.asInt();
  if (kontrolair == 1) {
    Blynk.virtualWrite(V5, 1); // Indikator Pompa 2: menyala
    Serial.println("Status kontrol air : On");
    Serial.println("<------------------------------->\n");
    digitalWrite(RPOMPA2_PIN, relayON); // Pompa 2 menyala
  } 
  if (kontrolair == 0){
    Blynk.virtualWrite(V5, 0); // Indikator Pompa 2: mati
    Serial.println("Status kontrol air : Off");
    Serial.println("<------------------------------->\n");
    digitalWrite(RPOMPA2_PIN, relayOFF); // Pompa 2 mati
  }
}

// Method untuk menyambungkan ke Bot Telegram
void connectBot() {
  myBot.setTelegramToken(BOTtoken); // Mengatur token bot telegram
  myBot.wifiConnect(WIFI_SSID, WIFI_PASSWORD); // Mengatur konektivitas jaringan bot telegram
  myBot.setMaxConnectionRetries(5); // Bot telegram dapat menyambungkan ulang ke WiFi yang diatur sebanyak 5x sebelum layanan dihentikan
  Serial.println("\nMenghubungkan ke: echeveria_bot..."); // Cetak ke serial monitor

  if(myBot.testConnection()){ // Jika bot telegram tersambung ke jaringan maka cetak ke serial monitor :
    Serial.println("Bot telegram berhasil tersambung ...[SUKSES]\n"); 
  } else{ // Jika bot telegram tidak tersambung ke jaringan maka cetak ke serial monitor :
    Serial.print("Bot telegram gagal tersambung\nMenyambungkan kembali\n"); 
    while (!myBot.testConnection()){ // Selama bot telegram tidak tersambung ke jaringan maka cetak ke serial monitor :
      Serial.print("."); delay(500);
    } Serial.println();
  }
}

// Method untuk membaca sensor
void BacaSensor(){
  // Baca nilai sensor DHT22
  suhu_udara = dht.readTemperature();
  kelembaban_udara = dht.readHumidity();
  
  // Baca nilai sensor FC-28
  kelembaban_tanah = fc28.getSoilMoisture();
  
  // Baca nilai sensor LDR
  analogLDR = analogRead(LDR_PIN);
  volt = analogLDR * 5 / 4095.0;
  resistance = 2000 * volt / (1 - volt / 5);
  cahaya = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));
}

// Method untuk menentukan batasan suhu, kelembaban, dan intensitas cahaya
void TresholdSensorState(){
  // Jika suhu udara rendah, kelembaban tinggi, dan intensitas cahaya rendah, maka :
  if (suhu_udara >= 0 && suhu_udara < 16) { if (kelembaban_udara > 90 && kelembaban_udara <=100) { if (cahaya >= 500) {  
    info_suhuudara = "Suhu Udara: Rendah";                   // Dingin
    info_kelembabanudara = "Kelembaban Udara: Tinggi";       // Basah
    info_intensitascahaya = "Intensitas Cahaya: Rendah";     // Gelap
    statusUdara = "Status Kualitas Udara: Bahaya";           // Status Udara: Bahaya
    statusSinar = "Status Kualitas Sinar: Aman";             // Status Sinar: Aman
    digitalWrite(RPOMPA1_PIN, relayOFF);                     // Pompa 1 mati
    Blynk.virtualWrite(V4, 0);                               // Indikator Pompa 1: mati
  } } }

  // Jika suhu udara sedang, kelembaban sedang, dan intensitas cahaya sedang, maka :  
  if (suhu_udara >= 16 && suhu_udara <= 34) { if (kelembaban_udara >= 30 && kelembaban_udara <= 90) { if (cahaya >= 200 && cahaya < 500) {  
    info_suhuudara = "Suhu Udara: Normal";                   // Normal
    info_kelembabanudara = "Kelembaban Udara: Normal";       // Lembab
    info_intensitascahaya = "Intensitas Cahaya: Normal";     // Remang-remang
    statusUdara = "Status Kualitas Udara: Aman";             // Status Udara: Aman
    statusSinar = "Status Kualitas Sinar: Aman";             // Status Sinar: Aman
    digitalWrite(RPOMPA1_PIN, relayOFF);                     // Pompa 1 mati
    Blynk.virtualWrite(V4, 0);                               // Indikator Pompa 1: mati
  } } }

  // Jika suhu udara tinggi, kelembaban rendah, dan intensitas cahaya tinggi, maka :
  if (suhu_udara > 34 && suhu_udara <= 100) { if (kelembaban_udara >= 0 && kelembaban_udara < 30) { if (cahaya < 200) {
    info_suhuudara = "Suhu Udara: Tinggi";                   // Panas
    info_kelembabanudara = "Kelembaban Udara: Rendah";       // Kering
    info_intensitascahaya = "Intensitas Cahaya: Tinggi";     // Cerah
    statusUdara = "Status Kualitas Udara: Bahaya";           // Status Udara: Bahaya
    statusSinar = "Status Kualitas Sinar: Bahaya";           // Status Sinar: Bahaya
    digitalWrite(RPOMPA1_PIN, relayON);                      // Pompa 1 menyala
    Blynk.virtualWrite(V4, 1);                               // Indikator Pompa 1: menyala
  } } } 

  // Jika kondisi tanah basah maka :
  if (kelembaban_tanah >= 60){
    info_kelembabantanah = "Kelembaban Tanah: Tinggi";       // Basah
    statusTanah = "Status Kualitas Tanah: Bahaya";           // Status Tanah: Bahaya
    digitalWrite(RPOMPA1_PIN, relayOFF);                     // Pompa 1 mati
    Blynk.virtualWrite(V4, 0);                               // Indikator Pompa 1: mati
  }

  // Jika kondisi tanah lembab maka :
  if (kelembaban_tanah > 40 && kelembaban_tanah < 60) { 
    info_kelembabantanah = "Kelembaban Tanah: Normal";       // Lembab
    statusTanah = "Status Kualitas Tanah: Aman";             // Status Tanah: Aman
    digitalWrite(RPOMPA1_PIN, relayOFF);                     // Pompa 1 mati
    Blynk.virtualWrite(V4, 0);                               // Indikator Pompa 1: mati
  }

  // Jika kondisi tanah kering maka :
  if (kelembaban_tanah <= 40) {
    info_kelembabantanah = "Kelembaban Tanah: Rendah";      // Kering
    statusTanah = "Status Kualitas Tanah: Bahaya";          // Status Tanah: Bahaya
    digitalWrite(RPOMPA1_PIN, relayON);                     // Pompa 1 menyala
    Blynk.virtualWrite(V4, 1);                              // Indikator Pompa 1: menyala
  }
}

// Method untuk mengatur visualisasi tombol bot telegram
void ButtonBot() { 
  // Monitoring menu dalam bentuk inline button
  InlineKey.addButton("🌤️ Monitoring Temperature", InlineMenu1, CTBotKeyboardButtonQuery);
  InlineKey.addRow();
  InlineKey.addButton("🌦️ Monitoring Humidity", InlineMenu2, CTBotKeyboardButtonQuery);
  InlineKey.addRow();
  InlineKey.addButton("🌱 Monitoring Soil Moisture", InlineMenu3, CTBotKeyboardButtonQuery);
  InlineKey.addRow();
  InlineKey.addButton("☀️ Monitoring Light Intensity", InlineMenu4, CTBotKeyboardButtonQuery);
  InlineKey.addRow();
  InlineKey.addButton("🚰 Controlling Water Pump", InlineMenu5, CTBotKeyboardButtonQuery);
  
  // Menu kontrol dalam bentuk inline button
  InlineOption.addButton("✅ Pump: Turn ON", "ON", CTBotKeyboardButtonQuery);
  InlineOption.addButton("❌ Pump: Turn OFF", "OFF", CTBotKeyboardButtonQuery);
  
  // Tombol -> default : hidden
  viewTombol = false;
}

// Method untuk mengatur bot telegram
void botTelegram() {
  TBMessage msg; // Konstruktor TBMessage -> msg
  
  if(myBot.getNewMessage(msg)){  
    if(msg.text.equalsIgnoreCase("/start")){ // Start Bot
      msg1 = "🙋🏻‍♂️ Hai @" + msg.sender.username + " 👋👋\nSelamat datang di Layanan BOT ECHEVERIA.";
      msg2 = "\n\n🔐 Silahkan isi kode rahasia 👇👇\n.................................. *(13 Characters)";
      sendMsg = msg1 + msg2; myBot.sendMessage(msg.sender.id, sendMsg); // Mengirim pesan
    } 
    else if(msg.text.equalsIgnoreCase(KodeBot)){ // Menu Utama
      msg1 = "🔓 Kode yang anda masukkan benar";
      myBot.sendMessage(msg.sender.id, msg1);
      main_menu:
      msg2 = "\n--------------------------------------------------------------\n 📝 MENU UTAMA \n--------------------------------------------------------------\nSilahkan pilih menu dibawah ini 👇👇";
      viewTombol = true; myBot.sendMessage(msg.sender.id, msg2, InlineKey); // Mengirim pesan dan menampilkan tombol
    }
    else if(msg.messageType == CTBotMessageQuery){ // Respon Inline Button
      if(msg.callbackQueryData.equals(InlineMenu1)){ // Menampilkan data monitoring suhu udara beserta statusnya
        Serial.println("\n<------------------------------->");
        Serial.println("Deteksi Suhu Udara: " + String(suhu_udara, 2) + "°C");
        Serial.println(info_suhuudara);
        Serial.println(statusUdara);
        Serial.println("<------------------------------->\n");
        msg1 = "🙋🏻‍♂️ Hai @" + msg.sender.username + " 👋👋\nBerikut hasil monitoring suhu udara pada tanaman echeveria terkini:\n\n--------------------------------------------------------------\n 🌤️ MONITORING TEMPERATURE \n--------------------------------------------------------------\n";
        msg2 = "📲 Suhu udara tanaman: " + String(suhu_udara) + "°C\n✍️ " + String(statusUdara) + "\n--------------------------------------------------------------"; 
        sendMsg = msg1 + msg2; myBot.sendMessage(msg.sender.id, sendMsg); // Mengirim pesan
      }
      else if(msg.callbackQueryData.equals(InlineMenu2)){ // Menampilkan data monitoring kelembaban udara beserta statusnya
        Serial.println("\n<------------------------------->");
        Serial.println("Deteksi Kelembaban Udara: " + String(kelembaban_udara) + "%");
        Serial.println(info_kelembabanudara);
        Serial.println(statusUdara);
        Serial.println("<------------------------------->\n");
        msg1 = "🙋🏻‍♂️ Hai @" + msg.sender.username + " 👋👋\nBerikut hasil monitoring kelembaban udara pada tanaman echeveria terkini:\n\n--------------------------------------------------------------\n 🌦️ MONITORING HUMIDITY \n--------------------------------------------------------------\n";
        msg2 = "📲 Kelembaban udara tanaman: " + String(kelembaban_udara) + "%\n✍️ " + String(statusUdara) + "\n--------------------------------------------------------------"; 
        sendMsg = msg1 + msg2; myBot.sendMessage(msg.sender.id, sendMsg); // Mengirim pesan
      }
      else if(msg.callbackQueryData.equals(InlineMenu3)){ // Menampilkan data monitoring kelembaban tanah beserta statusnya
        Serial.println("\n<------------------------------->");
        Serial.println("Deteksi Kelembaban Tanah: " + String(kelembaban_tanah) + "%");
        Serial.println(info_kelembabantanah);
        Serial.println(statusTanah);
        Serial.println("<------------------------------->\n");
        msg1 = "🙋🏻‍♂️ Hai @" + msg.sender.username + " 👋👋\nBerikut hasil monitoring kelembaban tanah pada tanaman echeveria terkini:\n\n--------------------------------------------------------------\n 🌱 MONITORING SOIL MOISTURE \n--------------------------------------------------------------\n";
        msg2 = "📲 Kelembaban tanah tanaman: " + String(kelembaban_tanah) + "%\n✍️ " + String(statusTanah) + "\n--------------------------------------------------------------"; 
        sendMsg = msg1 + msg2; myBot.sendMessage(msg.sender.id, sendMsg); // Mengirim pesan
      }
      else if(msg.callbackQueryData.equals(InlineMenu4)){ // Menampilkan data monitoring intensitas cahaya beserta statusnya
        Serial.println("\n<------------------------------->");
        Serial.println("Deteksi Cahaya: " + String(cahaya) + "lx");
        Serial.println(info_intensitascahaya);
        Serial.println(statusSinar);
        Serial.println("<------------------------------->\n");
        msg1 = "🙋🏻‍♂️ Hai @" + msg.sender.username + " 👋👋\nBerikut hasil monitoring cahaya pada tanaman echeveria terkini:\n\n--------------------------------------------------------------\n ☀️ MONITORING LIGHT INTENSITY \n--------------------------------------------------------------\n";
        msg2 = "📲 Cahaya tanaman: " + String(cahaya) + "lx\n✍️ " + String(statusSinar) + "\n--------------------------------------------------------------"; 
        sendMsg = msg1 + msg2; myBot.sendMessage(msg.sender.id, sendMsg); // Mengirim pesan
      }
      else if(msg.callbackQueryData.equals(InlineMenu5)){ // Opsi controlling
        sendMsg = "🙋🏻‍♂️ Hai @" + msg.sender.username + " 👋👋\nPilihlah opsi controlling berikut:\n";
        myBot.sendMessage(msg.sender.id, sendMsg, InlineOption); // Mengirim pesan dan menampilkan tombol
      }
      else if(msg.callbackQueryData.equals("ON")){ // Memberikan perintah untuk menyalakan pompa 2
        Blynk.virtualWrite(V5, 1); // Indikator Pompa 2: menyala
        Serial.println("\n<------------------------------->");
        Serial.println("Status kontrol air: On");
        Serial.println("<------------------------------->");
        msg1 = "🙋🏻‍♂️ Hai @" + msg.sender.username + " 👋👋\nBerikut hasil controlling pompa air pada tanaman echeveria terkini:\n\n--------------------------------------------------------------\n 🚰 CONTROLLING WATER PUMP \n--------------------------------------------------------------\n";
        msg2 = "📲 Controlling water pump: ON\n--------------------------------------------------------------"; 
        sendMsg = msg1 + msg2; myBot.sendMessage(msg.sender.id, sendMsg); // Mengirim pesan
        digitalWrite(RPOMPA2_PIN, relayON); // Pompa 2 menyala
      }
      else if(msg.callbackQueryData.equals("OFF")){ // Memberikan perintah untuk mematikan pompa 2
        Blynk.virtualWrite(V5, 0); // Indikator Pompa 2: mati
        Serial.println("\n<------------------------------->");
        Serial.println("Status kontrol air: Off");
        Serial.println("<------------------------------->");
        msg1 = "🙋🏻‍♂️ Hai @" + msg.sender.username + " 👋👋\nBerikut hasil controlling pompa air pada tanaman echeveria terkini:\n\n--------------------------------------------------------------\n 🚰 CONTROLLING WATER PUMP \n--------------------------------------------------------------\n";
        msg2 = "📲 Controlling water pump: OFF\n--------------------------------------------------------------"; 
        sendMsg = msg1 + msg2; myBot.sendMessage(msg.sender.id, sendMsg); // Mengirim pesan
        digitalWrite(RPOMPA2_PIN, relayOFF); // Pompa 2 mati
      }
    }
    else{ // Jika perintah tidak sesuai maka :
      sendMsg = "🙋🏻‍♂️ Hai @" + msg.sender.username + " 👋👋\n\n❌ Gagal mengakses, coba lagi";
      myBot.sendMessage(msg.sender.id, sendMsg); // Mengirim pesan gagal
    } 
  }
}

// Method untuk kirim data sensor ke Blynk melalui protokol TCP/IP
void sendData() {
  Blynk.virtualWrite(V0, suhu_udara);         // Mengirimkan data sensor suhu udara ke Blynk
  Blynk.virtualWrite(V1, kelembaban_udara);   // Mengirimkan data sensor kelembaban udara ke Blynk
  Blynk.virtualWrite(V2, kelembaban_tanah);   // Mengirimkan data sensor kelembaban tanah ke Blynk
  Blynk.virtualWrite(V3, cahaya);             // Mengirimkan data sensor intensitas cahaya ke Blynk
}

// Method untuk memulai LCD
void LCDinit(){
  lcd.init(); // Memulai LCD
  lcd.clear(); lcd.backlight(); lcd.setCursor(1,0); lcd.print("Starting"); lcd.setCursor(1,1); lcd.print("Smart System..."); delay(2500); // Tampilan Pertama
  lcd.clear(); lcd.backlight(); lcd.setCursor(1,0); lcd.print("Welcome to"); lcd.setCursor(1,1); lcd.print("Echeveria BoT..."); delay(2500); // Tampilan Kedua
  lcd.clear(); lcd.backlight(); lcd.setCursor(1,0); lcd.print("Loading...."); delay(5000); // Tampilan Ketiga
}

// Method untuk menampilkan data sensor ke LCD
void PrintLCD(){
  lcd.clear(); lcd.backlight(); lcd.setCursor(1,0); lcd.print("Suhu Udara:"); lcd.setCursor(1,1); lcd.print(""+String(suhu_udara)+" "+String((char)223)+"C"); delay(1000);
  lcd.clear(); lcd.backlight(); lcd.setCursor(1,0); lcd.print("Kelem.Udara:"); lcd.setCursor(1,1); lcd.print(""+String(kelembaban_udara)+" %"); delay(1000);
  lcd.clear(); lcd.backlight(); lcd.setCursor(1,0); lcd.print("Kelem.Tanah:"); lcd.setCursor(1,1); lcd.print(""+String(kelembaban_tanah)+" %"); delay(1000);
  lcd.clear(); lcd.backlight(); lcd.setCursor(1,0); lcd.print("Int.Cahaya:"); lcd.setCursor(1,1); lcd.print(""+String(cahaya)+" lx"); delay(1000);
}

// Method yang dijalankan sekali
void setup() {
  Serial.begin(SERIAL_DEBUG_BAUD); // Baudrate untuk papan ESP
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD); // Memulai Blynk
  connectBot(); // Memanggil method connectBot
  ButtonBot(); // Memanggil method ButtonBot
  LCDinit(); // Memanggil method LCDinit
  fc28.begin(); // Memulai sensor fc-28
  dht.begin(); // Memulai sensor dht
  pinMode(LDR_PIN, INPUT); // LDR sebagai INPUT
  pinMode(RPOMPA1_PIN, OUTPUT); // Pompa 1 sebagai OUTPUT
  pinMode(RPOMPA2_PIN, OUTPUT); // Pompa 2 sebagai OUTPUT
  digitalWrite(RPOMPA1_PIN, relayOFF); // Default relay1: OFF
  digitalWrite(RPOMPA2_PIN, relayOFF); // Default relay2: OFF
  timer.setInterval(1000L, sendData); // Interval pengiriman setiap 1 detik
}

// Method yang dijalankan berulang kali
void loop() {
  if ((millis() - lastTime) > timerDelay) { // Jika waktu sekarang dikurangi waktu terakhir lebih besar dari 1 detik maka :
    BacaSensor(); // Memanggil method BacaSensor
    TresholdSensorState(); // Memanggil method ThresholdSensorState
    PrintLCD(); // Memanggil method PrintLCD
    botTelegram(); // Memanggil method botTelegram
    lastTime = millis(); // Untuk menghitung waktu yang telah berlalu sejak pengiriman data terakhir
  }
  Blynk.run(); // Menjalankan Blynk
  timer.run(); // Menjalankan Timer
}
