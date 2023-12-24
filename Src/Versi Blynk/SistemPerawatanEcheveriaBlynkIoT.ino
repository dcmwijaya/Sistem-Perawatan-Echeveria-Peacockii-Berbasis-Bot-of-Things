//Deklarasi Library/Konstanta/Dsb
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "YOUR_BLYNK_TEMPLATE_ID"
#define BLYNK_DEVICE_NAME "YOUR_BLYNK_DEVICE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <CTBot.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32_FC28.h>
#define LDR_PIN 35
#define FC28_PIN 34
#define DHT_PIN 13
#define RPOMPA1_PIN 2
#define RPOMPA2_PIN 4
#define DHT_TYPE DHT22
FC28Sensor fc28;
DHT dht(DHT_PIN, DHT_TYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define WIFI_SSID "YOUR_WIFI_NAME"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#define BOTtoken "YOUR_API_BOT_TOKEN"
#define InlineMenu1 "InlineMonitoringSuhuUdara"
#define InlineMenu2 "InlineMonitoringKelembapanUdara"
#define InlineMenu3 "InlineMonitoringKelembapanTanah"
#define InlineMenu4 "InlineMonitoringIntensitasCahaya"
#define InlineMenu5 "InlineControllingPenyiramanAir"
#define ON "ON"
#define OFF "OFF"
#define KodeBot "ECHEVERIA2022"
CTBot myBot; CTBotInlineKeyboard InlineKey, InlineOption, InlineKeyNULL;
BlynkTimer timer;
#define SERIAL_DEBUG_BAUD 115200
const float GAMMA = 0.7; const float RL10 = 50;
int kontrolair, analogLDR, kelembapan_udara, kelembapan_tanah; 
float volt, resistance, suhu_udara, cahaya;
String statusUdara, statusTanah, statusSinar, info_suhuudara, info_kelembapanudara, info_kelembapantanah, info_intensitascahaya, sendMsg, msg1, msg2; 
bool viewTombol; bool relayON = HIGH; bool relayOFF = LOW;
long durasi = 0; long jeda = 1000;

BLYNK_WRITE(V6) { //kontrol air untuk menyiram tanaman echeveria
  kontrolair = param.asInt();
  digitalWrite(RPOMPA2_PIN, kontrolair);
  if (kontrolair == 1) {
    digitalWrite(RPOMPA2_PIN, relayON);
    Blynk.virtualWrite(V5, 1);
    Serial.println("Status kontrol air : On");
    Serial.println("<------------------------------->\n");
  } 
  if (kontrolair == 0){
    digitalWrite(RPOMPA2_PIN, relayOFF);
    Blynk.virtualWrite(V5, 0);
    Serial.println("Status kontrol air : Off");
    Serial.println("<------------------------------->\n");
  }
}


void connectBot() {
  myBot.setTelegramToken(BOTtoken);
  myBot.wifiConnect(WIFI_SSID, WIFI_PASSWORD); 
  myBot.setMaxConnectionRetries(5);
  Serial.println("\nMenghubungkan ke: echeveria_bot"); 

  if(myBot.testConnection()){
    Serial.println("Bot telegram berhasil tersambung dan sedang mengirim data...."); 
  } else{ 
    Serial.print("Bot telegram gagal tersambung\nMenyambungkan kembali"); 
    while (!myBot.testConnection()){ 
      Serial.print("."); delay(500);
    }
    Serial.println();
  }
}


void ButtonBot() { //Bagian yang mengatur visualisasi tombol di bot telegram
  //Inline Button Menu
  InlineKey.addButton("🌤️ Monitoring Temperature", InlineMenu1, CTBotKeyboardButtonQuery);
  InlineKey.addRow();
  InlineKey.addButton("🌦️ Monitoring Humidity", InlineMenu2, CTBotKeyboardButtonQuery);
  InlineKey.addRow();
  InlineKey.addButton("🌱 Monitoring Soil Moisture", InlineMenu3, CTBotKeyboardButtonQuery);
  InlineKey.addRow();
  InlineKey.addButton("☀️ Monitoring Light Intensity", InlineMenu4, CTBotKeyboardButtonQuery);
  InlineKey.addRow();
  InlineKey.addButton("🚰 Controlling Water Pump", InlineMenu5, CTBotKeyboardButtonQuery);
  InlineKey.addRow();
  InlineOption.addButton("✅ Pump: Turn ON", ON, CTBotKeyboardButtonQuery);
  InlineOption.addButton("❌ Pump: Turn OFF", OFF, CTBotKeyboardButtonQuery);
  viewTombol = false; //Tombol -> default : hidden
}


void sendData() { //Baca data sensor dan mengirim ke Blynk
  //baca nilai sensor DHT22
  suhu_udara = dht.readTemperature();
  kelembapan_udara = dht.readHumidity();
  //baca nilai sensor FC-28
  kelembapan_tanah = fc28.getSoilMoisture();
  //baca nilai sensor LDR
  analogLDR = analogRead(LDR_PIN);
  volt = analogLDR * 5 / 4095.0;
  resistance = 2000 * volt / (1 - volt / 5);
  cahaya = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));
  Blynk.virtualWrite(V0, suhu_udara); 
  Blynk.virtualWrite(V1, kelembapan_udara);
  Blynk.virtualWrite(V2, kelembapan_tanah);
  Blynk.virtualWrite(V3, cahaya);
  TresholdSensorState();
  PrintLCD();
  botTelegram();
}


