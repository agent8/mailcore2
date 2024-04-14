#ifndef __TIDY_H__
#define __TIDY_H__

/** @file tidy.h - Defines HTML Tidy API implemented by tidy library.

  Public interface is const-correct and doesn't explicitly depend
  on any globals.  Thus, thread-safety may be introduced w/out
  changing the interface.

  Looking ahead to a C++ wrapper, C functions always pass 
  this-equivalent as 1st arg.


  Copyright (c) 1998-2008 World Wide Web Consortium
  (Massachusetts Institute of Technology, European Research 
  Consortium for Informatics and Mathematics, Keio University).
  All Rights Reserved.

  Contributing Author(s):

     Dave Raggett <dsr@w3.org>

  The contributing author(s) would like to thank all those who
  helped with testing, bug fixes and suggestions for improvements. 
  This wouldn't have been possible without your help.

  COPYRIGHT NOTICE:
 
  This software and documentation is provided "as is," and
  the copyright holders and contributing author(s) make no
  representations or warranties, express or implied, including
  but not limited to, warranties of merchantability or fitness
  for any particular purpose or that the use of the software or
  documentation will not infringe any third party patents,
  copyrights, trademarks or other rights. 

  The copyright holders and contributing author(s) will not be held
  liable for any direct, indirect, special or consequential damages
  arising out of any use of the software or documentation, even if
  advised of the possibility of such damage.

  Permission is hereby granted to use, copy, modify, and distribute
  this source code, or portions hereof, documentation and executables,
  for any purpose, without fee, subject to the following restrictions:

  1. The origin of this source code must not be misrepresented.
  2. Altered versions must be plainly marked as such and must
     not be misrepresented as being the original source.
  3. This Copyright notice may not be removed or altered from any
     source or altered source distribution.
 
  The copyright holders and contributing author(s) specifically
  permit, without fee, and encourage the use of this source code
  as a component for supporting the Hypertext Markup Language in
  commercial products. If you use this source code in a product,
  acknowledgment is not required but would be appreciated.


  Created 2001-05-20 by Charles Reitzel
  Updated 2002-07-01 by Charles Reitzel - 1st Implementation

*/

#include "platform.h"
#include "tidyenum.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TIDY_RENAME_APPEND(str1,str2) str1##str2
#define TIDY_RENAME(str) TIDY_RENAME_APPEND(mc2,str)

