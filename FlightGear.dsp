# Microsoft Developer Studio Project File - Name="FlightGear" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=FlightGear - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FlightGear.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FlightGear.mak" CFG="FlightGear - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FlightGear - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "FlightGear - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FD /c  /MTd /I ".." /I ".\src" /I ".\src\include" /I "..\SimGear" /I "..\SimGear\metakit-2.4.3\include" /I "..\SimGear\zlib-1.1.4" /D "HAVE_CONFIG_H" /D "FGFS" /D "FG_NEW_ENVIRONMENT" /D "ENABLE_AUDIO_SUPPORT" /D "ENABLE_PLIB_JOYSTICK"
# SUBTRACT CPP /YX
# ADD RSC /l 0xc09 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib uuid.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /FR /FD /GZ /c  /MTd /I ".." /I ".\src" /I ".\src\include" /I "..\SimGear" /I "..\SimGear\metakit-2.4.3\include" /I "..\SimGear\zlib-1.1.4" /D "HAVE_CONFIG_H" /D "FGFS" /D "FG_NEW_ENVIRONMENT" /D "ENABLE_AUDIO_SUPPORT" /D "ENABLE_PLIB_JOYSTICK"
# ADD RSC /l 0xc09 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD LINK32 kernel32.lib user32.lib winspool.lib comdlg32.lib gdi32.lib shell32.lib wsock32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept 

!ENDIF 

# Begin Target