void TresholdSensorState(){ //batasan suhu, kelembapan, dan intensitas cahaya
  if (suhu_udara >= 0 && suhu_udara < 16) {
    if (kelembapan_udara > 90) {
      if (cahaya >= 500) {  
        info_suhuudara = "Suhu Udara: Rendah";               //Dingin
        info_kelembapanudara = "Kelembapan Udara: Tinggi";   //Basah
        info_intensitascahaya = "Intensitas Cahaya: Rendah"; //Gelap
        statusUdara = "Status Kualitas Udara: Bahaya";
        statusSinar = "Status Kualitas Sinar: Aman";
        digitalWrite(RPOMPA1_PIN, relayOFF);
        Blynk.virtualWrite(V4, 0);
      }
    }
  }
  if (suhu_udara >= 16 && suhu_udara <= 34) {
    if (kelembapan_udara >= 30 && kelembapan_udara <= 90) {
      if (cahaya >= 200 && cahaya < 500) {  
        info_suhuudara = "Suhu Udara: Normal";               //Remang-remang
        info_kelembapanudara = "Kelembapan Udara: Normal";   //Lembap
        info_intensitascahaya = "Intensitas Cahaya: Normal"; //Remang-remang
        statusUdara = "Status Kualitas Udara: Aman";
        statusSinar = "Status Kualitas Sinar: Aman";
        digitalWrite(RPOMPA1_PIN, relayOFF);
        Blynk.virtualWrite(V4, 0);
      }
    }
  }
  if (suhu_udara > 34 && kelembapan_udara < 30) {
    if (cahaya < 200) {
      info_suhuudara = "Suhu Udara: Tinggi";                 //Panas
      info_kelembapanudara = "Kelembapan Udara: Rendah";     //Kering
      info_intensitascahaya = "Intensitas Cahaya: Tinggi";   //Cerah
      statusUdara = "Status Kualitas Udara: Bahaya";
      statusSinar = "Status Kualitas Sinar: Bahaya";
      digitalWrite(RPOMPA1_PIN, relayON);
      Blynk.virtualWrite(V4, 1);
    }
  } 
  if (kelembapan_tanah >= 14.5 && kelembapan_tanah < 100){
    info_kelembapantanah = "Kelembapan Tanah: Tinggi";      //Basah
    statusTanah = "Status Kualitas Tanah: Bahaya";
    digitalWrite(RPOMPA1_PIN, relayOFF);
    Blynk.virtualWrite(V4, 0);
  }
  if (kelembapan_tanah >= 11.8 && kelembapan_tanah < 14.5) { 
    info_kelembapantanah = "Kelembapan Tanah: Normal";      //Lembap
    statusTanah = "Status Kualitas Tanah: Aman";
    digitalWrite(RPOMPA1_PIN, relayOFF);
    Blynk.virtualWrite(V4, 0);
  }
  if (kelembapan_tanah >= 0 && kelembapan_tanah < 11.8) {
    info_kelembapantanah = "Kelembapan Tanah: Rendah";     //Kering
    statusTanah = "Status Kualitas Tanah: Bahaya";
    digitalWrite(RPOMPA1_PIN, relayON);
    Blynk.virtualWrite(V4, 1);
  }
}


