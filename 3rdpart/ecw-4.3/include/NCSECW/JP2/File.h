/********************************************************
** Copyright (c) 2010, ERDAS, Inc. [http://www.erdas.com/]
** This document contains proprietary source code of
** ERDAS, Inc.
**
** This software is covered by US patent #6,442,298,
** #6,102,897 and #6,633,688.  Rights to use these patents 
** is included in the license agreements.
**
** FILE:     File.h
** CREATED:  28/11/2002 3:27:34 PM
** AUTHOR:   Simon Cope
** PURPOSE:  CFile class header
** EDITS:    [xx] ddMmmyy NAME COMMENTS
**			 [01] 03Aug04 tfl  Added integer member to NCSJP2PCSBox
**			 [02] 07Dec04 tfl  Moved GeodataUsage enum declaration to NCSECWClient.h
**			 [03] 17Dec04 tfl  Added static CFile::Shutdown() function called by CFile::Shutdown()
 *******************************************************/

#ifndef NCSJP2FILE_H
#define NCSJP2FILE_H

#ifndef NCSJP2DEFS_H
#include "NCSEcw/JPC/Types/Defs.h"
#endif // NCSJP2DEFS_H

#ifndef NCSECWCLIENT_H
#include "NCSECWClient.h"
#endif // NCSECWCLIENT_H

#ifndef NCSFILEBASE_H
#include "NCSEcw/SDK/FileBase.h"
#endif //NCSFILEBASE_H

// JP2 Box class
#ifndef NCSJP2BOX_H
#include "NCSEcw/JP2/Box.h"
#endif // NCSJP2BOX_H

// JP2 SuperBox class
#ifndef NCSJP2SUPERBOX_H
#include "NCSEcw/JP2/SuperBox.h"
#endif // NCSJP2SUPERBOX_H

// JPC ComponentDepthType
#ifndef NCSJPCCOMPONENTDEPTHTYPE_H
#include "NCSEcw/JPC/Types/ComponentDepthType.h"
#endif // NCSJPCCOMPONENTDEPTHTYPE_H

// JPC codestream classes
#ifndef NCSJPC_H
#include "NCSEcw/JPC/JPC.h"
#endif // NCSJPC_H

#ifndef NCSGLOBALINFO_H
#include "NCSEcw/SDK/GlobalInfo.h"
#endif //NCSGLOBALINFO_H

#include "NCSEcw/API/HeaderEditor.h"

#define ECW_COMPRESS_SDK_LIMIT_MASK			0xfe43218a
#define UUID_LEN							16
#define DEFAULT_GEODATA_PRECISION			0.000000001F

namespace NCS {
class CView;
namespace SDK {
	class CGlobalLock;
}
namespace JP2 {
class CReader;
class CWriter;
class CExtIndexBox;

	/**
	 * CContiguousCodestreamBox class - the JP2 codestream box.  This box is always present.
	 * 
	 * @author       Simon Cope
	 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
	 */	
class NCSECW_IMPEX CContiguousCodestreamBox: public CBox, public NCS::JPC::CJPC {
public:
		/** Box type */ 
	static UINT32	sm_nTBox;

		/** Default constructor, initialises members */
	CContiguousCodestreamBox();
		/** Virtual destructor */
	virtual ~CContiguousCodestreamBox();

		/** 
		 * Parse the JPC box from the JP2 file.
		 * @param		JP2File		JP2 file being parsed
		 * @param		Stream		IOStream to use to parse file.
		 * @return      CError	NCS_SUCCESS, or Error code on failure.
		 */
	virtual CError Parse(class CFile &JP2File, CIOStream &Stream);
		/** 
		 * UnParse the JPC box to the JP2 file.
		 * @param		JP2File		JP2 file being parsed
		 * @param		Stream		IOStream to use to parse file.
		 * @return      CError	NCS_SUCCESS, or Error code on failure.
		 */
	virtual CError UnParse(class CFile &JP2File, CIOStream &Stream);
};

/**
 * CFile class - the JP2 file class.
 * Note, the JP2File class is a superbox!
 * The JP2File is the base shared file object used by multiple CFile classes to 
 * access a JP2 file.
 * 
 * @author       Simon Cope
 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
 */
class NCSECW_IMPEX CFile: public CContiguousCodestreamBox, public CSuperBox, public SDK::CNodeTiler2D {
public:

	static NCSError EditReadInfo(char *pFilename, NCSEcwEditInfo **ppInfo);
	static NCSError EditWriteInfo(char *pFilename, NCSEcwEditInfo *pInfo, void (*pProgressFunc)(UINT64 nTotal, UINT64 nWritten, void *pClientData), BOOLEAN (*pCancelFunc)(void *pClientData), void *pClientData);

		/** 
		 * For purging memory on files that are being opened but not in the factory yet 
		 * eg. parsing the packets to write a j2i file mem usage can be large
		 */
	void PurgeNow(void);
		/**
		 * CSignatureBox class - the JP2 signature box.  This box is always present.
		 * 
		 * @author       Simon Cope
		 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
		 */	
	class NCSECW_IMPEX CSignatureBox: public CBox {
	public:
			/** Box type */ 
		static UINT32	sm_nTBox;
			/** JP2 file signature */
		static UINT32	sm_JP2Signature;

			/** Signature as read from file */
		UINT32		m_nSignature;

			/** Default constructor, initialises members */
		CSignatureBox();
			/** Virtual destructor */
		virtual ~CSignatureBox();
			/** 
			 * Update the extended length of the box prior to writing
			 */
		virtual void UpdateXLBox(void);
			/** 
			 * Parse the signature box from the JP2 file.
			 * @param		JP2File		JP2 file being parsed
			 * @param		Stream		IOStream to use to parse file.
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		virtual CError Parse(class CFile &JP2File, CIOStream &Stream);
			/** 
			 * UnParse the signature box to the JP2 file.
			 * @param		JP2File		JP2 file being parsed
			 * @param		Stream		IOStream to use to parse file.
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		virtual CError UnParse(class CFile &JP2File, CIOStream &Stream);
	};

		/**
		 * CFileTypeBox class - the JP2 file type box class.  This box is always present.
		 * 
		 * @author       Simon Cope
		 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
		 */	
	class NCSECW_IMPEX CFileTypeBox: public CBox {
	public:
			/** Compatibility list entry, 4 chars as UINT32 */
		typedef UINT32 CCLEntry;
			/** Compatibility list */
		typedef std::list<CCLEntry> CCLList;

			/** Box type */
		static UINT32	sm_nTBox;
			/** JP2 Brand */
		static UINT32	sm_JP2Brand;

			/** Brand as read from file */
		UINT32			m_Brand;
			/** Minor version */
		UINT32			m_nMinV;
			/** Compatibility list - other files may be readable as JP2, eg JPX files */
		CCLList	m_CLList;

			/** Default constructor, initialises members */
		CFileTypeBox();
			/** Virtual destructor */
		virtual ~CFileTypeBox();
			/** 
			 * Update the extended length of the box prior to writing
			 */
		virtual void UpdateXLBox(void);

