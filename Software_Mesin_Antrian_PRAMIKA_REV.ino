#include "RTClib.h"              /* https://downloads.arduino.cc/libraries/github.com/adafruit/RTClib-2.1.4.zip */
#include <EEPROM.h>
#include "Adafruit_Thermal.h"    /* https://downloads.arduino.cc/libraries/github.com/adafruit/Adafruit_Thermal_Printer_Library-1.4.1.zip */
#include "SoftwareSerial.h"
#include <LiquidCrystal_I2C.h>   /* https://downloads.arduino.cc/libraries/github.com/johnrickman/LiquidCrystal_I2C-1.1.2.zip */

#define TX_PIN 8
#define RX_PIN 9

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);

LiquidCrystal_I2C lcd(0x27, 16, 2);

RTC_DS3231 rtc;
DateTime now;
DateTime future;

char daysOfTheWeek[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};

int counter = 0, counter_besok, counter_reset = 0, Cek_Tanggal;

int mode = 1 ;
int loopp = 1,
    loopp_printer = 1;

#define Future_Button 4
#define Print_Button 5
#define diTekan LOW
#define Reset 0
#define LED_MODE1 10
#define LED_MODE2 11
#define LED_MODE3 12
#define Buzzer 13

byte addr = 4,
     addr_besok = 5,
     addr_CekTanggal = 6;

void Cetak_Antrian_Now() {
  while (loopp_printer <= 1) {
    //Thermal Printer Mencetak Struk
    printer.begin();

    printer.reset();
    printer.setDefault();

    printer.setTimes(100, 100);

    printer.justify('C');
    printer.setSize('L');
    printer.boldOn();
    printer.println("KLINIK UTAMA PRAMIKA");
    printer.boldOff();

    printer.justify('C');
    printer.setSize('S');
    printer.println(F("Jl.Mayjen Sutoyo No.10 Ponorogo"));
    printer.println(F("(0352 486054)\n"));

    DateTime now = rtc.now();
    printer.justify('C');
    printer.setSize('S');
    printer.print(daysOfTheWeek[now.dayOfTheWeek()]);
    printer.print(", ");
    printer.print(now.day());
    printer.print("-");
    printer.print(now.month());
    printer.print("-");
    printer.println(now.year());

    printer.print(now.hour());
    printer.print(":");
    printer.print(now.minute());
    printer.print(":");
    printer.println(now.second());
    printer.println("\n");

    if (counter < 10) {
      printer.justify('C');
      printer.setSize('L');
      printer.boldOn();
      printer.print("NO.");
      printer.print("00");
      printer.println(counter);
      printer.boldOff();
    }
    else if (counter >= 10 && counter < 100) {
      printer.justify('C');
      printer.setSize('L');
      printer.boldOn();
      printer.print("NO.");
      printer.print("0");
      printer.println(counter);
      printer.boldOff();
    }
    else if (counter >= 100) {
      printer.justify('C');
      printer.setSize('L');
      printer.boldOn();
      printer.print("NO.");
      printer.println(counter);
      printer.boldOff();
    }

    printer.justify('C');
    printer.setSize('S');
    printer.println(F("\nTerima Kasih"));

    printer.justify('C');
    printer.setSize('S');
    printer.boldOn();
    printer.println(F("\nNomor Antrian Tidak Boleh Dibawa Pulang"));
    printer.boldOff();

    printer.feed(10);
    printer.cutPaper();
    loopp_printer = 2;
  }
}

void Cetak_Antrian_NextShift() {
  while (loopp_printer <= 1) {
    //Thermal Printer Mencetak Struk
    printer.begin();

    printer.reset();
    printer.setDefault();

    printer.setTimes(100, 100);
    printer.justify('C');
    printer.setSize('L');
    printer.boldOn();
    printer.println("KLINIK UTAMA PRAMIKA");
    printer.boldOff();

    printer.justify('C');
    printer.setSize('S');
    printer.println(F("Jl.Mayjen Sutoyo No.10 Ponorogo"));
    printer.println(F("(0352 486054)\n"));

    DateTime now = rtc.now();
    printer.justify('C');
    printer.setSize('S');
    printer.print(daysOfTheWeek[now.dayOfTheWeek()]);
    printer.print(", ");
    printer.print(now.day());
    printer.print("-");
    printer.print(now.month());
    printer.print("-");
    printer.println(now.year());

    printer.print(now.hour());
    printer.print(":");
    printer.print(now.minute());
    printer.print(":");
    printer.println(now.second());
    printer.println("\n");

    if (counter < 10) {
      printer.justify('C');
      printer.setSize('L');
      printer.boldOn();
      printer.print("NO.");
      printer.print("00");
      printer.println(counter);
      printer.boldOff();
    }
    else if (counter >= 10 && counter < 100) {
      printer.justify('C');
      printer.setSize('L');
      printer.boldOn();
      printer.print("NO.");
      printer.print("0");
      printer.println(counter);
      printer.boldOff();
    }
    else if (counter >= 100) {
      printer.justify('C');
      printer.setSize('L');
      printer.boldOn();
      printer.print("NO.");
      printer.println(counter);
      printer.boldOff();
    }

    printer.justify('C');
    printer.setSize('S');
    printer.println(F("\n\nSilahkan Datang Kembali di Shift Selanjutnya"));

    printer.justify('C');
    printer.setSize('S');
    printer.println(F("\nTerima Kasih"));

    printer.justify('C');
    printer.setSize('S');
    printer.boldOn();
    printer.println(F("\nNomor Antrian Tidak Boleh Dibawa Pulang"));
    printer.boldOff();

    printer.feed(10);
    printer.cutPaper();
    loopp_printer = 2;
  }
}

