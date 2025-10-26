#ifndef CONFIG_H
#define CONFIG_H

/*
 * config.h
 * Konfigurasi utama untuk proyek Mic Jammer
 * Author: Ardian Fikri Abdulah
 * Company: Optimasi AI
 *
 * File ini menyimpan pengaturan pin dan parameter frekuensi utama.
 * Tambahkan baris `#include "config.h"` di bagian atas main.ino
 * dan hapus definisi pin/frekuensi duplikat dari file utama.
 */

/* ---------------------------
   PIN MAPPING
   --------------------------- */
#define FSYNC_PIN 10   // Pin FSYNC (CS) untuk AD9833


/* ---------------------------
   FREQUENCY CONFIGURATION
   --------------------------- */
#define START_FREQ_HZ   26000.0   // Frekuensi awal (Hz)
#define SWEEP_MIN_HZ    24000.0   // Frekuensi minimum (Hz)
#define SWEEP_MAX_HZ    26000.0   // Frekuensi maksimum (Hz)


/* ---------------------------
   AD9833 CLOCK REFERENCE
   --------------------------- */
#define AD9833_REF_CLK_HZ 25000000UL  // Clock referensi AD9833 (25 MHz)

#endif // CONFIG_H
