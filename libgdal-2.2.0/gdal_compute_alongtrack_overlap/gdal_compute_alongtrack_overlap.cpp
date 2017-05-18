//##################################################################################//
//						gdal_compute_alongtrack_overlap								//
//**********************************************************************************//
// Desc: Command line executable to compute overlap between to aerial image			//
//		 footprints.																//
//		 																			//
// Author: 	Mathieu Lattes (mathieu.lattes@yahoo.fr)								//
//																					//
//		 																			//
// Version:	v0.0.5_20170303-01 : Added double coord formating						//
//		 																			//
// ToDo: Full test with other drivers												//
//																					//
//**********************************************************************************//
// History:	v0.0.4_20170228-01 : Added Coord Sign Policy							//
//			v0.0.3_20170224-01 : Small buggs fixs (only first companion file renamed//
//								, Missing EQUAL() for -f test...					//
//			v0.0.2_20170106-01 : using std lib instead of char * as str container	//
//			v0.0.1 : initial release without std lib								//
//																					//
//##################################################################################//

#include <iostream>

#include "gdal_priv.h"
#include "ogrsf_frmts.h"

#include "commonutils.h"

#include "cpl_error.h"
#include "cpl_conv.h"
#include "cpl_vsi.h"
#include <string>


#include <boost/variant.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>


	//Declaration of a variant type object for possible value in fields
	typedef boost::variant< int, std::string, double, GIntBig> OgrFieldsVal;

	//*********************************************************************
	//!Update value of a field
	//*********************************************************************
	bool UpdateFieldVal (OGRFeature *poInFeature, const char* FieldName, OgrFieldsVal newVal )
		{
		bool Success = true;
		int iField = 0;
		int fieldCount = 0;
		std::vector<OgrFieldsVal>::iterator it;

		OGRFeatureDefn *poFDefn = poInFeature->GetDefnRef();

		fieldCount = poFDefn->GetFieldCount();
		//OGRFeatureDefn *poFDefn = poOutLayer->GetLayerDefn();
		//OGRFeature *poOutFeature = OGRFeature::CreateFeature( poOutLayer->GetLayerDefn() );

		//poOutFeature->SetFrom(poInFeature);


		for (int indF =0 ; indF <= fieldCount ; ++indF)
			{
			OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn( iField );
			const char *curFieldName = poFieldDefn->GetNameRef();
			
			if ( EQUAL(curFieldName,FieldName) )
				{
				OGRFieldType FType = poFieldDefn->GetType();

				if (FType == OFTString)
					{ poInFeature->SetField(FieldName, boost::get<std::string>(newVal).c_str());}
				else if (FType == OFTInteger)
					{ poInFeature->SetField(FieldName, boost::get<int>(newVal));}
				else if (FType == OFTReal)
					{ poInFeature->SetField(FieldName, boost::get<double>(newVal));}
				else if (FType == OFTInteger64)
					{ poInFeature->SetField(FieldName, boost::get<GIntBig>(newVal));}
				++iField;
				}
			}

		return Success;
		}


