# This file was automatically generated by SWIG (http://www.swig.org).
# Version 2.0.12
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.

package Geo::OSR;
use base qw(Exporter);
use base qw(DynaLoader);
package Geo::OSRc;
bootstrap Geo::OSR;
package Geo::OSR;
@EXPORT = qw();

# ---------- BASE METHODS -------------

package Geo::OSR;

sub TIEHASH {
    my ($classname,$obj) = @_;
    return bless $obj, $classname;
}

sub CLEAR { }

sub FIRSTKEY { }

sub NEXTKEY { }

sub FETCH {
    my ($self,$field) = @_;
    my $member_func = "swig_${field}_get";
    $self->$member_func();
}

sub STORE {
    my ($self,$field,$newval) = @_;
    my $member_func = "swig_${field}_set";
    $self->$member_func($newval);
}

sub this {
    my $ptr = shift;
    return tied(%$ptr);
}


# ------- FUNCTION WRAPPERS --------

package Geo::OSR;

*UseExceptions = *Geo::OSRc::UseExceptions;
*DontUseExceptions = *Geo::OSRc::DontUseExceptions;
*GetWellKnownGeogCSAsWKT = *Geo::OSRc::GetWellKnownGeogCSAsWKT;
*GetUserInputAsWKT = *Geo::OSRc::GetUserInputAsWKT;
*GetProjectionMethods = *Geo::OSRc::GetProjectionMethods;
*GetProjectionMethodParameterList = *Geo::OSRc::GetProjectionMethodParameterList;
*GetProjectionMethodParamInfo = *Geo::OSRc::GetProjectionMethodParamInfo;
*CreateCoordinateTransformation = *Geo::OSRc::CreateCoordinateTransformation;

############# Class : Geo::OSR::SpatialReference ##############

package Geo::OSR::SpatialReference;
use vars qw(@ISA %OWNER %ITERATORS %BLESSEDMEMBERS);
@ISA = qw( Geo::OSR );
%OWNER = ();
%ITERATORS = ();
use Carp;
sub new {
    my $pkg = shift;
    my %param = @_;
    my $self = Geo::OSRc::new_SpatialReference();
    if (exists $param{WKT}) {
        ImportFromWkt($self, $param{WKT});
    } elsif (exists $param{Text}) {
        ImportFromWkt($self, $param{Text});
    } elsif (exists $param{Proj4}) {
        ImportFromProj4($self, $param{Proj4});
    } elsif (exists $param{ESRI}) {
        ImportFromESRI($self, @{$param{ESRI}});
    } elsif (exists $param{EPSG}) {
        ImportFromEPSG($self, $param{EPSG});
    } elsif (exists $param{EPSGA}) {
        ImportFromEPSGA($self, $param{EPSGA});
    } elsif (exists $param{PCI}) {
        ImportFromPCI($self, @{$param{PCI}});
    } elsif (exists $param{USGS}) {
        ImportFromUSGS($self, @{$param{USGS}});
    } elsif (exists $param{XML}) {
        ImportFromXML($self, $param{XML});
    } elsif (exists $param{GML}) {
        ImportFromGML($self, $param{GML});
    } elsif (exists $param{URL}) {
        ImportFromUrl($self, $param{URL});
    } elsif (exists $param{ERMapper}) {
        ImportFromERM($self, @{$param{ERMapper}});
    } elsif (exists $param{ERM}) {
        ImportFromERM($self, @{$param{ERM}});
    } elsif (exists $param{MICoordSys}) {
        ImportFromMICoordSys($self, $param{MICoordSys});
    } elsif (exists $param{MapInfoCS}) {
        ImportFromMICoordSys($self, $param{MapInfoCS});
    } elsif (exists $param{WGS}) {
        eval {
            SetWellKnownGeogCS($self, 'WGS'.$param{WGS});
        };
        confess last_error() if $@;
    } else {
        error("Unrecognized/missing parameters: @_.");
    }
    bless $self, $pkg if defined $self;
}

sub DESTROY {
    return unless $_[0]->isa('HASH');
    my $self = tied(%{$_[0]});
    return unless defined $self;
    delete $ITERATORS{$self};
    if (exists $OWNER{$self}) {
        Geo::OSRc::delete_SpatialReference($self);
        delete $OWNER{$self};
    }
}

