/***************************************************************
 * Name:      DealCppFilesApp.cpp
 * Purpose:   Code for Application Class
 * Author:    thb (qq1552989@126.com)
 * Created:   2025-10-01
 * Copyright: thb (kerysoft.com)
 * License:
 **************************************************************/

#include "DealCppFilesApp.h"

//(*AppHeaders
#include "DealCppFilesMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(DealCppFilesApp);

bool DealCppFilesApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
        DealCppFilesDialog Dlg(NULL);
        SetTopWindow(&Dlg);
        Dlg.ShowModal();
        wxsOK = false;
    }
    //*)
    return wxsOK;

}
