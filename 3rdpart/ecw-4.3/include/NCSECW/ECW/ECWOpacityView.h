/********************************************************
** Copyright (c) 2010, ERDAS, Inc. [http://www.erdas.com/] .
** This document contains proprietary source code of
** ERDAS, Inc.,  
**
** This software is covered by US patent #6,442,298,
** #6,102,897 and #6,633,688.  Rights to use these patents 
** is included in the license agreements.
 *******************************************************/

#ifndef NCS_ECWOPACITY_VIEW
#define NCS_ECWOPACITY_VIEW

#include "NCSEcw/API/View.h"

namespace NCS {
namespace ECW {
	class CReader;
#ifdef ECW_COMPRESS_RW_SDK_VERSION
	class CWriter;
#endif
}
namespace JP2 {
	class CReader;
#ifdef ECW_COMPRESS_RW_SDK_VERSION
	class CWriter;
#endif
}
namespace JPC {
	class CResampler;
}
namespace SDK {
	class CFileBase;
}

namespace ECW {

class NCSECW_IMPEX CECWOpacityView: public NCS::CView {
public:
	CECWOpacityView();

	CError OpenOpacityFileView(SDK::CFileBase *pFile, bool bProgressiveDisplay, NCSFileType eType);
	CError ReadOpacityBand(SDK::CBuffer2DVector &Buffers, INT32 m_nAllOpacityBandNumber);
	CError Close ( bool bFreeCache = false );
};
}
}

#endif