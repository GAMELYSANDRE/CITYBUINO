# Paths to Arduino IDE and cloned Arduino-Makefile
ARDUINO_DIR = $(HOME)/Téléchargements/arduino-1.8.9
ARDMK_DIR = $(HOME)/Arduino-Makefile

# Specify the custom Gamebuino board and where it's installed
BOARD_TAG = gamebuino_meta_native
ALTERNATE_CORE_PATH = \
    $(HOME)/.arduino15/packages/gamebuino/hardware/samd/1.2.2

# The Arduino libraries the game uses
ARDUINO_LIBS = Gamebuino_META SPI

# The META lib expects __SKETCH_NAME__ to be defined
CFLAGS += -D__SKETCH_NAME__=\"$(TARGET).ino\"
CXXFLAGS += -D__SKETCH_NAME__=\"$(TARGET).ino\"

# Now that everything is configured, include Arduino-Makefile
include $(ARDMK_DIR)/Sam.mk