			/** 
			 * Parse the file type box from the JP2 file.
			 * @param		JP2File		JP2 file being parsed
			 * @param		Stream		IOStream to use to parse file.
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		virtual CError Parse(class CFile &JP2File, CIOStream &Stream);
			/** 
			 * UnParse the file type box to the JP2 file.
			 * @param		JP2File		JP2 file being parsed
			 * @param		Stream		IOStream to use to parse file.
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		virtual CError UnParse(class CFile &JP2File, CIOStream &Stream);
	};
		/**
		 * CHeaderBox class - the JP2 file header box class.  This box is always present.
		 * 
		 * @author       Simon Cope
		 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
		 */	
	class NCSECW_IMPEX CHeaderBox: public CSuperBox {
	public:
			/**
			 * CImageHeaderBox class - the JP2 file image header box class.  This box is always present.
			 * 
			 * @author       Simon Cope
			 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
			 */	
		class NCSECW_IMPEX CImageHeaderBox: public CBox, public NCS::JPC::CComponentDepthType {
		public:
				/** Box type */
			static UINT32	sm_nTBox;

				/** Image Width */
			UINT32			m_nWidth;
				/** Image Height */
			UINT32			m_nHeight;
				/** Number of image components, eg RGB = 3 */
			UINT16			m_nComponents;
				/** Compression type, for a JP2 == 7 */
			UINT8			m_nCompressionType;
				/** Actual colorspace in image is known, 0 == known & ColourSpaceBox available, 1 == unkown */
			UINT8			m_nUnknownColorspace;
				/** Intellectual property, 0 = none, 1 - IPRBox present */
			UINT8			m_nIPR;

				/** Default constructor, initialises members */
			CImageHeaderBox();
				/** Virtual destructor */
			virtual ~CImageHeaderBox();
				/** 
				 * Update the extended length of the box prior to writing
				 */
			virtual void UpdateXLBox(void);

				/** 
				 * Parse the image header box from the JP2 file.
				 * @param		JP2File		JP2 file being parsed
				 * @param		Stream		IOStream to use to parse file.
				 * @return      CError	NCS_SUCCESS, or Error code on failure.
				 */
			virtual CError Parse(class CFile &JP2File, CIOStream &Stream);
				/** 
				 * UnParse the image header box to the JP2 file.
				 * @param		JP2File		JP2 file being parsed
				 * @param		Stream		IOStream to use to parse file.
				 * @return      CError	NCS_SUCCESS, or Error code on failure.
				 */
			virtual CError UnParse(class CFile &JP2File, CIOStream &Stream);
		};
			/**
			 * CBitsPerComponentBox class - the JP2 file bits per component box class.
			 * This box is only present if m_nBitsPerComponent in the IMageHeaderBox is 255, indicating
			 * each component may be a different bit depth (eg, 5/6/6 RGB).
			 * 
			 * @author       Simon Cope
			 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
			 */	
		class NCSECW_IMPEX CBitsPerComponentBox: public CBox {
		public:
				/** Box type */
			static UINT32	sm_nTBox;

				/** Bit depth for each component */
			std::vector<NCS::JPC::CComponentDepthType>	m_Bits;

				/** Default constructor, initialised members */
			CBitsPerComponentBox();
				/** Virtual destructor */
			virtual ~CBitsPerComponentBox();
				/** 
				 * Update the extended length of the box prior to writing
				 */
			virtual void UpdateXLBox(void);

				/** 
				 * Parse the bits per component box from the JP2 file.
				 * @param		JP2File		JP2 file being parsed
				 * @param		Stream		IOStream to use to parse file.
				 * @return      CError	NCS_SUCCESS, or Error code on failure.
				 */
			virtual CError Parse(class CFile &JP2File, CIOStream &Stream);
				/** 
				 * UnParse the bits per component box to the JP2 file.
				 * @param		JP2File		JP2 file being parsed
				 * @param		Stream		IOStream to use to parse file.
				 * @return      CError	NCS_SUCCESS, or Error code on failure.
				 */
			virtual CError UnParse(class CFile &JP2File, CIOStream &Stream);
		};
			/**
			 * CColorSpecificationBox class - the JP2 file color specification box class.
			 * This box is only present when m_nUnknownColorspace in the ImageHeaderBox == 0, 
			 * indicating the colorspace of the image is known.
			 * 
			 * @author       Simon Cope
			 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
			 */	
		class NCSECW_IMPEX CColorSpecificationBox: public CBox {
		public:
				/** Box type */
			static UINT32	sm_nTBox;

				/** ColorSpace type, may be predefined or an ICC mapping */
			typedef enum {
					/** Either sRGB or GREYSCALE colorspace */
				ENUMERATED_COLORSPACE		= 1,
					/** Rstricted ICC color profile is present */
				RESTRICTED_ICC_PROFILE		= 2,
					/** Full ICC color profile is present */
				ICC_PROFILE		= 3			
			} Type;
				/** Enumerated colorspace types */
			typedef enum {
					/** sRGB colorspace */
				sRGB						= 16,
					/** GREYSCALE colorspace */
				GREYSCALE					= 17,
					/** YCbCr colorspace */
				YCbCr						= 18,
					/** sYCbCr colorspace */
				sYCC						= 22
			} EnumeratedType;

				/** ColorSpace method, either ENUMERATED or ICC */
			Type		m_eMethod;
				/** Precedence, always = 0 & is ignored */
			UINT8		m_nPrecedence;
				/** Approximation, always = 0 & is ignored */
			UINT8		m_nApproximation;
				/** If m_nMethod == ENUMERATED, this specifies colorspace */
			EnumeratedType		m_eEnumeratedColorspace;
				/** If m_nMethod == ICC, this specifies ICC profile */
			void		*m_pICCProfile;
				/** Length in bytes of the in-memory ICC profile */
			UINT32		m_nICCLen;

				/** Default constructor, initialises members */
			CColorSpecificationBox();
				/** Cirtual destructor */
			virtual ~CColorSpecificationBox();
				/** 
				 * Update the extended length of the box prior to writing
				 */
			virtual void UpdateXLBox(void);
				/** 
				 * Parse the color specification box from the JP2 file.
				 * @param		JP2File		JP2 file being parsed
				 * @param		Stream		IOStream to use to parse file.
				 * @return      CError	NCS_SUCCESS, or Error code on failure.
				 */
			virtual CError Parse(class CFile &JP2File, CIOStream &Stream);
				/** 
				 * UnParse the color specification box to the JP2 file.
				 * @param		JP2File		JP2 file being parsed
				 * @param		Stream		IOStream to use to parse file.
				 * @return      CError	NCS_SUCCESS, or Error code on failure.
				 */
			virtual CError UnParse(class CFile &JP2File, CIOStream &Stream);
		};
			/**
			 * CPaletteBox class - the JP2 file palette box class.
			 * This box is always present with a component mapping box.
			 * 
			 * @author       Simon Cope
			 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
			 */	
		class NCSECW_IMPEX CPaletteBox: public CBox {
		public:
			typedef std::vector<void*> PaletteEntry;
				/** Box type */
			static UINT32	sm_nTBox;

