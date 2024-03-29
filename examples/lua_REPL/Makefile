APPLICATION = lua_repl

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

BOARD_INSUFFICIENT_MEMORY := blackpill blackpill-128kib bluepill \
                             bluepill-128kib calliope-mini cc2650-launchpad \
                             cc2650stk hamilton i-nucleo-lrwan1 lsn50 \
                             maple-mini microbit nrf51dk nrf51dongle \
                             nucleo-f030r8 nucleo-f031k6 nucleo-f042k6 \
                             nucleo-f070rb nucleo-f072rb nucleo-f103rb \
                             nucleo-f302r8 nucleo-f303k8 nucleo-f334r8 \
                             nucleo-f410rb nucleo-l031k6 nucleo-l053r8 \
                             opencm904 spark-core stm32f0discovery \
                             airfy-beacon  arduino-mkr1000 \
                             arduino-mkrfox1200 arduino-mkrzero arduino-zero \
                             b-l072z-lrwan1  cc2538dk ek-lm4f120xl  feather-m0 \
                             ikea-tradfri limifrog-v1 lobaro-lorabox \
                             mbed_lpc1768  nrf6310 nucleo-f091rc  nucleo-l073rz \
                             nz32-sc151 openmote-cc2538 openmote-b pba-d-01-kw2x \
                             remote-pa remote-reva remote-revb samd21-xpro \
                             saml10-xpro saml11-xpro saml21-xpro samr21-xpro \
                             samr30-xpro seeeduino_arch-pro sensebox_samd21 slstk3401a \
                             sltb001a slwstk6220a sodaq-autonomo sodaq-explorer \
                             sodaq-one sodaq-sara-aff stk3600 stm32f3discovery \
                             stm32l0538-disco yunjia-nrf51822 \
                             esp8266-esp-12x esp8266-olimex-mod \
                             esp8266-sparkfun-thing firefly samr34-xpro \

BOARD_BLACKLIST := arduino-duemilanove arduino-leonardo \
                   arduino-mega2560 arduino-nano arduino-uno \
                   chronos hifive1 hifive1b jiminy-mega256rfr2 mega-xplained \
                   msb-430 msb-430h pic32-clicker pic32-wifire telosb \
                   waspmote-pro wsn430-v1_3b wsn430-v1_4 z1

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Uncomment the following lines to enable debugging features.
#CFLAGS_OPT = -Og
#CFLAGS += -DDEBUG_ASSERT_VERBOSE -DLUA_DEBUG

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

# This value is in excess because we are not sure of the exact requirements of
# lua (see the package's docs). It must be fixed in the future by taking
# appropriate measurements.
CFLAGS += -DTHREAD_STACKSIZE_MAIN='(THREAD_STACKSIZE_DEFAULT+7000)'

USEPKG += lua

LUA_PATH = $(BINDIR)/lua

# add directory of generated *.lua.h files to include path
CFLAGS += -I$(LUA_PATH)

# generate .lua.h header files of .lua files
LUA = $(wildcard *.lua)

LUA_H = $(LUA:%.lua=$(LUA_PATH)/%.lua.h)

BUILDDEPS += $(LUA_H) $(LUA_PATH)/

include $(RIOTBASE)/Makefile.include

# The code below generates a header file from any .lua scripts in the
# example directory. The header file contains a byte array of the
# ASCII characters in the .lua script.

$(LUA_PATH)/:
	$(Q)mkdir -p $@

# FIXME: This way of embedding lua code is not robust. A proper script will
#        be included later.
$(LUA_H): $(LUA_PATH)/%.lua.h: %.lua | $(LUA_PATH)/
	$(Q)xxd -i $< | sed 's/^unsigned/const unsigned/g' > $@
