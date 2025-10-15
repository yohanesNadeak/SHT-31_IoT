void intRtc() {
  if (!rtc.begin()) {
    Serial.println("RTC tidak ditemukan");
    while (1) delay(100);
  }
}

void ambilWaktu() {
  DateTime now = rtc.now() + TimeSpan(0, 0, 0, 20);
  sprintf(tanggal, "%02d/%02d/%04d %02d:%02d:%02d",
          now.day(), now.month(), now.year(),
          now.hour(), now.minute(), now.second());
  Serial.println(tanggal);
}