int main(int argc, char* argv[])
	{
    ::EarlySetConfigOptions(argc, argv);

    ::GDALAllRegister();

	//const char *pszFilePath = "C:\\Users\\Mathieu\\Desktop\\###ATrier\\Mayotte\\1609XX_MAYOTTE16_emprises2.shp";
	//const char *pszSQLStatement = "SELECT * FROM \"1609XX_MAYOTTE16_emprises2\" ORDER BY ImgNumber";												
	const char *pszFilePath = "K:\\AppliGIT\\AeroOfficeKmlToShp\\170412_AUVERGNE2017_Jobsite_Footprints.shp";
	const char *pszSQLStatement = "SELECT * FROM \"170412_AUVERGNE2017_Jobsite_Footprints\" ORDER BY ImgNumber";												

    argc = GDALGeneralCmdLineProcessor( argc, &argv, 0 );
    if( argc > 1 )
		{
		for( int i = 0; argv != NULL && argv[i] != NULL; i++ )
			{
			/*
			if( EQUAL(argv[i], "--set-gdaldata-path") )
				{ pszGdalDataPath = argv[i+1]; }

			if( EQUAL(argv[i], "--set-projlib-path") )
				{ pszProjLibPath = argv[i+1]; }
				*/

			if( EQUAL(argv[i], "--shp-to-process") )
				{ pszFilePath = argv[i+1]; }

			}
		}

    GDALDataset  *poDataset = NULL;

	std::string inputDataset = pszFilePath;
	
	std::string filename = ::CPLGetFilename(pszFilePath);
	std::string direname = ::CPLGetDirname(pszFilePath);
	std::string basename = ::CPLGetBasename(pszFilePath);
	//std::string pathname = ::CPLGetPath(pszFilePath);

	std::string outputDataset = direname;

	poDataset = (GDALDataset *) ::GDALOpenEx( inputDataset.c_str(), GDAL_OF_VECTOR, NULL, NULL, NULL );
  
	if( poDataset != NULL )
		{
		OGRLayer  *poLayer;

		poLayer = poDataset->ExecuteSQL(pszSQLStatement, NULL, NULL);

		OGRFeature *poFeatureBack = NULL, *poFeatureCur = NULL;
		OGRGeometry *poGeometryBack = NULL, *poGeometryCur = NULL;
		poLayer->ResetReading();

		poFeatureBack = poLayer->GetNextFeature();
		poGeometryBack = poFeatureBack->GetGeometryRef();

		if ( poFeatureBack != NULL )
			{
			for (poFeatureCur = poLayer->GetNextFeature(); poFeatureCur != NULL ;poFeatureCur = poLayer->GetNextFeature() )
				{
				poGeometryCur = poFeatureCur->GetGeometryRef();
				if( poGeometryBack != NULL && poGeometryCur != NULL 
						&& wkbFlatten(poGeometryBack->getGeometryType()) == wkbPolygon
						&& wkbFlatten(poGeometryCur->getGeometryType()) == wkbPolygon )
					{
					OGRPolygon *poPolygonBack= (OGRPolygon *) poGeometryBack;
					OGRPolygon *poPolygonCur= (OGRPolygon *) poGeometryCur;

					OGRPoint poCenterBack;
					poPolygonBack->Centroid(&poCenterBack);

					double OverlapArea = 0.0;

					OGRGeometry *Overlap = poPolygonBack->Intersection(poPolygonCur);
					if( Overlap != NULL  && wkbFlatten(Overlap->getGeometryType()) == wkbPolygon )
						{
						OGRPolygon *poPolygonOverlap = (OGRPolygon *) Overlap;
						OverlapArea = poPolygonOverlap->get_Area()/poPolygonBack->get_Area()*100.0;
						//printf( "BackArea(%.9f) / CurArea(%.9f) / IntersectionArea(%.9f) / Overlap (%.3f) \n", poPolygonBack->get_Area(), poPolygonCur->get_Area(), poPolygonOverlap->get_Area(),poPolygonOverlap->get_Area()/poPolygonBack->get_Area()*100.0);
						}
					
					bool Success = UpdateFieldVal (poFeatureCur, "Overlap", OverlapArea);
					poLayer->SetFeature(poFeatureCur);

					}
				else
					{ printf( "no point geometry\n" );}


				//Retrieving the attibuts
				/*
				OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
				int iField;
				for( iField = 0; iField < poFDefn->GetFieldCount(); iField++ )
					{
					OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn( iField );
					if( poFieldDefn->GetType() == OFTInteger )
						printf( "%d,", poFeature->GetFieldAsInteger( iField ) );
					else if( poFieldDefn->GetType() == OFTInteger64 )
						printf( CPL_FRMT_GIB ",", poFeature->GetFieldAsInteger64( iField ) );
					else if( poFieldDefn->GetType() == OFTReal )
						printf( "%.3f,", poFeature->GetFieldAsDouble(iField) );
					else if( poFieldDefn->GetType() == OFTString )
						printf( "%s,", poFeature->GetFieldAsString(iField) );
					else
						printf( "%s,", poFeature->GetFieldAsString(iField) );
					}
				*/
					
					OGRFeature::DestroyFeature( poFeatureBack );
					poFeatureBack = poFeatureCur;
					poGeometryBack = poGeometryCur;
					int temp= 1;
				}
			}



		::GDALClose((GDALDatasetH)poDataset);
		int temp = 0;
		}

	return 0;
	}

