
void cekSensor(){
if (!sht31.begin(0x44)) {  // Inisialisasi sensor SHT31 dengan alamat I2C 0x44
    Serial.println("Gagal menemukan sensor SHT31");
    while (1) delay(1);
  }
}
void sensorSHT31() {
 float tempC = sht31.readTemperature();
 float humi = sht31.readHumidity();
  
  if (isnan(tempC) || isnan(humi)) {
    Serial.println("Failed to read from SHT31 sensor!");
  } else {
    Serial.print("SHT31# Temperature: "); //perlu kah atau tidak
    Serial.print(tempC);
    Serial.print("°C  |  Humidity: ");
    Serial.print(humi);
    Serial.println("%");
  }
}
