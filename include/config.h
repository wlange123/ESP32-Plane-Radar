#pragma once

#include <cstdint>

#include <driver/gpio.h>

namespace config {

// --- Wi-Fi portal ---
constexpr char kPortalApName[] = "PlaneRadar-Setup";
constexpr char kPortalIp[] = "192.168.4.1";
/** mDNS host (no ".local" suffix); browser: http://plane-radar.local */
constexpr char kPortalHostname[] = "plane-radar";
constexpr char kPortalHostUrl[] = "plane-radar.local";

/** Per-attempt STA connect wait (ms); retried kWifiConnectAttempts times. */
constexpr unsigned long kWifiConnectAttemptMs = 15000;
constexpr uint8_t kWifiConnectAttempts = 3;
constexpr unsigned long kWifiPortalTimeoutSec = 0;  // 0 = no timeout while configuring
constexpr unsigned long kWifiConnectingFrameMs = 50;
/** Wait after disconnect before reconnecting (avoids portal on brief drops). */
constexpr unsigned long kWifiDownGraceMs = 4000;
/** Minimum interval between background reconnect tries. */
constexpr unsigned long kWifiReconnectIntervalMs = 15000;

#ifdef BOARD_CYD
// --- BOOT button (ESP32-2432S028, GPIO 0, active LOW) ---
constexpr gpio_num_t kBootPin = GPIO_NUM_0;
#else
// --- BOOT button (ESP32-C3 Super Mini, active LOW) ---
constexpr gpio_num_t kBootPin = GPIO_NUM_9;
#endif
constexpr unsigned long kBootResetHoldMs = 3000UL;
/** Ignore BOOT taps shorter than this (debounce). */
constexpr unsigned long kBootTapMinMs = 40UL;

#ifdef BOARD_CYD
// --- Display: ESP32-2432S028 (CYD), 320×240 landscape (HSPI) ---
// Controller variant: 1 = ILI9342 (native landscape), 0 = ILI9341
#define CYD_PANEL_ILI9342 1
constexpr bool kDisplayIli9342 = CYD_PANEL_ILI9342;
constexpr gpio_num_t kDisplayPinRst = GPIO_NUM_NC;
constexpr gpio_num_t kDisplayPinCs = GPIO_NUM_15;
constexpr gpio_num_t kDisplayPinDc = GPIO_NUM_2;
constexpr gpio_num_t kDisplayPinMosi = GPIO_NUM_13;
constexpr gpio_num_t kDisplayPinMiso = GPIO_NUM_12;
constexpr gpio_num_t kDisplayPinSclk = GPIO_NUM_14;
constexpr gpio_num_t kDisplayPinBacklight = GPIO_NUM_21;

constexpr int kDisplayWidth = 320;
constexpr int kDisplayHeight = 240;
// ILI9342: 2 = USB port on the right, 0 = USB port on the left
constexpr int kDisplayRotation = 2;
// --- Touch: XPT2046 resistive on VSPI; any tap cycles the range ---
constexpr bool kTouchEnabled = true;
constexpr int kTouchPinSclk = 25;
constexpr int kTouchPinMosi = 32;
constexpr int kTouchPinMiso = 39;
constexpr int kTouchPinCs = 33;
constexpr int kTouchPinIrq = 36;
constexpr unsigned long kTouchTapGapMs = 350UL;

/** Radar 240×240 on the left, info panel on the right. */
constexpr int kRadarOffsetX = 0;
constexpr int kInfoPanelWidth = kDisplayWidth - 240;
/** Full-screen frame sprite; 8 bit keeps it small enough for the ESP32 heap. */
constexpr uint8_t kFrameColorDepth = 8;

constexpr uint32_t kDisplaySpiWriteHz = 40000000;
// Wrong colors (inverted / red-blue swapped)? Toggle these two.
constexpr bool kDisplayInvert = true;
constexpr bool kDisplayRgbOrder = false;
constexpr bool kAircraftSwapRB = false;
#else
// --- Display: GC9A01 1.28" round 240×240 (SPI) ---
constexpr gpio_num_t kDisplayPinRst = GPIO_NUM_0;
constexpr gpio_num_t kDisplayPinCs = GPIO_NUM_1;
constexpr gpio_num_t kDisplayPinDc = GPIO_NUM_10;
constexpr gpio_num_t kDisplayPinMosi = GPIO_NUM_3;  // display SDA
constexpr gpio_num_t kDisplayPinSclk = GPIO_NUM_4;  // display SCL

constexpr int kDisplayWidth = 240;
constexpr int kDisplayHeight = 240;

constexpr uint32_t kDisplaySpiWriteHz = 40000000;
// GC9A01 modules often need invert + BGR for correct black/green output
constexpr bool kDisplayInvert = true;
constexpr bool kDisplayRgbOrder = true;
constexpr bool kAircraftSwapRB = true;
constexpr int kDisplayRotation = 0;
constexpr int kRadarOffsetX = 0;

#endif

// --- Radar center defaults (overridden via WiFi setup portal) ---
constexpr double kDefaultRadarLat = 52.3676;
constexpr double kDefaultRadarLon = 4.9041;

/** Poll adsb.fi (API public limit: 1 req/s). */
constexpr unsigned long kAdsbFetchIntervalMs = 3000;
/** Legacy scale unused — fetch uses radar::fetchRadiusKm() to screen edge. */
constexpr float kAdsbFetchRadiusScale = 1.0f;
/** false = hide aircraft with alt_baro "ground"; true = show them too. */
constexpr bool kAdsbShowGroundAircraft = false;

// --- UI colors (RGB565) — status screens ---
constexpr uint16_t kColorBlack = 0x0000;
constexpr uint16_t kColorYellow = 0xFFE0;
constexpr uint16_t kTextOnYellow = kColorBlack;
constexpr uint16_t kTextOnBlack = 0xFFFF;

}  // namespace config
