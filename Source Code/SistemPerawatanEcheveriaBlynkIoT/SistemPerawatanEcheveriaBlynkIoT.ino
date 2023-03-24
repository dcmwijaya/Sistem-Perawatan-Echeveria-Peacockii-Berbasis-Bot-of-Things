//Deklarasi Library/Konstanta/Dsb
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLV3XY2rl8"
#define BLYNK_DEVICE_NAME "Echeveria"
#define BLYNK_AUTH_TOKEN "yX9Ep64CmR0ZfOQSA7PD7tJNzUZDzKzS"
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
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define LDR_PIN 35
#define FC28_PIN 34
#define DHT_PIN 13
#define RPOMPA1_PIN 2
#define RPOMPA2_PIN 4
#define DHT_TYPE DHT22
DHT dht(DHT_PIN, DHT_TYPE);
#define WIFI_SSID "ISI DENGAN NAMA ROUTER ANDA"
#define WIFI_PASSWORD "ISI DENGAN PASSWORD ROUTER ANDA"
#define BOTtoken "5911801402:AAFEEuBYHPmDxlYQxfPpTCZkRpn5d8hV_3E"
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
int soilmeasurement = 0;
const float GAMMA = 0.7; const float RL10 = 50;
int kontrolair, analogLDR, analogFC28, value, kelembapan_udara, kelembapan_tanah; 
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
  
  //baca nilai analog sensor FC-28
  analogFC28 = analogRead(FC28_PIN);
  //percentage Range: 90-100
  if (analogFC28 >= 1300){ value = 100; } else if (analogFC28 >= 1287 && analogFC28 < 1300){ value = 99; } else if (analogFC28 >= 1274 && analogFC28 < 1287){ value = 98; } else if (analogFC28 >= 1261 && analogFC28 < 1274){ value = 97; } else if (analogFC28 >= 1248 && analogFC28 < 1261){ value = 96; } else if (analogFC28 >= 1235 && analogFC28 < 1248){ value = 95; } else if (analogFC28 >= 1222 && analogFC28 < 1235){ value = 94; } else if (analogFC28 >= 1209 && analogFC28 < 1222){ value = 93; } else if (analogFC28 >= 1196 && analogFC28 < 1209){ value = 92; } else if (analogFC28 >= 1183 && analogFC28 < 1196){ value = 91; }
  //percentage Range: 81-90
  if (analogFC28 >= 1170 && analogFC28 < 1183){ value = 90; } else if (analogFC28 >= 1157 && analogFC28 < 1170){ value = 89; } else if (analogFC28 >= 1144 && analogFC28 < 1157){ value = 88; } else if (analogFC28 >= 1131 && analogFC28 < 1144){ value = 87; } else if (analogFC28 >= 1118 && analogFC28 < 1131){ value = 86; } else if (analogFC28 >= 1105 && analogFC28 < 1118){ value = 85; } else if (analogFC28 >= 1092 && analogFC28 < 1105){ value = 84; } else if (analogFC28 >= 1079 && analogFC28 < 1092){ value = 83; } else if (analogFC28 >= 1066 && analogFC28 < 1079){ value = 82; } else if (analogFC28 >= 1053 && analogFC28 < 1066){ value = 81; }
  //percentage Range: 71-80
  if (analogFC28 >= 1040 && analogFC28 < 1053){ value = 80; } else if (analogFC28 >= 1027 && analogFC28 < 1040){ value = 79; } else if (analogFC28 >= 1014 && analogFC28 < 1027){ value = 78; } else if (analogFC28 >= 1001 && analogFC28 < 1014){ value = 77; } else if (analogFC28 >= 988 && analogFC28 < 1001){ value = 76; } else if (analogFC28 >= 975 && analogFC28 < 988){ value = 75; } else if (analogFC28 >= 962 && analogFC28 < 975){ value = 74; } else if (analogFC28 >= 949 && analogFC28 < 962){ value = 73; } else if (analogFC28 >= 936 && analogFC28 < 949){ value = 72; } else if (analogFC28 >= 923 && analogFC28 < 936){ value = 71; }
  //percentage Range: 61-70
  if (analogFC28 >= 910 && analogFC28 < 923){ value = 70; } else if (analogFC28 >= 897 && analogFC28 < 910){ value = 69; } else if (analogFC28 >= 884 && analogFC28 < 897){ value = 68; } else if (analogFC28 >= 871 && analogFC28 < 884){ value = 67; } else if (analogFC28 >= 858 && analogFC28 < 871){ value = 66; } else if (analogFC28 >= 845 && analogFC28 < 858){ value = 65; } else if (analogFC28 >= 832 && analogFC28 < 845){ value = 64; } else if (analogFC28 >= 819 && analogFC28 < 832){ value = 63; } else if (analogFC28 >= 806 && analogFC28 < 819){ value = 62; } else if (analogFC28 >= 793 && analogFC28 < 806){ value = 61; }
  //percentage Range: 51-60
  if (analogFC28 >= 780 && analogFC28 < 793){ value = 60; } else if (analogFC28 >= 767 && analogFC28 < 780) { value = 59; } else if (analogFC28 >= 754 && analogFC28 < 767) { value = 58; } else if (analogFC28 >= 741 && analogFC28 < 754) { value = 57; } else if (analogFC28 >= 728 && analogFC28 < 741) { value = 56; } else if (analogFC28 >= 715 && analogFC28 < 728) { value = 55; } else if (analogFC28 >= 702 && analogFC28 < 715) { value = 54; } else if (analogFC28 >= 689 && analogFC28 < 702) { value = 53; } else if (analogFC28 >= 676 && analogFC28 < 689) { value = 52; } else if (analogFC28 >= 663 && analogFC28 < 676) { value = 51; } 
  //percentage Range: 41-50
  if (analogFC28 >= 650 && analogFC28 < 663) { value = 50; } else if (analogFC28 >= 637 && analogFC28 < 650) { value = 49; } else if (analogFC28 >= 624 && analogFC28 < 637) { value = 48; } else if (analogFC28 >= 611 && analogFC28 < 624) { value = 47; } else if (analogFC28 >= 598 && analogFC28 < 611) { value = 46; } else if (analogFC28 >= 585 && analogFC28 < 598) { value = 45; } else if (analogFC28 >= 572 && analogFC28 < 585) { value = 44; } else if (analogFC28 >= 559 && analogFC28 < 572) { value = 43; } else if (analogFC28 >= 546 && analogFC28 < 559) { value = 42; } else if (analogFC28 >= 533 && analogFC28 < 546) { value = 41; }
  //percentage Range: 31-40
  if (analogFC28 >= 520 && analogFC28 < 533) { value = 40; } else if (analogFC28 >= 507 && analogFC28 < 520) { value = 39; } else if (analogFC28 >= 494 && analogFC28 < 507) { value = 38; } else if (analogFC28 >= 481 && analogFC28 < 494) { value = 37; } else if (analogFC28 >= 468 && analogFC28 < 481) { value = 36; } else if (analogFC28 >= 455 && analogFC28 < 468) { value = 35; } else if (analogFC28 >= 442 && analogFC28 < 455) { value = 34; } else if (analogFC28 >= 429 && analogFC28 < 442) { value = 33; } else if (analogFC28 >= 416 && analogFC28 < 429) { value = 32; } else if (analogFC28 >= 403 && analogFC28 < 416) { value = 31; }
  //percentage Range: 21-30
  if (analogFC28 >= 390 && analogFC28 < 403) { value = 30; } else if (analogFC28 >= 377 && analogFC28 < 390) { value = 29; } else if (analogFC28 >= 364 && analogFC28 < 377) { value = 28; } else if (analogFC28 >= 351 && analogFC28 < 364) { value = 27; } else if (analogFC28 >= 338 && analogFC28 < 351) { value = 26; } else if (analogFC28 >= 325 && analogFC28 < 338) { value = 25; } else if (analogFC28 >= 312 && analogFC28 < 325) { value = 24; } else if (analogFC28 >= 299 && analogFC28 < 312) { value = 23; } else if (analogFC28 >= 286 && analogFC28 < 299) { value = 22; } else if (analogFC28 >= 273 && analogFC28 < 286) { value = 21; }
  //percentage Range: 11-20
  if (analogFC28 >= 260 && analogFC28 < 273) { value = 20; } else if (analogFC28 >= 247 && analogFC28 < 260) { value = 19; } else if (analogFC28 >= 234 && analogFC28 < 247) { value = 18; } else if (analogFC28 >= 221 && analogFC28 < 234) { value = 17; } else if (analogFC28 >= 208 && analogFC28 < 221) { value = 16; } else if (analogFC28 >= 195 && analogFC28 < 208) { value = 15; } else if (analogFC28 >= 182 && analogFC28 < 195) { value = 14; } else if (analogFC28 >= 169 && analogFC28 < 182) { value = 13; } else if (analogFC28 >= 156 && analogFC28 < 169) { value = 12; } else if (analogFC28 >= 143 && analogFC28 < 156) { value = 11; }
  //percentage Range: 0-10
  if (analogFC28 >= 130  && analogFC28 < 143) { value = 10; } else if (analogFC28 >= 117 && analogFC28 < 130) { value = 9; } else if (analogFC28 >= 104 && analogFC28 < 117) { value = 8; } else if (analogFC28 >= 91 && analogFC28 < 104) { value = 7; } else if (analogFC28 >= 78 && analogFC28 < 91) { value = 6; } else if (analogFC28 >= 65 && analogFC28 < 78) { value = 5; } else if (analogFC28 >= 52 && analogFC28 < 65) { value = 4; } else if (analogFC28 >= 39 && analogFC28 < 52) { value = 3; } else if (analogFC28 >= 26 && analogFC28 < 39) { value = 2; } else if (analogFC28 >= 13 && analogFC28 < 26) { value = 1; } else if (analogFC28 < 13) { value = 0; }
  //nilai kelembapan tanah
  kelembapan_tanah = map(value, 0, 100, 0, 100);
  
  //baca nilai sensor LDR
  analogLDR = analogRead(LDR_PIN);
  volt = analogLDR * 5 / 4095.0;
  resistance = 2000 * volt / (1 - volt / 5);
  cahaya = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));

  //kirim data ke Blynk
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
      if (cahaya >= 0 && cahaya < 50) {  
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
      if (cahaya >= 50 && cahaya < 50000) {  
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
    if (cahaya >= 50000 && cahaya <= 100000) {
      info_suhuudara = "Suhu Udara: Tinggi";                 //Panas
      info_kelembapanudara = "Kelembapan Udara: Rendah";     //Kering
      info_intensitascahaya = "Intensitas Cahaya: Tinggi";   //Cerah
      statusUdara = "Status Kualitas Udara: Bahaya";
      statusSinar = "Status Kualitas Sinar: Bahaya";
      digitalWrite(RPOMPA1_PIN, relayON);
      Blynk.virtualWrite(V4, 1);
    }
  } 
  if (kelembapan_tanah >= 70 && kelembapan_tanah < 100){
    info_kelembapantanah = "Kelembapan Tanah: Tinggi";      //Basah
    statusTanah = "Status Kualitas Tanah: Bahaya";
    digitalWrite(RPOMPA1_PIN, relayOFF);
    Blynk.virtualWrite(V4, 0);
  }
  if (kelembapan_tanah >= 20 && kelembapan_tanah < 70){
    info_kelembapantanah = "Kelembapan Tanah: Normal";      //Lembap
    statusTanah = "Status Kualitas Tanah: Aman";
    digitalWrite(RPOMPA1_PIN, relayOFF);
    Blynk.virtualWrite(V4, 0);
  }
  if (kelembapan_tanah >= 0 && kelembapan_tanah < 20){
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
