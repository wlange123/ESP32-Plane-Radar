#pragma once

namespace ui {

/** Draw the static sonar/radar grid (black disc, green overlay, labels). */
void radarDisplayDraw();

/** Redraw aircraft only (blits cached grid; no full-screen clear). */
void radarDisplayRefreshAircraft();

/** Allocate the frame buffer early (before Wi-Fi fragments the heap). */
void radarDisplayPrealloc();

}  // namespace ui