				/** Number of entries in the palette, 1-1024 */
			UINT16		m_nEntries;
				/** Number of components generated by palette, eg RGB = 3 */
			UINT8		m_nComponents;
				/** Bit depth of each generated component, 1-38 bits, bit7 = sign */
			std::vector<NCS::JPC::CComponentDepthType>	m_Bits;
				/** Palette entries */
			std::vector<PaletteEntry> m_Entries;

				/** Default constructor, initialises members */
			CPaletteBox();
				/** Virtual destructor */
			virtual ~CPaletteBox();

				/** 
				 * Parse the palette box from the JP2 file.
				 * @param		JP2File		JP2 file being parsed
				 * @param		Stream		IOStream to use to parse file.
				 * @return      CError	NCS_SUCCESS, or Error code on failure.
				 */
			virtual CError Parse(class CFile &JP2File, CIOStream &Stream);
				/** 
				 * UnParse the palette box to the JP2 file.
				 * @param		JP2File		JP2 file being parsed
				 * @param		Stream		IOStream to use to parse file.
				 * @return      CError	NCS_SUCCESS, or Error code on failure.
				 */
			virtual CError UnParse(class CFile &JP2File, CIOStream &Stream);
		};
			/**
			 * CComponentMappingBox class - the JP2 file component mapping box class.
			 * This box is always present with a palette box to define channel usage.
			 * 
			 * @author       Simon Cope
			 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
			 */	
		class NCSECW_IMPEX CComponentMappingBox: public CBox {
		public:
				/** Type of component */
			typedef enum {
					/** This is the direct component value, eg Red */
				DIRECT		= 0,
					/** This component is a palette index */
				PALETTE		= 1
			} Type;

				/** Component mapping information  */
			typedef struct {
					/** 0-based index of the component this mapping is for */
				UINT16	m_iComponent;
					/** Type of component */
				Type	m_nType;
					/** Component "column" index into palette */
				UINT8	m_iPalette;
			} ComponentMapping;

				/** Box type */
			static UINT32	sm_nTBox;

				/** Number of entries in the componentmapping */
			UINT16		m_nEntries;

				/** Component->Palette mappings */
			std::vector<ComponentMapping>	m_Mapping;

				/** Default constructor, initialises members */
			CComponentMappingBox();
				/** Cirtual destructor */
			virtual ~CComponentMappingBox();

				/** 
				 * Parse the component mapping box from the JP2 file.
				 * @param		JP2File		JP2 file being parsed
				 * @param		Stream		IOStream to use to parse file.
				 * @return      CError	NCS_SUCCESS, or Error code on failure.
				 */
			virtual CError Parse(class CFile &JP2File, CIOStream &Stream);
				/** 
				 * UnParse the component mapping box to the JP2 file.
				 * @param		JP2File		JP2 file being parsed
				 * @param		Stream		IOStream to use to parse file.
				 * @return      CError	NCS_SUCCESS, or Error code on failure.
				 */
			virtual CError UnParse(class CFile &JP2File, CIOStream &Stream);
		};
			/**
			 * CChannelDefinitionBox class - the JP2 file channel definition box class.
			 * This box is optional.
			 * 
			 * @author       Simon Cope
			 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
			 */	
		class NCSECW_IMPEX CChannelDefinitionBox: public CBox {
		public:
				/** Channel type */
			typedef enum {
					/** Color value */
				COLOR			= 0,
					/** Opacity value */
				OPACITY			= 1,
					/** Premultiplied opacity value */
				PREMUL_OPACITY	= 2,
					/** Channel type is unknown */
				UNKNOWN			= 0xffff
			} Type;

				/** Color channel this channel is associated with */
			typedef enum {
					/** The entire image, eg RGBA */
				WHOLE_IMAGE		= 0,
					/** Red channel */
				R				= 1,
					/** Green channel */
				G				= 2,
					/** Blue channel */
				B				= 3,
					/** Luminance/Greyscale channel */
				Y				= 1,
					/** Cb channel */
				Cb				= 2,
					/** Cr channel */
				Cr				= 3,
					/** No channel associated */
				NONE			= 0xffff
			} Association;

				/** A channel definition */
			typedef struct {
					/** 0-based index of channel this definition is for */
				UINT16		m_iChannel;
					/** Channel type */
				Type		m_eType;
					/** Channel color component association */
				Association	m_eAssociation;
			} ChannelDefinition;

				/** Box type */
			static UINT32	sm_nTBox;

				/** Number of definitions */
			UINT16		m_nEntries;

				/** Channel Definitiona*/
			std::vector<ChannelDefinition>	m_Definitions;

				/** Default constructor, initialises members */
			CChannelDefinitionBox();
				/** Cirtual destructor */
			virtual ~CChannelDefinitionBox();

				/** 
				 * Get the ChannelDefinition for the specified channel index.
				 * @param		iChannel	Channel index
				 * @return      const ChannelDefinition*	ChannelDefinition, or NULL on failure.
				 */
			virtual const ChannelDefinition *GetDefinitition(UINT16 iChannel);
				/** 
				 * Update the extended length of the box prior to writing
				 */
			virtual void UpdateXLBox(void);
				/** 
				 * Parse the channel definition box from the JP2 file.
				 * @param		JP2File		JP2 file being parsed
				 * @param		Stream		IOStream to use to parse file.
				 * @return      CError	NCS_SUCCESS, or Error code on failure.
				 */
			virtual CError Parse(class CFile &JP2File, CIOStream &Stream);
				/** 
				 * UnParse the channel definition box to the JP2 file.
				 * @param		JP2File		JP2 file being parsed
				 * @param		Stream		IOStream to use to parse file.
				 * @return      CError	NCS_SUCCESS, or Error code on failure.
				 */
			virtual CError UnParse(class CFile &JP2File, CIOStream &Stream);
		};
			/**
			 * CResolutionBox class - the JP2 file resolution box class.
			 * This box is optional.
			 * 
			 * @author       Simon Cope
			 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
			 */	
		class NCSECW_IMPEX CResolutionBox: public CSuperBox {
		public:
				/**
				 * CCaptureResolutionBox class - the JP2 file capture resolution box class.
				 * This box is optional.
				 *
				 * Actual resolution is in grid points per meter, calculated as:
				 *
				 * Rc = (RcN / RcD) * 10^RcE
				 * 
				 * @author       Simon Cope
				 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
				 */	
			class NCSECW_IMPEX CCaptureResolutionBox: public CBox {
			public:
					/** Box type */
				static UINT32	sm_nTBox;

					/** Vertical grid resolution numerator */
				UINT16		m_nVRcN;
					/** Vertical grid resolution denominator */
				UINT16		m_nVRcD;
					/** Vertical grid resolution exponent, two's compliment */
				INT8		m_nVRcE;
					/** Horizontal grid resolution numerator */
				UINT16		m_nHRcN;
					/** Horizontal grid resolution denominator */
				UINT16		m_nHRcD;
					/** Horizontal grid resolution exponent, two's compliment */
				INT8		m_nHRcE;

				/** Default constructor, initialises members */
				CCaptureResolutionBox();
					/** Cirtual destructor */
				virtual ~CCaptureResolutionBox();


