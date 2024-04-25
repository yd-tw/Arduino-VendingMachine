#include <SPI.h>
#include <Wire.h>
#include <Servo.h>
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
  codecat();
  delay(1000);

  // 清除畫面
  display.clearDisplay();

  // 測試文字
}

void loop() {


  if (20 > HCSR04.distance()) {
    testdraw();
    while (1) {
      if (digitalRead(2)) {
        myservo.write(60);
        for (int i = 5; i >= 0; i--) {
          testdrawstyles(i);
          delay(1000);
        }
        myservo.write(150);
        codecat();
        break;
      }
    }
  }
}

void testdrawstyles(int x) {
  display.clearDisplay();
  display.setTextSize(2);       // 設定文字大小
  display.setTextColor(1);      // 1:OLED預設的顏色(這個會依該OLED的顏色來決定)
  display.setCursor(0, 0);      // 設定起始座標
  display.print(x);  // 要顯示的字串
  display.display();            // 要有這行才會把文字顯示出來
}

void testdraw() {
  display.clearDisplay();
  display.setTextSize(2);       // 設定文字大小
  display.setTextColor(1);      // 1:OLED預設的顏色(這個會依該OLED的顏色來決定)
  display.setCursor(0, 0);      // 設定起始座標
  display.print("Press\nButton\n\nowo");  // 要顯示的字串
  display.display();            // 要有這行才會把文字顯示出來
}

void codecat() {
  display.clearDisplay();
  display.setTextSize(2);       // 設定文字大小
  display.setTextColor(1);      // 1:OLED預設的顏色(這個會依該OLED的顏色來決定)
  display.setCursor(0, 0);      // 設定起始座標
  display.print("CodeCat");  // 要顯示的字串
  display.display();            // 要有這行才會把文字顯示出來
}
