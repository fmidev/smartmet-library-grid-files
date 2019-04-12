#!/usr/bin/php -q
<?php

// Parents for main level classes
$parents = array (
    "LatLon" => "GridDefinition",
    "Mercator" => "GridDefinition",
    "Gnomonic" => "GridDefinition",
    "LambertConformal" => "GridDefinition",
    "Gaussian" => "GridDefinition",
    "PolarStereographic" => "GridDefinition",
    "TransverseMercator" => "GridDefinition",
    "SimplePolyconic" => "GridDefinition",
    "Albers" => "GridDefinition",
    "MillersCylindrical" => "GridDefinition",
    "RotatedLatLon" => "GridDefinition",
    "ObliqueLambertConformal" => "GridDefinition",
    "RotatedGaussian" => "GridDefinition",
    "StretchedLatLon" => "GridDefinition",
    "StretchedGaussian" => "GridDefinition",
    "StretchedRotatedLatLon" => "GridDefinition",
    "StretchedRotatedGaussian" => "GridDefinition",
    "SphericalHarmonic" => "GridDefinition",
    "RotatedSphericalHarmonic" => "GridDefinition",
    "StretchedSphericalHarmonic" => "GridDefinition",
    "StretchedRotatedSphericalHarmonic" => "GridDefinition",
    "SpaceView" => "GridDefinition"
);

// Class names for templates
$templates = array (
    "grid_definition_0" => "LatLon",
    "grid_definition_1" => "Mercator",
    "grid_definition.2" => "Gnomonic",
    "grid_definition_3" => "LambertConformal",
    "grid_definition_4" => "Gaussian",
    "grid_definition_5" => "PolarStereographic",
    "grid_definition_6" => "TransverseMercator",
    "grid_definition_7" => "SimplePolyconic",
    "grid_definition_8" => "Albers",
    "grid_definition_9" => "MillersCylindrical",
    "grid_definition_10" => "RotatedLatLon",
    "grid_definition_13" => "ObliqueLambertConformal",
    "grid_definition_14" => "RotatedGaussian",
    "grid_definition_20" => "StretchedLatLon",
    "grid_definition_24" => "StretchedGaussian",
    "grid_definition_30" => "StretchedRotatedLatLon",
    "grid_definition_34" => "StretchedRotatedGaussian",
    "grid_definition_50" => "SphericalHarmonic",
    "grid_definition_60" => "RotatedSphericalHarmonic",
    "grid_definition_70" => "StretchedSphericalHarmonic",
    "grid_definition_80" => "StretchedRotatedSphericalHarmonic",
    "grid_definition_90" => "SpaceView",
    "grid_rotation" => "RotationSettings",
    "scanning_mode" => "ScanningModeSettings",
    "grid_first_last_resandcomp" => "GridAreaSettings",
    "resolution_flags" => "ResolutionFlagsSettings",
    "grid_stretching" => "GridStretchingSettings"
);

