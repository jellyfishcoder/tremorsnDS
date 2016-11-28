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
# DATA is a list of directories containing binary data                          #
# INCLUDES is a list of directories containing extra header files               #
# GRAPHICS is a list of directories containing files to be processed by grit    #
# AUDIO is a list of directories containing files to be processed by mmutil     #
# SOUNDBANK_NAME is the name of the maxmod generated by soundbank               # 
# ICON is the directory containing the icon file
#------------------------------------------------------------------------------#
TARGET		:=	$(notdir $(CURDIR))
BUILD		:=	build
SOURCES		:=	source
DATA		:=	
INCLUDES	:=	include
GRAPHICS	:=	gfx
AUDIO		:=	audio
SOUNDBANK_NAME	:=	soundbank
ICON		:=

#-------------------------#
# nDS Game Information    #
#-------------------------#
GAME_TITLE	:=	Tremors

#-------------------------#
# Code generation options #
#-------------------------#
ARCH		:=	-mthumb -mthumb-interwork

CFLAGS		:=	-g -Wall -O2\
				-march=armv5te -mtune=arm946e-s -fomit-frame-pointer\
				-ffast-math \
				$(ARCH) 

CFLAGS		+=	$(INCLUDE) -DARM9

CXXFLAGS	:=	$(CFLAGS) -fno-exceptions -std=c++11

ASFLAGS		:=	-g $(ARCH)
LDFLAGS		=	-specs=ds_arm9.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)

#-----------------------------------#
# Extra libraries linked to project #
#-----------------------------------#
LIBS		:=	-lmm9 -lfilesystem -lfat -lnds9

#------------------------------------------#
# List of directories containing libraries #
#------------------------------------------#
LIBDIRS		:=	$(LIBNDS) $(LIBNDS_CEREAL)

#----------------------------------#
# Not much to edit past this point #
#----------------------------------#
ifneq ($(BUILD),$(notdir $(CURDIR)))
#----------------------------------#

export OUTPUT	:=	$(CURDIR)/$(TARGET)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir)) \
					$(foreach dir,$(GRAPHICS),$(CURDIR)/$(dir)) \
					$(foreach dir,$(AUDIO),$(CURDIR)/$(dir))
export DEPSDIR	:=	$(CURDIR)/$(BUILD)

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*))) $(SOUNDBANK_NAME).bin
PNGFILES	:=	$(foreach dir,$(GRAPHICS),$(notdir $(wildcard $(dir)/*.png)))

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
				$(PNGFILES:.png=.o) \
				$(CPPFILES:.cpp=.o) \
				$(CFILES:.c=.o) \
				$(SFILES:.s=.o) 

export AUDIOFILES	:=	$(foreach dir,$(AUDIO),$(notdir $(wildcard $(dir)/*)))

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-iquote $(CURDIR)/$(dir)) \
				$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
				-I$(CURDIR)/$(BUILD)

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

#---------------#
# Set icon file #
#---------------#
ifeq ($(strip $(ICON)),)
	icons	:=	$(wildcard *.bmp)

	ifneq (,$(findstring $(TARGET).bmp,$(icons)))
	export GAME_ICON	:=	$(CURDIR)/$(TARGET).bmp
	else
	ifneq (,$(findstring icon.bmp,$(icons)))
	export GAME_ICON	:=	$(CURDIR)/icon.bmp
	endif
	endif
	else
	ifeq ($(suffix $(ICON)), .grf)
	export GAME_ICON	:=	$(CURDIR)/$(ICON)
	else
	export GAME_ICON	:=	$(CURDIR)/$(BUILD)/$(notdir $(basename $(ICON))).grf
	endif
endif

.PHONY:	$(BUILD) clean

#--------------------------------------#
# Build Rules (`make` or `make build`) #
#--------------------------------------#
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#----------------------------#
# Clean Rules (`make clean`) #
#----------------------------#
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(TARGET).elf $(TARGET).nds $(TARGET).arm9

#---------#
# What... #
#---------#
else

DEPENDS		:=	$(OFILES:.o=.d)

#--------------#
# Main Targets #
#--------------#
$(OUTPUT).nds	:	$(OUTPUT).elf
#$(OUTPUT).arm9	:	$(OUTPUT).elf
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
# Rule to create assembly source files using   #
# grit. Grit takes the image file and matching #
# grit file, then processes the image          #
# according to the instructions in the grit    #
# file. Add rules for any other image types.   #
#----------------------------------------------#
%.s %.h		:	%.png %.grit
	grit $< -fts -o$*

#----------------------------------------------#
# Rule to create soundbank file for the        #
# project using mmutil.                        #
#----------------------------------------------#
$(SOUNDBANK_NAME).bin	:	$(AUDIOFILES)
	@echo $(notdir $^)
	@mmutil $^ -d -o$(SOUNDBANK_NAME).bin -h$(SOUNDBANK_NAME).h

-include $(DEPSDIR)/*.d

#---------#
# The End #
#---------#
endif
