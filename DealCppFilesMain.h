/***************************************************************
 * Name:      DealCppFilesMain.h
 * Purpose:   Defines Application Frame
 * Author:    thb (qq1552989@126.com)
 * Created:   2025-10-01
 * Copyright: thb (kerysoft.com)
 * License:
 **************************************************************/

#ifndef DEALCPPFILESMAIN_H
#define DEALCPPFILESMAIN_H

//(*Headers(DealCppFilesDialog)
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class DealCppFilesDialog: public wxDialog
{
    public:

        DealCppFilesDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~DealCppFilesDialog();

    private:

        //(*Handlers(DealCppFilesDialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnStartClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(DealCppFilesDialog)
        static const wxWindowID ID_STATICTEXT1;
        static const wxWindowID ID_TEXTCTRL1;
        static const wxWindowID ID_STATICTEXT2;
        static const wxWindowID ID_TEXTCTRL2;
        static const wxWindowID ID_STATICTEXT3;
        static const wxWindowID ID_TEXTCTRL3;
        static const wxWindowID ID_STATICTEXT4;
        static const wxWindowID ID_STATICTEXT5;
        static const wxWindowID ID_BUTTON1;
        static const wxWindowID ID_BITMAPBUTTON1;
        static const wxWindowID ID_BUTTON2;
        static const wxWindowID ID_BUTTON3;
        static const wxWindowID ID_STATICTEXT6;
        //*)

        //(*Declarations(DealCppFilesDialog)
        wxBitmapButton* BitmapButton1;
        wxButton* Button1;
        wxButton* Button2;
        wxButton* Button3;
        wxStaticText* StaticResult;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStaticText* StaticText3;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxTextCtrl* TextNewFunc;
        wxTextCtrl* TextOldFunc;
        wxTextCtrl* TextPath;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // DEALCPPFILESMAIN_H