*IsSame = *Geo::OSRc::SpatialReference_IsSame;
*IsSameGeogCS = *Geo::OSRc::SpatialReference_IsSameGeogCS;
*IsSameVertCS = *Geo::OSRc::SpatialReference_IsSameVertCS;
*IsGeographic = *Geo::OSRc::SpatialReference_IsGeographic;
*IsProjected = *Geo::OSRc::SpatialReference_IsProjected;
*IsCompound = *Geo::OSRc::SpatialReference_IsCompound;
*IsGeocentric = *Geo::OSRc::SpatialReference_IsGeocentric;
*IsLocal = *Geo::OSRc::SpatialReference_IsLocal;
*IsVertical = *Geo::OSRc::SpatialReference_IsVertical;
*EPSGTreatsAsLatLong = *Geo::OSRc::SpatialReference_EPSGTreatsAsLatLong;
*EPSGTreatsAsNorthingEasting = *Geo::OSRc::SpatialReference_EPSGTreatsAsNorthingEasting;
*SetAuthority = *Geo::OSRc::SpatialReference_SetAuthority;
*GetAttrValue = *Geo::OSRc::SpatialReference_GetAttrValue;
*SetAttrValue = *Geo::OSRc::SpatialReference_SetAttrValue;
*SetAngularUnits = *Geo::OSRc::SpatialReference_SetAngularUnits;
*GetAngularUnits = *Geo::OSRc::SpatialReference_GetAngularUnits;
*GetAngularUnitsName = *Geo::OSRc::SpatialReference_GetAngularUnitsName;
*SetTargetLinearUnits = *Geo::OSRc::SpatialReference_SetTargetLinearUnits;
*SetLinearUnits = *Geo::OSRc::SpatialReference_SetLinearUnits;
*SetLinearUnitsAndUpdateParameters = *Geo::OSRc::SpatialReference_SetLinearUnitsAndUpdateParameters;
*GetTargetLinearUnits = *Geo::OSRc::SpatialReference_GetTargetLinearUnits;
*GetLinearUnits = *Geo::OSRc::SpatialReference_GetLinearUnits;
*GetLinearUnitsName = *Geo::OSRc::SpatialReference_GetLinearUnitsName;
*GetAuthorityCode = *Geo::OSRc::SpatialReference_GetAuthorityCode;
*GetAuthorityName = *Geo::OSRc::SpatialReference_GetAuthorityName;
*GetAxisName = *Geo::OSRc::SpatialReference_GetAxisName;
*GetAxisOrientation = *Geo::OSRc::SpatialReference_GetAxisOrientation;
*SetUTM = *Geo::OSRc::SpatialReference_SetUTM;
*_GetUTMZone = *Geo::OSRc::SpatialReference__GetUTMZone;
*SetStatePlane = *Geo::OSRc::SpatialReference_SetStatePlane;
*AutoIdentifyEPSG = *Geo::OSRc::SpatialReference_AutoIdentifyEPSG;
*SetProjection = *Geo::OSRc::SpatialReference_SetProjection;
*SetProjParm = *Geo::OSRc::SpatialReference_SetProjParm;
*GetProjParm = *Geo::OSRc::SpatialReference_GetProjParm;
*SetNormProjParm = *Geo::OSRc::SpatialReference_SetNormProjParm;
*GetNormProjParm = *Geo::OSRc::SpatialReference_GetNormProjParm;
*GetSemiMajor = *Geo::OSRc::SpatialReference_GetSemiMajor;
*GetSemiMinor = *Geo::OSRc::SpatialReference_GetSemiMinor;
*GetInvFlattening = *Geo::OSRc::SpatialReference_GetInvFlattening;
*SetACEA = *Geo::OSRc::SpatialReference_SetACEA;
*SetAE = *Geo::OSRc::SpatialReference_SetAE;
*SetBonne = *Geo::OSRc::SpatialReference_SetBonne;
*SetCEA = *Geo::OSRc::SpatialReference_SetCEA;
*SetCS = *Geo::OSRc::SpatialReference_SetCS;
*SetEC = *Geo::OSRc::SpatialReference_SetEC;
*SetEckertIV = *Geo::OSRc::SpatialReference_SetEckertIV;
*SetEckertVI = *Geo::OSRc::SpatialReference_SetEckertVI;
*SetEquirectangular = *Geo::OSRc::SpatialReference_SetEquirectangular;
*SetEquirectangular2 = *Geo::OSRc::SpatialReference_SetEquirectangular2;
*SetGaussSchreiberTMercator = *Geo::OSRc::SpatialReference_SetGaussSchreiberTMercator;
*SetGS = *Geo::OSRc::SpatialReference_SetGS;
*SetGH = *Geo::OSRc::SpatialReference_SetGH;
*SetIGH = *Geo::OSRc::SpatialReference_SetIGH;
*SetGEOS = *Geo::OSRc::SpatialReference_SetGEOS;
*SetGnomonic = *Geo::OSRc::SpatialReference_SetGnomonic;
*SetHOM = *Geo::OSRc::SpatialReference_SetHOM;
*SetHOM2PNO = *Geo::OSRc::SpatialReference_SetHOM2PNO;
*SetKrovak = *Geo::OSRc::SpatialReference_SetKrovak;
*SetLAEA = *Geo::OSRc::SpatialReference_SetLAEA;
*SetLCC = *Geo::OSRc::SpatialReference_SetLCC;
*SetLCC1SP = *Geo::OSRc::SpatialReference_SetLCC1SP;
*SetLCCB = *Geo::OSRc::SpatialReference_SetLCCB;
*SetMC = *Geo::OSRc::SpatialReference_SetMC;
*SetMercator = *Geo::OSRc::SpatialReference_SetMercator;
*SetMollweide = *Geo::OSRc::SpatialReference_SetMollweide;
*SetNZMG = *Geo::OSRc::SpatialReference_SetNZMG;
*SetOS = *Geo::OSRc::SpatialReference_SetOS;
*SetOrthographic = *Geo::OSRc::SpatialReference_SetOrthographic;
*SetPolyconic = *Geo::OSRc::SpatialReference_SetPolyconic;
*SetPS = *Geo::OSRc::SpatialReference_SetPS;
*SetRobinson = *Geo::OSRc::SpatialReference_SetRobinson;
*SetSinusoidal = *Geo::OSRc::SpatialReference_SetSinusoidal;
*SetStereographic = *Geo::OSRc::SpatialReference_SetStereographic;
*SetSOC = *Geo::OSRc::SpatialReference_SetSOC;
*SetTM = *Geo::OSRc::SpatialReference_SetTM;
*SetTMVariant = *Geo::OSRc::SpatialReference_SetTMVariant;
*SetTMG = *Geo::OSRc::SpatialReference_SetTMG;
*SetTMSO = *Geo::OSRc::SpatialReference_SetTMSO;
*SetVDG = *Geo::OSRc::SpatialReference_SetVDG;
*SetWellKnownGeogCS = *Geo::OSRc::SpatialReference_SetWellKnownGeogCS;
*SetFromUserInput = *Geo::OSRc::SpatialReference_SetFromUserInput;
*CopyGeogCSFrom = *Geo::OSRc::SpatialReference_CopyGeogCSFrom;
*SetTOWGS84 = *Geo::OSRc::SpatialReference_SetTOWGS84;
*GetTOWGS84 = *Geo::OSRc::SpatialReference_GetTOWGS84;
*SetLocalCS = *Geo::OSRc::SpatialReference_SetLocalCS;
*SetGeogCS = *Geo::OSRc::SpatialReference_SetGeogCS;
*SetProjCS = *Geo::OSRc::SpatialReference_SetProjCS;
*SetGeocCS = *Geo::OSRc::SpatialReference_SetGeocCS;
*SetVertCS = *Geo::OSRc::SpatialReference_SetVertCS;
*SetCompoundCS = *Geo::OSRc::SpatialReference_SetCompoundCS;
*ImportFromWkt = *Geo::OSRc::SpatialReference_ImportFromWkt;
*ImportFromProj4 = *Geo::OSRc::SpatialReference_ImportFromProj4;
*ImportFromUrl = *Geo::OSRc::SpatialReference_ImportFromUrl;
*ImportFromESRI = *Geo::OSRc::SpatialReference_ImportFromESRI;
*ImportFromEPSG = *Geo::OSRc::SpatialReference_ImportFromEPSG;
*ImportFromEPSGA = *Geo::OSRc::SpatialReference_ImportFromEPSGA;
*ImportFromPCI = *Geo::OSRc::SpatialReference_ImportFromPCI;
*ImportFromUSGS = *Geo::OSRc::SpatialReference_ImportFromUSGS;
*ImportFromXML = *Geo::OSRc::SpatialReference_ImportFromXML;
*ImportFromERM = *Geo::OSRc::SpatialReference_ImportFromERM;
*ImportFromMICoordSys = *Geo::OSRc::SpatialReference_ImportFromMICoordSys;
*ImportFromOzi = *Geo::OSRc::SpatialReference_ImportFromOzi;
*ExportToWkt = *Geo::OSRc::SpatialReference_ExportToWkt;
*ExportToPrettyWkt = *Geo::OSRc::SpatialReference_ExportToPrettyWkt;
*ExportToProj4 = *Geo::OSRc::SpatialReference_ExportToProj4;
*ExportToPCI = *Geo::OSRc::SpatialReference_ExportToPCI;
*ExportToUSGS = *Geo::OSRc::SpatialReference_ExportToUSGS;
*ExportToXML = *Geo::OSRc::SpatialReference_ExportToXML;
*ExportToMICoordSys = *Geo::OSRc::SpatialReference_ExportToMICoordSys;
*CloneGeogCS = *Geo::OSRc::SpatialReference_CloneGeogCS;
*Clone = *Geo::OSRc::SpatialReference_Clone;
*Validate = *Geo::OSRc::SpatialReference_Validate;
*StripCTParms = *Geo::OSRc::SpatialReference_StripCTParms;
*FixupOrdering = *Geo::OSRc::SpatialReference_FixupOrdering;
*Fixup = *Geo::OSRc::SpatialReference_Fixup;
*MorphToESRI = *Geo::OSRc::SpatialReference_MorphToESRI;
*MorphFromESRI = *Geo::OSRc::SpatialReference_MorphFromESRI;
sub DISOWN {
    my $self = shift;
    my $ptr = tied(%$self);
    delete $OWNER{$ptr};
}

