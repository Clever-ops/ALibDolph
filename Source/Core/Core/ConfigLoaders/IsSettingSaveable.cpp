// Copyright 2017 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "Core/ConfigLoaders/IsSettingSaveable.h"

#include <algorithm>
#include <vector>

#include "Common/Config/Config.h"
#include "Core/Config/GraphicsSettings.h"
#include "Core/Config/MainSettings.h"
#include "Core/Config/UISettings.h"

namespace ConfigLoaders
{
bool IsSettingSaveable(const Config::Location& config_location)
{
  for (Config::System system :
       {Config::System::SYSCONF, Config::System::GFX, Config::System::DualShockUDPClient,
        Config::System::Logger, Config::System::FreeLook})
  {
    if (config_location.system == system)
      return true;
  }

  if (config_location.system == Config::System::Main)
  {
    for (const std::string_view section :
         {"NetPlay", "General", "GBA", "Display", "Network", "Analytics", "AndroidOverlayButtons",
          "DSP", "GameList", "FifoPlayer", "AutoUpdate", "Movie", "Input", "Debug",
          "BluetoothPassthrough", "USBPassthrough", "Interface"})
    {
      if (config_location.section == section)
        return true;
    }

    // Android controller mappings are not saveable, other Android settings are.
    // TODO: Kill the current Android controller mappings system
    if (config_location.section == "Android")
    {
      static constexpr std::array<const char*, 8> android_setting_saveable = {
          "ControlScale",    "ControlOpacity", "EmulationOrientation", "JoystickRelCenter",
          "LastPlatformTab", "MotionControls", "PhoneRumble",          "ShowInputOverlay"};

      return std::any_of(
          android_setting_saveable.cbegin(), android_setting_saveable.cend(),
          [&config_location](const char* key) { return key == config_location.key; });
    }
  }

  static const auto s_setting_saveable = {
      // Main.Core

      &Config::MAIN_DEFAULT_ISO.GetLocation(),
      &Config::MAIN_ENABLE_CHEATS.GetLocation(),
      &Config::MAIN_MEMCARD_A_PATH.GetLocation(),
      &Config::MAIN_MEMCARD_B_PATH.GetLocation(),
      &Config::MAIN_AUTO_DISC_CHANGE.GetLocation(),
      &Config::MAIN_ALLOW_SD_WRITES.GetLocation(),
      &Config::MAIN_DPL2_DECODER.GetLocation(),
      &Config::MAIN_DPL2_QUALITY.GetLocation(),
      &Config::MAIN_AUDIO_LATENCY.GetLocation(),
      &Config::MAIN_AUDIO_STRETCH.GetLocation(),
      &Config::MAIN_AUDIO_STRETCH_LATENCY.GetLocation(),
      &Config::MAIN_OVERCLOCK.GetLocation(),
      &Config::MAIN_OVERCLOCK_ENABLE.GetLocation(),
      &Config::MAIN_RAM_OVERRIDE_ENABLE.GetLocation(),
      &Config::MAIN_MEM1_SIZE.GetLocation(),
      &Config::MAIN_MEM2_SIZE.GetLocation(),
      &Config::MAIN_GFX_BACKEND.GetLocation(),
      &Config::MAIN_ENABLE_SAVESTATES.GetLocation(),
      &Config::MAIN_FALLBACK_REGION.GetLocation(),
      &Config::MAIN_REAL_WII_REMOTE_REPEAT_REPORTS.GetLocation(),
      &Config::MAIN_DSP_HLE.GetLocation(),
      &Config::MAIN_CPU_CORE.GetLocation(),
      &Config::MAIN_SKIP_IPL.GetLocation(),
      &Config::MAIN_GC_LANGUAGE.GetLocation(),
      &Config::MAIN_AGP_CART_A_PATH.GetLocation(),
      &Config::MAIN_AGP_CART_B_PATH.GetLocation(),
      &Config::MAIN_BBA_MAC.GetLocation(),
      &Config::MAIN_BBA_XLINK_IP.GetLocation(),
      &Config::MAIN_BBA_XLINK_CHAT_OSD.GetLocation(),
      &Config::MAIN_OVERRIDE_REGION_SETTINGS.GetLocation(),
      &Config::MAIN_CUSTOM_RTC_ENABLE.GetLocation(),
      &Config::MAIN_CUSTOM_RTC_VALUE.GetLocation(),
      &Config::MAIN_JIT_FOLLOW_BRANCH.GetLocation(),
      &Config::MAIN_FLOAT_EXCEPTIONS.GetLocation(),
      &Config::MAIN_DIVIDE_BY_ZERO_EXCEPTIONS.GetLocation(),
      &Config::MAIN_LOW_DCBZ_HACK.GetLocation(),
      &Config::MAIN_FPRF.GetLocation(),
      &Config::MAIN_ACCURATE_NANS.GetLocation(),
      &Config::GetInfoForAdapterRumble(0).GetLocation(),
      &Config::GetInfoForAdapterRumble(1).GetLocation(),
      &Config::GetInfoForAdapterRumble(2).GetLocation(),
      &Config::GetInfoForAdapterRumble(3).GetLocation(),
      &Config::GetInfoForSimulateKonga(0).GetLocation(),
      &Config::GetInfoForSimulateKonga(1).GetLocation(),
      &Config::GetInfoForSimulateKonga(2).GetLocation(),
      &Config::GetInfoForSimulateKonga(3).GetLocation(),
      &Config::MAIN_EMULATION_SPEED.GetLocation(),
      &Config::MAIN_PERF_MAP_DIR.GetLocation(),
      &Config::MAIN_GPU_DETERMINISM_MODE.GetLocation(),
      &Config::MAIN_DISABLE_ICACHE.GetLocation(),
      &Config::MAIN_FAST_DISC_SPEED.GetLocation(),
      &Config::MAIN_SYNC_ON_SKIP_IDLE.GetLocation(),
      &Config::MAIN_FASTMEM.GetLocation(),
      &Config::MAIN_TIMING_VARIANCE.GetLocation(),
      &Config::MAIN_WII_SD_CARD.GetLocation(),
      &Config::MAIN_WII_KEYBOARD.GetLocation(),

      // UI.General

      &Config::MAIN_USE_DISCORD_PRESENCE.GetLocation(),
  };

  return std::any_of(begin(s_setting_saveable), end(s_setting_saveable),
                     [&config_location](const Config::Location* location) {
                       return *location == config_location;
                     });
}
}  // namespace ConfigLoaders
