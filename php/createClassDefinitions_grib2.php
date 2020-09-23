#!/usr/bin/php -q
<?php

// Parents for main level classes
$parents = array (
    "3" => "GridDefinition",
    "4" => "ProductDefinition",
    "5" => "RepresentationDefinition",
    "7" => "DataDefinition"
);

// Class names for templates
$templates = array (
    "1.calendar" => "CalendarTypeSettings",
    "1.offset" => "CalendarOffsetSettings",

    "1.0" => "UNUSED",
    "1.1" => "UNUSED",
    "1.2" => "Calendar",

    "3.shape_of_the_earth" => "EarthShapeSettings",
    "3.scanning_mode" => "ScanningModeSettings",
    "3.rotation" => "RotationSettings",
    "3.grid" => "GridSettings",
    "3.resolution_flags" => "ResolutionSettings",
    "3.stretching" => "StretchingSettings",
    "3.latlon" => "LatLonSettings",
    "3.latlon_vares" => "VariableLatLonSettings",
    "3.gaussian" => "GaussianSettings",
    "3.spherical_harmonics" => "SphericalHarmonicSettings",

    "3.0" => "LatLon",
    "3.1" => "RotatedLatLon",
    "3.2" => "StretchedLatLon",
    "3.3" => "StretchedRotatedLatLon",
    "3.4" => "VariableResolutionLatLon",
    "3.5" => "VariableResolutionRotatedLatLon",
    "3.10" => "Mercator",
    "3.12" => "TransverseMercator",
    "3.20" => "PolarStereographic",
    "3.30" => "LambertConformal",
    "3.31" => "Albers",
    "3.40" => "Gaussian",
    "3.41" => "RotatedGaussian",
    "3.42" => "StretchedGaussian",
    "3.43" => "StretchedRotatedGaussian",
    "3.50" => "SphericalHarmonic",
    "3.51" => "RotatedSphericalHarmonic",
    "3.52" => "StretchedSphericalHarmonic",
    "3.53" => "StretchedRotatedSphericalHarmonic",
    "3.90" => "SpaceView",
    "3.100" => "Triangular",
    "3.101" => "Unstructured",
    "3.110" => "EquatorialAzimuthalEquidistant",
    "3.120" => "AzimuthRange",
    "3.130" => "IrregularLatLon",
    "3.140" => "LambertAzimuthalEqualArea",
    "3.1000" => "CrossSection",
    "3.1100" => "Hovmoller",
    "3.1200" => "TimeSection",

    "4.categorical" => "CategoricalSettings",
    "4.circular_cluster" => "UNUSED", // TODO: bugged, same variable twice: "CircularClusterSettings",
    "4.derived" => "DerivedSettings",
    "4.eps" => "EpsSettings",
    "4.horizontal" => "HorizontalSettings",
    "4.parameter_aerosol_44" => "UNUSED", // TODO: bug fix crap: "ParameterAerosol44Settings",
    "4.parameter_aerosol" => "ParameterAerosolSettings",
    "4.parameter_aerosol_optical" => "ParameterAerosolOpticalSettings",
    "4.parameter_chemical" => "ParameterChemicalSettings",
    "4.parameter" => "ParameterSettings",
    "4.parameter_partition" => "ParameterPartitionSettings",
    "4.percentile" => "PercentileSettings",
    "4.point_in_time" => "PointInTimeSettings",
    "4.probability" => "ProbabilitySettings",
    "4.rectangular_cluster" => "RectangularClusterSettings",
    "4.reforecast" => "ReforecastSettings",
    "4.statistical" => "StatisticalSettings",
    "4.parameter_postproc" => "PostprocSettings",

    "4.0" => "NormalProduct",
    "4.1" => "EnsembleForecast",
    "4.2" => "EnsembleDerivedForecast",
    "4.3" => "EnsembleClusterDerivedForecast",
    "4.4" => "UNUSED", // TODO: bugged 4.circular_cluster "EnsembleClusterDerivedCircleForecast",
    "4.5" => "ProbabilityForecast",
    "4.6" => "PercentileForecast",
    "4.7" => "ForecastError",
    "4.8" => "AggregateForecast",
    "4.9" => "TimeIntervalProbabilityForecast",
    "4.10" => "TimeIntervalPercentileForecast",
    "4.11" => "TimeIntervalEnsembleForecast",
    "4.12" => "TimeIntervalEnsembleDerivedForecast",
    "4.13" => "TimeIntervalEnsembleClusterDerivedForecast",
    "4.14" => "UNUSED", // TODO bugged 4.circular_cluster "TimeIntervalEnsembleClusterDerivedCircleForecast",
    "4.15" => "TimeIntervalAggregateForecast",
    "4.20" => "UNUSED", // TODO bug: siteId is twice in template 4.20 "RadarProduct",
    "4.30" => "DeprecatedSatelliteProduct",
    "4.31" => "SatelliteProduct",
    "4.32" => "SimulatedSatelliteProduct",
    "4.33" => "SimulatedSatelliteEnsembleProduct",
    "4.34" => "TimeIntervalSimulatedSatelliteEnsembleProduct",
    "4.40" => "AtmosphericChemicalProduct",
    "4.41" => "AtmosphericChemicalEnsembleProduct",
    "4.42" => "AggregateAtmosphericChemicalProduct",
    "4.43" => "TimeIntervalAtmosphericChemicalEnsembleProduct",
    "4.44" => "UNUSED", // TODO: bugged template.4.parameter_aerosol_44 "AerosolProduct",
    "4.45" => "AerosolEnsembleProduct",
    "4.46" => "AggregateAerosolProduct",
    "4.47" => "TimeIntervalAerosolEnsembleProduct",
    "4.48" => "AerosolOpticalPropertiesProduct",
    "4.49" => "Product_49",
    "4.51" => "CategoricalForecast",
    "4.53" => "PartitionedProduct",
    "4.54" => "PartitionedEnsembleProduct",
    "4.55" => "Product_55",
    "4.56" => "Product_56",
    "4.57" => "Product_57",
    "4.58" => "Product_58",
    "4.59" => "Product_59",
    "4.60" => "EnsembleReforecast",
    "4.61" => "TimeIntervalEnsembleReforecast",
    "4.67" => "Product_67",
    "4.68" => "Product_68",
    "4.70" => "Product_70",
    "4.71" => "Product_71",
    "4.72" => "Product_72",
    "4.73" => "Product_73",
    "4.91" => "TimeIntervalCategoricalForecast",
    "4.254" => "CharacterStringProduct",
    "4.311" => "AuxiliarySatelliteProduct",
    "4.1000" => "CrossSectionProduct",
    "4.1001" => "ProcessedCrossSectionProduct",
    "4.1002" => "AreaProcessedCrossSectionProduct",
    "4.1100" => "HovmollerProduct",
    "4.1101" => "ProcessedHovmollerProduct",
    "4.2000" => "UNUSED",
    "4.40033" => "UNUSED", // Deprecated, use 4.33 instead
    "4.40034" => "UNUSED", // Deprecated, use 4.34 instead

    "5.original_values" => "OriginalValuesSettings",
    "5.packing" => "PackingSettings",
    "5.second_order" => "SecondOrderSettings",

    "5.0" => "GridDataRepresentation",
    "5.1" => "MatrixDataRepresentation",
    "5.2" => "ComplexGridDataRepresentation",
    "5.3" => "ComplexDifferenceGridDataRepresentation",
    "5.4" => "FloatingPointGridDataRepresentation",
    "5.6" => "PreprocessedGridDataRepresentation",
    "5.40" => "JpegGridDataRepresentation",
    "5.41" => "PngGridDataRepresentation",
    "5.42" => "SpectralGridDataRepresentation",
    "5.50" => "SpectralDataRepresentation",
    "5.51" => "SphericalHarmonicsDataRepresentation",
    "5.61" => "LogarithmicGridDataRepresentation",
    "5.40000" => "UNUSED", // use 5.40 instead
    "5.40010" => "UNUSED", // use 5.41 instead
    "5.50000" => "ComplexSphericalHarmonicsDataRepresentation",
    "5.50001" => "UNUSED", // documentation???
    "5.50002" => "UNUSED", // documentation???

    "7.second_order" => "ComplexPackingSettings",
    "second_order" => "UNUSED",

    "7.0" => "GridData",
    "7.1" => "MatrixData",
    "7.2" => "ComplexGridData",
    "7.3" => "ComplexDifferenceGridData",
    "7.4" => "FloatingPointGridData",
    "7.6" => "PreprocessedGridData",
    "7.40" => "JpegGridData",
    "7.41" => "PngGridData",
    "7.42" => "SpectralGridData",
    "7.50" => "SpectralData",
    "7.51" => "SphericalHarmonicsData",
    "7.61" => "LogarithmicGridData",
    "7.40000" => "UNUSED",
    "7.40010" => "UNUSED",
    "7.50000" => "ComplexSphericalHarmonicsData",
    "7.50001" => "UNUSED",
    "7.50002" => "UNUSED"
);

