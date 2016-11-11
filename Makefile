#-----------#
.SUFFIXES:
#-----------#

ifeq ($(strip $(DEVKITARM)),)
	$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/ds_rules

#-------------------------------------------------------------------------------#
# TARGET is the name of the output                                              #
# BUILD is the directory where object files & intermediate files will be placed #
# SOURCES is a list of directories containing source code                       #
# INCLUDES is a list of directories containing extra header files               #
# DATA is a list of directories containing binary data                          #
# GRAPHICS is a list of directories containing files to be processed by grit    #
# SPRITES is a lisst of directories containing sprite files for grit            #
# ------------------------------------------------------------------------------#
TARGET		:=	$(notdir $(CURDIR))
BUILD		:=	build
SOURCES		:=	source
DATA		:=	data
INCLUDES	:=	include
GRAPHICS	:=	gfx
SPRITES		:=	sprites

#-------------------------#
# Code generation options #
#-------------------------#
ARCH		:=	-mthumb -mthumb-interwork
CFLAGS		:=	-g -Wall -O2\
				-march=armv5te -mtune=arm946e-s -fomit-frame-pointer\
				-ffast-math \
				$(ARCH)
CFLAGS		+=	$(INCLUDE) -DARM9
CXXFLAGS	:=	$(CFLAGS) -fno-rtti -fno-exceptions
ASFLAGS		:=	-g $(ARCH)
LDFLAGS		=	-specs=ds_arm9.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)

#-----------------------------------#
# Extra libraries linked to project #
#-----------------------------------#
LIBS		:=	-lnds9

#------------------------------------------#
# List of directories containing libraries #
#------------------------------------------#
LIBDIRS		:=	$(LIBNDS)

#----------------------------------#
# Not much to edit past this point #
#----------------------------------#
ifneq ($(BUILDDIR), $(CURDIR))
export OUTPUT	:=	$(CURDIR)/$(TARGET)
export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir)) \
					$(foreach dir,$(GRAPHICS),$(CURDIR)/$(dir))
export DEPSDIR	:=	$(CURDIR)/$(BUILD)

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))
BMPFILES	:=	$(foreach dir,$(GRAPHICS),$(notdir $(wildcard $(dir)/*.bmp)))
SPRITE_FILES	:=	$(foreach dir,$(SPRITES),$(notdir $(wildcard $(dir)/*.png)))

#-----------------------------------#
# Use CXX for linking C++ projects, #
# but use CC for standard C         #
#-----------------------------------#
ifeq ($(strip $(CPPFILES)),)
export LD	:=	$(CC)
else
export LD	:=	$(CXX)
endif

export OFILES	:=	$(addsuffix .o,$(BINFILES)) \
				$(BMPFILES:.bmp=.o) \
				$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o) 

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-iquote $(CURDIR)/$(dir)) \
				$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
				-I$(CURDIR)/$(BUILD)

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

.PHONY:	$(BUILD) clean

#--------------------------------------#
# Build Rules (`make` or `make build`) #
#--------------------------------------#
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@make BUILDDIR=`cd $(BUILD) && pwd` --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#----------------------------#
# Clean Rules (`make clean`) #
#----------------------------#
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(TARGET).elf $(TARGET).nds $(TARGET).ds.gba

#---------#
# What... #
#---------#
else

DEPENDS		:=	$(OFILES:.o=.d)

#--------------#
# Main Targets #
#--------------#
$(OUTPUT).nds	:	$(OUTPUT).elf
$(OUTPUT).elf	:	$(OFILES)

#----------------------------------------------#
# Actually, you may need to copy and modify    #
# the bin2o rule for each extension in data    #
# directories.                                 #
#----------------------------------------------#

#----------------------------------------------#
# Rule to link binary data with .bin extension #
#----------------------------------------------#
%.bin.o		:	%.bin
	@echo $(notdir $<)
	@$(bin2o)

#----------------------------------------------#
# Rule to link binary data with .raw extension #
#----------------------------------------------#
%.raw.o		:	%.raw
	@echo $(notdir $<)
	@$(bin2o)

#----------------------------------------------#
# Rule to create assembly source files using   #
# grit. Grit takes the image file and matching #
# grit file, then processes the image          #
# according to the instructions in the grit    #
# file. Add rules for any other image types.   #
#----------------------------------------------#
%.s %.h		:	%.bmp %.grit
	grit $< -fts -o$*

#----------------------------------------------#
# Rule for grit to process animated sprites    #
#----------------------------------------------#
%.s %.h		:	%.png
	grit $< -ff../sprites/sprite.grit -o$*

-include $(DEPENDS)

#---------#
# The End #
#---------#
endif