sub ACQUIRE {
    my $self = shift;
    my $ptr = tied(%$self);
    $OWNER{$ptr} = 1;
}


############# Class : Geo::OSR::CoordinateTransformation ##############

package Geo::OSR::CoordinateTransformation;
use vars qw(@ISA %OWNER %ITERATORS %BLESSEDMEMBERS);
@ISA = qw( Geo::OSR );
%OWNER = ();
%ITERATORS = ();
sub new {
    my $pkg = shift;
    my $self = Geo::OSRc::new_CoordinateTransformation(@_);
    bless $self, $pkg if defined($self);
}

sub DESTROY {
    return unless $_[0]->isa('HASH');
    my $self = tied(%{$_[0]});
    return unless defined $self;
    delete $ITERATORS{$self};
    if (exists $OWNER{$self}) {
        Geo::OSRc::delete_CoordinateTransformation($self);
        delete $OWNER{$self};
    }
}

*TransformPoint = *Geo::OSRc::CoordinateTransformation_TransformPoint;
*_TransformPoints = *Geo::OSRc::CoordinateTransformation__TransformPoints;
sub DISOWN {
    my $self = shift;
    my $ptr = tied(%$self);
    delete $OWNER{$ptr};
}

sub ACQUIRE {
    my $self = shift;
    my $ptr = tied(%$self);
    $OWNER{$ptr} = 1;
}


# ------- VARIABLE STUBS --------

package Geo::OSR;

