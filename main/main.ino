#include <SPI.h>
#include <Wire.h>
#include <Servo.h>
#include <String.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "src/HCSR04/HCSR04.h"

#define SCREEN_WIDTH 128  // OLED 寬度像素
#define SCREEN_HEIGHT 64  // OLED 高度像素

// 設定OLED
#define OLED_RESET 4  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

HCSR04 HCSR04(7, 6);
Servo myservo;

void setup() {
  Serial.begin(9600);
  HCSR04.begin();
  myservo.attach(4);

  // 偵測是否安裝好OLED了
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // 一般1306 OLED的位址都是0x3C
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }

  text("CodeCat");
  delay(1000);
  display.clearDisplay();
}

void loop() {
  int dis = HCSR04.distance();
  Serial.println("dis: " + dis);

  if (20 > dis) {
    text("Press\nButton\n\nowo");
    while (1) {
      Serial.println("state: wait for button");
      if (digitalRead(2)) {
        myservo.write(60);
        for (int i = 5; i >= 0; i--) {
          text(String(i));
          delay(1000);
        }
        myservo.write(150);
        text("CodeCat");
        break;
      }
    }
  }
}

void text(String s) {
  Serial.println("show: " + s);
  display.clearDisplay();
  display.setTextSize(2);       // 設定文字大小
  display.setTextColor(1);      // 1:OLED預設的顏色(這個會依該OLED的顏色來決定)
  display.setCursor(0, 0);      // 設定起始座標
  display.print(s);  // 要顯示的字串
  display.display();            // 要有這行才會把文字顯示出來
}