# Name "FlightGear - Win32 Release"
# Name "FlightGear - Win32 Debug"
# Begin Group "Lib_Aircraft"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Aircraft\aircraft.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Aircraft"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Aircraft"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Aircraft\aircraft.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Aircraft"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Aircraft"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_Airports"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Airports\runways.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Airports"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Airports"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Airports\runways.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Airports"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Airports"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Airports\simple.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Airports"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Airports"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Airports\simple.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Airports"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Airports"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_ATC"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\ATC\ATC.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\ATC.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\atis.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\atis.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\tower.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\tower.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\approach.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\approach.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\ground.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\ground.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\commlist.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\commlist.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\ATCDialog.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\ATCDialog.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\ATCdisplay.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\ATCdisplay.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\ATCVoice.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\ATCVoice.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\ATCmgr.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\ATCmgr.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\ATCutils.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\ATCutils.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\ATCProjection.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\ATCProjection.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\AIMgr.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\AIMgr.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\AIEntity.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\AIEntity.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\AIPlane.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\AIPlane.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\AILocalTraffic.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\AILocalTraffic.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\transmission.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\transmission.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\transmissionlist.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\ATC\transmissionlist.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ATC"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ATC"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_Autopilot"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Autopilot\auto_gui.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Autopilot"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Autopilot"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Autopilot\auto_gui.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Autopilot"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Autopilot"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Autopilot\newauto.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Autopilot"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Autopilot"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Autopilot\newauto.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Autopilot"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Autopilot"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_Cockpit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Cockpit\cockpit.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\cockpit.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\dme.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\dme.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\hud.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\hud.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\hud_opts.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\hud_card.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\hud_dnst.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\hud_gaug.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\hud_inst.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\hud_labl.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\hud_ladr.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\hud_lat.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\hud_lon.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\hud_scal.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\hud_tbi.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\kr_87.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\kr_87.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\kt_70.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\kt_70.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\marker_beacon.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\marker_beacon.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\navcom.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\navcom.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\panel.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\panel.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\panel_io.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\panel_io.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\radiostack.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\radiostack.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Cockpit"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Cockpit"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_Built_in"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Cockpit\built_in\FGMagRibbon.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Built_in"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Built_in"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Cockpit\built_in\FGMagRibbon.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Built_in"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Built_in"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_Controls"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Controls\controls.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Controls"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Controls"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Controls\controls.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Controls"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Controls"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_Environment"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Environment\environment.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Environment"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Environment"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Environment\environment.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Environment"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Environment"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Environment\environment_mgr.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Environment"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Environment"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Environment\environment_mgr.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Environment"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Environment"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Environment\environment_ctrl.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Environment"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Environment"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Environment\environment_ctrl.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Environment"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Environment"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_Balloon"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\FDM\Balloon\BalloonSim.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Balloon"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Balloon"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\Balloon\BalloonSim.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Balloon"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Balloon"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_ExternalNet"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\FDM\ExternalNet\ExternalNet.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ExternalNet"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ExternalNet"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\ExternalNet\ExternalNet.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ExternalNet"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ExternalNet"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_ExternalPipe"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\FDM\ExternalPipe\ExternalPipe.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ExternalPipe"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ExternalPipe"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\ExternalPipe\ExternalPipe.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_ExternalPipe"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_ExternalPipe"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_JSBSim"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGAerodynamics.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGAerodynamics.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGAircraft.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGAircraft.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGAtmosphere.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGAtmosphere.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGAuxiliary.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGAuxiliary.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGCoefficient.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGCoefficient.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGColumnVector3.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGColumnVector3.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGColumnVector4.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGColumnVector4.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGConfigFile.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGConfigFile.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGDefs.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGFCS.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGFCS.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGFDMExec.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGFDMExec.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGFactorGroup.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGFactorGroup.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGForce.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGForce.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGGroundReactions.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGGroundReactions.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGInertial.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGInertial.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGInitialCondition.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGInitialCondition.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGJSBBase.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGJSBBase.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGLGear.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGLGear.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGMassBalance.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGMassBalance.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGMatrix33.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGMatrix33.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGModel.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGModel.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGNozzle.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGNozzle.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGOutput.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGOutput.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGPiston.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGPiston.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGPropeller.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGPropeller.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGPropulsion.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGPropulsion.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGPosition.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGPosition.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGRotation.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGRotation.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGRocket.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGRocket.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGScript.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGScript.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGState.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGState.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGTable.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGTable.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGThruster.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGThruster.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGTranslation.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGTranslation.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGTrim.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGTrim.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGTrimAxis.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGTrimAxis.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGTurbine.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGTurbine.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGUtility.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGUtility.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGEngine.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGEngine.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGTank.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGTank.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGfdmSocket.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGfdmSocket.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGTurbine.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGTurbine.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGPropertyManager.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGPropertyManager.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGSimTurbine.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\FGSimTurbine.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\JSBSim.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\JSBSim.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_JSBSim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_JSBSim"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_filtersjb"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\FDM\JSBSim\filtersjb\FGDeadBand.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_filtersjb"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_filtersjb"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\filtersjb\FGDeadBand.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_filtersjb"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_filtersjb"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\filtersjb\FGFCSComponent.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_filtersjb"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_filtersjb"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\filtersjb\FGFCSComponent.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_filtersjb"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_filtersjb"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\filtersjb\FGFilter.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_filtersjb"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_filtersjb"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\filtersjb\FGFilter.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_filtersjb"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_filtersjb"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\filtersjb\FGGain.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_filtersjb"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_filtersjb"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\filtersjb\FGGain.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_filtersjb"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_filtersjb"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\filtersjb\FGGradient.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_filtersjb"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_filtersjb"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\filtersjb\FGGradient.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_filtersjb"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_filtersjb"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\filtersjb\FGKinemat.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_filtersjb"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_filtersjb"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\filtersjb\FGKinemat.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_filtersjb"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_filtersjb"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\filtersjb\FGSummer.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_filtersjb"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_filtersjb"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\filtersjb\FGSummer.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_filtersjb"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_filtersjb"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\filtersjb\FGSwitch.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_filtersjb"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_filtersjb"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\filtersjb\FGSwitch.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_filtersjb"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_filtersjb"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\filtersjb\FGCondition.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_filtersjb"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_filtersjb"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\JSBSim\filtersjb\FGCondition.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_filtersjb"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_filtersjb"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_LaRCsim"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\LaRCsim.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\LaRCsim.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\LaRCsimIC.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\LaRCsimIC.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\IO360.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\IO360.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\atmos_62.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\atmos_62.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\default_model_routines.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\default_model_routines.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_accel.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_accel.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_aux.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_aux.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_cockpit.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_constants.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_generic.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_geodesy.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_geodesy.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_gravity.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_gravity.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_init.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_init.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_matrix.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_matrix.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_model.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_model.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_sim_control.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_step.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_step.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_sym.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_types.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\c172_aero.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\c172_engine.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\c172_gear.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\c172_init.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\basic_init.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\basic_init.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\basic_aero.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\basic_aero.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\basic_engine.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\basic_gear.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\navion_init.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\navion_aero.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\navion_engine.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\navion_gear.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\navion_init.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\uiuc_aero.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\cherokee_aero.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\cherokee_engine.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\cherokee_gear.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\cherokee_init.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_interface.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\LaRCsim\ls_interface.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_LaRCsim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_LaRCsim"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_UIUCModel"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_1DdataFileReader.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_1DdataFileReader.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_1Dinterpolation.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_1Dinterpolation.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_2DdataFileReader.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_2DdataFileReader.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_2Dinterpolation.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_2Dinterpolation.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_3Dinterpolation.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_3Dinterpolation.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_aerodeflections.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_aerodeflections.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_aircraftdir.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_aircraft.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_alh_ap.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_alh_ap.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_betaprobe.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_betaprobe.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_coef_drag.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_coef_drag.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_coef_lift.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_coef_lift.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_coef_pitch.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_coef_pitch.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_coef_roll.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_coef_roll.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_coef_sideforce.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_coef_sideforce.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_coef_yaw.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_coef_yaw.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_coefficients.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_coefficients.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_controlInput.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_controlInput.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_convert.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_convert.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_engine.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_engine.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_flapdata.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_flapdata.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_find_position.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_find_position.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_fog.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_fog.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_gear.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_gear.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_get_flapper.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_get_flapper.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_getwind.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_getwind.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_ice.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_ice.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_iceboot.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_iceboot.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_iced_nonlin.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_iced_nonlin.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_icing_demo.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_icing_demo.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_initializemaps.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_initializemaps.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_CD.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_CD.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_CL.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_CL.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_CY.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_CY.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_Cm.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_Cm.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_Cn.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_Cn.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_Croll.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_Croll.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_controlSurface.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_controlSurface.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_engine.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_engine.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_fog.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_fog.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_geometry.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_geometry.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_ice.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_ice.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_gear.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_gear.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_init.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_init.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_keyword.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_keyword.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_mass.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_mass.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_misc.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_misc.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_record1.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_record1.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_record2.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_record2.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_record3.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_record3.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_record4.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_record4.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_record5.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_record5.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_record6.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_map_record6.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_init.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_init.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_geometry.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_geometry.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_controlSurface.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_controlSurface.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_mass.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_mass.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_engine.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_engine.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_CD.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_CD.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_CL.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_CL.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_Cm.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_Cm.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_CY.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_CY.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_Croll.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_Croll.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_Cn.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_Cn.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_gear.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_gear.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_ice.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_ice.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_fog.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_fog.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_record.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_record.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_misc.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_misc.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_functions.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_menu_functions.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_pah_ap.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_pah_ap.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_parsefile.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_parsefile.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_recorder.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_recorder.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_warnings_errors.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_warnings_errors.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_wrapper.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UIUCModel\uiuc_wrapper.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_UIUCModel"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_UIUCModel"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_YASim"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\FDM\YASim\YASim.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\YASim.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Airplane.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Airplane.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Atmosphere.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Atmosphere.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\BodyEnvironment.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\ControlMap.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\ControlMap.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\FGFDM.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\FGFDM.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Gear.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Gear.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Glue.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Glue.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Integrator.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Integrator.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Jet.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Jet.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Math.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Math.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Model.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Model.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\PistonEngine.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\PistonEngine.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\PropEngine.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\PropEngine.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Propeller.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Propeller.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\RigidBody.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\RigidBody.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Rotor.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Rotor.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Rotorblade.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Rotorblade.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Rotorpart.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Rotorpart.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\SimpleJet.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\SimpleJet.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Surface.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Surface.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Thruster.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Thruster.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Vector.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Wing.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\YASim\Wing.hpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_YASim"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_YASim"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_Flight"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\FDM\ADA.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Flight"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Flight"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\ADA.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Flight"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Flight"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\Balloon.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Flight"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Flight"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\Balloon.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Flight"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Flight"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\flight.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Flight"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Flight"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\flight.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Flight"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Flight"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\MagicCarpet.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Flight"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Flight"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\MagicCarpet.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Flight"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Flight"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UFO.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Flight"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Flight"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\UFO.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Flight"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Flight"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\NullFDM.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Flight"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Flight"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\FDM\NullFDM.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Flight"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Flight"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_GUI"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\GUI\new_gui.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_GUI"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_GUI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\GUI\new_gui.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_GUI"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_GUI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\GUI\dialog.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_GUI"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_GUI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\GUI\dialog.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_GUI"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_GUI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\GUI\menubar.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_GUI"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_GUI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\GUI\menubar.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_GUI"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_GUI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\GUI\gui.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_GUI"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_GUI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\GUI\gui.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_GUI"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_GUI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\GUI\gui_funcs.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_GUI"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_GUI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\GUI\gui_local.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_GUI"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_GUI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\GUI\gui_local.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_GUI"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_GUI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\GUI\mouse.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_GUI"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_GUI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\GUI\preset_dlg.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_GUI"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_GUI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\GUI\preset_dlg.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_GUI"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_GUI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\GUI\prop_picker.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_GUI"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_GUI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\GUI\prop_picker.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_GUI"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_GUI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\GUI\sgVec3Slider.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_GUI"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_GUI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\GUI\sgVec3Slider.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_GUI"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_GUI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\GUI\trackball.c

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_GUI"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_GUI"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\GUI\trackball.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_GUI"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_GUI"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_Input"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Input\input.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Input"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Input"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Input\input.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Input"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Input"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_Instrumentation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Instrumentation\instrument_mgr.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\instrument_mgr.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\annunciator.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\annunciator.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\dme.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\dme.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\gps.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\gps.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\adf.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\adf.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\gyro.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\gyro.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\airspeed_indicator.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\airspeed_indicator.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\attitude_indicator.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\attitude_indicator.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\altimeter.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\altimeter.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\turn_indicator.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\turn_indicator.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\slip_skid_ball.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\slip_skid_ball.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\heading_indicator.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\heading_indicator.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\vertical_speed_indicator.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\vertical_speed_indicator.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\mag_compass.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\mag_compass.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\clock.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Instrumentation\clock.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Instrumentation"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Instrumentation"

