#pragma once

#include "phc.hpp"
#include <wx/wx.h>

// class MyFrame : public wxFrame
// {
// public:
//     MyFrame() : wxFrame(nullptr, wxID_ANY, "Egyszerű GUI", wxDefaultPosition, wxSize(400, 300))
//     {
//         // Fő konténer (függőleges elrendezés)
//         wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

//         // Szövegbeviteli mezők létrehozása
//         input1 = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
//         input2 = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
//         input3 = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);

//         // Címkék és mezők hozzáadása a sizerhez némi margóval (padding)
//         mainSizer->Add(new wxStaticText(this, wxID_ANY, "Első mező:"), 0, wxALL, 5);
//         mainSizer->Add(input1, 0, wxEXPAND | wxALL, 5);

//         mainSizer->Add(new wxStaticText(this, wxID_ANY, "Második mező:"), 0, wxALL, 5);
//         mainSizer->Add(input2, 0, wxEXPAND | wxALL, 5);

//         mainSizer->Add(new wxStaticText(this, wxID_ANY, "Harmadik mező:"), 0, wxALL, 5);
//         mainSizer->Add(input3, 0, wxEXPAND | wxALL, 5);

//         // Submit gomb hozzáadása
//         submitButton = new wxButton(this, wxID_ANY, "Küldés");
//         mainSizer->Add(submitButton, 0, wxALIGN_CENTER | wxALL, 15);

//         // Eseménykezelő társítása a gombhoz
//         submitButton->Bind(wxEVT_BUTTON, &MyFrame::OnSubmit, this);

//         // Ablak elrendezésének beállítása
//         SetSizer(mainSizer);
//         Layout();
//     }

// private:
//     wxTextCtrl *input1;
//     wxTextCtrl *input2;
//     wxTextCtrl *input3;
//     wxButton *submitButton;

//     // Gombnyomásra lefutó függvény
//     void OnSubmit(wxCommandEvent &event)
//     {
//         wxString val1 = input1->GetValue();
//         wxString val2 = input2->GetValue();
//         wxString val3 = input3->GetValue();

//         wxString üzenet = wxString::Format("Bevitt adatok:\n1: %s\n2: %s\n3: %s", val1, val2, val3);

//         // Felugró ablak az adatokkal
//         wxMessageBox(üzenet, "Eredmény", wxOK | wxICON_INFORMATION);
//     }
// };

// class MyApp : public wxApp {
// public:
//     virtual bool OnInit() {
//         MyFrame* frame = new MyFrame();
//         frame->Show(true);
//         return true;
//     }
// };
