INPUTCOMMON_DIR := $(BASE_DIR)/InputCommon
INPUTCOMMON_OBJECTS :=
INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/InputConfig.o
INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControllerEmu/ControllerEmu.o
INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControllerEmu/Control/Control.o
INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControllerEmu/Control/Input.o
INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControllerEmu/Control/Output.o
INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControllerEmu/ControlGroup/AnalogStick.o
INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControllerEmu/ControlGroup/Buttons.o
INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControllerEmu/ControlGroup/ControlGroup.o
INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControllerEmu/ControlGroup/Cursor.o
INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControllerEmu/ControlGroup/Extension.o
INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControllerEmu/ControlGroup/Force.o
INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControllerEmu/ControlGroup/MixedTriggers.o
INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControllerEmu/ControlGroup/ModifySettingsButton.o
INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControllerEmu/ControlGroup/Slider.o
INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControllerEmu/ControlGroup/Tilt.o
INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControllerEmu/ControlGroup/Triggers.o
INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControllerEmu/Setting/BooleanSetting.o
INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControllerEmu/Setting/NumericSetting.o
INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControllerInterface/ControllerInterface.o
INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControlReference/ControlReference.o
INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControllerInterface/Device.o
INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControlReference/ExpressionParser.o
#INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControllerInterface/Xlib/XInput2.o
#INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/GCAdapter.o
#INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControllerInterface/evdev/evdev.o
#INPUTCOMMON_OBJECTS += $(INPUTCOMMON_DIR)/ControllerInterface/Pipes/Pipes.o

$(call add_lib,inputcommon,$(INPUTCOMMON_OBJECTS))