#define tidySetFreeCall TIDY_RENAME(tidySetFreeCall)
#define tidySetMallocCall TIDY_RENAME(tidySetMallocCall)
#define tidySetPanicCall TIDY_RENAME(tidySetPanicCall)
#define tidySetReallocCall TIDY_RENAME(tidySetReallocCall)
#define tidyAttrIsABBR TIDY_RENAME(tidyAttrIsABBR)
#define tidyAttrIsALINK TIDY_RENAME(tidyAttrIsALINK)
#define tidyAttrIsALT TIDY_RENAME(tidyAttrIsALT)
#define tidyAttrIsBGCOLOR TIDY_RENAME(tidyAttrIsBGCOLOR)
#define tidyAttrIsCHECKED TIDY_RENAME(tidyAttrIsCHECKED)
#define tidyAttrIsCOLSPAN TIDY_RENAME(tidyAttrIsCOLSPAN)
#define tidyAttrIsCONTENT TIDY_RENAME(tidyAttrIsCONTENT)
#define tidyAttrIsDATAFLD TIDY_RENAME(tidyAttrIsDATAFLD)
#define tidyAttrIsEvent TIDY_RENAME(tidyAttrIsEvent)
#define tidyAttrIsFOR TIDY_RENAME(tidyAttrIsFOR)
#define tidyAttrIsHEIGHT TIDY_RENAME(tidyAttrIsHEIGHT)
#define tidyAttrIsHREF TIDY_RENAME(tidyAttrIsHREF)
#define tidyAttrIsHTTP_EQUIV TIDY_RENAME(tidyAttrIsHTTP_EQUIV)
#define tidyAttrIsID TIDY_RENAME(tidyAttrIsID)
#define tidyAttrIsISMAP TIDY_RENAME(tidyAttrIsISMAP)
#define tidyAttrIsLANG TIDY_RENAME(tidyAttrIsLANG)
#define tidyAttrIsLANGUAGE TIDY_RENAME(tidyAttrIsLANGUAGE)
#define tidyAttrIsLINK TIDY_RENAME(tidyAttrIsLINK)
#define tidyAttrIsLONGDESC TIDY_RENAME(tidyAttrIsLONGDESC)
#define tidyAttrIsNAME TIDY_RENAME(tidyAttrIsNAME)
#define tidyAttrIsOnBLUR TIDY_RENAME(tidyAttrIsOnBLUR)
#define tidyAttrIsOnCLICK TIDY_RENAME(tidyAttrIsOnCLICK)
#define tidyAttrIsOnFOCUS TIDY_RENAME(tidyAttrIsOnFOCUS)
#define tidyAttrIsOnKEYDOWN TIDY_RENAME(tidyAttrIsOnKEYDOWN)
#define tidyAttrIsOnKEYPRESS TIDY_RENAME(tidyAttrIsOnKEYPRESS)
#define tidyAttrIsOnKEYUP TIDY_RENAME(tidyAttrIsOnKEYUP)
#define tidyAttrIsOnMOUSEDOWN TIDY_RENAME(tidyAttrIsOnMOUSEDOWN)
#define tidyAttrIsOnMOUSEMOVE TIDY_RENAME(tidyAttrIsOnMOUSEMOVE)
#define tidyAttrIsOnMOUSEOUT TIDY_RENAME(tidyAttrIsOnMOUSEOUT)
#define tidyAttrIsOnMOUSEOVER TIDY_RENAME(tidyAttrIsOnMOUSEOVER)
#define tidyAttrIsOnMOUSEUP TIDY_RENAME(tidyAttrIsOnMOUSEUP)
#define tidyAttrIsREL TIDY_RENAME(tidyAttrIsREL)
#define tidyAttrIsROWSPAN TIDY_RENAME(tidyAttrIsROWSPAN)
#define tidyAttrIsSELECTED TIDY_RENAME(tidyAttrIsSELECTED)
#define tidyAttrIsSRC TIDY_RENAME(tidyAttrIsSRC)
#define tidyAttrIsSTYLE TIDY_RENAME(tidyAttrIsSTYLE)
#define tidyAttrIsSUMMARY TIDY_RENAME(tidyAttrIsSUMMARY)
#define tidyAttrIsTARGET TIDY_RENAME(tidyAttrIsTARGET)
#define tidyAttrIsTEXT TIDY_RENAME(tidyAttrIsTEXT)
#define tidyAttrIsTITLE TIDY_RENAME(tidyAttrIsTITLE)
#define tidyAttrIsTYPE TIDY_RENAME(tidyAttrIsTYPE)
#define tidyAttrIsUSEMAP TIDY_RENAME(tidyAttrIsUSEMAP)
#define tidyAttrIsVALUE TIDY_RENAME(tidyAttrIsVALUE)
#define tidyAttrIsVLINK TIDY_RENAME(tidyAttrIsVLINK)
#define tidyAttrIsWIDTH TIDY_RENAME(tidyAttrIsWIDTH)
#define tidyAttrIsXMLNS TIDY_RENAME(tidyAttrIsXMLNS)
#define tidyAttrGetABBR TIDY_RENAME(tidyAttrGetABBR)
#define tidyAttrGetALINK TIDY_RENAME(tidyAttrGetALINK)
#define tidyAttrGetALT TIDY_RENAME(tidyAttrGetALT)
#define tidyAttrGetBGCOLOR TIDY_RENAME(tidyAttrGetBGCOLOR)
#define tidyAttrGetById TIDY_RENAME(tidyAttrGetById)
#define tidyAttrGetCHECKED TIDY_RENAME(tidyAttrGetCHECKED)
#define tidyAttrGetCOLSPAN TIDY_RENAME(tidyAttrGetCOLSPAN)
#define tidyAttrGetCONTENT TIDY_RENAME(tidyAttrGetCONTENT)
#define tidyAttrGetDATAFLD TIDY_RENAME(tidyAttrGetDATAFLD)
#define tidyAttrGetFOR TIDY_RENAME(tidyAttrGetFOR)
#define tidyAttrGetHEIGHT TIDY_RENAME(tidyAttrGetHEIGHT)
#define tidyAttrGetHREF TIDY_RENAME(tidyAttrGetHREF)
#define tidyAttrGetHTTP_EQUIV TIDY_RENAME(tidyAttrGetHTTP_EQUIV)
#define tidyAttrGetID TIDY_RENAME(tidyAttrGetID)
#define tidyAttrGetISMAP TIDY_RENAME(tidyAttrGetISMAP)
#define tidyAttrGetLANG TIDY_RENAME(tidyAttrGetLANG)
#define tidyAttrGetLANGUAGE TIDY_RENAME(tidyAttrGetLANGUAGE)
#define tidyAttrGetLINK TIDY_RENAME(tidyAttrGetLINK)
#define tidyAttrGetLONGDESC TIDY_RENAME(tidyAttrGetLONGDESC)
#define tidyAttrGetNAME TIDY_RENAME(tidyAttrGetNAME)
#define tidyAttrGetOnBLUR TIDY_RENAME(tidyAttrGetOnBLUR)
#define tidyAttrGetOnCLICK TIDY_RENAME(tidyAttrGetOnCLICK)
#define tidyAttrGetOnFOCUS TIDY_RENAME(tidyAttrGetOnFOCUS)
#define tidyAttrGetOnKEYDOWN TIDY_RENAME(tidyAttrGetOnKEYDOWN)
#define tidyAttrGetOnKEYPRESS TIDY_RENAME(tidyAttrGetOnKEYPRESS)
#define tidyAttrGetOnKEYUP TIDY_RENAME(tidyAttrGetOnKEYUP)
#define tidyAttrGetOnMOUSEDOWN TIDY_RENAME(tidyAttrGetOnMOUSEDOWN)
#define tidyAttrGetOnMOUSEMOVE TIDY_RENAME(tidyAttrGetOnMOUSEMOVE)
#define tidyAttrGetOnMOUSEOUT TIDY_RENAME(tidyAttrGetOnMOUSEOUT)
#define tidyAttrGetOnMOUSEOVER TIDY_RENAME(tidyAttrGetOnMOUSEOVER)
#define tidyAttrGetOnMOUSEUP TIDY_RENAME(tidyAttrGetOnMOUSEUP)
#define tidyAttrGetREL TIDY_RENAME(tidyAttrGetREL)
#define tidyAttrGetROWSPAN TIDY_RENAME(tidyAttrGetROWSPAN)
#define tidyAttrGetSELECTED TIDY_RENAME(tidyAttrGetSELECTED)
#define tidyAttrGetSRC TIDY_RENAME(tidyAttrGetSRC)
#define tidyAttrGetSTYLE TIDY_RENAME(tidyAttrGetSTYLE)
#define tidyAttrGetSUMMARY TIDY_RENAME(tidyAttrGetSUMMARY)
#define tidyAttrGetTARGET TIDY_RENAME(tidyAttrGetTARGET)
#define tidyAttrGetTEXT TIDY_RENAME(tidyAttrGetTEXT)
#define tidyAttrGetTITLE TIDY_RENAME(tidyAttrGetTITLE)
#define tidyAttrGetTYPE TIDY_RENAME(tidyAttrGetTYPE)
#define tidyAttrGetUSEMAP TIDY_RENAME(tidyAttrGetUSEMAP)
#define tidyAttrGetVALUE TIDY_RENAME(tidyAttrGetVALUE)
#define tidyAttrGetVLINK TIDY_RENAME(tidyAttrGetVLINK)
#define tidyAttrGetWIDTH TIDY_RENAME(tidyAttrGetWIDTH)
#define tidyAttrGetXMLNS TIDY_RENAME(tidyAttrGetXMLNS)
#define tidyBufAlloc TIDY_RENAME(tidyBufAlloc)
#define tidyBufAllocWithAllocator TIDY_RENAME(tidyBufAllocWithAllocator)
#define tidyBufAppend TIDY_RENAME(tidyBufAppend)
#define tidyBufAttach TIDY_RENAME(tidyBufAttach)
#define tidyBufCheckAlloc TIDY_RENAME(tidyBufCheckAlloc)
#define tidyBufClear TIDY_RENAME(tidyBufClear)
#define tidyBufDetach TIDY_RENAME(tidyBufDetach)
#define tidyBufEndOfInput TIDY_RENAME(tidyBufEndOfInput)
#define tidyBufFree TIDY_RENAME(tidyBufFree)
#define tidyBufGetByte TIDY_RENAME(tidyBufGetByte)
#define tidyBufInit TIDY_RENAME(tidyBufInit)
#define tidyBufInitWithAllocator TIDY_RENAME(tidyBufInitWithAllocator)
#define tidyBufPopByte TIDY_RENAME(tidyBufPopByte)
#define tidyBufPutByte TIDY_RENAME(tidyBufPutByte)
#define tidyBufUngetByte TIDY_RENAME(tidyBufUngetByte)
#define tidyInitInputBuffer TIDY_RENAME(tidyInitInputBuffer)
#define tidyInitOutputBuffer TIDY_RENAME(tidyInitOutputBuffer)
#define tidyFileExists TIDY_RENAME(tidyFileExists)
#define tidyGetByte TIDY_RENAME(tidyGetByte)
#define tidyInitSink TIDY_RENAME(tidyInitSink)
#define tidyInitSource TIDY_RENAME(tidyInitSource)
#define tidyIsEOF TIDY_RENAME(tidyIsEOF)
#define tidyPutByte TIDY_RENAME(tidyPutByte)
#define tidyUngetByte TIDY_RENAME(tidyUngetByte)
#define tidyNodeCMIsBlock TIDY_RENAME(tidyNodeCMIsBlock)
#define tidyNodeCMIsEmpty TIDY_RENAME(tidyNodeCMIsEmpty)
#define tidyNodeCMIsInline TIDY_RENAME(tidyNodeCMIsInline)
#define tidyNodeIsA TIDY_RENAME(tidyNodeIsA)
#define tidyNodeIsADDRESS TIDY_RENAME(tidyNodeIsADDRESS)
#define tidyNodeIsAPPLET TIDY_RENAME(tidyNodeIsAPPLET)
#define tidyNodeIsAREA TIDY_RENAME(tidyNodeIsAREA)
#define tidyNodeIsB TIDY_RENAME(tidyNodeIsB)
#define tidyNodeIsBASE TIDY_RENAME(tidyNodeIsBASE)
#define tidyNodeIsBASEFONT TIDY_RENAME(tidyNodeIsBASEFONT)
#define tidyNodeIsBIG TIDY_RENAME(tidyNodeIsBIG)
#define tidyNodeIsBLINK TIDY_RENAME(tidyNodeIsBLINK)
#define tidyNodeIsBLOCKQUOTE TIDY_RENAME(tidyNodeIsBLOCKQUOTE)
#define tidyNodeIsBODY TIDY_RENAME(tidyNodeIsBODY)
#define tidyNodeIsBR TIDY_RENAME(tidyNodeIsBR)
#define tidyNodeIsCAPTION TIDY_RENAME(tidyNodeIsCAPTION)
#define tidyNodeIsCENTER TIDY_RENAME(tidyNodeIsCENTER)
#define tidyNodeIsCOL TIDY_RENAME(tidyNodeIsCOL)
#define tidyNodeIsCOLGROUP TIDY_RENAME(tidyNodeIsCOLGROUP)
#define tidyNodeIsDD TIDY_RENAME(tidyNodeIsDD)
#define tidyNodeIsDIR TIDY_RENAME(tidyNodeIsDIR)
#define tidyNodeIsDIV TIDY_RENAME(tidyNodeIsDIV)
#define tidyNodeIsDL TIDY_RENAME(tidyNodeIsDL)
#define tidyNodeIsDT TIDY_RENAME(tidyNodeIsDT)
#define tidyNodeIsEM TIDY_RENAME(tidyNodeIsEM)
#define tidyNodeIsEMBED TIDY_RENAME(tidyNodeIsEMBED)
#define tidyNodeIsFONT TIDY_RENAME(tidyNodeIsFONT)
#define tidyNodeIsFORM TIDY_RENAME(tidyNodeIsFORM)
#define tidyNodeIsFRAME TIDY_RENAME(tidyNodeIsFRAME)
#define tidyNodeIsFRAMESET TIDY_RENAME(tidyNodeIsFRAMESET)
#define tidyNodeIsH1 TIDY_RENAME(tidyNodeIsH1)
#define tidyNodeIsH2 TIDY_RENAME(tidyNodeIsH2)
#define tidyNodeIsH3 TIDY_RENAME(tidyNodeIsH3)
#define tidyNodeIsH4 TIDY_RENAME(tidyNodeIsH4)
#define tidyNodeIsH5 TIDY_RENAME(tidyNodeIsH5)
#define tidyNodeIsH6 TIDY_RENAME(tidyNodeIsH6)
#define tidyNodeIsHEAD TIDY_RENAME(tidyNodeIsHEAD)
#define tidyNodeIsHR TIDY_RENAME(tidyNodeIsHR)
#define tidyNodeIsHTML TIDY_RENAME(tidyNodeIsHTML)
#define tidyNodeIsHeader TIDY_RENAME(tidyNodeIsHeader)
#define tidyNodeIsI TIDY_RENAME(tidyNodeIsI)
#define tidyNodeIsIFRAME TIDY_RENAME(tidyNodeIsIFRAME)
#define tidyNodeIsIMG TIDY_RENAME(tidyNodeIsIMG)
#define tidyNodeIsINPUT TIDY_RENAME(tidyNodeIsINPUT)
#define tidyNodeIsISINDEX TIDY_RENAME(tidyNodeIsISINDEX)
#define tidyNodeIsLABEL TIDY_RENAME(tidyNodeIsLABEL)
#define tidyNodeIsLAYER TIDY_RENAME(tidyNodeIsLAYER)
#define tidyNodeIsLI TIDY_RENAME(tidyNodeIsLI)
#define tidyNodeIsLINK TIDY_RENAME(tidyNodeIsLINK)
#define tidyNodeIsLISTING TIDY_RENAME(tidyNodeIsLISTING)
#define tidyNodeIsMAP TIDY_RENAME(tidyNodeIsMAP)
#define tidyNodeIsMARQUEE TIDY_RENAME(tidyNodeIsMARQUEE)
#define tidyNodeIsMENU TIDY_RENAME(tidyNodeIsMENU)
#define tidyNodeIsMETA TIDY_RENAME(tidyNodeIsMETA)
#define tidyNodeIsNOBR TIDY_RENAME(tidyNodeIsNOBR)
#define tidyNodeIsNOFRAMES TIDY_RENAME(tidyNodeIsNOFRAMES)
#define tidyNodeIsNOSCRIPT TIDY_RENAME(tidyNodeIsNOSCRIPT)
#define tidyNodeIsOBJECT TIDY_RENAME(tidyNodeIsOBJECT)
#define tidyNodeIsOL TIDY_RENAME(tidyNodeIsOL)
#define tidyNodeIsOPTGROUP TIDY_RENAME(tidyNodeIsOPTGROUP)
#define tidyNodeIsOPTION TIDY_RENAME(tidyNodeIsOPTION)
#define tidyNodeIsP TIDY_RENAME(tidyNodeIsP)
#define tidyNodeIsPARAM TIDY_RENAME(tidyNodeIsPARAM)
#define tidyNodeIsPRE TIDY_RENAME(tidyNodeIsPRE)
#define tidyNodeIsQ TIDY_RENAME(tidyNodeIsQ)
#define tidyNodeIsS TIDY_RENAME(tidyNodeIsS)
#define tidyNodeIsSCRIPT TIDY_RENAME(tidyNodeIsSCRIPT)
#define tidyNodeIsSELECT TIDY_RENAME(tidyNodeIsSELECT)
#define tidyNodeIsSMALL TIDY_RENAME(tidyNodeIsSMALL)
#define tidyNodeIsSPACER TIDY_RENAME(tidyNodeIsSPACER)
#define tidyNodeIsSPAN TIDY_RENAME(tidyNodeIsSPAN)
#define tidyNodeIsSTRIKE TIDY_RENAME(tidyNodeIsSTRIKE)
#define tidyNodeIsSTRONG TIDY_RENAME(tidyNodeIsSTRONG)
#define tidyNodeIsSTYLE TIDY_RENAME(tidyNodeIsSTYLE)
#define tidyNodeIsTABLE TIDY_RENAME(tidyNodeIsTABLE)
#define tidyNodeIsTD TIDY_RENAME(tidyNodeIsTD)
#define tidyNodeIsTEXTAREA TIDY_RENAME(tidyNodeIsTEXTAREA)
#define tidyNodeIsTH TIDY_RENAME(tidyNodeIsTH)
#define tidyNodeIsTITLE TIDY_RENAME(tidyNodeIsTITLE)
#define tidyNodeIsTR TIDY_RENAME(tidyNodeIsTR)
#define tidyNodeIsText TIDY_RENAME(tidyNodeIsText)
#define tidyNodeIsU TIDY_RENAME(tidyNodeIsU)
#define tidyNodeIsUL TIDY_RENAME(tidyNodeIsUL)
#define tidyNodeIsWBR TIDY_RENAME(tidyNodeIsWBR)
#define tidyNodeIsXMP TIDY_RENAME(tidyNodeIsXMP)
#define tidyAccessWarningCount TIDY_RENAME(tidyAccessWarningCount)
#define tidyAttrFirst TIDY_RENAME(tidyAttrFirst)
#define tidyAttrGetId TIDY_RENAME(tidyAttrGetId)
#define tidyAttrIsProp TIDY_RENAME(tidyAttrIsProp)
#define tidyAttrName TIDY_RENAME(tidyAttrName)
#define tidyAttrNext TIDY_RENAME(tidyAttrNext)
#define tidyAttrValue TIDY_RENAME(tidyAttrValue)
#define tidyCleanAndRepair TIDY_RENAME(tidyCleanAndRepair)
#define tidyConfigErrorCount TIDY_RENAME(tidyConfigErrorCount)
#define tidyCreate TIDY_RENAME(tidyCreate)
#define tidyCreateWithAllocator TIDY_RENAME(tidyCreateWithAllocator)
#define tidyDetectedGenericXml TIDY_RENAME(tidyDetectedGenericXml)
#define tidyDetectedHtmlVersion TIDY_RENAME(tidyDetectedHtmlVersion)
#define tidyDetectedXhtml TIDY_RENAME(tidyDetectedXhtml)
#define tidyErrorCount TIDY_RENAME(tidyErrorCount)
#define tidyErrorSummary TIDY_RENAME(tidyErrorSummary)
#define tidyGeneralInfo TIDY_RENAME(tidyGeneralInfo)
#define tidyGetAppData TIDY_RENAME(tidyGetAppData)
#define tidyGetBody TIDY_RENAME(tidyGetBody)
#define tidyGetChild TIDY_RENAME(tidyGetChild)
#define tidyGetHead TIDY_RENAME(tidyGetHead)
#define tidyGetHtml TIDY_RENAME(tidyGetHtml)
#define tidyGetNext TIDY_RENAME(tidyGetNext)
#define tidyGetNextOption TIDY_RENAME(tidyGetNextOption)
#define tidyGetOption TIDY_RENAME(tidyGetOption)
#define tidyGetOptionByName TIDY_RENAME(tidyGetOptionByName)
#define tidyGetOptionList TIDY_RENAME(tidyGetOptionList)
#define tidyGetParent TIDY_RENAME(tidyGetParent)
#define tidyGetPrev TIDY_RENAME(tidyGetPrev)
#define tidyGetRoot TIDY_RENAME(tidyGetRoot)
#define tidyLoadConfig TIDY_RENAME(tidyLoadConfig)
#define tidyLoadConfigEnc TIDY_RENAME(tidyLoadConfigEnc)
#define tidyNodeColumn TIDY_RENAME(tidyNodeColumn)
#define tidyNodeGetId TIDY_RENAME(tidyNodeGetId)
#define tidyNodeGetName TIDY_RENAME(tidyNodeGetName)
#define tidyNodeGetText TIDY_RENAME(tidyNodeGetText)
#define tidyNodeGetType TIDY_RENAME(tidyNodeGetType)
#define tidyNodeGetValue TIDY_RENAME(tidyNodeGetValue)
#define tidyNodeHasText TIDY_RENAME(tidyNodeHasText)
#define tidyNodeIsProp TIDY_RENAME(tidyNodeIsProp)
#define tidyNodeLine TIDY_RENAME(tidyNodeLine)
#define tidyOptCopyConfig TIDY_RENAME(tidyOptCopyConfig)
#define tidyOptDiffThanDefault TIDY_RENAME(tidyOptDiffThanDefault)
#define tidyOptDiffThanSnapshot TIDY_RENAME(tidyOptDiffThanSnapshot)
#define tidyOptGetBool TIDY_RENAME(tidyOptGetBool)
#define tidyOptGetCategory TIDY_RENAME(tidyOptGetCategory)
#define tidyOptGetCurrPick TIDY_RENAME(tidyOptGetCurrPick)
#define tidyOptGetDeclTagList TIDY_RENAME(tidyOptGetDeclTagList)
#define tidyOptGetDefault TIDY_RENAME(tidyOptGetDefault)
#define tidyOptGetDefaultBool TIDY_RENAME(tidyOptGetDefaultBool)
#define tidyOptGetDefaultInt TIDY_RENAME(tidyOptGetDefaultInt)
#define tidyOptGetDoc TIDY_RENAME(tidyOptGetDoc)
#define tidyOptGetDocLinksList TIDY_RENAME(tidyOptGetDocLinksList)
#define tidyOptGetEncName TIDY_RENAME(tidyOptGetEncName)
#define tidyOptGetId TIDY_RENAME(tidyOptGetId)
#define tidyOptGetIdForName TIDY_RENAME(tidyOptGetIdForName)
#define tidyOptGetInt TIDY_RENAME(tidyOptGetInt)
#define tidyOptGetName TIDY_RENAME(tidyOptGetName)
#define tidyOptGetNextDeclTag TIDY_RENAME(tidyOptGetNextDeclTag)
#define tidyOptGetNextDocLinks TIDY_RENAME(tidyOptGetNextDocLinks)
#define tidyOptGetNextPick TIDY_RENAME(tidyOptGetNextPick)
#define tidyOptGetPickList TIDY_RENAME(tidyOptGetPickList)
#define tidyOptGetType TIDY_RENAME(tidyOptGetType)
#define tidyOptGetValue TIDY_RENAME(tidyOptGetValue)
#define tidyOptIsReadOnly TIDY_RENAME(tidyOptIsReadOnly)
#define tidyOptParseValue TIDY_RENAME(tidyOptParseValue)
#define tidyOptResetAllToDefault TIDY_RENAME(tidyOptResetAllToDefault)
#define tidyOptResetToDefault TIDY_RENAME(tidyOptResetToDefault)
#define tidyOptResetToSnapshot TIDY_RENAME(tidyOptResetToSnapshot)
#define tidyOptSaveFile TIDY_RENAME(tidyOptSaveFile)
#define tidyOptSaveSink TIDY_RENAME(tidyOptSaveSink)
#define tidyOptSetBool TIDY_RENAME(tidyOptSetBool)
#define tidyOptSetInt TIDY_RENAME(tidyOptSetInt)
#define tidyOptSetValue TIDY_RENAME(tidyOptSetValue)
#define tidyOptSnapshot TIDY_RENAME(tidyOptSnapshot)
#define tidyParseBuffer TIDY_RENAME(tidyParseBuffer)
#define tidyParseFile TIDY_RENAME(tidyParseFile)
#define tidyParseSource TIDY_RENAME(tidyParseSource)
#define tidyParseStdin TIDY_RENAME(tidyParseStdin)
#define tidyParseString TIDY_RENAME(tidyParseString)
#define tidyRelease TIDY_RENAME(tidyRelease)
#define tidyReleaseDate TIDY_RENAME(tidyReleaseDate)
#define tidyRunDiagnostics TIDY_RENAME(tidyRunDiagnostics)
#define tidySaveBuffer TIDY_RENAME(tidySaveBuffer)
#define tidySaveFile TIDY_RENAME(tidySaveFile)
#define tidySaveSink TIDY_RENAME(tidySaveSink)
#define tidySaveStdout TIDY_RENAME(tidySaveStdout)
#define tidySaveString TIDY_RENAME(tidySaveString)
#define tidySetAppData TIDY_RENAME(tidySetAppData)
#define tidySetCharEncoding TIDY_RENAME(tidySetCharEncoding)
#define tidySetErrorBuffer TIDY_RENAME(tidySetErrorBuffer)
#define tidySetErrorFile TIDY_RENAME(tidySetErrorFile)
#define tidySetErrorSink TIDY_RENAME(tidySetErrorSink)
#define tidySetInCharEncoding TIDY_RENAME(tidySetInCharEncoding)
#define tidySetOptionCallback TIDY_RENAME(tidySetOptionCallback)
#define tidySetOutCharEncoding TIDY_RENAME(tidySetOutCharEncoding)
#define tidySetReportFilter TIDY_RENAME(tidySetReportFilter)
#define tidyStatus TIDY_RENAME(tidyStatus)
#define tidyWarningCount TIDY_RENAME(tidyWarningCount)