*SRS_WKT_WGS84 = *Geo::OSRc::SRS_WKT_WGS84;
*SRS_PT_ALBERS_CONIC_EQUAL_AREA = *Geo::OSRc::SRS_PT_ALBERS_CONIC_EQUAL_AREA;
*SRS_PT_AZIMUTHAL_EQUIDISTANT = *Geo::OSRc::SRS_PT_AZIMUTHAL_EQUIDISTANT;
*SRS_PT_CASSINI_SOLDNER = *Geo::OSRc::SRS_PT_CASSINI_SOLDNER;
*SRS_PT_CYLINDRICAL_EQUAL_AREA = *Geo::OSRc::SRS_PT_CYLINDRICAL_EQUAL_AREA;
*SRS_PT_BONNE = *Geo::OSRc::SRS_PT_BONNE;
*SRS_PT_ECKERT_I = *Geo::OSRc::SRS_PT_ECKERT_I;
*SRS_PT_ECKERT_II = *Geo::OSRc::SRS_PT_ECKERT_II;
*SRS_PT_ECKERT_III = *Geo::OSRc::SRS_PT_ECKERT_III;
*SRS_PT_ECKERT_IV = *Geo::OSRc::SRS_PT_ECKERT_IV;
*SRS_PT_ECKERT_V = *Geo::OSRc::SRS_PT_ECKERT_V;
*SRS_PT_ECKERT_VI = *Geo::OSRc::SRS_PT_ECKERT_VI;
*SRS_PT_EQUIDISTANT_CONIC = *Geo::OSRc::SRS_PT_EQUIDISTANT_CONIC;
*SRS_PT_EQUIRECTANGULAR = *Geo::OSRc::SRS_PT_EQUIRECTANGULAR;
*SRS_PT_GALL_STEREOGRAPHIC = *Geo::OSRc::SRS_PT_GALL_STEREOGRAPHIC;
*SRS_PT_GAUSSSCHREIBERTMERCATOR = *Geo::OSRc::SRS_PT_GAUSSSCHREIBERTMERCATOR;
*SRS_PT_GEOSTATIONARY_SATELLITE = *Geo::OSRc::SRS_PT_GEOSTATIONARY_SATELLITE;
*SRS_PT_GOODE_HOMOLOSINE = *Geo::OSRc::SRS_PT_GOODE_HOMOLOSINE;
*SRS_PT_IGH = *Geo::OSRc::SRS_PT_IGH;
*SRS_PT_GNOMONIC = *Geo::OSRc::SRS_PT_GNOMONIC;
*SRS_PT_HOTINE_OBLIQUE_MERCATOR_AZIMUTH_CENTER = *Geo::OSRc::SRS_PT_HOTINE_OBLIQUE_MERCATOR_AZIMUTH_CENTER;
*SRS_PT_HOTINE_OBLIQUE_MERCATOR = *Geo::OSRc::SRS_PT_HOTINE_OBLIQUE_MERCATOR;
*SRS_PT_HOTINE_OBLIQUE_MERCATOR_TWO_POINT_NATURAL_ORIGIN = *Geo::OSRc::SRS_PT_HOTINE_OBLIQUE_MERCATOR_TWO_POINT_NATURAL_ORIGIN;
*SRS_PT_LABORDE_OBLIQUE_MERCATOR = *Geo::OSRc::SRS_PT_LABORDE_OBLIQUE_MERCATOR;
*SRS_PT_LAMBERT_CONFORMAL_CONIC_1SP = *Geo::OSRc::SRS_PT_LAMBERT_CONFORMAL_CONIC_1SP;
*SRS_PT_LAMBERT_CONFORMAL_CONIC_2SP = *Geo::OSRc::SRS_PT_LAMBERT_CONFORMAL_CONIC_2SP;
*SRS_PT_LAMBERT_CONFORMAL_CONIC_2SP_BELGIUM = *Geo::OSRc::SRS_PT_LAMBERT_CONFORMAL_CONIC_2SP_BELGIUM;
*SRS_PT_LAMBERT_AZIMUTHAL_EQUAL_AREA = *Geo::OSRc::SRS_PT_LAMBERT_AZIMUTHAL_EQUAL_AREA;
*SRS_PT_MERCATOR_1SP = *Geo::OSRc::SRS_PT_MERCATOR_1SP;
*SRS_PT_MERCATOR_2SP = *Geo::OSRc::SRS_PT_MERCATOR_2SP;
*SRS_PT_MERCATOR_AUXILIARY_SPHERE = *Geo::OSRc::SRS_PT_MERCATOR_AUXILIARY_SPHERE;
*SRS_PT_MILLER_CYLINDRICAL = *Geo::OSRc::SRS_PT_MILLER_CYLINDRICAL;
*SRS_PT_MOLLWEIDE = *Geo::OSRc::SRS_PT_MOLLWEIDE;
*SRS_PT_NEW_ZEALAND_MAP_GRID = *Geo::OSRc::SRS_PT_NEW_ZEALAND_MAP_GRID;
*SRS_PT_OBLIQUE_STEREOGRAPHIC = *Geo::OSRc::SRS_PT_OBLIQUE_STEREOGRAPHIC;
*SRS_PT_ORTHOGRAPHIC = *Geo::OSRc::SRS_PT_ORTHOGRAPHIC;
*SRS_PT_POLAR_STEREOGRAPHIC = *Geo::OSRc::SRS_PT_POLAR_STEREOGRAPHIC;
*SRS_PT_POLYCONIC = *Geo::OSRc::SRS_PT_POLYCONIC;
*SRS_PT_ROBINSON = *Geo::OSRc::SRS_PT_ROBINSON;
*SRS_PT_SINUSOIDAL = *Geo::OSRc::SRS_PT_SINUSOIDAL;
*SRS_PT_STEREOGRAPHIC = *Geo::OSRc::SRS_PT_STEREOGRAPHIC;
*SRS_PT_SWISS_OBLIQUE_CYLINDRICAL = *Geo::OSRc::SRS_PT_SWISS_OBLIQUE_CYLINDRICAL;
*SRS_PT_TRANSVERSE_MERCATOR = *Geo::OSRc::SRS_PT_TRANSVERSE_MERCATOR;
*SRS_PT_TRANSVERSE_MERCATOR_SOUTH_ORIENTED = *Geo::OSRc::SRS_PT_TRANSVERSE_MERCATOR_SOUTH_ORIENTED;
*SRS_PT_TRANSVERSE_MERCATOR_MI_21 = *Geo::OSRc::SRS_PT_TRANSVERSE_MERCATOR_MI_21;
*SRS_PT_TRANSVERSE_MERCATOR_MI_22 = *Geo::OSRc::SRS_PT_TRANSVERSE_MERCATOR_MI_22;
*SRS_PT_TRANSVERSE_MERCATOR_MI_23 = *Geo::OSRc::SRS_PT_TRANSVERSE_MERCATOR_MI_23;
*SRS_PT_TRANSVERSE_MERCATOR_MI_24 = *Geo::OSRc::SRS_PT_TRANSVERSE_MERCATOR_MI_24;
*SRS_PT_TRANSVERSE_MERCATOR_MI_25 = *Geo::OSRc::SRS_PT_TRANSVERSE_MERCATOR_MI_25;
*SRS_PT_TUNISIA_MINING_GRID = *Geo::OSRc::SRS_PT_TUNISIA_MINING_GRID;
*SRS_PT_TWO_POINT_EQUIDISTANT = *Geo::OSRc::SRS_PT_TWO_POINT_EQUIDISTANT;
*SRS_PT_VANDERGRINTEN = *Geo::OSRc::SRS_PT_VANDERGRINTEN;
*SRS_PT_KROVAK = *Geo::OSRc::SRS_PT_KROVAK;
*SRS_PT_IMW_POLYCONIC = *Geo::OSRc::SRS_PT_IMW_POLYCONIC;
*SRS_PT_WAGNER_I = *Geo::OSRc::SRS_PT_WAGNER_I;
*SRS_PT_WAGNER_II = *Geo::OSRc::SRS_PT_WAGNER_II;
*SRS_PT_WAGNER_III = *Geo::OSRc::SRS_PT_WAGNER_III;
*SRS_PT_WAGNER_IV = *Geo::OSRc::SRS_PT_WAGNER_IV;
*SRS_PT_WAGNER_V = *Geo::OSRc::SRS_PT_WAGNER_V;
*SRS_PT_WAGNER_VI = *Geo::OSRc::SRS_PT_WAGNER_VI;
*SRS_PT_WAGNER_VII = *Geo::OSRc::SRS_PT_WAGNER_VII;
*SRS_PT_QSC = *Geo::OSRc::SRS_PT_QSC;
*SRS_PT_AITOFF = *Geo::OSRc::SRS_PT_AITOFF;
*SRS_PT_WINKEL_I = *Geo::OSRc::SRS_PT_WINKEL_I;
*SRS_PT_WINKEL_II = *Geo::OSRc::SRS_PT_WINKEL_II;
*SRS_PT_WINKEL_TRIPEL = *Geo::OSRc::SRS_PT_WINKEL_TRIPEL;
*SRS_PT_CRASTER_PARABOLIC = *Geo::OSRc::SRS_PT_CRASTER_PARABOLIC;
*SRS_PT_LOXIMUTHAL = *Geo::OSRc::SRS_PT_LOXIMUTHAL;
*SRS_PT_QUARTIC_AUTHALIC = *Geo::OSRc::SRS_PT_QUARTIC_AUTHALIC;
*SRS_PT_SCH = *Geo::OSRc::SRS_PT_SCH;
*SRS_PP_CENTRAL_MERIDIAN = *Geo::OSRc::SRS_PP_CENTRAL_MERIDIAN;
*SRS_PP_SCALE_FACTOR = *Geo::OSRc::SRS_PP_SCALE_FACTOR;
*SRS_PP_STANDARD_PARALLEL_1 = *Geo::OSRc::SRS_PP_STANDARD_PARALLEL_1;
*SRS_PP_STANDARD_PARALLEL_2 = *Geo::OSRc::SRS_PP_STANDARD_PARALLEL_2;
*SRS_PP_PSEUDO_STD_PARALLEL_1 = *Geo::OSRc::SRS_PP_PSEUDO_STD_PARALLEL_1;
*SRS_PP_LONGITUDE_OF_CENTER = *Geo::OSRc::SRS_PP_LONGITUDE_OF_CENTER;
*SRS_PP_LATITUDE_OF_CENTER = *Geo::OSRc::SRS_PP_LATITUDE_OF_CENTER;
*SRS_PP_LONGITUDE_OF_ORIGIN = *Geo::OSRc::SRS_PP_LONGITUDE_OF_ORIGIN;
*SRS_PP_LATITUDE_OF_ORIGIN = *Geo::OSRc::SRS_PP_LATITUDE_OF_ORIGIN;
*SRS_PP_FALSE_EASTING = *Geo::OSRc::SRS_PP_FALSE_EASTING;
*SRS_PP_FALSE_NORTHING = *Geo::OSRc::SRS_PP_FALSE_NORTHING;
*SRS_PP_AZIMUTH = *Geo::OSRc::SRS_PP_AZIMUTH;
*SRS_PP_LONGITUDE_OF_POINT_1 = *Geo::OSRc::SRS_PP_LONGITUDE_OF_POINT_1;
*SRS_PP_LATITUDE_OF_POINT_1 = *Geo::OSRc::SRS_PP_LATITUDE_OF_POINT_1;
*SRS_PP_LONGITUDE_OF_POINT_2 = *Geo::OSRc::SRS_PP_LONGITUDE_OF_POINT_2;
*SRS_PP_LATITUDE_OF_POINT_2 = *Geo::OSRc::SRS_PP_LATITUDE_OF_POINT_2;
*SRS_PP_LONGITUDE_OF_POINT_3 = *Geo::OSRc::SRS_PP_LONGITUDE_OF_POINT_3;
*SRS_PP_LATITUDE_OF_POINT_3 = *Geo::OSRc::SRS_PP_LATITUDE_OF_POINT_3;
*SRS_PP_RECTIFIED_GRID_ANGLE = *Geo::OSRc::SRS_PP_RECTIFIED_GRID_ANGLE;
*SRS_PP_LANDSAT_NUMBER = *Geo::OSRc::SRS_PP_LANDSAT_NUMBER;
*SRS_PP_PATH_NUMBER = *Geo::OSRc::SRS_PP_PATH_NUMBER;
*SRS_PP_PERSPECTIVE_POINT_HEIGHT = *Geo::OSRc::SRS_PP_PERSPECTIVE_POINT_HEIGHT;
*SRS_PP_SATELLITE_HEIGHT = *Geo::OSRc::SRS_PP_SATELLITE_HEIGHT;
*SRS_PP_FIPSZONE = *Geo::OSRc::SRS_PP_FIPSZONE;
*SRS_PP_ZONE = *Geo::OSRc::SRS_PP_ZONE;
*SRS_PP_LATITUDE_OF_1ST_POINT = *Geo::OSRc::SRS_PP_LATITUDE_OF_1ST_POINT;
*SRS_PP_LONGITUDE_OF_1ST_POINT = *Geo::OSRc::SRS_PP_LONGITUDE_OF_1ST_POINT;
*SRS_PP_LATITUDE_OF_2ND_POINT = *Geo::OSRc::SRS_PP_LATITUDE_OF_2ND_POINT;
*SRS_PP_LONGITUDE_OF_2ND_POINT = *Geo::OSRc::SRS_PP_LONGITUDE_OF_2ND_POINT;
*SRS_PP_PEG_POINT_LATITUDE = *Geo::OSRc::SRS_PP_PEG_POINT_LATITUDE;
*SRS_PP_PEG_POINT_LONGITUDE = *Geo::OSRc::SRS_PP_PEG_POINT_LONGITUDE;
*SRS_PP_PEG_POINT_HEADING = *Geo::OSRc::SRS_PP_PEG_POINT_HEADING;
*SRS_PP_PEG_POINT_HEIGHT = *Geo::OSRc::SRS_PP_PEG_POINT_HEIGHT;
*SRS_UL_METER = *Geo::OSRc::SRS_UL_METER;
*SRS_UL_FOOT = *Geo::OSRc::SRS_UL_FOOT;
*SRS_UL_FOOT_CONV = *Geo::OSRc::SRS_UL_FOOT_CONV;
*SRS_UL_US_FOOT = *Geo::OSRc::SRS_UL_US_FOOT;
*SRS_UL_US_FOOT_CONV = *Geo::OSRc::SRS_UL_US_FOOT_CONV;
*SRS_UL_NAUTICAL_MILE = *Geo::OSRc::SRS_UL_NAUTICAL_MILE;
*SRS_UL_NAUTICAL_MILE_CONV = *Geo::OSRc::SRS_UL_NAUTICAL_MILE_CONV;
*SRS_UL_LINK = *Geo::OSRc::SRS_UL_LINK;
*SRS_UL_LINK_CONV = *Geo::OSRc::SRS_UL_LINK_CONV;
*SRS_UL_CHAIN = *Geo::OSRc::SRS_UL_CHAIN;
*SRS_UL_CHAIN_CONV = *Geo::OSRc::SRS_UL_CHAIN_CONV;
*SRS_UL_ROD = *Geo::OSRc::SRS_UL_ROD;
*SRS_UL_ROD_CONV = *Geo::OSRc::SRS_UL_ROD_CONV;
*SRS_UL_LINK_Clarke = *Geo::OSRc::SRS_UL_LINK_Clarke;
*SRS_UL_LINK_Clarke_CONV = *Geo::OSRc::SRS_UL_LINK_Clarke_CONV;
*SRS_UL_KILOMETER = *Geo::OSRc::SRS_UL_KILOMETER;
*SRS_UL_KILOMETER_CONV = *Geo::OSRc::SRS_UL_KILOMETER_CONV;
*SRS_UL_DECIMETER = *Geo::OSRc::SRS_UL_DECIMETER;
*SRS_UL_DECIMETER_CONV = *Geo::OSRc::SRS_UL_DECIMETER_CONV;
*SRS_UL_CENTIMETER = *Geo::OSRc::SRS_UL_CENTIMETER;
*SRS_UL_CENTIMETER_CONV = *Geo::OSRc::SRS_UL_CENTIMETER_CONV;
*SRS_UL_MILLIMETER = *Geo::OSRc::SRS_UL_MILLIMETER;
*SRS_UL_MILLIMETER_CONV = *Geo::OSRc::SRS_UL_MILLIMETER_CONV;
*SRS_UL_INTL_NAUT_MILE = *Geo::OSRc::SRS_UL_INTL_NAUT_MILE;
*SRS_UL_INTL_NAUT_MILE_CONV = *Geo::OSRc::SRS_UL_INTL_NAUT_MILE_CONV;
*SRS_UL_INTL_INCH = *Geo::OSRc::SRS_UL_INTL_INCH;
*SRS_UL_INTL_INCH_CONV = *Geo::OSRc::SRS_UL_INTL_INCH_CONV;
*SRS_UL_INTL_FOOT = *Geo::OSRc::SRS_UL_INTL_FOOT;
*SRS_UL_INTL_FOOT_CONV = *Geo::OSRc::SRS_UL_INTL_FOOT_CONV;
*SRS_UL_INTL_YARD = *Geo::OSRc::SRS_UL_INTL_YARD;
*SRS_UL_INTL_YARD_CONV = *Geo::OSRc::SRS_UL_INTL_YARD_CONV;
*SRS_UL_INTL_STAT_MILE = *Geo::OSRc::SRS_UL_INTL_STAT_MILE;
*SRS_UL_INTL_STAT_MILE_CONV = *Geo::OSRc::SRS_UL_INTL_STAT_MILE_CONV;
*SRS_UL_INTL_FATHOM = *Geo::OSRc::SRS_UL_INTL_FATHOM;
*SRS_UL_INTL_FATHOM_CONV = *Geo::OSRc::SRS_UL_INTL_FATHOM_CONV;
*SRS_UL_INTL_CHAIN = *Geo::OSRc::SRS_UL_INTL_CHAIN;
*SRS_UL_INTL_CHAIN_CONV = *Geo::OSRc::SRS_UL_INTL_CHAIN_CONV;
*SRS_UL_INTL_LINK = *Geo::OSRc::SRS_UL_INTL_LINK;
*SRS_UL_INTL_LINK_CONV = *Geo::OSRc::SRS_UL_INTL_LINK_CONV;
*SRS_UL_US_INCH = *Geo::OSRc::SRS_UL_US_INCH;
*SRS_UL_US_INCH_CONV = *Geo::OSRc::SRS_UL_US_INCH_CONV;
*SRS_UL_US_YARD = *Geo::OSRc::SRS_UL_US_YARD;
*SRS_UL_US_YARD_CONV = *Geo::OSRc::SRS_UL_US_YARD_CONV;
*SRS_UL_US_CHAIN = *Geo::OSRc::SRS_UL_US_CHAIN;
*SRS_UL_US_CHAIN_CONV = *Geo::OSRc::SRS_UL_US_CHAIN_CONV;
*SRS_UL_US_STAT_MILE = *Geo::OSRc::SRS_UL_US_STAT_MILE;
*SRS_UL_US_STAT_MILE_CONV = *Geo::OSRc::SRS_UL_US_STAT_MILE_CONV;
*SRS_UL_INDIAN_YARD = *Geo::OSRc::SRS_UL_INDIAN_YARD;
*SRS_UL_INDIAN_YARD_CONV = *Geo::OSRc::SRS_UL_INDIAN_YARD_CONV;
*SRS_UL_INDIAN_FOOT = *Geo::OSRc::SRS_UL_INDIAN_FOOT;
*SRS_UL_INDIAN_FOOT_CONV = *Geo::OSRc::SRS_UL_INDIAN_FOOT_CONV;
*SRS_UL_INDIAN_CHAIN = *Geo::OSRc::SRS_UL_INDIAN_CHAIN;
*SRS_UL_INDIAN_CHAIN_CONV = *Geo::OSRc::SRS_UL_INDIAN_CHAIN_CONV;
*SRS_UA_DEGREE = *Geo::OSRc::SRS_UA_DEGREE;
*SRS_UA_DEGREE_CONV = *Geo::OSRc::SRS_UA_DEGREE_CONV;
*SRS_UA_RADIAN = *Geo::OSRc::SRS_UA_RADIAN;
*SRS_PM_GREENWICH = *Geo::OSRc::SRS_PM_GREENWICH;
*SRS_DN_NAD27 = *Geo::OSRc::SRS_DN_NAD27;
*SRS_DN_NAD83 = *Geo::OSRc::SRS_DN_NAD83;
*SRS_DN_WGS72 = *Geo::OSRc::SRS_DN_WGS72;
*SRS_DN_WGS84 = *Geo::OSRc::SRS_DN_WGS84;
*SRS_WGS84_SEMIMAJOR = *Geo::OSRc::SRS_WGS84_SEMIMAJOR;
*SRS_WGS84_INVFLATTENING = *Geo::OSRc::SRS_WGS84_INVFLATTENING;
*OAO_Other = *Geo::OSRc::OAO_Other;
*OAO_North = *Geo::OSRc::OAO_North;
*OAO_South = *Geo::OSRc::OAO_South;
*OAO_East = *Geo::OSRc::OAO_East;
*OAO_West = *Geo::OSRc::OAO_West;
*OAO_Up = *Geo::OSRc::OAO_Up;
*OAO_Down = *Geo::OSRc::OAO_Down;


