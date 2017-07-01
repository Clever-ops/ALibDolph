LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE  := glslang
LOCAL_SRC_FILES := glslang/GenericCodeGen/CodeGen.cpp \
                   glslang/GenericCodeGen/Link.cpp \
                   glslang/MachineIndependent/Constant.cpp \
                   glslang/MachineIndependent/glslang_tab.cpp \
                   glslang/MachineIndependent/InfoSink.cpp \
                   glslang/MachineIndependent/Initialize.cpp \
                   glslang/MachineIndependent/Intermediate.cpp \
                   glslang/MachineIndependent/intermOut.cpp \
                   glslang/MachineIndependent/IntermTraverse.cpp \
                   glslang/MachineIndependent/limits.cpp \
                   glslang/MachineIndependent/linkValidate.cpp \
                   glslang/MachineIndependent/parseConst.cpp \
                   glslang/MachineIndependent/ParseHelper.cpp \
                   glslang/MachineIndependent/PoolAlloc.cpp \
                   glslang/MachineIndependent/preprocessor/Pp.cpp \
                   glslang/MachineIndependent/preprocessor/PpAtom.cpp \
                   glslang/MachineIndependent/preprocessor/PpContext.cpp \
                   glslang/MachineIndependent/preprocessor/PpMemory.cpp \
                   glslang/MachineIndependent/preprocessor/PpScanner.cpp \
                   glslang/MachineIndependent/preprocessor/PpSymbols.cpp \
                   glslang/MachineIndependent/preprocessor/PpTokens.cpp \
                   glslang/MachineIndependent/propagateNoContraction.cpp \
                   glslang/MachineIndependent/reflection.cpp \
                   glslang/MachineIndependent/RemoveTree.cpp \
                   glslang/MachineIndependent/Scan.cpp \
                   glslang/MachineIndependent/ShaderLang.cpp \
                   glslang/MachineIndependent/SymbolTable.cpp \
                   glslang/MachineIndependent/Versions.cpp \
                   hlsl/hlslGrammar.cpp \
                   hlsl/hlslOpMap.cpp \
                   hlsl/hlslParseables.cpp \
                   hlsl/hlslParseHelper.cpp \
                   hlsl/hlslScanContext.cpp \
                   hlsl/hlslTokenStream.cpp \
                   OGLCompilersDLL/InitializeDll.cpp \
                   SPIRV/disassemble.cpp \
                   SPIRV/doc.cpp \
                   SPIRV/GlslangToSpv.cpp \
                   SPIRV/InReadableOrder.cpp \
                   SPIRV/Logger.cpp \
                   SPIRV/SpvBuilder.cpp \
                   SPIRV/SPVRemapper.cpp \
                   glslang/OSDependent/Unix/ossource.cpp
include $(BUILD_STATIC_LIBRARY)