					/** 
					 * Parse the capture resolution box from the JP2 file.
					 * @param		JP2File		JP2 file being parsed
					 * @param		Stream		IOStream to use to parse file.
					 * @return      CError	NCS_SUCCESS, or Error code on failure.
					 */
				virtual CError Parse(class CFile &JP2File, CIOStream &Stream);
					/** 
					 * UnParse the capture resolution box to the JP2 file.
					 * @param		JP2File		JP2 file being parsed
					 * @param		Stream		IOStream to use to parse file.
					 * @return      CError	NCS_SUCCESS, or Error code on failure.
					 */
				virtual CError UnParse(class CFile &JP2File, CIOStream &Stream);
			};
				/**
				 * CDefaultDisplayResolutionBox class - the JP2 file default display resolution box class.
				 * This box is optional.
				 *
				 * Actual resolution is in grid points per meter, calculated as:
				 *
				 * Rc = (RcN / RcD) * 10^RcE
				 * 
				 * @author       Simon Cope
				 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
				 */	
			class NCSECW_IMPEX CDefaultDisplayResolutionBox: public CCaptureResolutionBox {
			public:
					/** Box type */
				static UINT32	sm_nTBox;

				/** Default constructor, initialises members */
				CDefaultDisplayResolutionBox();
					/** Cirtual destructor */
				virtual ~CDefaultDisplayResolutionBox();
			};
				/** Box Type */
			static UINT32	sm_nTBox;

				/** CaptureResolutionBox within ResolutionBox */
			CCaptureResolutionBox m_Capture;
				/** DefaultDisplayResolutionBox within ResolutionBox */
			CDefaultDisplayResolutionBox m_DefaultDisplay;

				/** Default constructor, initialises members */
			CResolutionBox();
				/** Virtual destructor */
			virtual ~CResolutionBox();
		};

			/** Box Type */
		static UINT32	sm_nTBox;

			/** ImageHeaderBox within HeaderBox */
		CImageHeaderBox m_ImageHeader;
			/** Optional BitsPerComponentBox within HeaderBox */
		CBitsPerComponentBox m_BitsPerComponent;
			/** Optional ColorSpecificationBox within HeaderBox */
		CColorSpecificationBox m_ColorSpecification; 
			/** Optional PaletteBox within HeaderBox */
		CPaletteBox m_Palette;
			/** OPtional ComponentMappingBox within HeaderBox */
		CComponentMappingBox m_ComponentMapping;
			/** Optional ChannelDefinitionBox within HeaderBox */
		CChannelDefinitionBox m_ChannelDefinition;
			/** OPtional ResolutionBox within HeaderBox */
		CResolutionBox m_Resolution;

			/** Default contructor, initialises members */
		CHeaderBox();
			/** Virtual destructor */
		virtual ~CHeaderBox();
	};
		/**
		 * CIntellectualPropertyBox class - the JP2 IPR box.  This box is optional.
		 * 
		 * @author       Simon Cope
		 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
		 */	
	class NCSECW_IMPEX CIntellectualPropertyBox: public CBox {
	public:
			/** Box type */ 
		static UINT32	sm_nTBox;

			/** Default constructor, initialises members */
		CIntellectualPropertyBox();
			/** Virtual destructor */
		virtual ~CIntellectualPropertyBox();
			/** 
			 * Parse the JPC box from the JP2 file.
			 * @param		JP2File		JP2 file being parsed
			 * @param		Stream		IOStream to use to parse file.
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		virtual CError Parse(class CFile &JP2File, CIOStream &Stream);
	};
		/**
		 * CXMLBox class - the JP2 XML box.  This box is optional, and there may be more than one.
		 * 
		 * @author       Simon Cope
		 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
		 */	
	class NCSECW_IMPEX CXMLBox: public CBox {
	public:
			/** Box type */ 
		static UINT32	sm_nTBox;

			/** Default constructor, initialises members */
		CXMLBox();
			/** Virtual destructor */
		virtual ~CXMLBox();
			/** 
			 * Parse the XML box from the JP2 file.
			 * @param		JP2File		JP2 file being parsed
			 * @param		Stream		IOStream to use to parse file.
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		virtual CError Parse(class CFile &JP2File, CIOStream &Stream);
			/** 
			 * UnParse the XML box to the JP2 file.
			 * @param		JP2File		JP2 file being parsed
			 * @param		Stream		IOStream to use to parse file.
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		virtual CError UnParse(class CFile &JP2File, CIOStream &Stream);
	};
		/**
		 * CUUIDBox class - the JP2 UUID box.  This box is optional, and there may be more than one.
		 * 
		 * @author       Simon Cope
		 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
		 */	
	class NCSECW_IMPEX CUUIDBox: public CBox {
	public:
			/** Box type */ 
		static UINT32	sm_nTBox;
			/** UUID */
		UUID	m_UUID;
			/** UUID Box data */
		void *m_pData;
			/** UUID Box data Length*/
		INT32 m_nLength;

			/** Default constructor, initialises members */
		CUUIDBox();
			/** Virtual destructor */
		virtual ~CUUIDBox();

			/** 
			 * Parse the UUID box from the JP2 file.
			 * @param		JP2File		JP2 file being parsed
			 * @param		Stream		IOStream to use to parse file.
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		virtual CError Parse(class CFile &JP2File, CIOStream &Stream);
			/** 
			 * UnParse the UUID box to the JP2 file.
			 * @param		JP2File		JP2 file being parsed
			 * @param		Stream		IOStream to use to parse file.
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		virtual CError UnParse(class CFile &JP2File, CIOStream &Stream);
	};
		/**
		 * CUUIDInfoBox class - the JP2 UUIDInfo box.  This box is optional, and there may be more than one.
		 * 
		 * @author       Simon Cope
		 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
		 */	
	class NCSECW_IMPEX CUUIDInfoBox: public CSuperBox {
	public:
			/**
			 * CUUIDListBox class - the JP2 file UUIDList box class.
			 * This box is required within a UUIDInfo box.
			 * 
			 * @author       Simon Cope
			 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
			 */	
		class NCSECW_IMPEX CUUIDListBox: public CBox {
		public:
			
				/** Box type */
			static UINT32	sm_nTBox;
				/** Number of entries */
			UINT16		m_nEntries;
				/** UUIDs */
			std::vector<UUID> m_UUIDs;
			
				/** Default constructor, initialises members */
			CUUIDListBox();
				/** Virtual destructor */
			virtual ~CUUIDListBox();

				/** 
				 * Parse the UUID List box from the JP2 file.
				 * @param		JP2File		JP2 file being parsed
				 * @param		Stream		IOStream to use to parse file.
				 * @return      CError	NCS_SUCCESS, or Error code on failure.
				 */
			virtual CError Parse(class CFile &JP2File, CIOStream &Stream);
				/**
				 * UnParse the UUID list box to the JP2 file.
				 * @param		JP2File		JP2 file being parsed
				 * @param		Stream		IOStream to use to parse file.
				 * @return      CError	NCS_SUCCESS, or Error code on failure.
				 */
			virtual CError UnParse(class CFile &JP2File, CIOStream &Stream);
		};
			/**
			 * CDataEntryURLBox class - the JP2 file DateEntryURL box class.
			 * This box is required within a UUIDInfo box.
			 * 
			 * @author       Simon Cope
			 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
			 */	
		class NCSECW_IMPEX CDataEntryURLBox: public CBox {
		public:
			