package Geo::OSR;
use strict;
use warnings;

use vars qw /%PROJECTIONS %PARAMETERS %LINEAR_UNITS %ANGULAR_UNITS %DATUMS/;

for (keys %Geo::OSR::) {
    if (/^SRS_PT_(\w+)/) {
        my $p = eval '$Geo::OSR::'.$_;
        $PROJECTIONS{$p} = 1;
    }
    elsif (/^SRS_PP_(\w+)/) {
        my $p = eval '$Geo::OSR::'.$_;
        $PARAMETERS{$p} = 1;
    }
    elsif (/^SRS_UL_(\w+)/) {
        my $p = eval '$Geo::OSR::'.$_;
        $LINEAR_UNITS{$p} = 1;
    }
    elsif (/^SRS_UA_(\w+)/) {
        my $p = eval '$Geo::OSR::'.$_;
        $ANGULAR_UNITS{$p} = 1;
    }
    elsif (/^SRS_DN_(\w+)/) {
        my $p = eval '$Geo::OSR::'.$_;
        $DATUMS{$p} = 1;
    }
}

sub Projections {
    return keys %PROJECTIONS;
}

sub Parameters {
    return keys %PARAMETERS;
}

sub LinearUnits {
    return keys %LINEAR_UNITS;
}

sub AngularUnits {
    return keys %ANGULAR_UNITS;
}