$nohash = array (
    "mEarthShape" => "",
    "mBasicAngleOfTheInitialProductionDomain" => "",
    "mSubdivisionsOfBasicAngle" => "",
    "mResolution" => "",
    "mResolutionAndComponentFlag" => "",
    "mLongitudeOfLastGridPoint" => "",
    "mLatitudeOfLastGridPoint" => ""
);

/*
 * Processed lines:
 * - byte[16]
 * - codetable[1]
 * - codetable[2]
 * - flags[1]
 * - flags [1]
 * - ieeefloat
 * - include
 * - unsigned[1], unsigned[2], unsigned[3], unsigned[4]
 * - signed[1], signed[2], signed[4]
 */

define ( 'PADDING', 30 );

$templateFile = $argv [1];
$name = substr ( $templateFile, strpos ( $templateFile, "template." ) + 9, - 4 );
$class = $templates [$name];
$outdir = $argv [2];

// print "TemplateFile : " . $templateFile . "\n";
// print "Name : " . $name . "\n";
// print "Class : " . $class . "\n";
// print "Outdir : " . $outdir . "\n";

if (! isset ( $class ))
  echo str_pad ( $name, PADDING ), "UNKNOWN\n";
else if ($class == "UNUSED")
  echo str_pad ( $name, PADDING ), "UNUSED\n";
