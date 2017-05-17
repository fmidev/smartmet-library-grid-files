CREATE_CLASS_DEFINITIONS = ../../../php/createClassDefinitions_grib1.php
T_DIR = /usr/share/grib_api/definitions/grib1
T_TARGET_DIR = .

H_FILES = \
  LatLon.h \
  Mercator.h \
  LambertConformal.h \
  Gaussian.h \
  PolarStereographic.h \
  Albers.h \
  RotatedLatLon.h \
  ObliqueLambertConformal.h \
  RotatedGaussian.h \
  StretchedLatLon.h \
  StretchedGaussian.h \
  StretchedRotatedLatLon.h \
  StretchedRotatedGaussian.h \
  SphericalHarmonic.h \
  RotatedSphericalHarmonic.h \
  StretchedSphericalHarmonic.h \
  StretchedRotatedSphericalHarmonic.h \
  SpaceView.h \
	RotationSettings.h \
	ScanningModeSettings.h \
	GridAreaSettings.h \
	ResolutionFlagsSettings.h \
	GridStretchingSettings.h

CPP_FILES = \
  LatLon.cpp \
  Mercator.cpp \
  LambertConformal.cpp \
  Gaussian.cpp \
  PolarStereographic.cpp \
  Albers.cpp \
  RotatedLatLon.cpp \
  ObliqueLambertConformal.cpp \
  RotatedGaussian.cpp \
  StretchedLatLon.cpp \
  StretchedGaussian.cpp \
  StretchedRotatedLatLon.cpp \
  StretchedRotatedGaussian.cpp \
  SphericalHarmonic.cpp \
  RotatedSphericalHarmonic.cpp \
  StretchedSphericalHarmonic.cpp \
  StretchedRotatedSphericalHarmonic.cpp \
  SpaceView.cpp \
	RotationSettings.cpp \
	ScanningModeSettings.cpp \
	GridAreaSettings.cpp \
	ResolutionFlagsSettings.cpp \
	GridStretchingSettings.cpp
	


all: definitions

definitions: $(H_FILES)

clean:
	rm -f $(H_FILES)
	rm -f $(CPP_FILES)


LatLon.h: $(T_DIR)/grid_definition_0.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/grid_definition_0.def $(T_TARGET_DIR)

Mercator.h: $(T_DIR)/grid_definition_1.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/grid_definition_1.def $(T_TARGET_DIR)

LambertConformal.h: $(T_DIR)/grid_definition_3.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/grid_definition_3.def $(T_TARGET_DIR)

Gaussian.h: $(T_DIR)/grid_definition_4.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/grid_definition_4.def $(T_TARGET_DIR)

PolarStereographic.h: $(T_DIR)/grid_definition_5.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/grid_definition_5.def $(T_TARGET_DIR)

Albers.h: $(T_DIR)/grid_definition_8.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/grid_definition_8.def $(T_TARGET_DIR)

RotatedLatLon.h: $(T_DIR)/grid_definition_10.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/grid_definition_10.def $(T_TARGET_DIR)

ObliqueLambertConformal.h: $(T_DIR)/grid_definition_13.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/grid_definition_13.def $(T_TARGET_DIR)

RotatedGaussian.h: $(T_DIR)/grid_definition_14.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/grid_definition_14.def $(T_TARGET_DIR)

StretchedLatLon.h: $(T_DIR)/grid_definition_20.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/grid_definition_20.def $(T_TARGET_DIR)

StretchedGaussian.h: $(T_DIR)/grid_definition_24.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/grid_definition_24.def $(T_TARGET_DIR)

StretchedRotatedLatLon.h: $(T_DIR)/grid_definition_30.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/grid_definition_30.def $(T_TARGET_DIR)

StretchedRotatedGaussian.h: $(T_DIR)/grid_definition_34.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/grid_definition_34.def $(T_TARGET_DIR)

SphericalHarmonic.h: $(T_DIR)/grid_definition_50.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/grid_definition_50.def $(T_TARGET_DIR)

RotatedSphericalHarmonic.h: $(T_DIR)/grid_definition_60.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/grid_definition_60.def $(T_TARGET_DIR)

StretchedSphericalHarmonic.h: $(T_DIR)/grid_definition_70.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/grid_definition_70.def $(T_TARGET_DIR)

StretchedRotatedSphericalHarmonic.h: $(T_DIR)/grid_definition_80.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/grid_definition_80.def $(T_TARGET_DIR)

SpaceView.h: $(T_DIR)/grid_definition_90.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/grid_definition_90.def $(T_TARGET_DIR)

RotationSettings.h: $(T_DIR)/grid_rotation.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/grid_rotation.def $(T_TARGET_DIR)

ScanningModeSettings.h: $(T_DIR)/scanning_mode.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/scanning_mode.def $(T_TARGET_DIR)
	
GridAreaSettings.h: $(T_DIR)/grid_first_last_resandcomp.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/grid_first_last_resandcomp.def $(T_TARGET_DIR)
	
ResolutionFlagsSettings.h: $(T_DIR)/resolution_flags.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/resolution_flags.def $(T_TARGET_DIR)
	
	
GridStretchingSettings.h: $(T_DIR)/grid_stretching.def $(CREATE_CLASS_DEFINITIONS)
	$(CREATE_CLASS_DEFINITIONS) $(T_DIR)/grid_stretching.def $(T_TARGET_DIR)
	

		