#if defined(ANDROID) || defined(__ANDROID__)
typedef unsigned long ulong;
#endif

/** @defgroup Opaque Opaque Types
**
** Cast to implementation types within lib.
** Reduces inter-dependencies/conflicts w/ application code.
** @{
*/

/** @struct TidyDoc
**  Opaque document datatype
*/
opaque_type( TidyDoc );

/** @struct TidyOption
**  Opaque option datatype
*/
opaque_type( TidyOption );

/** @struct TidyNode
**  Opaque node datatype
*/
opaque_type( TidyNode );

/** @struct TidyAttr
**  Opaque attribute datatype
*/
opaque_type( TidyAttr );

/** @} end Opaque group */

TIDY_STRUCT struct _TidyBuffer;
typedef struct _TidyBuffer TidyBuffer;


/** @defgroup Memory  Memory Allocation
**
** Tidy uses a user provided allocator for all
** memory allocations.  If this allocator is
** not provided, then a default allocator is
** used which simply wraps standard C malloc/free
** calls.  These wrappers call the panic function
** upon any failure.  The default panic function
** prints an out of memory message to stderr, and
** calls exit(2).
**
** For applications in which it is unacceptable to
** abort in the case of memory allocation, then the
** panic function can be replaced with one which
** longjmps() out of the tidy code.  For this to
** clean up completely, you should be careful not
** to use any tidy methods that open files as these
** will not be closed before panic() is called.
**
** TODO: associate file handles with tidyDoc and
** ensure that tidyDocRelease() can close them all.
**
** Calling the withAllocator() family (
** tidyCreateWithAllocator, tidyBufInitWithAllocator,
** tidyBufAllocWithAllocator) allow settings custom
** allocators).
**
** All parts of the document use the same allocator.
** Calls that require a user provided buffer can
** optionally use a different allocator.
**
** For reference in designing a plug-in allocator,
** most allocations made by tidy are less than 100
** bytes, corresponding to attribute names/values, etc.
**
** There is also an additional class of much larger
** allocations which are where most of the data from
** the lexer is stored.  (It is not currently possible
** to use a separate allocator for the lexer, this
** would be a useful extension).
**
** In general, approximately 1/3rd of the memory
** used by tidy is freed during the parse, so if
** memory usage is an issue then an allocator that 
** can reuse this memory is a good idea.
**
** @{
*/