				/** Box type */
			static UINT32	sm_nTBox;

				/** Version */
			UINT8		m_nVersion;
				/** Flags */
			UINT8		m_Flags[3];
				/** Location URL */
			UINT8		*m_pLocation;

				/** Default constructor, initialises members */
			CDataEntryURLBox();
				/** Cirtual destructor */
			virtual ~CDataEntryURLBox();

				/** 
				 * Parse the Data Entry URL box from the JP2 file.
				 * @param		JP2File		JP2 file being parsed
				 * @param		Stream		IOStream to use to parse file.
				 * @return      CError	NCS_SUCCESS, or Error code on failure.
				 */
			virtual CError Parse(class CFile &JP2File, CIOStream &Stream);
				/**
				 * UnParse the Data Entry URL box to the JP2 file.
				 * @param		JP2File		JP2 file being parsed
				 * @param		Stream		IOStream to use to parse file.
				 * @return      CError	NCS_SUCCESS, or Error code on failure.
				 */
			virtual CError UnParse(class CFile &JP2File, CIOStream &Stream);
		};
			/** Box Type */
		static UINT32	sm_nTBox;
				/** UUIDListBox within UUIDInfo */
		CUUIDListBox m_List;
				/** DataEntryURLBox within the UUIDInfo */
		CDataEntryURLBox m_DE;

				/** Default constructor, initialises members */
		CUUIDInfoBox();
			/** Virtual destructor */
		virtual ~CUUIDInfoBox();
	};
		/**
		 * CPCSBox class - the JP2 PCS GeoKey box.  This box is optional
		 * This implements a quick and dirty GeoTIFF tag parser rather than rely on a 3rd party 
		 * TIFF implementation such as TIFFlib.  Alternatively, an application can read the box contents 
		 * directly to implement more reobust/thorough parsing of the PCS tag values.
		 * 
		 * @author       Simon Cope & Tom Lynch
		 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
		 */	
	class NCSECW_IMPEX CPCSBox: public CUUIDBox {
	public:
			/** Relevent TIFF tag names */
		typedef enum {
				/** Model Pixel Scale */
			ModelPixelScale		= 0x830e,
				/** Model Tie Point */
			ModelTiePoint		= 0x8482,
				/** Model Transformantion */
			ModelTransformation = 0x85d8,
				/** GetKey Directory */
			GeoKeyDirectory		= 0x87af,
				/** GeoKey Double Parameters */
			GeoDoubleParams		= 0x87b0,
				/** GetKey ASCII Parameters */
			GeoASCIIParams		= 0x87b1,
		} TIFFTagNames;

			/** TIFF Tag structure */
		typedef struct {
				/** Tag value */
			UINT16 Tag;
				/** Tag type */
			UINT16 Type;
				/** Number of values */
			UINT32 Count;
				/** IFD offset to values */
			UINT32 Offset;
				/** Vector of the parsed double values */
			std::vector<double>	Values;
		} TIFFTag;

			/** GeoKey value union */
		typedef union {
				/** An integer value - u16 */
			UINT16		nValue;
				/** A double value */
			double		dValue;
				/** A string value */
			char		*pValue;
		} GeoKeyValue;

			/** GetKey type enum = u16, double, ASCII */
		typedef enum {
				/** An integer value */
			GKT_SHORT	= 0,
				/** A double value */
			GKT_DOUBLE	= GeoDoubleParams,
				/** A string value */
			GKT_ASCII   = GeoASCIIParams
		} GeoKeyType;

			/** An GeoKey value */
		typedef struct {
				/** The Key ID */
			UINT16 KeyID;
				/** The Key Type */
			GeoKeyType Type;
				/** Number of values */
			UINT16 Count;

				/** The value */
			GeoKeyValue v;
		} GeoKey;

			/** UUID for the PCS box */
		static UUID sm_UUID;

			/** Default constructor, initialises members */
		CPCSBox();
			/** Virtual destructor */
		virtual ~CPCSBox();

			/** Update the extended length for the box before writing */
		virtual void UpdateXLBox(void);
			/** 
			 * Parse the PCS GeoKey box from the JP2 file.
			 * @param		JP2File		JP2 file being parsed
			 * @param		Stream		IOStream to use to parse file.
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		virtual CError Parse(class CFile &JP2File, CIOStream &Stream);
			/** 
			 * UnParse the PCS GeoKey box to the JP2 file.
			 * @param		JP2File		JP2 file being parsed
			 * @param		Stream		IOStream to use to parse file.
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		virtual CError UnParse(class CFile &JP2File, CIOStream &Stream);
			/** 
			 * get an NCSFileViewFileInfoEx structure equivalent of the parsed PCS box.
			 * @param		FileInfo	Info struct to fill in
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		CError GetFileInfo(NCSFileViewFileInfoEx &FileInfo);
			/** 
			 * Setup the PCS box from an NCSFileViewFileInfoEx structure prior to writing out
			 * @param		FileInfo	Info struct to create PCS box from
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		CError SetFileInfo(NCSFileViewFileInfoEx &FileInfo);
			/**
			 * Set the precision used in processing registration by the PCS box.
			 * @param		fPrecision	The value below which to discard registration values
			 */
		static void SetPrecision(IEEE4 fPrecision);
	private:
			/** 
			 * get a tag from it's name 
			 * @param		eTag		Tag name to get tag for
			 * @return      TIFFTag*	TIFF Tag, or NULL on failure.
			 */
		TIFFTag *GetTag(TIFFTagNames eTag);
			/** 
			 * get a GetKey from it's key name
			 * @param		Key			GetKey name to get
			 * @return      GeoKey*		GeoKey, or NULL on failure.
			 */
		GeoKey *GetKey(UINT16 Key);
			/** 
			 * Process the GeoTIFF Info 
			 * @return      CError	NCS_SUCCESS, or error on failure
			 */
		CError ProcessGeoTIFFInfo();
			/** 
			 * Format the GetTIFF Info
			 * @param		pBuf		Info buffer
			 * @return      CError	NCS_SUCCESS, or error on failure\
			 */
		CError FormatGeoTIFFInfo(UINT8 *pBuf, char *szFilename);

			/** PCSFileInfo */
		NCSFileViewFileInfoEx m_PCSFileInfo;
			/** Vector of the TIFF Tags */
		std::vector<TIFFTag> m_TIFFTags;
			/** Vector of the GeoKeys */
		std::vector<GeoKey> m_GeoKeys;
			/** Actual GeoTIFF box length - FIXME is this required? */
		UINT32 m_nGeoTIFFBoxLength;
			/** Geodata precision */
		static IEEE4 sm_fGeodataPrecisionEpsilon;
	};
		/**
		 * CGMLGeoLocationBox class - the JP2 GML box.  This box is optional
		 * 
		 * @author       Simon Cope
		 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
		 */	
	class NCSECW_IMPEX CGMLGeoLocationBox: public CXMLBox {
	public:
			/** Default constructor, initialises members */
		CGMLGeoLocationBox();
			/** Virtual destructor */
		virtual ~CGMLGeoLocationBox();

