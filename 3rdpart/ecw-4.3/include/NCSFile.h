/********************************************************
** Copyright (c) 2010, ERDAS, Inc. [http://www.erdas.com/]
** This document contains proprietary source code of
** ERDAS, Inc.
**
** This software is covered by US patent #6,442,298,
** #6,102,897 and #6,633,688.  Rights to use these patents 
** is included in the license agreements.
**
** FILE:     NCSFile.h 
** CREATED:  14/03/2003 3:27:34 PM
** AUTHOR:   Simon Cope
** PURPOSE:  CFile class header
** EDITS:    [xx] ddMmmyy NAME COMMENTS
**			 [01] 07Sep04 tfl  Added support for configuring georeferencing use
**			 [02] 11Nov04 tfl  Added rotation member to ensure rotation data persists
**			 [03] 19Jan06 tfl  Changed tiled views vector to a single view-strip member
 *******************************************************/

#ifndef NCSFILE_H
#define NCSFILE_H

#ifndef NCSVIEW_H
#include "NCSEcw/API/View.h"
#endif // NCSVIEW_H

#ifndef NCS_NO_COMPAT_NAMES
typedef NCS::CView CNCSFile;
#endif

#include "NCSJP2FileView.h"

#endif // !NCSFILE_H