/** Prototype for the allocator's function table */
struct _TidyAllocatorVtbl;
/** The allocators function table */
typedef struct _TidyAllocatorVtbl TidyAllocatorVtbl;

/** Prototype for the allocator */
struct _TidyAllocator;
/** The allocator **/
typedef struct _TidyAllocator TidyAllocator;

/** An allocator's function table.  All functions here must
    be provided.
 */
struct _TidyAllocatorVtbl {
    /** Called to allocate a block of nBytes of memory */
    void* (TIDY_CALL *alloc)( TidyAllocator *self, size_t nBytes );
    /** Called to resize (grow, in general) a block of memory.
        Must support being called with NULL.
    */
    void* (TIDY_CALL *realloc)( TidyAllocator *self, void *block, size_t nBytes );
    /** Called to free a previously allocated block of memory */
    void (TIDY_CALL *free)( TidyAllocator *self, void *block);
    /** Called when a panic condition is detected.  Must support
        block == NULL.  This function is not called if either alloc 
        or realloc fails; it is up to the allocator to do this.
        Currently this function can only be called if an error is
        detected in the tree integrity via the internal function
        CheckNodeIntegrity().  This is a situation that can
        only arise in the case of a programming error in tidylib.
        You can turn off node integrity checking by defining
        the constant NO_NODE_INTEGRITY_CHECK during the build.
    **/
    void (TIDY_CALL *panic)( TidyAllocator *self, ctmbstr msg );
};