!ENDIF 

# End Source File
# End Group
# Begin Group "main"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Main\bootstrap.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\main"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_Main"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Main\main.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\main.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\fg_commands.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\fg_commands.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\fg_init.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\fg_init.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\fg_io.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\fg_io.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\fg_props.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\fg_props.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\globals.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\globals.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\logger.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\logger.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\options.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\options.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\splash.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\splash.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\util.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\util.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\viewer.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\viewer.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\viewmgr.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Main\viewmgr.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Main"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Main"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_Model"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Model\acmodel.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Model"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Model"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Model\acmodel.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Model"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Model"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Model\model_panel.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Model"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Model"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Model\model_panel.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Model"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Model"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Model\modelmgr.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Model"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Model"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Model\modelmgr.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Model"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Model"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Model\panelnode.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Model"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Model"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Model\panelnode.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Model"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Model"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_MultiPlayer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\MultiPlayer\multiplayrxmgr.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_MultiPlayer"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_MultiPlayer"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\MultiPlayer\multiplayrxmgr.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_MultiPlayer"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_MultiPlayer"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\MultiPlayer\multiplaytxmgr.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_MultiPlayer"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_MultiPlayer"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\MultiPlayer\multiplaytxmgr.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_MultiPlayer"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_MultiPlayer"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\MultiPlayer\mpplayer.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_MultiPlayer"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_MultiPlayer"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\MultiPlayer\mpplayer.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_MultiPlayer"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_MultiPlayer"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\MultiPlayer\mpmessages.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_MultiPlayer"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_MultiPlayer"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_Navaids"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Navaids\fix.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Navaids"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Navaids"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Navaids\fixlist.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Navaids"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Navaids"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Navaids\fixlist.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Navaids"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Navaids"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Navaids\ils.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Navaids"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Navaids"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Navaids\ilslist.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Navaids"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Navaids"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Navaids\ilslist.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Navaids"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Navaids"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Navaids\mkrbeacons.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Navaids"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Navaids"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Navaids\mkrbeacons.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Navaids"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Navaids"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Navaids\nav.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Navaids"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Navaids"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Navaids\navlist.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Navaids"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Navaids"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Navaids\navlist.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Navaids"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Navaids"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_Network"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Network\protocol.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\protocol.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\atc610x.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\atc610x.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\atlas.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\atlas.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\garmin.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\garmin.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\httpd.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\httpd.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\joyclient.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\joyclient.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\native.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\native.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\native_ctrls.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\native_ctrls.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\native_fdm.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\native_fdm.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\native_gui.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\native_gui.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\net_ctrls.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\net_fdm.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\net_fdm_mini.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\net_gui.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\nmea.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\nmea.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\opengc.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\opengc.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\opengc_data.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\props.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\props.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\pve.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\pve.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\ray.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\ray.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\rul.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\rul.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\generic.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Network\generic.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Network"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Network"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_Objects"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Objects\ssgEntityArray.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Objects"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Objects"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Objects\ssgEntityArray.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Objects"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Objects"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_Replay"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Replay\replay.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Replay"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Replay"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Replay\replay.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Replay"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Replay"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_Scenery"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Scenery\FGTileLoader.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Scenery"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Scenery"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Scenery\FGTileLoader.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Scenery"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Scenery"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Scenery\hitlist.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Scenery"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Scenery"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Scenery\hitlist.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Scenery"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Scenery"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Scenery\newcache.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Scenery"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Scenery"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Scenery\newcache.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Scenery"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Scenery"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Scenery\scenery.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Scenery"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Scenery"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Scenery\scenery.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Scenery"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Scenery"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Scenery\tileentry.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Scenery"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Scenery"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Scenery\tileentry.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Scenery"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Scenery"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Scenery\tilemgr.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Scenery"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Scenery"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Scenery\tilemgr.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Scenery"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Scenery"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_Scripting"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Scripting\scriptmgr.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Scripting"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Scripting"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Scripting\scriptmgr.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Scripting"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Scripting"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_Sound"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Sound\beacon.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Sound"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Sound"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Sound\beacon.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Sound"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Sound"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Sound\fg_fx.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Sound"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Sound"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Sound\fg_fx.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Sound"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Sound"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Sound\morse.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Sound"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Sound"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Sound\morse.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Sound"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Sound"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_Systems"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Systems\system_mgr.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Systems"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Systems"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Systems\system_mgr.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Systems"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Systems"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Systems\electrical.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Systems"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Systems"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Systems\electrical.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Systems"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Systems"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Systems\pitot.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Systems"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Systems"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Systems\pitot.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Systems"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Systems"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Systems\static.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Systems"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Systems"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Systems\static.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Systems"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Systems"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Systems\vacuum.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Systems"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Systems"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Systems\vacuum.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Systems"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Systems"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_Time"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\Time\fg_timer.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Time"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Time"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Time\fg_timer.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Time"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Time"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Time\light.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Time"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Time"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Time\light.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Time"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Time"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Time\moonpos.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Time"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Time"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Time\moonpos.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Time"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Time"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Time\sunpos.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Time"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Time"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Time\sunpos.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Time"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Time"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Time\sunsolver.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Time"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Time"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Time\sunsolver.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Time"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Time"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Time\tmp.cxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Time"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Time"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\Time\tmp.hxx

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_Time"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_Time"