void botTelegram() {
  if( millis() - durasi > jeda ){
    durasi = millis();

    sendData(); //Memanggil method sendData
    connectBot(); //Memanggil method connectBot
    TBMessage msg; //Constructor TBMessage
    
    if(myBot.getNewMessage(msg)){  
      if(msg.text.equalsIgnoreCase("/start")){ //Start Bot
        msg1 = "🙋🏻‍♂️ Hai @" + msg.sender.username + " 👋👋\nSelamat datang di Layanan BOT ECHEVERIA.";
        msg2 = "\n\n🔐 Silahkan isi kode rahasia 👇👇\n.................................. *(13 Characters)";
        sendMsg = msg1 + msg2; myBot.sendMessage(msg.sender.id, sendMsg);
      } 
      else if(msg.text.equalsIgnoreCase(KodeBot)){ //Menu Utama
        msg1 = "🔓 Kode yang anda masukkan benar";
        myBot.sendMessage(msg.sender.id, msg1);
        main_menu:
        msg2 = "\n--------------------------------------------------------------\n 📝 MENU UTAMA \n--------------------------------------------------------------\nSilahkan pilih menu dibawah ini 👇👇";
        viewTombol = true; myBot.sendMessage(msg.sender.id, msg2, InlineKey);
      }
      else if(msg.messageType == CTBotMessageQuery){ //Respon Inline Button
        if(msg.callbackQueryData.equals(InlineMenu1)){ //Menampilkan data monitoring suhu udara
          Serial.println("\n<------------------------------->");
          Serial.println("Deteksi Suhu Udara: " + String(suhu_udara, 2) + "°C");
          Serial.println(info_suhuudara);
          Serial.println(statusUdara);
          Serial.println("<------------------------------->\n");
          msg1 = "🙋🏻‍♂️ Hai @" + msg.sender.username + " 👋👋\nBerikut hasil monitoring suhu udara pada tanaman echeveria terkini:\n\n--------------------------------------------------------------\n 🌤️ MONITORING TEMPERATURE \n--------------------------------------------------------------\n";
          msg2 = "📲 Suhu udara tanaman: " + String(suhu_udara) + "°C\n✍️ " + String(statusUdara) + "\n--------------------------------------------------------------"; 
          sendMsg = msg1 + msg2; myBot.sendMessage(msg.sender.id, sendMsg);
        }
        else if(msg.callbackQueryData.equals(InlineMenu2)){ //Menampilkan data monitoring kelembapan udara
          Serial.println("\n<------------------------------->");
          Serial.println("Deteksi Kelembapan Udara: " + String(kelembapan_udara) + "%");
          Serial.println(info_kelembapanudara);
          Serial.println(statusUdara);
          Serial.println("<------------------------------->\n");
          msg1 = "🙋🏻‍♂️ Hai @" + msg.sender.username + " 👋👋\nBerikut hasil monitoring kelembapan udara pada tanaman echeveria terkini:\n\n--------------------------------------------------------------\n 🌦️ MONITORING HUMIDITY \n--------------------------------------------------------------\n";
          msg2 = "📲 Kelembapan udara tanaman: " + String(kelembapan_udara) + "%\n✍️ " + String(statusUdara) + "\n--------------------------------------------------------------"; 
          sendMsg = msg1 + msg2; myBot.sendMessage(msg.sender.id, sendMsg);
        }
        else if(msg.callbackQueryData.equals(InlineMenu3)){ //Menampilkan data monitoring kelembapan tanah
          Serial.println("\n<------------------------------->");
          Serial.println("Deteksi Kelembapan Tanah: " + String(kelembapan_tanah) + "%");
          Serial.println(info_kelembapantanah);
          Serial.println(statusTanah);
          Serial.println("<------------------------------->\n");
          msg1 = "🙋🏻‍♂️ Hai @" + msg.sender.username + " 👋👋\nBerikut hasil monitoring kelembapan tanah pada tanaman echeveria terkini:\n\n--------------------------------------------------------------\n 🌱 MONITORING SOIL MOISTURE \n--------------------------------------------------------------\n";
          msg2 = "📲 Kelembapan tanah tanaman: " + String(kelembapan_tanah) + "%\n✍️ " + String(statusTanah) + "\n--------------------------------------------------------------"; 
          sendMsg = msg1 + msg2; myBot.sendMessage(msg.sender.id, sendMsg);
        }
        else if(msg.callbackQueryData.equals(InlineMenu4)){ //Menampilkan data monitoring intensitas cahaya
          Serial.println("\n<------------------------------->");
          Serial.println("Deteksi Cahaya: " + String(cahaya) + "lx");
          Serial.println(info_intensitascahaya);
          Serial.println(statusSinar);
          Serial.println("<------------------------------->\n");
          msg1 = "🙋🏻‍♂️ Hai @" + msg.sender.username + " 👋👋\nBerikut hasil monitoring cahaya pada tanaman echeveria terkini:\n\n--------------------------------------------------------------\n ☀️ MONITORING LIGHT INTENSITY \n--------------------------------------------------------------\n";
          msg2 = "📲 Cahaya tanaman: " + String(cahaya) + "lx\n✍️ " + String(statusSinar) + "\n--------------------------------------------------------------"; 
          sendMsg = msg1 + msg2; myBot.sendMessage(msg.sender.id, sendMsg);
        }
        else if(msg.callbackQueryData.equals(InlineMenu5)){ //Opsi controlling
          sendMsg = "🙋🏻‍♂️ Hai @" + msg.sender.username + " 👋👋\nPilihlah opsi controlling berikut:\n";
          myBot.sendMessage(msg.sender.id, sendMsg, InlineOption);
        }
        else if(msg.callbackQueryData.equals(ON)){ //Memberikan perintah untuk menyalakan pompa 2
          Blynk.virtualWrite(V5, 1);
          Serial.println("\n<------------------------------->");
          Serial.println("Status kontrol air: On");
          Serial.println("<------------------------------->");
          msg1 = "🙋🏻‍♂️ Hai @" + msg.sender.username + " 👋👋\nBerikut hasil controlling pompa air pada tanaman echeveria terkini:\n\n--------------------------------------------------------------\n 🚰 CONTROLLING WATER PUMP \n--------------------------------------------------------------\n";
          msg2 = "📲 Controlling water pump: ON\n--------------------------------------------------------------"; 
          sendMsg = msg1 + msg2; myBot.sendMessage(msg.sender.id, sendMsg);
          digitalWrite(RPOMPA2_PIN, relayON);
        }
        else if(msg.callbackQueryData.equals(OFF)){ //Memberikan perintah untuk menyalakan pompa 2
          Blynk.virtualWrite(V5, 0);
          Serial.println("\n<------------------------------->");
          Serial.println("Status kontrol air: Off");
          Serial.println("<------------------------------->");
          msg1 = "🙋🏻‍♂️ Hai @" + msg.sender.username + " 👋👋\nBerikut hasil controlling pompa air pada tanaman echeveria terkini:\n\n--------------------------------------------------------------\n 🚰 CONTROLLING WATER PUMP \n--------------------------------------------------------------\n";
          msg2 = "📲 Controlling water pump: OFF\n--------------------------------------------------------------"; 
          sendMsg = msg1 + msg2; myBot.sendMessage(msg.sender.id, sendMsg);
          digitalWrite(RPOMPA2_PIN, relayOFF);
        }
      }
      else{ //Control Error jika perintah tidak sesuai
        sendMsg = "🙋🏻‍♂️ Hai @" + msg.sender.username + " 👋👋\n\n❌ Gagal mengakses, coba lagi";
        myBot.sendMessage(msg.sender.id, sendMsg);
      } 
    }
  }
}