/** An allocator.  To create your own allocator, do something like
    the following:
    
    typedef struct _MyAllocator {
       TidyAllocator base;
       ...other custom allocator state...
    } MyAllocator;
    
    void* MyAllocator_alloc(TidyAllocator *base, void *block, size_t nBytes)
    {
        MyAllocator *self = (MyAllocator*)base;
        ...
    }
    (etc)

    static const TidyAllocatorVtbl MyAllocatorVtbl = {
        MyAllocator_alloc,
        MyAllocator_realloc,
        MyAllocator_free,
        MyAllocator_panic
    };

    myAllocator allocator;
    TidyDoc doc;

    allocator.base.vtbl = &amp;MyAllocatorVtbl;
    ...initialise allocator specific state...
    doc = tidyCreateWithAllocator(&allocator);
    ...

    Although this looks slightly long winded, the advantage is that to create
    a custom allocator you simply need to set the vtbl pointer correctly.
    The vtbl itself can reside in static/global data, and hence does not
    need to be initialised each time an allocator is created, and furthermore
    the memory is shared amongst all created allocators.
*/
struct _TidyAllocator {
    const TidyAllocatorVtbl *vtbl;
};

/** Callback for "malloc" replacement */
typedef void* (TIDY_CALL *TidyMalloc)( size_t len );
/** Callback for "realloc" replacement */
typedef void* (TIDY_CALL *TidyRealloc)( void* buf, size_t len );
/** Callback for "free" replacement */
typedef void  (TIDY_CALL *TidyFree)( void* buf );
/** Callback for "out of memory" panic state */
typedef void  (TIDY_CALL *TidyPanic)( ctmbstr mssg );


/** Give Tidy a malloc() replacement */
TIDY_EXPORT Bool TIDY_CALL tidySetMallocCall( TidyMalloc fmalloc );
/** Give Tidy a realloc() replacement */
TIDY_EXPORT Bool TIDY_CALL tidySetReallocCall( TidyRealloc frealloc );
/** Give Tidy a free() replacement */
TIDY_EXPORT Bool TIDY_CALL tidySetFreeCall( TidyFree ffree );
/** Give Tidy an "out of memory" handler */
TIDY_EXPORT Bool TIDY_CALL tidySetPanicCall( TidyPanic fpanic );

/** @} end Memory group */

/** @defgroup Basic Basic Operations
**
** Tidy public interface
**
** Several functions return an integer document status:
**
** <pre>
** 0    -> SUCCESS
** >0   -> 1 == TIDY WARNING, 2 == TIDY ERROR
** <0   -> SEVERE ERROR
** </pre>
** 
The following is a short example program.

<pre>
#include &lt;tidy.h&gt;
#include &lt;buffio.h&gt;
#include &lt;stdio.h&gt;
#include &lt;errno.h&gt;


int main(int argc, char **argv )
{
  const char* input = "&lt;title&gt;Foo&lt;/title&gt;&lt;p&gt;Foo!";
  TidyBuffer output;
  TidyBuffer errbuf;
  int rc = -1;
  Bool ok;

  TidyDoc tdoc = tidyCreate();                     // Initialize "document"
  tidyBufInit( &amp;output );
  tidyBufInit( &amp;errbuf );
  printf( "Tidying:\t\%s\\n", input );

  ok = tidyOptSetBool( tdoc, TidyXhtmlOut, yes );  // Convert to XHTML
  if ( ok )
    rc = tidySetErrorBuffer( tdoc, &amp;errbuf );      // Capture diagnostics
  if ( rc &gt;= 0 )
    rc = tidyParseString( tdoc, input );           // Parse the input
  if ( rc &gt;= 0 )
    rc = tidyCleanAndRepair( tdoc );               // Tidy it up!
  if ( rc &gt;= 0 )
    rc = tidyRunDiagnostics( tdoc );               // Kvetch
  if ( rc &gt; 1 )                                    // If error, force output.
    rc = ( tidyOptSetBool(tdoc, TidyForceOutput, yes) ? rc : -1 );
  if ( rc &gt;= 0 )
    rc = tidySaveBuffer( tdoc, &amp;output );          // Pretty Print

  if ( rc &gt;= 0 )
  {
    if ( rc &gt; 0 )
      printf( "\\nDiagnostics:\\n\\n\%s", errbuf.bp );
    printf( "\\nAnd here is the result:\\n\\n\%s", output.bp );
  }
  else
    printf( "A severe error (\%d) occurred.\\n", rc );

  tidyBufFree( &amp;output );
  tidyBufFree( &amp;errbuf );
  tidyRelease( tdoc );
  return rc;
}
</pre>
** @{
*/

TIDY_EXPORT TidyDoc TIDY_CALL     tidyCreate(void);
TIDY_EXPORT TidyDoc TIDY_CALL     tidyCreateWithAllocator( TidyAllocator *allocator );
TIDY_EXPORT void TIDY_CALL        tidyRelease( TidyDoc tdoc );

/** Let application store a chunk of data w/ each Tidy instance.
**  Useful for callbacks.
*/
TIDY_EXPORT void TIDY_CALL        tidySetAppData( TidyDoc tdoc, void* appData );

/** Get application data set previously */
TIDY_EXPORT void* TIDY_CALL       tidyGetAppData( TidyDoc tdoc );

/** Get release date (version) for current library */
TIDY_EXPORT ctmbstr TIDY_CALL     tidyReleaseDate(void);

/* Diagnostics and Repair
*/

/** Get status of current document. */
TIDY_EXPORT int TIDY_CALL         tidyStatus( TidyDoc tdoc );

/** Detected HTML version: 0, 2, 3 or 4 */
TIDY_EXPORT int TIDY_CALL         tidyDetectedHtmlVersion( TidyDoc tdoc );

/** Input is XHTML? */
TIDY_EXPORT Bool TIDY_CALL        tidyDetectedXhtml( TidyDoc tdoc );

/** Input is generic XML (not HTML or XHTML)? */
TIDY_EXPORT Bool TIDY_CALL        tidyDetectedGenericXml( TidyDoc tdoc );

/** Number of Tidy errors encountered.  If > 0, output is suppressed
**  unless TidyForceOutput is set.
*/
TIDY_EXPORT uint TIDY_CALL        tidyErrorCount( TidyDoc tdoc );

/** Number of Tidy warnings encountered. */
TIDY_EXPORT uint TIDY_CALL        tidyWarningCount( TidyDoc tdoc );

/** Number of Tidy accessibility warnings encountered. */
TIDY_EXPORT uint TIDY_CALL        tidyAccessWarningCount( TidyDoc tdoc );

/** Number of Tidy configuration errors encountered. */
TIDY_EXPORT uint TIDY_CALL        tidyConfigErrorCount( TidyDoc tdoc );

/* Get/Set configuration options
*/
/** Load an ASCII Tidy configuration file */
TIDY_EXPORT int TIDY_CALL         tidyLoadConfig( TidyDoc tdoc, ctmbstr configFile );

/** Load a Tidy configuration file with the specified character encoding */
TIDY_EXPORT int TIDY_CALL         tidyLoadConfigEnc( TidyDoc tdoc, ctmbstr configFile,
                                                     ctmbstr charenc );

TIDY_EXPORT Bool TIDY_CALL        tidyFileExists( TidyDoc tdoc, ctmbstr filename );


/** Set the input/output character encoding for parsing markup.
**  Values include: ascii, latin1, raw, utf8, iso2022, mac,
**  win1252, utf16le, utf16be, utf16, big5 and shiftjis.  Case in-sensitive.
*/
TIDY_EXPORT int TIDY_CALL         tidySetCharEncoding( TidyDoc tdoc, ctmbstr encnam );

/** Set the input encoding for parsing markup.
** As for tidySetCharEncoding but only affects the input encoding
**/
TIDY_EXPORT int TIDY_CALL         tidySetInCharEncoding( TidyDoc tdoc, ctmbstr encnam );

/** Set the output encoding.
**/
TIDY_EXPORT int TIDY_CALL         tidySetOutCharEncoding( TidyDoc tdoc, ctmbstr encnam );

/** @} end Basic group */