sub Datums {
    return keys %DATUMS;
}

sub RELEASE_PARENT {
}


package Geo::OSR::SpatialReference;
use strict;
use warnings;
use Carp;

Geo::GDAL->import(qw(:INTERNAL));

sub Export {
    my $self = shift;
    my $format;
    $format = pop if @_ == 1;
    my %params = @_;
    $format //= $params{to} //= $params{format} //= $params{as} //= '';
    my $simplify = $params{simplify} // 0;
    my $dialect = $params{dialect} // '';
    my %converters = (
        WKT => sub { return ExportToWkt($self) },
        Text => sub { return ExportToWkt($self) },
        PrettyWKT => sub { return ExportToPrettyWkt($self, $simplify) },
        Proj4 => sub { return ExportToProj4($self) },
        PCI => sub { return ExportToPCI($self) },
        USGS => sub { return ExportToUSGS($self) },
        GML => sub { return ExportToXML($self, $dialect) },
        XML => sub { return ExportToXML($self, $dialect) },
        MICoordSys => sub { return ExportToMICoordSys() },
        MapInfoCS => sub { return ExportToMICoordSys() },
        );
    error(1, $format, \%converters) unless $converters{$format};
    return $converters{$format}->();
}
*AsText = *ExportToWkt;
*As = *Export;

