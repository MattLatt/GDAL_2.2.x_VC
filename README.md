# GDAL_2.2.x_VC
==============================================================================
This repository contain Visual C++ 2010 workspace of the GDAL 2.2.x library (http://gdal.org)

    1. The Folder gdal-2.2.0 contain the 01/20/2017 gdal 2.2.0 source release
	(http://download.osgeo.org/gdal/2.2.0/gdal220.zip). The file ./gdal-2.2.0/port/cpl_config.h.vc has been 
	renamed into ./gdal-2.2.0/port/cpl_config.h in order to compile with MS visual C++ and the file 
	./gdal-2.2.0/gcore/Version.rc has been slightly modified (including gdal_version.h instead of gdal.h)
	to avoid the RC1015 error compilation I have with VS 2010. I kept a copy of the original file provided
	by OSgeo (./gdal-2.2.0/gcore/Version.rc.orig).

	2. The folder libgdal-2.2.0 contain a MS Visual Studio Solution with all the workspaces and a "binaries"
	sub-folder with each architecture and configuration binaries copied by VC post-build steps.
	There is both dynamic (dll) and static workspaces (lib) of GDAL 2.2.0 with 5 test workspaces:
	
		2.1. test_dynamic_gdalbuildvrt workspace:
		this is the gdalbuildvrt code provided by gdal (in the app folder of the source package) in a 
		"windows console" workspace dynamically linked to GDAL 2.2.0

		2.2. test_dynamic_ogr2ogr workspace:
		this is the ogr2ogr code provided by gdal (in the app folder of the source package) in a 
		"windows console" workspace dynamically linked to GDAL 2.2.0
	
		2.3. test_static_libgdal-2.2.0 workspace:
		this is a simple console program that dump all the supported drivers (GDAL/OGR) with theire 
		capabilities (i.e. Read/Write)
		
		2.4. test_static_gdalinfo workspace:
		this is the gdalinfo code provided by gdal (in the app folder of the source package) in a 
		"windows console" workspace statically linked to GDAL 2.2.0
		
		2.5. test_dynamic_gdal_envvars_internals workspace:
		this is a simple console program dynamically linked to GDAL 2.2.0 that show how to set env vars 
		with C++, so you may not use the GDAL Cmd console.
	
		2.6. gdal_rename workspace:
		This is still a work in progress. The goal of this project is to allow to rename GDALDatasets regarding
		the geographic metadatas (ie coordinates).
		It was designed to run on tiled datasets as aerial orthophotos splited in 1 sq km tiles for example.
		For now it is working only with GTiff datasets.
		
	3. The 3rdpart folder contain the libraries not provided internally by GDAL and necessary for some format
	I choosed to add (OSM, ECW...). For now it contain the libexpat 2.4.0 (linked dynamically), 
	Proj.4 lib V4.9.2 (linked dynamically), ECW 4.3 SDK (linked dynamically), libcurl 7.49.1 (linked dynamically),
	lib geos 3.5.0 (linked dynamically), lib hdf5 1.8.17, lib Xerces 3.1.4 and libsqlite 3.12 amalgamation included in the GDAL workspaces.
	
It contain too a dump (made by test_static_libgdal-2.2.0.exe) that print out all the supported drivers with
theire capabilites in ods and txt format : SupportedDrivers.ods and SupportedDrivers.txt

/!\ Due to GitHub (free version) limitation I've deleted the static version of gdal-2.2.0.lib (more than 650 MB),
so you will have to rebuild the static lib version to build the "test_static_XX workspaces".


## 2017-05-29:	
	1. READEME.md, SupportedDrivers.txt, SupportedDrivers.ods modification to be up-to-date. 

## 2017-05-19:	
	1. Added Lib Xerces 3.1.4 for some drivers

## 2017-05-16:	
	1. Compiled with the 04/28/2017 GDAL 2.2.0 Release	