else
{
  echo str_pad ( $name, PADDING ), "--> $class\n";
  process_template ( $templateFile, $name, $class, $outdir );
}





function process_template($file, $name, $class, $outdir)
{
  // We need to find class names for includes
  global $templates, $parents, $nohash;

  // Variable replacements. Note that if the row is of the form
  //
  // codetable[1] stepUnits 'stepUnits.table' = 1 : transient,dump,no_copy;
  //
  // there is no actual data in the file. Seems like what is needed a
  // no_copy field plus an assigment.

  $variables = array (
      'byte\s*\[16\]' => 'std::array<char,16>',
      'codetable\s*\[1\]' => 'T::UInt8_opt',
      'codetable\s*\[2\]' => 'T::UInt16_opt',
      'flags\s*\[1\]' => 'std::uint8_t',
      'ieeefloat' => 'float',
      'unsigned\s*\[1\]' => 'T::UInt8_opt',
      'unsigned\s*\[2\]' => 'T::UInt16_opt',
      'unsigned\s*\[3\]' => 'T::UInt24_opt',
      'unsigned\s*\[4\]' => 'T::UInt32_opt',
      'signed\s*\[1\]' => 'T::Int8_opt',
      'signed\s*\[2\]' => 'T::Int16_opt',
      'signed\s*\[4\]' => 'T::Int32_opt'
  );

  $realtypes = array (
      'std::array<char,16>' => 'const std::array<char,16> &',
      'float' => 'float',
      'std::uint8_t' => 'std::uint8_t',
      'std::uint16_t' => 'std::uint16_t',
      'T::UInt8_opt' => 'const T::UInt8_opt &',
      'T::UInt16_opt' => 'const T::UInt16_opt &',
      'T::UInt24_opt' => 'const T::UInt24_opt &',
      'T::UInt32_opt' => 'const T::UInt32_opt &',
      'T::Int8_opt' => 'const T::Int8_opt &',
      'T::Int16_opt' => 'const T::Int16_opt &',
      'T::Int32_opt' => 'const T::Int32_opt &'
  );

  // Generated member names in order of generation
  $members = array ();

  // The types of the generated variables
  $cpptypes = array ();

  // Respective code table if any
  $codetables = array ();

  // Respective flag table if any
  $flagtables = array ();

  $getters = "";
  $setters = "";

  // ********** generate the header **********

  $parentdecl = "";
  $parent = "";

  $section = extract_section ( $name );
  if (isset ( $section ) && isset ( $parents [$section] ))
  {
    $parent = $parents ["$section"];
    $parentdecl = " : public $parent";
    $headers ["\"../${parent}.h\""] = true;
  }

  $header  = "// ***********************************************************************\n";
  $header .= "//                      DO NOT EDIT THIS FILE !!!\n";
  $header .= "// ***********************************************************************\n";
  $header .= "//   This file is automatically generated from the grib_api templates. All\n";
  $header .= "//   changes will be overridden. If you want to do permanent changes then\n";
  $header .= "//   you should write them into the '${class}Impl.*' files.\n";
  $header .= "// ***********************************************************************\n\n"; 
  $header .= "#pragma once\n";

  $body = "\n\nnamespace SmartMet\n";
  $body .= "{ namespace GRIB2";
  $body .= "{\n/*! \brief The class is automatically created from the template ($name).*/\n\n";
  $body .= "class $class $parentdecl\n";
  $body .= "{ public:\n";
  $body .= "${class}();\n";
  $body .= "${class}(const ${class}& other);\n";
  $body .= "virtual ~${class}();\n\n";
   
  $p = explode(".", $name);
  if (($p[0] == "3" || $p[0] == "4" ||  $p[0] == "5"  || $p[0] == "7") &&  is_numeric($p[1]))
  {  
    $body .= "virtual uint getTemplateNumber() const;\n";
    
    if ($parent > " ")
      $body .= "virtual ${parent}* create${parent}() const;\n";
  }

  $body .= "virtual void read(MemoryReader& memoryReader);\n";
  $body .= "virtual void write(DataWriter& dataWriter);\n";
  $body .= "virtual void getAttributeList(std::string prefix,T::AttributeList& attributeList) const;\n";
  $body .= "virtual void print(std::ostream& stream,uint level,uint optionFlags) const;\n";
  $body .= "virtual T::Hash countHash();\n\n";

  $protected = "\n\nprotected:\n\n";
 
  $footer = "\n};\n\n} // namespace GRIB2\n} // namespace SmartMet\n";

  $rows = file ( $file );

  $hash = "";

  $skippedcode = "\n";
  foreach ( $rows as $row )
  {
    $skippedcode .= "// $row";
    $line = $row;
    trim ( $line );
    if (empty ( $line ))
      continue;

    if (preg_match ( "/\s*include/", $row ))
    {
      $protected .= $skippedcode . "\n";
      $skippedcode = "\n";
      $incname = extract_include ( $line );
      $incclass = $templates [$incname];
      if (isset ( $incclass ))
      {
        // variable name = class name without trailing "settings"
        $var = $incclass;
        if (substr ( $var, - 8 ) == "Settings")
          $var = substr ( $var, 0, - 8 );
        $var = lcfirst ( $var );
        $Var = ucfirst ( $var );

        $body .= "$incclass * get$Var() const;";

        $getters .= "\n/*! \brief The method returns the pointer to the {@link m${Var}} attribute. */\n\n";        
        $getters .= "$incclass * ${class}::get$Var() const { try { return static_cast<${incclass}*>(&m${Var}); } catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}\n}\n\n";

        $body .= "void set$Var($incclass& $var);";
        $setters .= "void ${class}::set$Var($incclass& $var) { try { m${Var} = $var; } catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}\n}\n\n";

        $protected .= "mutable $incclass m$Var;\n";
        $headers ["\"${incclass}.h\""] = 1;

        $members [$Var] = "class";
      }
    } 
    else
    {
      foreach ( $variables as $vartype => $cpptype )
      {
        if (preg_match ( "/\s*$vartype\s+(\w+)/", $row, $matches ))
        {
          if (is_phony_data ( $row ))
          {
            $skippedcode .= "// (The above is a phony setting)\n";
          } 
          else
          {
            $protected .= $skippedcode . "\n";
            $skippedcode = "\n";

            $var = $matches [1]; // for method names
            $var = lcfirst ( $var );
            $Var = ucfirst ( $var ); // for variable names prefixed with lower case 'm'

            $realtype = $realtypes [$cpptype];

            $protected .= "$cpptype m$Var;\n";

            $cpptypes [$Var] = $cpptype;
    	      $prefix = "";    	    
    	      
    	      if (isset($nohash["m$Var"])) { $prefix = "//"; }

            if (substr ( $vartype, 0, 4 ) == "byte")
            {
              $body .= "$realtype get$Var() const;\n";
              $getters .= "\n/*! \brief The method returns the value of the {@link m${Var}} attribute. */\n\n";        
              $getters .= "$realtype ${class}::get$Var() const { try { return m${Var}; } catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}\n}\n\n";

              $body .= "void set$Var($cpptype $var);\n";
              $setters .= "void ${class}::set$Var($cpptype $var) { try { m${Var} = $var; } catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}\n}\n\n";

              $headers ["<array>"] = 1;
              $members [$Var] = "normal";
              if (strpos($realtype, "boost::optional") > 0 or strpos($realtype, "_opt") > 0)
                $hash .= "${prefix} if (m${Var}) boost::hash_combine(seed,*m${Var});\n";
              else
                $hash .= "${prefix} boost::hash_combine(seed,m${Var});\n";
            } 
            else if (substr ( $vartype, 0, 9 ) == "codetable")
            {
              $body .= "$realtype get$Var() const;\n";
              $getters .= "\n/*! \brief The method returns the value of the {@link m${Var}} attribute. */\n\n";        
              $getters .= "$realtype ${class}::get$Var() const { try { return m${Var}; } catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}\n}\n\n";

              $body .= "void set$Var($cpptype $var);\n";
              $setters .= "void ${class}::set$Var($cpptype $var) { try { m${Var} = $var; } catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}\n}\n\n";

              $members [$Var] = "codetable";
              $codetables [$var] = extract_codetable ( $row );
              if (strpos ( $realtype, "boost::optional" ) > 0  or  strpos($realtype, "_opt") > 0)
                $hash .= "${prefix} if (m${Var}) boost::hash_combine(seed,*m${Var});\n";
              else
                $hash .= "${prefix} boost::hash_combine(seed,m${Var});\n";
            } 
            else if (substr ( $vartype, 0, 5 ) == "flags")
            {
              $body .= "$realtype get$Var() const;\n";
              $getters .= "\n/*! \brief The method returns the value of the {@link m${Var}} attribute. */\n\n";        
              $getters .= "$realtype ${class}::get$Var() const { try { return m${Var}; } catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}\n}\n\n";

              $body .= "void set$Var($cpptype $var);\n";
              $setters .= "void ${class}::set$Var($cpptype $var) { try { m${Var} = $var; } catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}\n}\n\n";

              $members [$Var] = "flagtable";
              $flagtables [$var] = extract_flagtable ( $row );
              if (strpos($realtype,"boost::optional") > 0  or strpos($realtype, "_opt") > 0)              
                $hash .= "${prefix} if (m${Var}) boost::hash_combine(seed,*m${Var});\n";
              else
                $hash .= "${prefix} boost::hash_combine(seed,m${Var});\n";
            } 
            else
            {
              $body .= "$realtype get$Var() const;\n";
              $getters .= "\n/*! \brief The method returns the value of the {@link m${Var}} attribute. */\n\n";        
              $getters .= "$realtype ${class}::get$Var() const { try { return m${Var}; } catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}\n}\n\n";

              $body .= "void set$Var($cpptype $var);\n";
              $setters .= "void ${class}::set$Var($cpptype $var) { try { m${Var} = $var; } catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}\n}\n\n";

              $members [$Var] = "normal";
              if (strpos ( $realtype, "boost::optional" ) > 0  or strpos($realtype, "_opt") > 0)
                $hash .= "${prefix} if (m${Var}) boost::hash_combine(seed,*m${Var});\n";
              else
                $hash .= "${prefix} boost::hash_combine(seed,m${Var});\n";
            }
          }
          break;
        }
      }
    }
  }

  // Add unique includes
  $headers ['"../../common/DataWriter.h"'] = true;
  $headers ['"../../common/MemoryReader.h"'] = true;
  $headers ['"../../common/AttributeList.h"'] = true;
  $headers ['"../../grid/Typedefs.h"'] = true;

  $headers = array_keys ( $headers );

  sort ( $headers );
  foreach ( $headers as $h )
    $header .= "#include $h\n";

  $output = $header . $body . $protected . $skippedcode . $footer;
  $outfile = $outdir . "/" . $class . ".h";
  file_put_contents ( $outfile, $output );
  system ( "clang-format -i -style=file $outfile" );


  // ********** generate the cpp file **********

  $outfile = $outdir . "/" . $class . ".cpp";

  $cpp  = "// ***********************************************************************\n";
  $cpp .= "//                      DO NOT EDIT THIS FILE !!!\n";
  $cpp .= "// ***********************************************************************\n";
  $cpp .= "//   This file is automatically generated from the grib_api templates. All\n";
  $cpp .= "//   changes will be overridden. If you want to do permanent changes then\n";
  $cpp .= "//   you should write them into the '${class}Impl.*' files.\n";
  $cpp .= "// ***********************************************************************\n\n"; 
  $cpp .= "#include \"${class}.h\"\n";
  $cpp .= "#include \"../../common/GeneralFunctions.h\"\n";
  $cpp .= "#include \"../../common/GeneralDefinitions.h\"\n";
  $cpp .= "#include <macgyver/Exception.h>\n";
  $cpp .= "#include <iostream>\n";
  $cpp .= "#include <boost/functional/hash.hpp>\n";

  $cpp .= "\n";

  $cpp .= "namespace SmartMet { namespace GRIB2 {\n";




  // ##### Adding the constructor.

  $cpp .= "\n/*! \brief The constructor of the class. */\n\n";

  $cpp .= "${class}::${class}() { try {\n";

  foreach ( $members as $Var => $type )
  {
    $var = lcfirst ( $Var );

    if ($type == "class")
      ; 
    else
    {
      $cpptype = $cpptypes [$Var];
      if (substr ( $cpptype, - 2 ) == "_t")
	    $cpp .= "m$Var = 0;";
      else if ($cpptype == "float")
	    $cpp .= "m$Var = 0;";
      else if ($cpptype == "std::array<char,16>")
	    $cpp .= "m$Var = {0};";
    }
  }
  $cpp .= "} catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}}\n\n";




  // ##### Adding the copy constructor.

  $cpp .= "\n/*! \brief The copy constructor of the class. */\n\n";

  $cpp .= "${class}::${class}(const ${class}& other)\n";
  
  if ($parent > " ")
    $cpp .= ":${parent}(other)\n";  

  $cpp .= "{ try {\n";

  foreach ( $members as $Var => $type )
  {
    $cpp .= "m$Var = other.m$Var;\n";
  }

  $cpp .= "} catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}}\n\n";




  // ##### Adding the destructor.

  $cpp .= "\n/*! \brief The destructor of the class. */\n\n";
  $cpp .= "${class}::~${class}() {\n}\n\n";




  // ##### Adding the read method.
  
  $cpp .= "\n/*! \brief The method reads and initializes all data related to the current object.\n\n";
  $cpp .= "        \param memoryReader  This object controls the access to the memory mapped file.\n";
  $cpp .= "*/\n\n";
  
  $cpp .= "void ${class}::read(MemoryReader& memoryReader) {\n try {\n";

  foreach ( $members as $Var => $type )
  {
    $var = lcfirst ( $Var );

    if ($type == "class")
      $cpp .= "m$Var.read(memoryReader);\n";
    else
    {
      $cpp .= "m$Var = ";
      $cpptype = $cpptypes [$Var];
      if (substr ($cpptype,0,3) == "T::")
        $cpp .= "memoryReader.read_" . substr($cpptype, strlen( "T::" ), 100 ) . "();\n";
      else
      if (substr ( $cpptype, - 2 ) == "_t")
        $cpp .= "memoryReader.read_" . substr($cpptype, strlen( "std::" ), - 2 ) . "();\n";
      else if ($cpptype == "float")
        $cpp .= "memoryReader.read_float();\n";
      else if ($cpptype == "std::array<char,16>")
        $cpp .= "memoryReader.read_uuid();\n";
      else
        $cpp .= "SHIT";
    }
  }
  $cpp .= "} catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}}\n\n";




  // ##### Adding the writer method.
  
  $cpp .= "\n/*! \brief The method writes all data related to the current object.\n\n";
  $cpp .= "        \param dataWriter  This object is used for writing the object data.\n";
  $cpp .= "*/\n\n";
  
  $cpp .= "void ${class}::write(DataWriter& dataWriter) {\n try {\n";

  foreach ( $members as $Var => $type )
  {
    $var = lcfirst ( $Var );

    if ($type == "class")
      $cpp .= "m$Var.write(dataWriter);\n";
    else
      $cpp .= "dataWriter << m$Var;\n";
  }
  $cpp .= "} catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}}\n\n";




  // ##### Adding the getAttributeList method.

  $cpp .= "/*! \brief The method is used for collecting the current class attributeList.\n\n";

  $cpp .= "    \param prefix         The prefix of the each attributeList parameter.\n";
  $cpp .= "    \param attributeList  The attributeList storage.\n";
  $cpp .= "*/\n\n";

  $cpp .= "void ${class}::getAttributeList(std::string prefix,T::AttributeList& attributeList) const { ";
  $cpp .= "try {";
  
  if (!empty($members))
    $cpp .= "char name[300];";

  foreach ( $members as $member => $type )
  {
    $method = lcfirst ( $member );

    if ($type == "class")
    {
      $cpp .= "sprintf(name,\"%s${class}.\",prefix.c_str());\n";
      $cpp .= "m${member}.getAttributeList(name,attributeList);\n";
    } 
    else
    {
      $cpp .= "sprintf(name,\"%s${class}.$member\",prefix.c_str());\n";
      $cpp .= "attributeList.addAttribute(name,toString(m${member}));\n";
    }
  }
  $cpp .= "} catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}}\n\n";


  
  
  // ##### Adding the print method.

  $cpp .= "/*! \brief The method prints the content of the current object into the given stream.\n\n";

  $cpp .= "    \param ostream      The output stream.\n";
  $cpp .= "    \param level        The print level (used when printing multi-level structures).\n";
  $cpp .= "    \param optionFlags  The printing options expressed in flag-bits.\n";
  $cpp .= "*/\n\n";

  $cpp .= "void ${class}::print(std::ostream& stream,uint level,uint optionFlags) const { ";
  $cpp .= "try {"; 
  $cpp .= "stream << space(level) << \"${class}\\n\";";

  foreach ( $members as $member => $type )
  {
    //$codetable = @$codetables [$member];
    //$flagtable = @$flagtables [$member];

    $method = lcfirst ( $member );

    if ($type == "class")
    {
      $cpp .= "m${member}.print(stream,level+1,optionFlags);";
      $prefix = "";
      if (isset($nohash["m${member}"])) { $prefix = "//";}
      $hash .= "${prefix} boost::hash_combine(seed,m${member}.countHash());\n";
    } 
    else
    {
      $cpp .= "stream << space(level) << \"- $member = \" << toString(m${member}) << \"\\n\";\n";
    }
  }
  $cpp .= "} catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}}\n\n";



  
  // ##### Adding the hash method.

  $cpp .= "\n/*! \brief The method counts the hash value of the current object. */\n\n";

  $cpp .= "T::Hash ${class}::countHash() { try { std::size_t seed = 0;\n${hash} return seed;\n";
  $cpp .= "} catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}}\n\n";


  
  
  if (($p[0] == "3" || $p[0] == "4" ||  $p[0] == "5"  || $p[0] == "7") &&  is_numeric($p[1]))
  {    
  // ##### Adding the getTemplateNumber method.
 
    $cpp .= "\n/*! \brief The method return the template number of the current class. */\n\n";
    $cpp .= "uint ${class}::getTemplateNumber() const {return ${p[1]};}\n\n";

    
    // ##### Adding the create method.
    
    if ($parent > " ")
    {
      $cpp .= "${parent}* ${class}::create${parent}() const\n";
      $cpp .= "{ try { return static_cast<${parent}*>(new ${class}(*this));\n";
      $cpp .= "} catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}}\n\n";
    }    
  }



  // ##### Adding the getters.

  $cpp .= $getters;




  // ##### Adding the setters.

  $cpp .= $setters;




  // $cpp .= $extracode;

  $cpp .= "\n} // namespace GRIB2\n} // namespace SmartMet\n";



  file_put_contents ( $outfile, $cpp );
  system ( "clang-format -i -style=file $outfile" );
}