/** @defgroup Configuration Configuration Options
**
** Functions for getting and setting Tidy configuration options.
** @{
*/

/** Applications using TidyLib may want to augment command-line and
**  configuration file options.  Setting this callback allows an application 
**  developer to examine command-line and configuration file options after
**  TidyLib has examined them and failed to recognize them.
**/

typedef Bool (TIDY_CALL *TidyOptCallback)( ctmbstr option, ctmbstr value );

TIDY_EXPORT Bool TIDY_CALL          tidySetOptionCallback( TidyDoc tdoc, TidyOptCallback pOptCallback );

/** Get option ID by name */
TIDY_EXPORT TidyOptionId TIDY_CALL  tidyOptGetIdForName( ctmbstr optnam );

/** Get iterator for list of option */
/** 
Example:
<pre>
TidyIterator itOpt = tidyGetOptionList( tdoc );
while ( itOpt )
{
  TidyOption opt = tidyGetNextOption( tdoc, &itOpt );
  .. get/set option values ..
}
</pre>
*/

TIDY_EXPORT TidyIterator TIDY_CALL  tidyGetOptionList( TidyDoc tdoc );
/** Get next Option */
TIDY_EXPORT TidyOption TIDY_CALL    tidyGetNextOption( TidyDoc tdoc, TidyIterator* pos );

/** Lookup option by ID */
TIDY_EXPORT TidyOption TIDY_CALL    tidyGetOption( TidyDoc tdoc, TidyOptionId optId );
/** Lookup option by name */
TIDY_EXPORT TidyOption TIDY_CALL    tidyGetOptionByName( TidyDoc tdoc, ctmbstr optnam );

/** Get ID of given Option */
TIDY_EXPORT TidyOptionId TIDY_CALL  tidyOptGetId( TidyOption opt );

/** Get name of given Option */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetName( TidyOption opt );

/** Get datatype of given Option */
TIDY_EXPORT TidyOptionType TIDY_CALL tidyOptGetType( TidyOption opt );

/** Is Option read-only? */
TIDY_EXPORT Bool TIDY_CALL          tidyOptIsReadOnly( TidyOption opt );

/** Get category of given Option */
TIDY_EXPORT TidyConfigCategory TIDY_CALL tidyOptGetCategory( TidyOption opt );

/** Get default value of given Option as a string */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetDefault( TidyOption opt );

/** Get default value of given Option as an unsigned integer */
TIDY_EXPORT ulong TIDY_CALL         tidyOptGetDefaultInt( TidyOption opt );

/** Get default value of given Option as a Boolean value */
TIDY_EXPORT Bool TIDY_CALL          tidyOptGetDefaultBool( TidyOption opt );

/** Iterate over Option "pick list" */
TIDY_EXPORT TidyIterator TIDY_CALL  tidyOptGetPickList( TidyOption opt );
/** Get next string value of Option "pick list" */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetNextPick( TidyOption opt, TidyIterator* pos );

/** Get current Option value as a string */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetValue( TidyDoc tdoc, TidyOptionId optId );
/** Set Option value as a string */
TIDY_EXPORT Bool TIDY_CALL          tidyOptSetValue( TidyDoc tdoc, TidyOptionId optId, ctmbstr val );
/** Set named Option value as a string.  Good if not sure of type. */
TIDY_EXPORT Bool TIDY_CALL          tidyOptParseValue( TidyDoc tdoc, ctmbstr optnam, ctmbstr val );

/** Get current Option value as an integer */
TIDY_EXPORT ulong TIDY_CALL         tidyOptGetInt( TidyDoc tdoc, TidyOptionId optId );
/** Set Option value as an integer */
TIDY_EXPORT Bool TIDY_CALL          tidyOptSetInt( TidyDoc tdoc, TidyOptionId optId, ulong val );

/** Get current Option value as a Boolean flag */
TIDY_EXPORT Bool TIDY_CALL          tidyOptGetBool( TidyDoc tdoc, TidyOptionId optId );
/** Set Option value as a Boolean flag */
TIDY_EXPORT Bool TIDY_CALL          tidyOptSetBool( TidyDoc tdoc, TidyOptionId optId, Bool val );

/** Reset option to default value by ID */
TIDY_EXPORT Bool TIDY_CALL          tidyOptResetToDefault( TidyDoc tdoc, TidyOptionId opt );
/** Reset all options to their default values */
TIDY_EXPORT Bool TIDY_CALL          tidyOptResetAllToDefault( TidyDoc tdoc );

/** Take a snapshot of current config settings */
TIDY_EXPORT Bool TIDY_CALL          tidyOptSnapshot( TidyDoc tdoc );
/** Reset config settings to snapshot (after document processing) */
TIDY_EXPORT Bool TIDY_CALL          tidyOptResetToSnapshot( TidyDoc tdoc );

/** Any settings different than default? */
TIDY_EXPORT Bool TIDY_CALL          tidyOptDiffThanDefault( TidyDoc tdoc );
/** Any settings different than snapshot? */
TIDY_EXPORT Bool TIDY_CALL          tidyOptDiffThanSnapshot( TidyDoc tdoc );

/** Copy current configuration settings from one document to another */
TIDY_EXPORT Bool TIDY_CALL          tidyOptCopyConfig( TidyDoc tdocTo, TidyDoc tdocFrom );

/** Get character encoding name.  Used with TidyCharEncoding,
**  TidyOutCharEncoding, TidyInCharEncoding */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetEncName( TidyDoc tdoc, TidyOptionId optId );

/** Get current pick list value for option by ID.  Useful for enum types. */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetCurrPick( TidyDoc tdoc, TidyOptionId optId);

/** Iterate over user declared tags */
TIDY_EXPORT TidyIterator TIDY_CALL  tidyOptGetDeclTagList( TidyDoc tdoc );
/** Get next declared tag of specified type: TidyInlineTags, TidyBlockTags,
**  TidyEmptyTags, TidyPreTags */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetNextDeclTag( TidyDoc tdoc, 
                                                          TidyOptionId optId,
                                                          TidyIterator* iter );
/** Get option description */
TIDY_EXPORT ctmbstr TIDY_CALL       tidyOptGetDoc( TidyDoc tdoc, TidyOption opt );

/** Iterate over a list of related options */
TIDY_EXPORT TidyIterator TIDY_CALL  tidyOptGetDocLinksList( TidyDoc tdoc,
                                                  TidyOption opt );
/** Get next related option */
TIDY_EXPORT TidyOption TIDY_CALL    tidyOptGetNextDocLinks( TidyDoc tdoc,
                                                  TidyIterator* pos );

/** @} end Configuration group */

/** @defgroup IO  I/O and Messages
**
** By default, Tidy will define, create and use 
** instances of input and output handlers for 
** standard C buffered I/O (i.e. FILE* stdin,
** FILE* stdout and FILE* stderr for content
** input, content output and diagnostic output,
** respectively.  A FILE* cfgFile input handler
** will be used for config files.  Command line
** options will just be set directly.
**
** @{
*/

/*****************
   Input Source
*****************/
/** Input Callback: get next byte of input */
typedef int  (TIDY_CALL *TidyGetByteFunc)( void* sourceData );

/** Input Callback: unget a byte of input */
typedef void (TIDY_CALL *TidyUngetByteFunc)( void* sourceData, byte bt );

/** Input Callback: is end of input? */
typedef Bool (TIDY_CALL *TidyEOFFunc)( void* sourceData );

/** End of input "character" */
#define EndOfStream (~0u)

/** TidyInputSource - Delivers raw bytes of input
*/
TIDY_STRUCT
typedef struct _TidyInputSource
{
  /* Instance data */
  void*               sourceData;  /**< Input context.  Passed to callbacks */

  /* Methods */
  TidyGetByteFunc     getByte;     /**< Pointer to "get byte" callback */
  TidyUngetByteFunc   ungetByte;   /**< Pointer to "unget" callback */
  TidyEOFFunc         eof;         /**< Pointer to "eof" callback */
} TidyInputSource;

/** Facilitates user defined source by providing
**  an entry point to marshal pointers-to-functions.
**  Needed by .NET and possibly other language bindings.
*/
TIDY_EXPORT Bool TIDY_CALL tidyInitSource( TidyInputSource*  source,
                                          void*             srcData,
                                          TidyGetByteFunc   gbFunc,
                                          TidyUngetByteFunc ugbFunc,
                                          TidyEOFFunc       endFunc );

