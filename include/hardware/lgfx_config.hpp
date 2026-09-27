#pragma once

#define LGFX_USE_V1
#include <LovyanGFX.hpp>

#include "config.h"

#ifdef BOARD_CYD

/** LovyanGFX device: ESP32-2432S028 (CYD), ILI9341 on HSPI + PWM backlight. */
class LGFX : public lgfx::LGFX_Device {
  lgfx::Bus_SPI _bus;
#if CYD_PANEL_ILI9342
  lgfx::Panel_ILI9342 _panel;
#else
  lgfx::Panel_ILI9341 _panel;
#endif
  lgfx::Light_PWM _light;
  lgfx::Touch_XPT2046 _touch;

public:
  LGFX() {
    {
      auto cfg = _bus.config();
      cfg.spi_host = HSPI_HOST;
      cfg.spi_mode = 0;
      cfg.freq_write = config::kDisplaySpiWriteHz;
      cfg.freq_read = 16000000;
      cfg.pin_sclk = static_cast<int>(config::kDisplayPinSclk);
      cfg.pin_mosi = static_cast<int>(config::kDisplayPinMosi);
      cfg.pin_miso = static_cast<int>(config::kDisplayPinMiso);
      cfg.pin_dc = static_cast<int>(config::kDisplayPinDc);
      _bus.config(cfg);
      _panel.setBus(&_bus);
    }
    {
      auto cfg = _panel.config();
      cfg.pin_cs = static_cast<int>(config::kDisplayPinCs);
      cfg.pin_rst = static_cast<int>(config::kDisplayPinRst);
      cfg.pin_busy = -1;
      cfg.panel_width = config::kDisplayIli9342 ? 320 : 240;
      cfg.panel_height = config::kDisplayIli9342 ? 240 : 320;
      cfg.memory_width = cfg.panel_width;
      cfg.memory_height = cfg.panel_height;
      cfg.readable = true;
      cfg.invert = config::kDisplayInvert;
      cfg.rgb_order = config::kDisplayRgbOrder;
      cfg.bus_shared = false;
      _panel.config(cfg);
    }
    {
      auto cfg = _light.config();
      cfg.pin_bl = static_cast<int>(config::kDisplayPinBacklight);
      cfg.invert = false;
      cfg.freq = 12000;
      cfg.pwm_channel = 7;
      _light.config(cfg);
      _panel.setLight(&_light);
    }
    {
      auto cfg = _touch.config();
      cfg.spi_host = VSPI_HOST;
      cfg.freq = 1000000;
      cfg.pin_sclk = config::kTouchPinSclk;
      cfg.pin_mosi = config::kTouchPinMosi;
      cfg.pin_miso = config::kTouchPinMiso;
      cfg.pin_cs = config::kTouchPinCs;
      cfg.pin_int = config::kTouchPinIrq;
      cfg.bus_shared = false;
      cfg.x_min = 300;
      cfg.x_max = 3900;
      cfg.y_min = 200;
      cfg.y_max = 3700;
      _touch.config(cfg);
      _panel.setTouch(&_touch);
    }
    setPanel(&_panel);
  }
};

#else

/** LovyanGFX device: GC9A01 on SPI. Pin values come from config.h. */
class LGFX : public lgfx::LGFX_Device {
  lgfx::Bus_SPI _bus;
  lgfx::Panel_GC9A01 _panel;

public:
  LGFX() {
    {
      auto cfg = _bus.config();
      cfg.spi_host = SPI2_HOST;
      cfg.freq_write = config::kDisplaySpiWriteHz;
      cfg.pin_sclk = static_cast<int>(config::kDisplayPinSclk);
      cfg.pin_mosi = static_cast<int>(config::kDisplayPinMosi);
      cfg.pin_miso = -1;
      cfg.pin_dc = static_cast<int>(config::kDisplayPinDc);
      _bus.config(cfg);
      _panel.setBus(&_bus);
    }
    {
      auto cfg = _panel.config();
      cfg.pin_cs = static_cast<int>(config::kDisplayPinCs);
      cfg.pin_rst = static_cast<int>(config::kDisplayPinRst);
      cfg.invert = config::kDisplayInvert;
      cfg.rgb_order = config::kDisplayRgbOrder;
      _panel.config(cfg);
    }
    setPanel(&_panel);
  }
};

#endif
