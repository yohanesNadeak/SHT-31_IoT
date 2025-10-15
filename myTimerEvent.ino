void myTimerEvent() {
  sensorSHT31();  // Membaca sensor SHT31 secara berkala
  ambilWaktu();   // Menampilkan waktu
 float tempC = sht31.readTemperature();
 float humi = sht31.readHumidity();
  if (!isnan(humi) && !isnan(tempC)) {
    // Kirim data ke Blynk
    Blynk.virtualWrite(V0, tempC);
    Blynk.virtualWrite(V1, humi);

    Serial.print(F("Kelembapan: "));
    Serial.print(humi);
    Serial.print(F("%  Suhu: "));
    Serial.print(tempC);
    Serial.println(F("°C"));

    // Kontrol LED indikator suhu >= 35°C
    //if (t >= 35) {
    //Blynk.virtualWrite(V2, HIGH);
    //digitalWrite(LED1, HIGH);
    //} else {
    //Blynk.virtualWrite(V2, LOW);
    //digitalWrite(LED1, LOW);
    //}

    // Kirim data ke ThingSpeak
    ThingSpeak.setField(1, tempC);
    ThingSpeak.setField(2, humi);

    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if (x == 200) {
      Serial.println("Update channel ThingSpeak berhasil.");
      digitalWrite(LED2, HIGH);
    } else {
      Serial.println("Gagal update channel ThingSpeak, kode HTTP: " + String(x));
      digitalWrite(LED2, LOW);
    }
  } else {
    Serial.println("Gagal membaca sensor SHT31!");
  }

  simpanDatawaktu();  // Menyimpan data ke microSD


  //buka

  //simpan http code


  //close
}