			/** Update the extended length of the box prior to writing */
		virtual void UpdateXLBox(void);
			/** 
			 * Parse the GML GeoLocation box from the JP2 file.
			 * @param		JP2File		JP2 file being parsed
			 * @param		Stream		IOStream to use to parse file.
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		virtual CError Parse(class CFile &JP2File, CIOStream &Stream);

		virtual CError Parse(const char *pXML, UINT32 nImageWidth, UINT32 nImageHeight);

			/** 
			 * UnParse the GML GeoLocation box to the JP2 file.
			 * @param		JP2File		JP2 file being parsed
			 * @param		Stream		IOStream to use to parse file.
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		virtual CError UnParse(class CFile &JP2File, CIOStream &Stream);

			/** 
			 * get an NCSFileViewFileInfoEx structure equivalent of the parsed GML box.
			 * @param		FileInfo	Info struct to fill in
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		CError GetFileInfo(NCSFileViewFileInfoEx &FileInfo);
			/** 
			 * Setup the GML box from an NCSFileViewFileInfoEx structure prior to writing out
			 * @param		FileInfo	Info struct to create PCS box from
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		CError SetFileInfo(NCSFileViewFileInfoEx &FileInfo);

	private:
		int ParseGML( const char *pGML, UINT32 &nEPSGCode, bool &bSRSAttributePresent,
			 double &dRegX, double &dRegY, double *pP1, double *pP2);

		CError SetGMLFileInfo(UINT32 nImageWidth, UINT32 nImageHeight, int nResults, UINT32 nEPSGCode,
			bool bSRSAttributePresent, double dRegX, double dRegY, double *pP1, double *pP2);

			/** GML FileInfo structure */
		NCSFileViewFileInfoEx	m_GMLFileInfo;
			/** 
			 * Setup the GML box prior to writing out
			 * @param		pBuf		Buffer to format XMl into 
			 * @param		nBufLen		Buffer length
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */			
		CError FormatXML(char *pBuf, UINT32 nBufLen);
	};
		/**
		 * CWorldBox class - the JP2 World file box.  This box is optional
		 * 
		 * @author       Tom Lynch
		 * @version      $Revision: #3 $ $Author: jshao $ $Date: 2012/03/12 $ 
		 */	
	class NCSECW_IMPEX CWorldBox: public CUUIDBox {
	public:
			/** UUID for the World box */
		static UUID sm_UUID;
			/** Default constructor, initialises members */
		CWorldBox();
			/** Virtual destructor */
		virtual ~CWorldBox();
			/** Update the extended length for the box before writing */
		virtual void UpdateXLBox(void);
			/** 
			 * Parse the World box from the JP2 file.
			 * @param		JP2File		JP2 file being parsed
			 * @param		Stream		IOStream to use to parse file.
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		virtual CError Parse(class CFile &JP2File, CIOStream &Stream);
			/** 
			 * UnParse the World box to the JP2 file.
			 * @param		JP2File		JP2 file being parsed
			 * @param		Stream		IOStream to use to parse file.
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		virtual CError UnParse(class CFile &JP2File, CIOStream &Stream);
			/** 
			 * get an NCSFileViewFileInfoEx structure equivalent of the parsed World box.
			 * @param		FileInfo	Info struct to fill in
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		CError GetFileInfo(NCSFileViewFileInfoEx &FileInfo);
			/** 
			 * Setup the World box from an NCSFileViewFileInfoEx structure prior to writing out
			 * @param		FileInfo	Info struct to create World box from
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		CError SetFileInfo(NCSFileViewFileInfoEx &FileInfo);
			/**
			 * Set the precision used in processing registration by the World box.
			 * @param		fPrecision	The value below which to discard registration values
			 */
		static void SetPrecision(IEEE4 fPrecision);
	private:
		CError ProcessWorldInfo();
			/** 
			 * Format the GetTIFF Info
			 * @param		pBuf		Info buffer
			 * @return      CError	NCS_SUCCESS, or error on failure\
			 */
		CError FormatWorldInfo(UINT8 *pBuf);

			/** WorldFileInfo */
		NCSFileViewFileInfoEx m_WorldFileInfo;
			/** Accumulated length of box */
		UINT32 m_nWorldBoxLength;
			/** World chunk "feature flags" */
		UINT8 m_pFeatureFlags[8];
			/** Geodata precision */
		static IEEE4 sm_fGeodataPrecisionEpsilon;
	};

	class NCSECW_IMPEX CAssociationBox: public CSuperBox {
	public:
		static UINT32	sm_nTBox;

		/** Default constructor, initialises members */
		CAssociationBox();
		/** Virtual destructor */
		virtual ~CAssociationBox() {};

		virtual CError UnParse(class CFile &JP2File, CIOStream &Stream);
	};

	class NCSECW_IMPEX CReaderRequirementsBox: public CBox {
	public:
		static UINT32	sm_nTBox;
		CReaderRequirementsBox();
			/** Virtual destructor */
		virtual ~CReaderRequirementsBox();
			/** Update the extended length for the box before writing */
		virtual void UpdateXLBox(void);
			/** 
			 * Parse the XML box from the JP2 file.
			 * @param		JP2File		JP2 file being parsed
			 * @param		Stream		IOStream to use to parse file.
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		virtual CError Parse(class NCS::JP2::CFile &JP2File, CIOStream &Stream);
			/** 
			 * UnParse the XML box to the JP2 file.
			 * @param		JP2File		JP2 file being parsed
			 * @param		Stream		IOStream to use to parse file.
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		virtual CError UnParse(class NCS::JP2::CFile &JP2File, CIOStream &Stream);
	};

	class NCSECW_IMPEX CLabelBox: public CBox {
	public:
		static UINT32	sm_nTBox;
		char *m_szLabel;

			/** Default constructor, initialises members */
		CLabelBox();
			/** Overloaded constructor, specify label */
		CLabelBox(const char *szLabel);
			/** Virtual destructor */
		virtual ~CLabelBox();
			/** Update the extended length for the box before writing */
		virtual void UpdateXLBox(void);
			/**
			 * Set the label to be parsed out into the file.
			 * @param		szLabel		Label text
			 */
		virtual void SetLabel(const char* szLabel);
			/**
			 * Get the label text of this box, if any
			 * @return		const char *		Label text
			 */
		virtual const char *GetLabel() const;
			/** 
			 * Parse the XML box from the JP2 file.
			 * @param		JP2File		JP2 file being parsed
			 * @param		Stream		IOStream to use to parse file.
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		virtual CError Parse(class NCS::JP2::CFile &JP2File, CIOStream &Stream);
			/** 
			 * UnParse the XML box to the JP2 file.
			 * @param		JP2File		JP2 file being parsed
			 * @param		Stream		IOStream to use to parse file.
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		virtual CError UnParse(class NCS::JP2::CFile &JP2File, CIOStream &Stream);
	};

	class NCSECW_IMPEX CGMLJP2Box: public CXMLBox {
	public:
			/** Maximum size of GML data buffers */
		static const UINT32 sm_nMAX_SIZE;
		//const UINT32 sm_nMAX_SIZE;
			/** Default constructor, initialises members */
		CGMLJP2Box();
			/** Virtual destructor */
		virtual ~CGMLJP2Box();