void Cetak_Antrian_Besok() {
  while (loopp_printer <= 1) {
    //Thermal Printer Mencetak Struk
    printer.begin();

    printer.reset();
    printer.setDefault();

    printer.setTimes(100, 100);
    printer.justify('C');
    printer.setSize('L');
    printer.boldOn();
    printer.println("KLINIK UTAMA PRAMIKA");
    printer.boldOff();

    printer.justify('C');
    printer.setSize('S');
    printer.println(F("Jl.Mayjen Sutoyo No.10 Ponorogo"));
    printer.println(F("(0352 486054)\n"));

    DateTime now = rtc.now();
    printer.justify('C');
    printer.setSize('S');
    printer.print(daysOfTheWeek[now.dayOfTheWeek()]);
    printer.print(", ");
    printer.print(now.day());
    printer.print("-");
    printer.print(now.month());
    printer.print("-");
    printer.println(now.year());

    printer.print(now.hour());
    printer.print(":");
    printer.print(now.minute());
    printer.print(":");
    printer.println(now.second());
    printer.println("\n");

    if (counter_besok < 10) {
      printer.justify('C');
      printer.setSize('L');
      printer.boldOn();
      printer.print("NO.");
      printer.print("00");
      printer.println(counter_besok);
      printer.boldOff();
    }
    else if (counter_besok >= 10 && counter_besok < 100) {
      printer.justify('C');
      printer.setSize('L');
      printer.boldOn();
      printer.print("NO.");
      printer.print("0");
      printer.println(counter_besok);
      printer.boldOff();
    }
    else if (counter_besok >= 100) {
      printer.justify('C');
      printer.setSize('L');
      printer.boldOn();
      printer.print("NO.");
      printer.println(counter_besok);
      printer.boldOff();
    }

    printer.justify('C');
    printer.setSize('S');
    printer.println(F("\n\nSilahkan Datang Kembali Besok"));

    String Hari = daysOfTheWeek[now.dayOfTheWeek()];

    if (Hari == "Jum'at") {
      DateTime future (now + TimeSpan(3, 0, 0, 0));
      printer.justify('C');
      printer.setSize('S');
      printer.print("\nSenin");
      printer.print(", ");
      printer.print(future.day());
      printer.print("-");
      printer.print(future.month());
      printer.print("-");
      printer.println(future.year() );
    }
    else if (Hari == "Sabtu") {
      DateTime future (now + TimeSpan(2, 0, 0, 0));
      printer.justify('C');
      printer.setSize('S');
      printer.print("\nSenin");
      printer.print(", ");
      printer.print(future.day());
      printer.print("-");
      printer.print(future.month());
      printer.print("-");
      printer.println(future.year() );
    }
    else if (Hari == "Minggu") {
      DateTime future (now + TimeSpan(1, 0, 0, 0));
      printer.justify('C');
      printer.setSize('S');
      printer.print("\nSenin");
      printer.print(", ");
      printer.print(future.day());
      printer.print("-");
      printer.print(future.month());
      printer.print("-");
      printer.println(future.year() );
    }
    else {
      DateTime future (now + TimeSpan(1, 0, 0, 0));
      printer.justify('C');
      printer.setSize('S');
      printer.print("\nBesok");
      printer.print(", ");
      printer.print(future.day());
      printer.print("-");
      printer.print(future.month());
      printer.print("-");
      printer.println(future.year() );
    }

    printer.justify('C');
    printer.setSize('S');
    printer.println(F("\nTerima Kasih"));

    printer.justify('C');
    printer.setSize('S');
    printer.boldOn();
    printer.println(F("\nNomor Antrian Tidak Boleh Dibawa Pulang"));
    printer.boldOff();

    printer.feed(10);
    printer.cutPaper();
    loopp_printer = 2;
  }
}

