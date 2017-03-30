// Copyright 2010 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included./

#pragma once

#include "Common/CommonTypes.h"
#include "Core/PowerPC/PowerPC.h"
#include "Core/PowerPC/Jit64Common/Jit64Base.h"

// We offset by 0x80 because the range of one byte memory offsets is
// -0x80..0x7f.
#define PPCSTATE(x)                                                                                \
  MDisp(RPPCSTATE, (int)((char*)&PowerPC::ppcState.x - (char*)&PowerPC::ppcState) - 0x80)
// In case you want to disable the ppcstate register:
// #define PPCSTATE(x) M(&PowerPC::ppcState.x)
#define PPCSTATE_LR PPCSTATE(spr[SPR_LR])
#define PPCSTATE_CTR PPCSTATE(spr[SPR_CTR])
#define PPCSTATE_SRR0 PPCSTATE(spr[SPR_SRR0])
#define PPCSTATE_SRR1 PPCSTATE(spr[SPR_SRR1])

namespace Gen
{
inline OpArg MScaledPIC(X64Reg scaled, int scale, const void* ptr)
{
   return MComplex(RPPCSTATE, scaled, scale, PtrOffset(ptr, (char*)&PowerPC::ppcState + 0x80));
}
inline OpArg MDispPIC(X64Reg value, const void* ptr)
{
  return MScaledPIC(value, SCALE_1, ptr);
}
}
