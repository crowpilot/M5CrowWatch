//#pragma mark - Depend ESP8266Audio and ESP8266_Spiram libraries
/*
  cd ~/Arduino/libraries
  git clone https://github.com/earlephilhower/ESP8266Audio
  git clone https://github.com/Gianbacchio/ESP8266_Spiram

  Use the "Tools->ESP32 Sketch Data Upload" menu to write the MP3 to SPIFFS
  Then upload the sketch normally.
  https://github.com/me-no-dev/arduino-esp32fs-plugin
*/

#include "FS.h"
#include <M5Stack.h>
#include <WiFi.h>
#include "time.h"
#include "SPIFFS.h"
#include "AudioFileSourceSPIFFS.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"


AudioGeneratorMP3 *mp3;
AudioFileSourceSPIFFS *file;
AudioOutputI2S *out;
AudioFileSourceID3 *id3;

struct tm timeinfo;

void setup()
{
  M5.begin(true, false, false, false);
  M5.Power.begin();
  //WiFi.mode(WIFI_OFF);
  SPIFFS.begin();
  delay(500);

  M5.Lcd.drawJpgFile(SPIFFS, "/crow.jpg", 0, 0);

  //delay(10000);

  M5.Lcd.setTextFont(2);
  //M5.Lcd.printf("Sample MP3 playback begins...\n");
  //Serial.printf("Sample MP3 playback begins...\n");

  char ssid[40];
  char password[40];
  String buf;

  File f = SPIFFS.open("/config.txt");
  buf = f.readStringUntil('\n');
  buf.toCharArray(ssid,40);
  buf =f.readStringUntil('\n');
  buf.toCharArray(password,40);
  f.close();
  //M5.lcd.println(ssid);
  //M5.lcd.println(password);

  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
  }
  //M5.Lcd.println(WiFi.localIP());
  configTime(3600*9,0,"ntp.nict.jp","ntp.jst.mfeed.ad.jp");
  M5.Lcd.setTextSize(4);
}

void caw(){
  file = new AudioFileSourceSPIFFS("/crow3.mp3");
  id3 = new AudioFileSourceID3(file);
  out = new AudioOutputI2S(0, 1); // Output to builtInDAC
  out->SetOutputModeMono(true);
  mp3 = new AudioGeneratorMP3();
  mp3->begin(id3, out);
  while(mp3->isRunning()){
    if(!mp3->loop()){
      mp3->stop();
    }
  }
}

void loop()
{
//caw();
  static int flg;
  if(!getLocalTime(&timeinfo)){
     return;
  }
  M5.Lcd.setCursor(50,180);
  M5.Lcd.printf("%02d:%02d",timeinfo.tm_hour,timeinfo.tm_min);

  if(timeinfo.tm_min%30 != 0){
    flg=1;
  }

  if((timeinfo.tm_min%60 == 0 )and (flg==1)){
    for(int i=0;i<timeinfo.tm_hour;i++){
      caw();
    }
    flg=0;
  }else if((timeinfo.tm_min%30==0 )and (flg==1)){
    caw();
    flg=0;
  }
  
  //caw();
}
