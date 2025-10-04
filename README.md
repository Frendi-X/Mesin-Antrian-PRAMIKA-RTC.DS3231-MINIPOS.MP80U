# Sistem Mesin Antrian Klinik Otomatis dengan RTC DS3231 & Thermal Printer MINIPOS.MP80U

Proyek ini menggunakan Arduino sebagai kontroler utama kemudian untuk mengambil data waktu menggunakan RTC DS3231. Pada proyek kali ini printer yang digunakan yaitu Printer MINI POS MP-80U atau printer yang sudah support dengan cutPaper. Hanya menggunakan 3 tombol utama untuk digunakan (Counter - Pemilihan Mode - Reset). [PESANAN - Klinik Utama Pramika]

---

## 🧩 Fitur Utama

- ✅ **Tiga mode antrian:**
  1. **Mode 1 – Sekarang:** mencetak nomor antrian untuk pasien saat ini.  
  2. **Mode 2 – Shift Selanjutnya:** mencetak nomor antrian untuk pasien di shift berikutnya.  
  3. **Mode 3 – Besok:** mencetak nomor antrian untuk keesokan hari.

- 🕒 **Waktu Real-Time (RTC DS3231):**
  - Menampilkan dan mencetak tanggal & jam secara otomatis.
  - Mendeteksi perubahan hari dan mengatur ulang antrian ke 0 setiap pergantian hari.

- 🖨️ **Thermal Printer Otomatis:**
  - Mencetak struk nomor antrian dengan format:
    ```
    KLINIK UTAMA PRAMIKA
    Jl. Mayjen Sutoyo No.10 Ponorogo
    (0352 486054)

    [Hari, Tanggal, Jam]
    NO: 00X

    Terima Kasih
    Nomor Antrian Tidak Boleh Dibawa Pulang
    ```

- 💾 **Penyimpanan EEPROM:**
  - Menyimpan data antrian hari ini, antrian besok, dan tanggal terakhir.
  - Data tetap tersimpan meski Arduino dimatikan.

- 🔊 **Buzzer Indikator:** berbunyi saat tombol ditekan atau reset dilakukan.

- 💡 **Indikator LED Mode:**
  - LED 1 = Mode Sekarang  
  - LED 2 = Mode Shift Selanjutnya  
  - LED 3 = Mode Besok

---

## ⚙️ Komponen yang Digunakan

| Komponen | Deskripsi |
|----------|------------|
| Arduino UNO / Mega | Mikrokontroler utama |
| RTC DS3231 | Menyimpan waktu & tanggal secara real-time |
| Thermal Printer (Adafruit) | Mencetak struk antrian |
| LCD 16x2 I2C | Menampilkan nomor antrian saat ini |
| EEPROM internal | Menyimpan data antrian |
| Tombol Push | Tombol mode & cetak antrian |
| 3 LED indikator | Menunjukkan mode aktif |
| Buzzer | Pemberi notifikasi audio |

---

## 🧾 Library yang Diperlukan

Pastikan library berikut telah diinstal di Arduino IDE:

| Library | Link Download |
|----------|----------------|
| **RTClib** | [RTClib v2.1.4](https://downloads.arduino.cc/libraries/github.com/adafruit/RTClib-2.1.4.zip) |
| **Adafruit Thermal Printer** | [Adafruit Thermal Printer v1.4.1](https://downloads.arduino.cc/libraries/github.com/adafruit/Adafruit_Thermal_Printer_Library-1.4.1.zip) |
| **LiquidCrystal I2C** | [LiquidCrystal I2C v1.1.2](https://downloads.arduino.cc/libraries/github.com/johnrickman/LiquidCrystal_I2C-1.1.2.zip) |

---

## 🔌 Pin Konfigurasi

| Fungsi | Pin Arduino |
|--------|--------------|
| TX Thermal Printer | Pin 8 |
| RX Thermal Printer | Pin 9 |
| Tombol Mode | Pin 4 |
| Tombol Cetak | Pin 5 |
| LED Mode 1 | Pin 10 |
| LED Mode 2 | Pin 11 |
| LED Mode 3 | Pin 12 |
| Buzzer | Pin 13 |
| SDA (LCD I2C & RTC) | A4 |
| SCL (LCD I2C & RTC) | A5 |

---

## 📋 Cara Penggunaan

1. **Nyalakan alat.**
   - LCD akan menampilkan *NOMOR ANTRIAN NO: 00X*.
   - LED mode 1 menyala.

2. **Ganti mode:**
   - Tekan **tombol mode (Pin 4)** untuk berpindah ke Mode 2 atau Mode 3.
   - LED yang menyala menunjukkan mode aktif.

3. **Cetak nomor antrian:**
   - Tekan **tombol print (Pin 5)** untuk mencetak nomor antrian.
   - Printer akan mencetak struk lengkap dengan tanggal & jam.

4. **Reset otomatis:**
   - Sistem akan mereset nomor antrian ketika tanggal berganti.
   - Bisa juga melakukan reset manual (tahan tombol print beberapa detik).

---

## 🧠 Mekanisme EEPROM

| Alamat EEPROM | Fungsi |
|----------------|---------|
| `addr = 4` | Menyimpan nomor antrian hari ini |
| `addr_besok = 5` | Menyimpan nomor antrian besok |
| `addr_CekTanggal = 6` | Menyimpan tanggal terakhir digunakan |

---

## Contacs us : 
* [Frendi RoboTech](https://www.instagram.com/frendi.co/)
* [Whatsapp : +6287888227410](https://wa.me/+6287888227410)
* [Email    : frendirobotech@gmail.com](https://mail.google.com/mail/u/0/?view=cm&tf=1&fs=1&to=frendirobotech@gmail.com) atau [Email    : frendix45@gmail.com](https://mail.google.com/mail/u/0/?view=cm&tf=1&fs=1&to=frendix45@gmail.com)

---

## 👨‍💻 Author
Dikembangkan oleh: Imam Sa'id Nurfrendi [Reog Robotic & Robotech Electronics]  
Lisensi: Open Source (MIT)


## Contacs us : 
* [Frendi RoboTech](https://www.instagram.com/frendi.co/)
* [Whatsapp : +6287888227410](https://wa.me/+6287888227410)
* [Email    : frendirobotech@gmail.com](https://mail.google.com/mail/u/0/?view=cm&tf=1&fs=1&to=frendirobotech@gmail.com)