// Assuming string of form 'include "template.filename.def" ... ' return filename
function extract_include($line)
{
//  preg_match ( '/\s*include\s+"template\.([\w.]+)\.def"/', $line, $matches );
//  return $matches [1];

  $name = substr ( $line, strpos ( $line, "\"grib2/template." ) + 16, - 1 );
  $name2 = substr ( $name, 0, strpos ( $name, ".def" ) );
  return $name2;
}




/*
 * Assuming lines of form
 *
 * codetable[X] shapeOfTheEarth ('3.2.table',masterDir,localDir) ...
 * codetable[X] partitionNumber ('4.[partitionTable].table',masterDir,localDir) ...
 * codetable[X] parameterCategory ('4.1.[discipline:l].table',masterDir,localDir) ...
 * codetable[X] parameterNumber ('4.2.[discipline:l].[parameterCategory:l].table',masterDir,localDir) ..
 * codetable[X] spatialProcessing 'grib2/tables/[tablesVersion]/4.15.table'
 *
 * extract the table name apart from the .table suffix. Note that we will detect
 * parameterCategory and parameterNumber as special cases else where and handle
 * them without the need to know the discipline and parameterCategory.
 *
 * No idea why these are used:grib2/tables/[tablesVersion]/4.15.table
 * Why not just use ('4.15.table',masterDir,localDir) ???
 * To prevent local tables?
 */