void LCDinit(){ //Memulai komunikasi serial dengan LCD
  lcd.init();
  //start LCD
  lcd.clear(); lcd.backlight(); lcd.setCursor(1,0); lcd.print("Starting"); lcd.setCursor(1,1); lcd.print("Smart System..."); delay(2500);
  //welcome LCD
  lcd.clear(); lcd.backlight(); lcd.setCursor(1,0); lcd.print("Welcome to"); lcd.setCursor(1,1); lcd.print("Echeveria BoT..."); delay(2500);
  //loading
  lcd.clear(); lcd.backlight(); lcd.setCursor(1,0); lcd.print("Loading...."); delay(5000);
}


void PrintLCD(){ //Menampilkan data ke LCD
  lcd.clear(); lcd.backlight(); lcd.setCursor(1,0); lcd.print("Suhu Udara:"); lcd.setCursor(1,1); lcd.print(""+String(suhu_udara)+" "+String((char)223)+"C"); delay(1000);
  lcd.clear(); lcd.backlight(); lcd.setCursor(1,0); lcd.print("Kelem.Udara:"); lcd.setCursor(1,1); lcd.print(""+String(kelembapan_udara)+" %"); delay(1000);
  lcd.clear(); lcd.backlight(); lcd.setCursor(1,0); lcd.print("Kelem.Tanah:"); lcd.setCursor(1,1); lcd.print(""+String(kelembapan_tanah)+" %"); delay(1000);
  lcd.clear(); lcd.backlight(); lcd.setCursor(1,0); lcd.print("Int.Cahaya:"); lcd.setCursor(1,1); lcd.print(""+String(cahaya)+" lx"); delay(1000);
}


void setup() { //Fungsi yang dijalankan sekali
  Serial.begin(SERIAL_DEBUG_BAUD);
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);
  ButtonBot();
  fc28.initFC28Sensor(SERIAL_DEBUG_BAUD, FC28_PIN);
  dht.begin();
  pinMode(LDR_PIN, INPUT);
  pinMode(FC28_PIN, INPUT);
  pinMode(DHT_PIN, INPUT);
  pinMode(RPOMPA1_PIN, OUTPUT);
  pinMode(RPOMPA2_PIN, OUTPUT);
  digitalWrite(RPOMPA1_PIN, relayOFF);
  digitalWrite(RPOMPA2_PIN, relayOFF);
  LCDinit();
  timer.setInterval(1000L, sendData);
}


void loop() { //Fungsi yang dijalankan berulang kali
  Blynk.run();
  timer.run();
}