/** Helper: get next byte from input source */
TIDY_EXPORT uint TIDY_CALL tidyGetByte( TidyInputSource* source );

/** Helper: unget byte back to input source */
TIDY_EXPORT void TIDY_CALL tidyUngetByte( TidyInputSource* source, uint byteValue );

/** Helper: check if input source at end */
TIDY_EXPORT Bool TIDY_CALL tidyIsEOF( TidyInputSource* source );


/****************
   Output Sink
****************/
/** Output callback: send a byte to output */
typedef void (TIDY_CALL *TidyPutByteFunc)( void* sinkData, byte bt );


/** TidyOutputSink - accepts raw bytes of output
*/
TIDY_STRUCT
typedef struct _TidyOutputSink
{
  /* Instance data */
  void*               sinkData;  /**< Output context.  Passed to callbacks */

  /* Methods */
  TidyPutByteFunc     putByte;   /**< Pointer to "put byte" callback */
} TidyOutputSink;

/** Facilitates user defined sinks by providing
**  an entry point to marshal pointers-to-functions.
**  Needed by .NET and possibly other language bindings.
*/
TIDY_EXPORT Bool TIDY_CALL tidyInitSink( TidyOutputSink* sink, 
                                        void*           snkData,
                                        TidyPutByteFunc pbFunc );

/** Helper: send a byte to output */
TIDY_EXPORT void TIDY_CALL tidyPutByte( TidyOutputSink* sink, uint byteValue );


/** Callback to filter messages by diagnostic level:
**  info, warning, etc.  Just set diagnostic output 
**  handler to redirect all diagnostics output.  Return true
**  to proceed with output, false to cancel.
*/
typedef Bool (TIDY_CALL *TidyReportFilter)( TidyDoc tdoc, TidyReportLevel lvl,
                                           uint line, uint col, ctmbstr mssg );

/** Give Tidy a filter callback to use */
TIDY_EXPORT Bool TIDY_CALL    tidySetReportFilter( TidyDoc tdoc,
                                                  TidyReportFilter filtCallback );

/** Set error sink to named file */
TIDY_EXPORT FILE* TIDY_CALL   tidySetErrorFile( TidyDoc tdoc, ctmbstr errfilnam );
/** Set error sink to given buffer */
TIDY_EXPORT int TIDY_CALL     tidySetErrorBuffer( TidyDoc tdoc, TidyBuffer* errbuf );
/** Set error sink to given generic sink */
TIDY_EXPORT int TIDY_CALL     tidySetErrorSink( TidyDoc tdoc, TidyOutputSink* sink );

/** @} end IO group */

/* TODO: Catalog all messages for easy translation
TIDY_EXPORT ctmbstr     tidyLookupMessage( int errorNo );
*/



/** @defgroup Parse Document Parse
**
** Parse markup from a given input source.  String and filename 
** functions added for convenience.  HTML/XHTML version determined
** from input.
** @{
*/

/** Parse markup in named file */
TIDY_EXPORT int TIDY_CALL         tidyParseFile( TidyDoc tdoc, ctmbstr filename );

/** Parse markup from the standard input */
TIDY_EXPORT int TIDY_CALL         tidyParseStdin( TidyDoc tdoc );

/** Parse markup in given string */
TIDY_EXPORT int TIDY_CALL         tidyParseString( TidyDoc tdoc, ctmbstr content );

/** Parse markup in given buffer */
TIDY_EXPORT int TIDY_CALL         tidyParseBuffer( TidyDoc tdoc, TidyBuffer* buf );

/** Parse markup in given generic input source */
TIDY_EXPORT int TIDY_CALL         tidyParseSource( TidyDoc tdoc, TidyInputSource* source);

/** @} End Parse group */


/** @defgroup Clean Diagnostics and Repair
**
** @{
*/
/** Execute configured cleanup and repair operations on parsed markup */
TIDY_EXPORT int TIDY_CALL         tidyCleanAndRepair( TidyDoc tdoc );

/** Run configured diagnostics on parsed and repaired markup. 
**  Must call tidyCleanAndRepair() first.
*/
TIDY_EXPORT int TIDY_CALL         tidyRunDiagnostics( TidyDoc tdoc );

/** @} end Clean group */


/** @defgroup Save Document Save Functions
**
** Save currently parsed document to the given output sink.  File name
** and string/buffer functions provided for convenience.
** @{
*/

/** Save to named file */
TIDY_EXPORT int TIDY_CALL         tidySaveFile( TidyDoc tdoc, ctmbstr filename );

/** Save to standard output (FILE*) */
TIDY_EXPORT int TIDY_CALL         tidySaveStdout( TidyDoc tdoc );

/** Save to given TidyBuffer object */
TIDY_EXPORT int TIDY_CALL         tidySaveBuffer( TidyDoc tdoc, TidyBuffer* buf );

/** Save document to application buffer.  If buffer is not big enough,
**  ENOMEM will be returned and the necessary buffer size will be placed
**  in *buflen.
*/
TIDY_EXPORT int TIDY_CALL         tidySaveString( TidyDoc tdoc,
                                                 tmbstr buffer, uint* buflen );

/** Save to given generic output sink */
TIDY_EXPORT int TIDY_CALL         tidySaveSink( TidyDoc tdoc, TidyOutputSink* sink );

/** @} end Save group */


/** @addtogroup Basic
** @{
*/
/** Save current settings to named file.
    Only non-default values are written. */
TIDY_EXPORT int TIDY_CALL         tidyOptSaveFile( TidyDoc tdoc, ctmbstr cfgfil );

/** Save current settings to given output sink.
    Only non-default values are written. */
TIDY_EXPORT int TIDY_CALL         tidyOptSaveSink( TidyDoc tdoc, TidyOutputSink* sink );


/* Error reporting functions 
*/

/** Write more complete information about errors to current error sink. */
TIDY_EXPORT void TIDY_CALL        tidyErrorSummary( TidyDoc tdoc );

/** Write more general information about markup to current error sink. */
TIDY_EXPORT void TIDY_CALL        tidyGeneralInfo( TidyDoc tdoc );

/** @} end Basic group (again) */


/** @defgroup Tree Document Tree
**
** A parsed and, optionally, repaired document is
** represented by Tidy as a Tree, much like a W3C DOM.
** This tree may be traversed using these functions.
** The following snippet gives a basic idea how these
** functions can be used.
**
<pre>
void dumpNode( TidyNode tnod, int indent )
{
  TidyNode child;

  for ( child = tidyGetChild(tnod); child; child = tidyGetNext(child) )
  {
    ctmbstr name;
    switch ( tidyNodeGetType(child) )
    {
    case TidyNode_Root:       name = "Root";                    break;
    case TidyNode_DocType:    name = "DOCTYPE";                 break;
    case TidyNode_Comment:    name = "Comment";                 break;
    case TidyNode_ProcIns:    name = "Processing Instruction";  break;
    case TidyNode_Text:       name = "Text";                    break;
    case TidyNode_CDATA:      name = "CDATA";                   break;
    case TidyNode_Section:    name = "XML Section";             break;
    case TidyNode_Asp:        name = "ASP";                     break;
    case TidyNode_Jste:       name = "JSTE";                    break;
    case TidyNode_Php:        name = "PHP";                     break;
    case TidyNode_XmlDecl:    name = "XML Declaration";         break;

    case TidyNode_Start:
    case TidyNode_End:
    case TidyNode_StartEnd:
    default:
      name = tidyNodeGetName( child );
      break;
    }
    assert( name != NULL );
    printf( "\%*.*sNode: \%s\\n", indent, indent, " ", name );
    dumpNode( child, indent + 4 );
  }
}

void dumpDoc( TidyDoc tdoc )
{
  dumpNode( tidyGetRoot(tdoc), 0 );
}

void dumpBody( TidyDoc tdoc )
{
  dumpNode( tidyGetBody(tdoc), 0 );
}
</pre>

@{

*/

TIDY_EXPORT TidyNode TIDY_CALL    tidyGetRoot( TidyDoc tdoc );
TIDY_EXPORT TidyNode TIDY_CALL    tidyGetHtml( TidyDoc tdoc );
TIDY_EXPORT TidyNode TIDY_CALL    tidyGetHead( TidyDoc tdoc );
TIDY_EXPORT TidyNode TIDY_CALL    tidyGetBody( TidyDoc tdoc );