void beep(int kali) {
  for (int x = 1; x <= kali; x++) {
    digitalWrite(Buzzer, HIGH);
    delay(100);
    digitalWrite(Buzzer, LOW);
    delay(100);
  }
}

void Tampilan_LCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("NOMOR ANTRIAN");
  if (counter < 10) {
    lcd.setCursor(0, 1);
    lcd.print("NO: ");
    lcd.print("00");
    lcd.print(counter);
  }
  else if (counter >= 10 && counter < 100) {
    lcd.setCursor(0, 1);
    lcd.print("NO: ");
    lcd.print("0");
    lcd.print(counter);
  }
  else if (counter >= 100) {
    lcd.setCursor(0, 1);
    lcd.print("NO: ");
    lcd.print(counter);
  }
}

void setup () {
  Serial.begin(115200);
  EEPROM.begin();
  mySerial.begin(115200);
  printer.begin();
  lcd.init();
  lcd.backlight();

//  if (! rtc.begin()) {
//    Serial.println("Couldn't find RTC");
//    Serial.flush();
//    abort();
//  }
//
//  if (rtc.lostPower()) {
//    Serial.println("RTC lost power, let's set the time!");
//    //  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//    // This line sets the RTC with an explicit date & time, for example to set
//    // January 21, 2014 at 3am you would call:
//    rtc.adjust(DateTime(2023, 6, 6, 21, 52, 0));
//  }
//  rtc.adjust(DateTime(2023, 6, 6, 21, 52, 0));

  DateTime now = rtc.now();

  pinMode(Future_Button, INPUT);
  pinMode(Print_Button, INPUT);
  pinMode(LED_MODE1, OUTPUT);
  pinMode(LED_MODE2, OUTPUT);
  pinMode(LED_MODE3, OUTPUT);
  pinMode(Buzzer, OUTPUT);

  digitalWrite(LED_MODE1, LOW);
  digitalWrite(LED_MODE2, LOW);
  digitalWrite(LED_MODE3, LOW);
  digitalWrite(Buzzer, LOW);

  /* RESET ANTRIAN BESOK MENJADI NOL */
  // EEPROM.write(addr_besok, 0);

  Cek_Tanggal = EEPROM.read(addr_CekTanggal);
  delay(100);
  counter_besok = EEPROM.read(addr_besok);
  delay(100);

  if (Cek_Tanggal != now.day()) {
    counter = counter_besok;
    Serial.print("Hari ini : ");
    Serial.print(now.day());
    Serial.print("\n");
    Serial.print("Kemarin : ");
    Serial.print(Cek_Tanggal);
    Serial.print("\nMulai Counter Kemarin");
    counter_besok = 0;
  }
  else {
    counter = EEPROM.read(addr);
    Serial.println("Mulai Counter Hari Ini ");
  }

  Tampilan_LCD();

  Serial.print("Hari ini : ");
  Serial.print(now.day());
  Serial.print("\nKemarin : ");
  Serial.print(Cek_Tanggal);
  Serial.print("\n\nCounter EEPROM 1 : ");
  Serial.print(counter);
  Serial.print("\nCounter EEPROM 2 : ");
  Serial.println(counter_besok);

  Cek_Tanggal = now.day();
  delay(100);
  EEPROM.write(addr_CekTanggal, Cek_Tanggal);
}

