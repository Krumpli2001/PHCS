#pragma once

#include "phc.hpp"
#include <wx/wx.h>
#include <wx/filepicker.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <fstream>

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

class MyFrame : public wxFrame
{
public:
    MyFrame();

private:
    void OnHello(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);

    void OnSubmit(wxCommandEvent &event);

    wxFilePickerCtrl *m_field1;
    wxFilePickerCtrl *m_field2;
    wxFilePickerCtrl *m_field3;
    //wxFilePickerCtrl* m_field4;
};

enum
{
    ID_Hello = 1
};