sub Set {
    my($self, %params) = @_;
    if (exists $params{Authority} and exists $params{TargetKey} and exists $params{Node} and exists $params{Code}) {
        SetAuthority($self, $params{TargetKey}, $params{Authority}, $params{Code});
    } elsif (exists $params{Node} and exists $params{Value}) {
        SetAttrValue($self, $params{Node}, $params{Value});
    } elsif (exists $params{AngularUnits} and exists $params{Value}) {
        SetAngularUnits($self, $params{AngularUnits}, $params{Value});
    } elsif (exists $params{LinearUnits} and exists $params{Node} and exists $params{Value}) {
        SetTargetLinearUnits($self, $params{Node}, $params{LinearUnits}, $params{Value});
    } elsif (exists $params{LinearUnits} and exists $params{Value}) {
        SetLinearUnitsAndUpdateParameters($self, $params{LinearUnits}, $params{Value});
    } elsif ($params{Parameter} and exists $params{Value}) {
        error(1, $params{Parameter}, \%Geo::OSR::PARAMETERS) unless exists $Geo::OSR::PARAMETERS{$params{Parameter}};
        $params{Normalized} ?
            SetNormProjParm($self, $params{Parameter}, $params{Value}) :
            SetProjParm($self, $params{Parameter}, $params{Value});
    } elsif (exists $params{Name}) {
        SetWellKnownGeogCS($self, $params{Name});
    } elsif (exists $params{GuessFrom}) {
        SetFromUserInput($self, $params{GuessFrom});
    } elsif (exists $params{LOCAL_CS}) {
        SetLocalCS($self, $params{LOCAL_CS});
    } elsif (exists $params{GeocentricCS}) {
        SetGeocCS($self, $params{GeocentricCS});
    } elsif (exists $params{VerticalCS} and $params{Datum}) {
        my $type = $params{VertDatumType} || 2005;
        SetVertCS($self, $params{VerticalCS}, $params{Datum}, $type);
    } elsif (exists $params{CoordinateSystem}) {
        my @parameters = ();
        @parameters = @{$params{Parameters}} if ref($params{Parameters});
        if ($params{CoordinateSystem} eq 'State Plane' and exists $params{Zone}) {
            my $NAD83 = exists $params{NAD83} ? $params{NAD83} : 1;
            my $name = exists $params{UnitName} ? $params{UnitName} : undef;
            my $c = exists $params{UnitConversionFactor} ? $params{UnitConversionFactor} : 0.0;
            SetStatePlane($self, $params{Zone}, $NAD83, $name, $c);
        } elsif ($params{CoordinateSystem} eq 'UTM' and exists $params{Zone} and exists $params{North}) {
            my $north = exists $params{North} ? $params{North} : 1;
            SetUTM($self, $params{Zone}, $north);
        } elsif ($params{CoordinateSystem} eq 'WGS') {
            SetTOWGS84($self, @parameters);
        } elsif ($params{CoordinateSystem} and $params{Datum} and $params{Spheroid}) {
            SetGeogCS($self, $params{CoordinateSystem}, $params{Datum}, $params{Spheroid}, @parameters);
        } elsif ($params{CoordinateSystem} and $params{HorizontalCS} and $params{VerticalCS}) {
            SetCompoundCS($self, $params{CoordinateSystem}, $params{HorizontalCS}, $params{VerticalCS});
        } else {
            SetProjCS($self, $params{CoordinateSystem});
        }
    } elsif (exists $params{Projection}) {
        error(1, $params{Projection}, \%Geo::OSR::PROJECTIONS) unless exists $Geo::OSR::PROJECTIONS{$params{Projection}};
        my @parameters = ();
        @parameters = @{$params{Parameters}} if ref($params{Parameters});
        if ($params{Projection} eq 'Albers_Conic_Equal_Area') {
            SetACEA($self, @parameters);
        } elsif ($params{Projection} eq 'Azimuthal_Equidistant') {
            SetAE($self, @parameters);
        } elsif ($params{Projection} eq 'Bonne') {
            SetBonne($self, @parameters);
        } elsif ($params{Projection} eq 'Cylindrical_Equal_Area') {
            SetCEA($self, @parameters);
        } elsif ($params{Projection} eq 'Cassini_Soldner') {
            SetCS($self, @parameters);
        } elsif ($params{Projection} eq 'Equidistant_Conic') {
            SetEC($self, @parameters);
            # Eckert_I, Eckert_II, Eckert_III, Eckert_V ?
        } elsif ($params{Projection} eq 'Eckert_IV') {
            SetEckertIV($self, @parameters);
        } elsif ($params{Projection} eq 'Eckert_VI') {
            SetEckertVI($self, @parameters);
        } elsif ($params{Projection} eq 'Equirectangular') {
            @parameters == 4 ?
                SetEquirectangular($self, @parameters) :
                SetEquirectangular2($self, @parameters);
        } elsif ($params{Projection} eq 'Gauss_Schreiber_Transverse_Mercator') {
            SetGaussSchreiberTMercator($self, @parameters);
        } elsif ($params{Projection} eq 'Gall_Stereographic') {
            SetGS($self, @parameters);
        } elsif ($params{Projection} eq 'Goode_Homolosine') {
            SetGH($self, @parameters);
        } elsif ($params{Projection} eq 'Interrupted_Goode_Homolosine') {
            SetIGH($self);
        } elsif ($params{Projection} eq 'Geostationary_Satellite') {
            SetGEOS($self, @parameters);
        } elsif ($params{Projection} eq 'Gnomonic') {
            SetGnomonic($self, @parameters);
        } elsif ($params{Projection} eq 'Hotine_Oblique_Mercator') {
            # Hotine_Oblique_Mercator_Azimuth_Center ?
            SetHOM($self, @parameters);
        } elsif ($params{Projection} eq 'Hotine_Oblique_Mercator_Two_Point_Natural_Origin') {
            SetHOM2PNO($self, @parameters);
        } elsif ($params{Projection} eq 'Krovak') {
            SetKrovak($self, @parameters);
        } elsif ($params{Projection} eq 'Lambert_Azimuthal_Equal_Area') {
            SetLAEA($self, @parameters);
        } elsif ($params{Projection} eq 'Lambert_Conformal_Conic_2SP') {
            SetLCC($self, @parameters);
        } elsif ($params{Projection} eq 'Lambert_Conformal_Conic_1SP') {
            SetLCC1SP($self, @parameters);
        } elsif ($params{Projection} eq 'Lambert_Conformal_Conic_2SP_Belgium') {
            SetLCCB($self, @parameters);
        } elsif ($params{Projection} eq 'miller_cylindrical') {
            SetMC($self, @parameters);
        } elsif ($params{Projection} =~ /^Mercator/) {
            # Mercator_1SP, Mercator_2SP, Mercator_Auxiliary_Sphere ?
            # variant is in Variant (or Name)
            SetMercator($self, @parameters);
        } elsif ($params{Projection} eq 'Mollweide') {
            SetMollweide($self, @parameters);
        } elsif ($params{Projection} eq 'New_Zealand_Map_Grid') {
            SetNZMG($self, @parameters);
        } elsif ($params{Projection} eq 'Oblique_Stereographic') {
            SetOS($self, @parameters);
        } elsif ($params{Projection} eq 'Orthographic') {
            SetOrthographic($self, @parameters);
        } elsif ($params{Projection} eq 'Polyconic') {
            SetPolyconic($self, @parameters);
        } elsif ($params{Projection} eq 'Polar_Stereographic') {
            SetPS($self, @parameters);
        } elsif ($params{Projection} eq 'Robinson') {
            SetRobinson($self, @parameters);
        } elsif ($params{Projection} eq 'Sinusoidal') {
            SetSinusoidal($self, @parameters);
        } elsif ($params{Projection} eq 'Stereographic') {
            SetStereographic($self, @parameters);
        } elsif ($params{Projection} eq 'Swiss_Oblique_Cylindrical') {
            SetSOC($self, @parameters);
        } elsif ($params{Projection} eq 'Transverse_Mercator_South_Orientated') {
            SetTMSO($self, @parameters);
        } elsif ($params{Projection} =~ /^Transverse_Mercator/) {
            my($variant) = $params{Projection} =~ /^Transverse_Mercator_(\w+)/;
            $variant //= $params{Variant} //= $params{Name};
            $variant ?
                SetTMVariant($self, $variant, @parameters) :
                SetTM($self, @parameters);
        } elsif ($params{Projection} eq 'Tunisia_Mining_Grid') {
            SetTMG($self, @parameters);
        } elsif ($params{Projection} eq 'VanDerGrinten') {
            SetVDG($self, @parameters);
        } else {
            # Aitoff, Craster_Parabolic, International_Map_of_the_World_Polyconic, Laborde_Oblique_Mercator
            # Loximuthal, Miller_Cylindrical, Quadrilateralized_Spherical_Cube, Quartic_Authalic, Two_Point_Equidistant
            # Wagner_I, Wagner_II, Wagner_III, Wagner_IV, Wagner_V, Wagner_VI, Wagner_VII
            # Winkel_I, Winkel_II, Winkel_Tripel
            # ?
            SetProjection($self, $params{Projection});
        }
    } else {
        error("Not enough information to create a spatial reference object.");
    }
}

sub GetUTMZone {
    my $self = shift;
    my $zone = _GetUTMZone($self);
    if (wantarray) {
        my $north = 1;
        if ($zone < 0) {
            $zone *= -1;
            $north = 0;
        }
        return ($zone, $north);
    } else {
        return $zone;
    }
}


package Geo::OSR::CoordinateTransformation;
use strict;
use warnings;

Geo::GDAL->import(qw(:INTERNAL));

sub TransformPoints {
    my($self, $points) = @_;
    _TransformPoints($self, $points), return unless ref($points->[0]->[0]);
    for my $p (@$points) {
        TransformPoints($self, $p);
    }
}
1;