!ENDIF 

# End Source File
# End Group
# Begin Group "Lib_WeatherCM"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\WeatherCM\FGAirPressureItem.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGAirPressureItem.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGCloud.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGCloudItem.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGCloudItem.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGLocalWeatherDatabase.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGLocalWeatherDatabase.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGPhysicalProperties.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGPhysicalProperties.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGPhysicalProperties_bind.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGPhysicalProperty.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGPhysicalProperty.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGSnowRain.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGTemperatureItem.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGTemperatureItem.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGThunderstorm.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGThunderstorm.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGTurbulenceItem.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGTurbulenceItem.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGVaporPressureItem.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGVaporPressureItem.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGWeatherDefs.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGWeatherFeature.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGWeatherUtils.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGWeatherParse.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGWeatherParse.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGWeatherVectorWrap.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGWindItem.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\FGWindItem.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\linintp2.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\linintp2.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\sphrintp.cpp

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\WeatherCM\sphrintp.h

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# PROP Intermediate_Dir "Release\Lib_WeatherCM"

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# PROP Intermediate_Dir "Debug\Lib_WeatherCM"

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE = .\src\Include\config.h-msvc6

!IF  "$(CFG)" == "FlightGear - Win32 Release"

# Begin Custom Build - Creating config.h
InputPath=.\src\Include\config.h-msvc6

".\src\Include\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy .\src\Include\config.h-msvc6 .\src\Include\config.h

# End Custom Build

!ELSEIF  "$(CFG)" == "FlightGear - Win32 Debug"

# Begin Custom Build - Creating config.h
InputPath=.\src\Include\config.h-msvc6

".\src\Include\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy .\src\Include\config.h-msvc6 .\src\Include\config.h

# End Custom Build

!ENDIF

# End Source File
# End Target
# End Project
