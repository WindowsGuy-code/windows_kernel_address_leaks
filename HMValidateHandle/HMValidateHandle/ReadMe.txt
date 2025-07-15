================
IMPORTANT NOTICE
================

This method of leaking the Kernel Address has been patched, most likeley in Windows Build 17074 and anything after.  
Proof (Windows 10 Pro, 2009, 22631):
8C 06 11 00 00 00 00 00 C0 BB 07 00 00 00 00 00 18 00 0A 60 00 07 00 80 00 01 00 00 00 00 C0 04. These are the first 32 bytes of tagWND.

========================================================================
    CONSOLE APPLICATION : HMValidateHandle Project Overview
========================================================================

AppWizard has created this HMValidateHandle application for you.

This file contains a summary of what you will find in each of the files that
make up your HMValidateHandle application.


HMValidateHandle.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

HMValidateHandle.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

HMValidateHandle.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named HMValidateHandle.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