$nohash = array (
    "mResolutionFlags" => "",
    "mZero" => "",
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
 * - ibmfloat
 * - include
 * - unsigned[1], unsigned[2], unsigned[4]
 * - signed[1], signed[2], signed[3], signed[4]
 * - ascii[4]
 */

define ( 'PADDING', 30 );

$templateFile = $argv [1];

$pos = strlen ( $templateFile ) - 1;
while ( $pos > 0 && $templateFile {$pos} != "/" )
  $pos = $pos - 1;

if ($pos > 0)
  $pos = $pos + 1;

$name = substr ( $templateFile, $pos, - 4 );

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
      'codetable\s*\[1\]' => 'std::uint8_t',
      'codetable\s*\[2\]' => 'std::uint16_t',
      'flags\s*\[1\]' => 'std::uint8_t',
      'ieeefloat' => 'float',
      'ibmfloat' => 'ibmfloat',
      'unsigned\s*\[1\]' => 'std::uint8_t',
      'unsigned\s*\[2\]' => 'std::uint16_t',
      'unsigned\s*\[3\]' => 'std::uint24_t',
      'unsigned\s*\[4\]' => 'std::uint32_t',
      'signed\s*\[1\]' => 'std::int8_t',
      'signed\s*\[2\]' => 'std::int16_t',
      'signed\s*\[3\]' => 'std::int24_t',
      'signed\s*\[4\]' => 'std::int32_t',
      'ascii\s*\[4\]' => 'std::uint32_t'
  );

  $realtypes = array (
      'std::array<char,16>' => 'const std::array<char,16> &',
      'float' => 'float',
      'ibmfloat' => 'ibmfloat',
      'std::uint8_t' => 'std::uint8_t',
      'std::uint16_t' => 'std::uint16_t',
      'std::uint24_t' => 'std::uint24_t',
      'std::uint32_t' => 'std::uint32_t',
      'std::int8_t' => 'std::int8_t',
      'std::int16_t' => 'std::int16_t',
      'std::int24_t' => 'std::int24_t',
      'std::int32_t' => 'std::int32_t'
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
  if (isset ( $class ) && isset ( $parents [$class] ))
  {
    $parent = $parents ["$class"];
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
  $body .= "{ namespace GRIB1";
  $body .= "{\n/*! \brief The class is automatically created from the template ($name).*/\n\n";
  $body .= "class $class $parentdecl\n";
  $body .= "{ public:\n";
  $body .= "${class}();\n";
  $body .= "${class}(const ${class}& other);\n";
  $body .= "virtual ~${class}();\n\n";

  $body .= "virtual void getAttributeList(std::string prefix,T::AttributeList& attributeList) const;\n";
  $body .= "virtual void read(MemoryReader& memoryReader);\n";
  $body .= "virtual void write(DataWriter& dataWriter);\n";
  $body .= "virtual void print(std::ostream& stream,uint level,uint optionFlags) const;\n";
  $body .= "virtual T::Hash countHash();\n\n";

  $p = explode("_", $name);
  if ($p[0] == "grid" && $p[1] == "definition" &&  is_numeric($p[2]))
  {  
    $body .= "virtual uint getTemplateNumber() const;\n";

    if ($parent > " ")
      $body .= "virtual ${parent}* create${parent}() const;\n";
  }
  
  $protected = "\n\nprotected:\n\n";

  $footer = "\n};\n\n} // namespace GRIB1\n} // namespace SmartMet\n";

  $rows = file ( $file );

  $hash = "";

  $allRows = array ();
  $rowCnt = 0;

  foreach ( $rows as $row )
  {
    $line = $row;
    trim ( $line );
    if (empty ( $line ))
      continue;

    $allRows [$rowCnt] = $row;
    $rowCnt = $rowCnt + 1;

    if (preg_match ( "/\s*template/", $row ))
    {
      $template_name = extract_template ( $line );

      $templateRows = file ( $template_name );

      foreach ( $templateRows as $tRow )
      {
        $allRows [$rowCnt] = $tRow;
        $rowCnt = $rowCnt + 1;
      }
    }
  }

  $skippedcode = "\n";
  foreach ( $allRows as $row )
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

        $body .= "$incclass * get$Var() const;\n";
    
        $getters .= "\n/*! \brief The method returns the pointer to the {@link m${Var}} attribute. */\n\n";        
        $getters .= "$incclass * ${class}::get$Var() const { try { return static_cast<${incclass}*>(&m${Var}); } catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}\n}\n\n";

        $body .= "void set$Var($incclass& $var);\n";
        $setters .= "void ${class}::set$Var($incclass& $var) { try { m${Var} = $var; } catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}\n}\n\n";
        
        $protected .= "mutable $incclass m$Var;\n";
        $headers ["\"${incclass}.h\""] = 1;

        $members [$Var] = "class";
      }
    } else
    {
      $modRow = str_replace ( ".", "_", $row );
      foreach ( $variables as $vartype => $cpptype )
      {
        if (preg_match ( "/\s*$vartype\s+(\w+)/", $modRow, $matches ))
        {
          if (is_phony_data ( $row ))
          {
            $skippedcode .= "// (The above is a phony setting)\n";
          } else
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
              $getters .= "\n/*! \brief The method returns the value of the {@linkm${Var}} attribute. */\n\n";        
              $getters .= "$realtype ${class}::get$Var() const { try { return m${Var}; } catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}\n}\n\n";

              $body .= "void set$Var($cpptype $var);\n";
              $setters .= "void ${class}::set$Var($cpptype $var) { try { m${Var} = $var; } catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}\n}\n\n";

              $headers ["<array>"] = 1;
              $members [$Var] = "normal";
              if (strpos ( $realtype, "boost::optional" ) > 0)
                $hash .= "${prefix} if (m${Var}) boost::hash_combine(seed,*m${Var});\n";
              else
                $hash .= "${prefix} boost::hash_combine(seed,m${Var});\n";
            } else if (substr ( $vartype, 0, 9 ) == "codetable")
            {
              $body .= "$realtype get$Var() const;\n";
              $getters .= "\n/*! \brief The method returns the value of the {@link m${Var}} attribute. */\n\n";        
              $getters .= "$realtype ${class}::get$Var() const { try { return m${Var}; } catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}\n}\n\n";

              $body .= "void set$Var($cpptype $var);\n";
              $setters .= "void ${class}::set$Var($cpptype $var) { try { m${Var} = $var; } catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}\n}\n\n";

              $members [$Var] = "codetable";
              $codetables [$var] = extract_codetable ( $row );
              if (strpos ( $realtype, "boost::optional" ) > 0)
                $hash .= "${prefix} if (m${Var}) boost::hash_combine(seed,*m${Var});\n";
              else
                $hash .= "${prefix} boost::hash_combine(seed,m${Var});\n";
            } else if (substr ( $vartype, 0, 5 ) == "flags")
            {
              $body .= "$realtype get$Var() const;\n";
              $getters .= "\n/*! \brief The method returns the value of the {@link m${Var}} attribute. */\n\n";        
              $getters .= "$realtype ${class}::get$Var() const { try { return m${Var}; } catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}\n}\n\n";

              $body .= "void set$Var($cpptype $var);\n";
              $setters .= "void ${class}::set$Var($cpptype $var) { try { m${Var} = $var; } catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}\n}\n\n";

              $members [$Var] = "flagtable";
              $flagtables [$var] = extract_flagtable ( $row );
              if (strpos ( $realtype, "boost::optional" ) > 0)
                $hash .= "${prefix} if (m${Var}) boost::hash_combine(seed,*m${Var});\n";
              else
                $hash .= "${prefix} boost::hash_combine(seed,m${Var});\n";
            } else
            {
              $body .= "$realtype get$Var() const;\n";
              $getters .= "\n/*! \brief The method returns the value of the {@link m${Var}} attribute. */\n\n";        
              $getters .= "$realtype ${class}::get$Var() const { try { return m${Var}; } catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}\n}\n\n";

              $body .= "void set$Var($cpptype $var);\n";
              $setters .= "void ${class}::set$Var($cpptype $var) { try { m${Var} = $var; } catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}\n}\n\n";

              $members [$Var] = "normal";
              if (strpos ( $realtype, "boost::optional" ) > 0)
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
  $cpp .= "#include \"../../common/Exception.h\"\n";
  $cpp .= "#include \"../../common/GeneralFunctions.h\"\n";
  $cpp .= "#include \"../../common/GeneralDefinitions.h\"\n";
  $cpp .= "#include <iostream>\n";
  $cpp .= "#include <boost/functional/hash.hpp>\n";
  $cpp .= "\n";
  $cpp .= "namespace SmartMet { namespace GRIB1 {\n";




  // ##### Adding the constructor

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




  // ##### Adding the copy constructor

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




  // ##### Adding the destructor

  $cpp .= "\n/*! \brief The destructor of the class. */\n\n";
  $cpp .= "${class}::~${class}() {\n}\n\n";


  // ##### Adding the read method.
  
  $cpp .= "\n/*! \brief The method reads and initializes all data related to the current section object.\n\n";
  $cpp .= "        \param memoryReader  This object controls the access to the memory mapped file. \n";
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
      else if ($cpptype == "ibmfloat")
        $cpp .= "memoryReader.read_ibmFloat();\n";
      else if ($cpptype == "std::array<char,16>")
        $cpp .= "memoryReader.read_uuid();\n";
      else
        $cpp .= "SHIT";
    }
  }
  $cpp .= "} catch (...) {throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);}}\n\n";



  
  // ##### Adding the write method.
  
  $cpp .= "\n/*! \brief The method writes all data related to the current section object.\n\n";
  $cpp .= "        \param dataWriter  This object controls the write stream. \n";
  $cpp .= "*/\n\n";

  $cpp .= "void ${class}::write(DataWriter& dataWriter) {\n try {\n";

  foreach ( $members as $Var => $type )
  {
    $var = lcfirst ( $Var );
    $cpptype = $cpptypes [$Var];

    if ($type == "class")
      $cpp .= "m$Var.write(dataWriter);\n";
    else if ($cpptype == "std::int24_t")
      $cpp .= "dataWriter.write_int24(m$Var);\n";
    else if ($cpptype == "std::uint24_t")
      $cpp .= "dataWriter.write_uint24(m$Var);\n";
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

  
  
   
  if ($p[0] == "grid" && $p[1] == "definition" &&  is_numeric($p[2]))
  {  
  
    // ##### Adding the getTemplateNumber method.
  
    $cpp .= "\n/*! \brief The method return the template number of the current class. */\n\n";
    $cpp .= "uint ${class}::getTemplateNumber() const {return ${p[2]};}\n\n";


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


  $cpp .= "\n} // namespace GRIB1\n} // namespace SmartMet\n";



  file_put_contents ( $outfile, $cpp );
  system ( "clang-format -i -style=file $outfile" );
}





// Assuming string of form 'include "filename.def" ... ' return filename
function extract_include($line)
{
  preg_match ( '/\s*include\s+"([\w.]+)\.def"/', $line, $matches );
  return $matches [1];
}





// Assuming string of form 'template commonBlock "grib1/filename.def" ... ' return filename
function extract_template($line)
{
  $templateDir = "/usr/share/grib_api/definitions/";
  $name = substr ( $line, strpos ( $line, "\"" ) + 1, - 1 );
  $name2 = substr ( $name, 0, strpos ( $name, "\"" ) );
  return $templateDir . $name2;
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