			/** Update the extended length of the box prior to writing */
		virtual void UpdateXLBox(void);
			/** 
			 * Parse the GMLJP2 box from the JP2 file.
			 * @param		JP2File		JP2 file being parsed
			 * @param		Stream		IOStream to use to parse file.
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		virtual CError Parse(class NCS::JP2::CFile &JP2File, CIOStream &Stream);
			/** 
			 * UnParse the GMLJP2 box to the JP2 file.
			 * @param		JP2File		JP2 file being parsed
			 * @param		Stream		IOStream to use to parse file.
			 * @return      CError	NCS_SUCCESS, or Error code on failure.
			 */
		virtual CError UnParse(class NCS::JP2::CFile &JP2File, CIOStream &Stream);
			/**
			 * Set the GML data to be unparsed by this box
			 * @param		szData		data to be unparsed
			 */
		void SetGML(const char *szData);
			/**
			 * Get the raw GML data parsed from inside this box
			 * @return		char *	     The raw data
			 */
		const char *GetGML();
	private:
		char *m_szData;
	};

	typedef enum
	{
		GMLRootInstance,
		GMLDictionary,
		GMLOther
	} GMLJP2Type;
	typedef std::pair<GMLJP2Type, CGMLJP2Box *> CGMLJP2ValuePair;

	class NCSECW_IMPEX CGMLJP2Data: public std::vector<CGMLJP2ValuePair>
	{
	public:
		CGMLJP2Data();
		~CGMLJP2Data();
		/** Push a new XML box with associated type to the back of this vector, if valid to do so*/
		bool Push(GMLJP2Type Type, CGMLJP2Box* pBox);
		/** Parse all GMLJP2 related data from an input file */
		CError ParseGMLJP2Boxes(class NCS::JP2::CFile &File, CIOStream& Stream);
		CError ParseGMLJP2Boxes(const char *pGML, UINT32 nImageWidth, UINT32 nImageHeight );
		/** Add GMLJP2 box structure to an output JP2File */
		CError ConstructGMLJP2Boxes(class NCS::JP2::CFile &File, UINT32 nEPSGCode =0);
		/** Set NCS style georef info for output */
		CError SetFileInfo(NCSFileViewFileInfoEx &FileInfo);
		/** Get NCS style georef info from data */
		CError GetFileInfo(NCSFileViewFileInfoEx &FileInfo);
		/** Get root instance box, if any, otherwise return NULL */
		CGMLJP2Box *GetRootInstance();
		/** Get dictionary box, if any, otherwise return NULL */
		CGMLJP2Box *GetDictionary();
		/** Get dictionary name, if any */
		const char *GetDictionaryName() const;
		/** Construct a GMLJP2 root-instance box for output */
		CError FormatRootInstanceGML(char *pBuf, UINT32 nBufferLength, UINT32 nEPSGCode =0);

		/** Do we have a GMLJP2 root-instance? */
		bool m_bHaveRootInstance;
		/** GML root instance data */
		CGMLJP2Box m_GMLBox;
		/** Top-level asoc box for top-level label and lower asoc box */
		CAssociationBox m_TopAsocBox;
	private:
		/** Parse a GMLJP2 root-instance box */
		bool ParseRootInstance(CGMLJP2Box *pBox);
		bool ParseRootInstance(const char *pGML);
		/** Parse a GMLJP2 dictionary box */
		bool ParseDictionary(CGMLJP2Box *pDict);
		/** Do we have a GMLJP2 dictionary box? */
		bool m_bHaveDictionary;
		/** Do we require a GMLJP2 dictionary box with a specific name? */
		bool m_bNeedDictionary;
		/** Name of required dictionary box */
		std::string m_DictionaryName;
		/** Name of GML fragment detailing SRS within dictionary box */
		std::string m_DictionaryRef;
		/** NCS style geodata */
		NCSFileViewFileInfoEx m_GMLFileInfo;
		/** File height in pixels */
		UINT32 m_nImageHeight;
		/** File width in pixels */
		UINT32 m_nImageWidth;
		/** Top-level label for output : "gml.data" */
		CLabelBox m_TopLabelBox;
		/** Bottom-level label for output : "gml.root-instance" */
		CLabelBox m_LowerLabelBox;
		/** Bottom-level asoc box for bottom-level label and GML root instance data */
		CAssociationBox m_LowerAsocBox;
		// CJP2HeaderEditor friend class to gain access to 
		//friend class CJP2HeaderEditor;
	};

		/** SignatureBox within JP2File */
	CSignatureBox		m_Signature;
		/** FileTypeBox within JP2File */
	CFileTypeBox		m_FileType;
		/** HeaderBox within JP2File */
	CHeaderBox		m_Header;
		/** ContiguousCodestreamBox ie "JPC" within JP2File */
//	CContiguousCodestreamBox	m_Codestream;
		/** IntellectualPropertyBox within JP2File */
	CIntellectualPropertyBox m_IPR;
		/** GML geolocation box */
	CGMLGeoLocationBox m_GML;
		/** PCS Geokey box */
	CPCSBox m_PCS;
		/** Aggregated GMLJP2 data */
	CGMLJP2Data m_GMLJP2Data;

		/** Component index for each output channel - 1:1 unless a palette is present */
	std::vector<UINT16>	m_ChannelComponentIndex;

		/** 
		 * Get the memory image of the file.
		 * @param		pLength		Returned length of image
		 * @return      void *		NCSMalloc()'d pointer to image.
		 */
	virtual void *GetMemImage(UINT32 &nLength);
		/** 
		 * Get length of a packet in the file.
		 * @param		nPacket		Absolute Packet number to determine length for
		 * @return      UINT32		Packet length or 0 on failure.
		 */
	virtual UINT32 GetPacketLength(NCSBlockId nPacket);
		/** 
		 * Read a packet from the file.
		 * @param		nPacket		Absolute Packet number to determine length for
		 * @param		pLength		Returned length of packet (header+data)
		 * @return      void *		NCSMalloc()'d pointer to read packet (header+data).
		 */
	virtual void *GetPacket(NCSBlockId nPacket, UINT32 &nLength);
		/** 
		 * Get number of a packet in the file.
		 * @return      UINT32		Number of Packets or 0 on failure.
		 */
	virtual UINT32 GetNrPackets();

