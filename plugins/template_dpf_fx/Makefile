#!/usr/bin/make -f
# Makefile for DISTRHO Plugins #
# ---------------------------- #
# Created by falkTX
#

# --------------------------------------------------------------
# Project name, used for binaries

NAME = template_fx

# --------------------------------------------------------------
# Files to build

FILES_DSP = \
	Template_DPF_FX_Plugin.cpp

FILES_UI  = \
	Template_DPF_FX_UI.cpp \
	Artwork.cpp


# --------------------------------------------------------------
# Do some magic

include ../../dpf/Makefile.plugins.mk

# --------------------------------------------------------------
# Enable lv2, vst and jack app

TARGETS += jack

ifeq ($(HAVE_OPENGL),true)
TARGETS += lv2_sep
else
TARGETS += lv2_dsp
endif

TARGETS += vst

all: $(TARGETS)

# --------------------------------------------------------------