void loop () {
  DateTime now = rtc.now();

  //  Cek_Tanggal = now.day();
  //  EEPROM.write(addr_CekTanggal, Cek_Tanggal);

  if (digitalRead(Future_Button) == diTekan) {
    mode = mode + 1;
    if (mode == 4) {
      mode = 1;
    }
    Serial.print("\tMode : ");
    Serial.print(mode);
    delay(500);
  }

  if (mode == 1) {
    digitalWrite(LED_MODE1, HIGH);
    digitalWrite(LED_MODE2, LOW);
    digitalWrite(LED_MODE3, LOW);
    /* ----------------------------------------------------SEKARANG---------------------------------------------------- */
    if (digitalRead(Print_Button) == diTekan) {
      loopp = 1;
      while (loopp <= 1) {
        counter_reset = counter_reset + 1;

        if (counter_reset == 10) { // JEDA WAKTU RESET 10 x delay(1000)
          counter = -1;
          EEPROM.write(addr, counter);
          beep(2);
          delay(1000);
          counter_reset = 0;
          Serial.println("------------------------------------------RESET COUNTER---------------------------------------");
        }

        if (digitalRead(Print_Button) == !diTekan) {
          counter_reset = 0;
          counter = counter + 1;
          EEPROM.write(addr, counter);
          Tampilan_LCD();

          if (counter > 0) {
            Cetak_Antrian_Now();
            Serial.print("\nPrint Out ");
          }

          Serial.print("\nMode : ");
          Serial.print(mode);
          Serial.print("\tCounter : ");
          Serial.print(counter);
          Serial.print("\tHari : ");
          Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
          Serial.print(", ");
          Serial.print(now.day());
          Serial.print(" ");
          Serial.print(now.month());
          Serial.print(" ");
          Serial.print(now.year(), DEC);
          Serial.print(", Pukul : ");
          Serial.print(now.hour(), DEC);
          Serial.print(':');
          Serial.print(now.minute(), DEC);
          Serial.print(':');
          Serial.print(now.second(), DEC);
          Serial.println();
          loopp = 2;
          loopp_printer = 1;
        }
        delay(500);
      }

    }
  }
  else if (mode == 2) {
    digitalWrite(LED_MODE1, LOW);
    digitalWrite(LED_MODE2, HIGH);
    digitalWrite(LED_MODE3, LOW);
    /* ----------------------------------------------------SHIFT SELANJUTNYA---------------------------------------------------- */
    if (digitalRead(Print_Button) == diTekan) {
      loopp = 1;
      while (loopp <= 1) {
        counter_reset = counter_reset + 1;

        if (counter_reset == 10) { // JEDA WAKTU RESET 10 x delay(1000)
          counter = -1;
          EEPROM.write(addr, counter);
          beep(2);
          delay(1000);
          counter_reset = 0;
          Serial.println("------------------------------------------RESET COUNTER---------------------------------------");
        }

        if (digitalRead(Print_Button) == !diTekan) {
          counter_reset = 0;
          counter = counter + 1;
          EEPROM.write(addr, counter);
          Tampilan_LCD();

          if (counter > 0) {
            Cetak_Antrian_NextShift();
            Serial.print("\nPrint Out ");
          }

          Serial.print("\nMode : ");
          Serial.print(mode);
          Serial.print("\tCounter : ");
          Serial.print(counter);
          Serial.print("\tHari : ");
          Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
          Serial.print(", ");
          Serial.print(now.day());
          Serial.print(" ");
          Serial.print(now.month());
          Serial.print(" ");
          Serial.print(now.year(), DEC);
          Serial.print(", Pukul : ");
          Serial.print(now.hour(), DEC);
          Serial.print(':');
          Serial.print(now.minute(), DEC);
          Serial.print(':');
          Serial.print(now.second(), DEC);
          Serial.println();
          loopp = 2;
          loopp_printer = 1;
        }
        delay(500);
      }

    }
  }
  else if (mode == 3) {
    digitalWrite(LED_MODE1, LOW);
    digitalWrite(LED_MODE2, LOW);
    digitalWrite(LED_MODE3, HIGH);
    /* ----------------------------------------------------BESOK---------------------------------------------------- */
    if (digitalRead(Print_Button) == diTekan) {
      loopp = 1;
      while (loopp <= 1) {
        counter_reset = counter_reset + 1;

        if (counter_reset == 10) { // JEDA WAKTU RESET 10 x delay(1000)
          counter = -1;
          EEPROM.write(addr, counter);
          beep(2);
          delay(1000);
          counter_reset = 0;
          Serial.println("------------------------------------------RESET COUNTER---------------------------------------");
        }

        if (digitalRead(Print_Button) == !diTekan) {
          counter_reset = 0;
          counter_besok = counter_besok + 1;
          EEPROM.write(addr_besok, counter_besok);

          if (counter_besok > 0) {
            Cetak_Antrian_Besok();
            Serial.print("\nPrint Out ");
          }

          Serial.print("\nMode : ");
          Serial.print(mode);
          Serial.print("\tCounter : ");
          Serial.print(counter_besok);
          Serial.print("\tHari : ");
          Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
          Serial.print(", ");
          Serial.print(now.day());
          Serial.print(" ");
          Serial.print(now.month());
          Serial.print(" ");
          Serial.print(now.year(), DEC);
          Serial.print(", Pukul : ");
          Serial.print(now.hour(), DEC);
          Serial.print(':');
          Serial.print(now.minute(), DEC);
          Serial.print(':');
          Serial.print(now.second(), DEC);
          Serial.println();
          loopp = 2;
          loopp_printer = 1;
        }
        delay(500);
      }

    }
  }
}