		/** 
		 * Get a pointer to a UUID box bsed on the specified UUID.  Iterate via the pLast paramter.
		 * @param		uuid		UUID to find UUID box for
		 * @param		pLast		Pointer to last returned UUID box (or NULL on first call), used to iterate through multiple UUID boxes with the same UUID
		 * @return      CUUIDBox*		Pointer to UUID Box.
		 */
	CUUIDBox *GetUUIDBox(UUID uuid, CUUIDBox *pLast = NULL);
		/** 
		 * Get a pointer to an XML box.  Iterate via the pLast paramter.
		 * @param		pLast		Pointer to last returned XML box (or NULL on first call), used to iterate through multiple XML boxes
		 * @return      CXMLBox*		Pointer to XML Box.
		 */
	CXMLBox *GetXMLBox(CXMLBox *pLast = NULL);

		/** 
		 * Set the compression parameters (dimensions, registration, bitdepth etc).
		 * @param		Info		FileInfo structure
		 * @return      CError	NCS_SUCCESS, or error on failure 
		 */
	virtual CError SetCompress(NCSFileViewFileInfoEx &Info);
		/** 
		 * Write the next line in BIL format into the file.
		 * @param		nCtx				Unique Context ID
		 * @param		pSrc				Source buffer
		 * @param		iComponent			Component index
		 * @return      bool				true on success, else false.
		 */
	virtual bool WriteLine(ContextID nCtx, CBuffer2D *pSrc, UINT16 iComponent);
		/** 
		 * Get normal Node Width.
		 * @return      INT32		Un-clipped Width of codeblocks.
		 */
	virtual UINT32 GetNodeWidth(UINT16 iComponent = 0);
		/** 
		 * Get normal Node Height.
		 * @return      INT32		Un-clipped height of codeblocks.
		 */
	virtual UINT32 GetNodeHeight(UINT16 iComponent = 0);
		/** 
		 * Get number of nodes wide.
		 * @return      INT32		Nr of codeblocks across.
		 */
	virtual UINT32 GetNumNodesWide(UINT16 iComponent = 0);
		/** 
		 * Get number of nodes high.
		 * @return      INT32		Nr of codeblocks high.
		 */
	virtual UINT32 GetNumNodesHigh(UINT16 iComponent = 0);
		/** 
		 * Get pointer to specific node.
		 * @param		UINT32		Node nr
		 * @return      CNode2D * Ptr to node.
		 */
	virtual CNode2D *GetNodePtr(UINT32 nNode, UINT16 iComponent = 0);

		/** 
		 * Enable unlimited compression - NOTE YOU MUST COMPLY WITH THE EULA.
		 */
	//static void SetKeySize(char *szKey) { CFileBase::SetKeySize(szKey); };

	virtual NCSFileType GetFileType() { return(NCS_FILE_JP2); };
	virtual NCSFileViewFileInfoEx *GetFileInfo();

//protected:
	friend class CFileFactory;

		/** Default constructor, initialises members */
	CFile();
		/** Virtual Destructor */
	virtual ~CFile();

		/** 
		 * Open the JP2 file from the specified stream.
		 * @param		Stream		Stream of JP2 file to open
		 * @return      CError	NCS_SUCCESS or error code on failuer.
		 */
	virtual CError Open(CIOStream *pStream);
		/** 
		 * Close the JP2 file.
		 * @param		bFreeCache	Free the cache & delete file object if last close
		 * @return      CError	NCS_SUCCESS or error code on failuer.
		 */
	virtual CError Close();

private:
	friend NCS::CView;
	friend CReader;
	friend CWriter;
	friend SDK::CGlobalLock;
	friend JP2::CExtIndexBox;

	// Header Editor helper functions
	static NCSError JP2WriteGMLBox(NCS::JP2::CFile *jp2File, NCS::CIOStream* IOStream);
	static NCSError JP2WriteFreeBox(UINT64 boxOffset,UINT64 boxLength, NCS::CIOStream* pIOStream);
	static void JP2SetEditInfo(NCSFileViewFileInfoEx *pInfo,NCSEcwEditInfo* pEditInfo);

	virtual CIOStream *CreateBlockStream(const CString &URLPath, const CString &);

		/** 
		 * Add a JP2 file box to a memory image
		 * @param		pImage			Existing memory image to append box to.
		 * @param		pLength			Current/returned length of memory image.
		 * @param		pBox			JP2 Box to append to memory image.
		 * @return      void*			Memory image with appended box, else NULL on error.
		 */
	void *GetMemImage_AddBox(void *pImage, UINT32 *pLength, CBox *pBox);
		/** 
		 * Add a JPC codestream marker to a memory image
		 * @param		pImage			Existing memory image to append box to.
		 * @param		pLength			Current/returned length of memory image.
		 * @param		pMarker			JPC codestream marker to append to memory image.
		 * @return      void*			Memory image with appended box, else NULL on error.
		 */
	void *GetMemImage_AddMarker(void *pImage, UINT32 *pLength, NCS::JPC::CMarker *pMarker);
		/** 
		 * Add the JPC codestream to a memory image (excluding packets)
		 * @param		pImage			Existing memory image to append box to.
		 * @param		pLength			Current/returned length of memory image.
		 * @return      void*			Memory image with appended box, else NULL on error.
		 */
	void *GetMemImage_AddCodestream(void *pImage, UINT32 *pLength);

	// Estimate memory required for outputing the file
	// Added on 08/03/2012
	UINT64 EstimateMemoryRequired();
//#ifdef _DEBUG
public:
//#endif
		/** 
		 * How much memory in use for all JP2 files
		 * @return      UINT64		Memory in use in bytes
		 */
	static UINT64 sMemoryInUse();

#ifdef _DEBUG
private:
#endif

//	static bool OverBudget(float factor = 1.0);

		/** 
		 * Purge unused memory at specified purgestage
		 * @param		eStage		Purge stage to free memory at
		 */
	virtual void PurgeMemory(SDK::CGlobalInfo::Purge eStage, float factor = 1.0);

		/** Compression profile on writing */
	JPC::CJPC::Profile	m_eCompressionProfile;
		/** Compression resolution levels on writing */
	UINT8				m_nCompressionLevels;
		/** Compression quality layers on writing */
	UINT16				m_nCompressionLayers;
		/** Compression precinct width on writing */
	UINT32				m_nCompressionPrecinctWidth;
		/** Compression precinct height on writing */
	UINT32				m_nCompressionPrecinctHeight;
		/** Compression tile width on writing */
	UINT32				m_nCompressionTileWidth;
		/** Compression tile height on writing */
	UINT32				m_nCompressionTileHeight;
		/** Compression output SOP on writing */
	bool				m_bCompressionIncludeSOP;
		/** Compression output EPH on writing */
	bool				m_bCompressionIncludeEPH;
		/** Compression output JPC only on writing (no JP2 wrapper output) */
	bool				m_bCodestreamOnly;
		/** Compression progression order on writing (LRCP, RLCP, RPCL only) */
	NCS::JPC::CProgressionOrderType::Type	m_eCompressionOrder;
		/** # of layers to decompress on reading - FIXME unimplemented */
	UINT16				m_nDecompressionLayers;

	/** GeoData usage priority */
	static UINT32		sm_nGeodataUsage;
};
}
}

#ifndef NCS_NO_COMPAT_NAMES
typedef NCS::JP2::CFile CNCSJP2File;
#endif

#endif // !NCSJP2FILE_H