function extract_codetable($line)
{
  preg_match ( "/\s*codetable\[\d+\]\s*\w+.*'(.*)\.table'/", $line, $matches );
  $match = $matches [1];

  // Replace a special case with an easier reference
  if (strncmp ( $match, 'grib2/tables/[tablesVersion]/', 29 ) == 0)
    $match = substr ( $match, 29 );
  return $match;
}





/*
 * Assuming lines similar to codetables but with "flags" instead of "codetable"
 * extract the table name.
 */

function extract_flagtable($line)
{
  preg_match ( "/\s*flags\s*\[\d+\]\s*\w+.*'(.*)\.table'/", $line, $matches );
  $match = $matches [1];

  // Replace a special case with an easier reference
  if (strncmp ( $match, 'grib2/tables/[tablesVersion]/', 29 ) == 0)
    $match = substr ( $match, 29 );
  return $match;
}





/*
 * Extract section number from template name. For example "3.1" ==> "3".
 * Note that names such as 3.foo are not allowed
 */

function extract_section($name)
{
  $pos = strpos ( $name, "." );
  if (is_numeric ( substr ( $name, $pos + 1 ) ))
    return substr ( $name, 0, $pos );
  return null;
}





// Phony line:
//
// codetable[1] stepUnits 'stepUnits.table' = 1 : transient,dump,no_copy;
//
// because of assignment and transient (just guessing)

function is_phony_data($line)
{
  if (strpos ( $line, "transient" ) != 0 && strpos ( $line, "=" ) != 0)
    return true;
  else
    return false;
}


