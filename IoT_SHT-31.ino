#define BLYNK_TEMPLATE_ID "TMPL6zm9_tUzt"
#define BLYNK_TEMPLATE_NAME "Mentoring SHT31"
#define BLYNK_AUTH_TOKEN "RL8c7s-Aph-0ZPvpmqCWl8DFWDos2my9"
#define BLYNK_PRINT Serial
#include <SD.h>              //Library Micro SD
#include <FS.h>              //Library Micro SD
#include <Wire.h>            //Library komunikasi I2C
#include "RTClib.h"          //library RTC
#include "variabel.h"        //Variabel data tanggal
#include <Adafruit_SHT31.h>  //Library sensor SHT31
#include <Adafruit_Sensor.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiManager.h>
#include <BlynkSimpleEsp32.h>
#include "ThingSpeak.h"

#define uS_TO_S_FACTOR 1000000ULL  //mengonversi waktu dari mikrodetik ke detik.
#define TIME_TO_SLEEP 15           //waktu dalam detik (15 detik) esp akan tidur
RTC_DATA_ATTR int bootCount = 0;   //menghitung jumlah kali perangkat telah booting.

RTC_DS3231 rtc;  //Objek RTC
File myFile;     //Objek MICRO SD
Adafruit_SHT31 sht31 = Adafruit_SHT31();

//char ssid[] = "zzzz";
//char pass[] = "anesssss";

unsigned long myChannelNumber = 3088707;
const char* myWriteAPIKey = "FQUW834C7OV1TVOH";

const int LED1 = 4;
const int LED2 = 2;

BlynkTimer timer;
WiFiClient client;

void print_wakeup_reason();
void myTimerEvent();

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.begin(115200);  //Memulai komunikasi Serial
  Wire.begin();
  intRtc();      //Menghubungkan ke RTC
  intMicroSD();  //Menghubungkan Ke MicroSD
  cekSensor();

  WiFi.mode(WIFI_STA);

  WiFiManager wm;

  bool res = wm.autoConnect("ESP-32 Yohanes", "anesssss");

  if (!res) {
    Serial.println("Gagal terhubung, restart ESP");
    delay(3000);
    ESP.restart();
  } else {
    Serial.println("Terhubung ke WiFi :)");
  }

  ThingSpeak.begin(client);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); //untuk wifi manual
  Blynk.config(BLYNK_AUTH_TOKEN);

  timer.setInterval(1000L, myTimerEvent);  // Atur timer yang memanggil fungsi myTimerEvent setiap 3000 ms (3 detik)

  ambilWaktu();       //Mengambil waktu
  sensorSHT31();      //Membaca sensor SHT31
  simpanDatawaktu();  //Menyimpan data ke microSD
}

void loop() {
  //espmauBobo();
  Blynk.run();
  timer.run();  // Mengecek dan menjalankan timer yang aktif

  //delay(3000);         //jeda 0,8 detik
  tidur();
}
