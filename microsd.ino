void intMicroSD() {
  while (!Serial) {  //Tunggu hingga koneksi Serial Monitor
    ;
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(5)) {  //Pin CS microSD = 5
    Serial.println("initialization failed!");
    while (1)
      ;
  }
  Serial.println("initialization done.");
}

void simpanDatawaktu() {
   float tempC = sht31.readTemperature();
 float humi = sht31.readHumidity();
  myFile = SD.open("/SHT31.txt", FILE_APPEND);
  if (myFile) {
    myFile.print(tanggal);
    myFile.print(", ");
    myFile.print(tempC);
    myFile.print(", ");
    myFile.println(humi);
    digitalWrite(LED1, 0);
    Serial.println("Data disimpan");
    myFile.close();

  } else {
    Serial.println("gagal membuka waktu.txt");
    digitalWrite(LED1, 1);
  }
}