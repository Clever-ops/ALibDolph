// Copyright (C) 2003-2008 Dolphin Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official SVN repository and contact information can be found at
// http://code.google.com/p/dolphin-emu/

#include "Common.h"

#include "../../CoreTiming.h"
#include "../../HW/SystemTimers.h"
#include "../PowerPC.h"
#include "../PPCTables.h"
#include "x64Emitter.h"

#include "Jit.h"
#include "JitCache.h"
#include "JitRegCache.h"

// #define INSTRUCTION_START Default(inst); return;
#define INSTRUCTION_START

#ifdef _M_IX86
#define DISABLE_32BIT Default(inst); return;
#else
#define DISABLE_32BIT ;
#endif

namespace Jit64
{
	void mtspr(UGeckoInstruction inst)
	{
		INSTRUCTION_START;
		u32 iIndex = (inst.SPRU << 5) | (inst.SPRL & 0x1F);
		int d = inst.RD;

		switch (iIndex)
		{
		case SPR_LR:
		case SPR_CTR:
			// These are safe to do the easy way, see the bottom of this function.
			break;

		case SPR_GQR0:
		case SPR_GQR0 + 1:
		case SPR_GQR0 + 2:
		case SPR_GQR0 + 3:
		case SPR_GQR0 + 4:
		case SPR_GQR0 + 5:
		case SPR_GQR0 + 6:
		case SPR_GQR0 + 7:
			js.blockSetsQuantizers = true;
			// Prevent recompiler from compiling in old quantizer values.
			// TODO - actually save the set state and use it in following quantizer ops.
			break;
		// TODO - break block if quantizers are written to.
		default:
			Default(inst);
			return;
		}

		// OK, this is easy.
		gpr.Lock(d);
		gpr.LoadToX64(d, true);
		MOV(32, M(&PowerPC::ppcState.spr[iIndex]), gpr.R(d));
		gpr.UnlockAll();
	}

	void mfspr(UGeckoInstruction inst)
	{
		INSTRUCTION_START;
		u32 iIndex = (inst.SPRU << 5) | (inst.SPRL & 0x1F);
		int d = inst.RD;
		switch (iIndex)
		{
//		case SPR_DEC:
			//MessageBox(NULL, "Read from DEC", "????", MB_OK);
			//break;
		case SPR_TL:
		case SPR_TU:
			//CALL((void *)&CoreTiming::Advance);
			// fall through
		default:
			gpr.Lock(d);
			gpr.LoadToX64(d,false);
			MOV(32, gpr.R(d), M(&PowerPC::ppcState.spr[iIndex]));
			gpr.UnlockAll();
			break;
		}
	}

	void mtmsr(UGeckoInstruction inst)
	{
		INSTRUCTION_START;
		gpr.LoadToX64(inst.RS);
		MOV(32, M(&MSR), gpr.R(inst.RS));
	}

	void mfmsr(UGeckoInstruction inst)
	{
		INSTRUCTION_START;
		//Privileged?
		gpr.LoadToX64(inst.RD, false);
		MOV(32, gpr.R(inst.RD), M(&MSR));
	}

	void mftb(UGeckoInstruction inst)
	{
		INSTRUCTION_START;
		mfspr(inst);
	}
}

