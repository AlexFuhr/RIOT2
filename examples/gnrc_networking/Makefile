# name of your application
APPLICATION = gnrc_networking

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

BOARD_INSUFFICIENT_MEMORY := arduino-duemilanove arduino-leonardo \
                             arduino-mega2560 arduino-nano \
                             arduino-uno blackpill bluepill calliope-mini \
                             chronos hifive1 hifive1b i-nucleo-lrwan1 mega-xplained \
                             microbit msb-430 msb-430h \
                             nucleo-f031k6 nucleo-f042k6 nucleo-f303k8 \
                             nucleo-l031k6 nucleo-f030r8 nucleo-f070rb \
                             nucleo-f072rb nucleo-f103rb nucleo-f302r8 \
                             nucleo-f334r8 nucleo-l053r8 saml10-xpro \
                             saml11-xpro spark-core stm32f0discovery \
                             stm32l0538-disco telosb \
                             waspmote-pro wsn430-v1_3b wsn430-v1_4 z1

# Include packages that pull up and auto-init the link layer.
# NOTE: 6LoWPAN will be included if IEEE802.15.4 devices are present
USEMODULE += gnrc_netdev_default
USEMODULE += auto_init_gnrc_netif
# Activate ICMPv6 error messages
USEMODULE += gnrc_icmpv6_error
# Specify the mandatory networking modules for IPv6 and UDP
USEMODULE += gnrc_ipv6_router_default
USEMODULE += gnrc_udp
# Add a routing protocol
USEMODULE += gnrc_rpl
USEMODULE += auto_init_gnrc_rpl
# This application dumps received packets to STDIO using the pktdump module
USEMODULE += gnrc_pktdump
# Additional networking modules that can be dropped if not needed
USEMODULE += gnrc_icmpv6_echo
# Add also the shell, some shell commands
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps
USEMODULE += netstats_l2
USEMODULE += netstats_ipv6
USEMODULE += netstats_rpl
# need to include for using external sensor (use default parameters)
USEMODULE += bme280
# we want to use SAUL:
USEMODULE += saul_default
USEMODULE += xtimer
# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Uncomment the following 2 lines to specify static link lokal IPv6 address
# this might be useful for testing, in cases where you cannot or do not want to
# run a shell with ifconfig to get the real link lokal address.
#IPV6_STATIC_LLADDR ?= '"fe80::cafe:cafe:cafe:1"'
#CFLAGS += -DGNRC_IPV6_STATIC_LLADDR=$(IPV6_STATIC_LLADDR)

# Uncomment this to join RPL DODAGs even if DIOs do not contain
# DODAG Configuration Options (see the doc for more info)
# CFLAGS += -DGNRC_RPL_DODAG_CONF_OPTIONAL_ON_JOIN

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include

# Set a custom channel if needed
include $(RIOTMAKE)/default-channel.inc.mk