/* parent / child */
TIDY_EXPORT TidyNode TIDY_CALL    tidyGetParent( TidyNode tnod );
TIDY_EXPORT TidyNode TIDY_CALL    tidyGetChild( TidyNode tnod );

/* siblings */
TIDY_EXPORT TidyNode TIDY_CALL    tidyGetNext( TidyNode tnod );
TIDY_EXPORT TidyNode TIDY_CALL    tidyGetPrev( TidyNode tnod );

/* Null for non-element nodes and all pure HTML
TIDY_EXPORT ctmbstr     tidyNodeNsLocal( TidyNode tnod );
TIDY_EXPORT ctmbstr     tidyNodeNsPrefix( TidyNode tnod );
TIDY_EXPORT ctmbstr     tidyNodeNsUri( TidyNode tnod );
*/

/* Iterate over attribute values */
TIDY_EXPORT TidyAttr TIDY_CALL    tidyAttrFirst( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL    tidyAttrNext( TidyAttr tattr );

TIDY_EXPORT ctmbstr TIDY_CALL     tidyAttrName( TidyAttr tattr );
TIDY_EXPORT ctmbstr TIDY_CALL     tidyAttrValue( TidyAttr tattr );

/* Null for pure HTML
TIDY_EXPORT ctmbstr     tidyAttrNsLocal( TidyAttr tattr );
TIDY_EXPORT ctmbstr     tidyAttrNsPrefix( TidyAttr tattr );
TIDY_EXPORT ctmbstr     tidyAttrNsUri( TidyAttr tattr );
*/

/** @} end Tree group */


/** @defgroup NodeAsk Node Interrogation
**
** Get information about any givent node.
** @{
*/

/* Node info */
TIDY_EXPORT TidyNodeType TIDY_CALL tidyNodeGetType( TidyNode tnod );
TIDY_EXPORT ctmbstr TIDY_CALL     tidyNodeGetName( TidyNode tnod );

TIDY_EXPORT Bool TIDY_CALL tidyNodeIsText( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsProp( TidyDoc tdoc, TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsHeader( TidyNode tnod ); /* h1, h2, ... */

TIDY_EXPORT Bool TIDY_CALL tidyNodeHasText( TidyDoc tdoc, TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeGetText( TidyDoc tdoc, TidyNode tnod, TidyBuffer* buf );

/* Copy the unescaped value of this node into the given TidyBuffer as UTF-8 */
TIDY_EXPORT Bool TIDY_CALL tidyNodeGetValue( TidyDoc tdoc, TidyNode tnod, TidyBuffer* buf );

TIDY_EXPORT TidyTagId TIDY_CALL tidyNodeGetId( TidyNode tnod );

TIDY_EXPORT uint TIDY_CALL tidyNodeLine( TidyNode tnod );
TIDY_EXPORT uint TIDY_CALL tidyNodeColumn( TidyNode tnod );

/** @defgroup NodeIsElementName Deprecated node interrogation per TagId
**
** @deprecated The functions tidyNodeIs{ElementName} are deprecated and 
** should be replaced by tidyNodeGetId.
** @{
*/
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsHTML( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsHEAD( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsTITLE( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsBASE( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsMETA( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsBODY( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsFRAMESET( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsFRAME( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsIFRAME( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsNOFRAMES( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsHR( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsH1( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsH2( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsPRE( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsLISTING( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsP( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsUL( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsOL( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsDL( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsDIR( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsLI( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsDT( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsDD( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsTABLE( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsCAPTION( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsTD( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsTH( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsTR( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsCOL( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsCOLGROUP( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsBR( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsA( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsLINK( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsB( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsI( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsSTRONG( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsEM( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsBIG( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsSMALL( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsPARAM( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsOPTION( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsOPTGROUP( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsIMG( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsMAP( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsAREA( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsNOBR( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsWBR( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsFONT( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsLAYER( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsSPACER( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsCENTER( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsSTYLE( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsSCRIPT( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsNOSCRIPT( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsFORM( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsTEXTAREA( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsBLOCKQUOTE( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsAPPLET( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsOBJECT( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsDIV( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsSPAN( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsINPUT( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsQ( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsLABEL( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsH3( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsH4( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsH5( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsH6( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsADDRESS( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsXMP( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsSELECT( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsBLINK( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsMARQUEE( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsEMBED( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsBASEFONT( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsISINDEX( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsS( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsSTRIKE( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsU( TidyNode tnod );
TIDY_EXPORT Bool TIDY_CALL tidyNodeIsMENU( TidyNode tnod );

/** @} End NodeIsElementName group */

/** @} End NodeAsk group */


/** @defgroup Attribute Attribute Interrogation
**
** Get information about any given attribute.
** @{
*/

TIDY_EXPORT TidyAttrId TIDY_CALL tidyAttrGetId( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsEvent( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsProp( TidyAttr tattr );

/** @defgroup AttrIsAttributeName Deprecated attribute interrogation per AttrId
**
** @deprecated The functions  tidyAttrIs{AttributeName} are deprecated and 
** should be replaced by tidyAttrGetId.
** @{
*/
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsHREF( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsSRC( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsID( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsNAME( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsSUMMARY( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsALT( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsLONGDESC( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsUSEMAP( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsISMAP( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsLANGUAGE( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsTYPE( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsVALUE( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsCONTENT( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsTITLE( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsXMLNS( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsDATAFLD( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsWIDTH( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsHEIGHT( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsFOR( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsSELECTED( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsCHECKED( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsLANG( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsTARGET( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsHTTP_EQUIV( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsREL( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsOnMOUSEMOVE( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsOnMOUSEDOWN( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsOnMOUSEUP( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsOnCLICK( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsOnMOUSEOVER( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsOnMOUSEOUT( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsOnKEYDOWN( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsOnKEYUP( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsOnKEYPRESS( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsOnFOCUS( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsOnBLUR( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsBGCOLOR( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsLINK( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsALINK( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsVLINK( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsTEXT( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsSTYLE( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsABBR( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsCOLSPAN( TidyAttr tattr );
TIDY_EXPORT Bool TIDY_CALL tidyAttrIsROWSPAN( TidyAttr tattr );

/** @} End AttrIsAttributeName group */

/** @} end AttrAsk group */


/** @defgroup AttrGet Attribute Retrieval
**
** Lookup an attribute from a given node
** @{
*/

TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetById( TidyNode tnod, TidyAttrId attId );

/** @defgroup AttrGetAttributeName Deprecated attribute retrieval per AttrId
**
** @deprecated The functions tidyAttrGet{AttributeName} are deprecated and 
** should be replaced by tidyAttrGetById.
** For instance, tidyAttrGetID( TidyNode tnod ) can be replaced by 
** tidyAttrGetById( TidyNode tnod, TidyAttr_ID ). This avoids a potential
** name clash with tidyAttrGetId for case-insensitive languages.
** @{
*/
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetHREF( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetSRC( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetID( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetNAME( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetSUMMARY( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetALT( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetLONGDESC( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetUSEMAP( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetISMAP( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetLANGUAGE( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetTYPE( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetVALUE( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetCONTENT( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetTITLE( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetXMLNS( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetDATAFLD( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetWIDTH( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetHEIGHT( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetFOR( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetSELECTED( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetCHECKED( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetLANG( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetTARGET( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetHTTP_EQUIV( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetREL( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetOnMOUSEMOVE( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetOnMOUSEDOWN( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetOnMOUSEUP( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetOnCLICK( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetOnMOUSEOVER( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetOnMOUSEOUT( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetOnKEYDOWN( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetOnKEYUP( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetOnKEYPRESS( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetOnFOCUS( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetOnBLUR( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetBGCOLOR( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetLINK( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetALINK( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetVLINK( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetTEXT( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetSTYLE( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetABBR( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetCOLSPAN( TidyNode tnod );
TIDY_EXPORT TidyAttr TIDY_CALL tidyAttrGetROWSPAN( TidyNode tnod );

/** @} End AttrGetAttributeName group */

/** @} end AttrGet group */

#ifdef __cplusplus
}  /* extern "C" */
#endif
#endif /* __TIDY_H__ */

/*
 * local variables:
 * mode: c
 * indent-tabs-mode: nil
 * c-basic-offset: 4
 * eval: (c-set-offset 'substatement-open 0)
 * end:
 */
