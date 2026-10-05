#include "read_xlsx.hpp"
#include "read_dbf.hpp"
#include "compare.hpp"
#include "gui.hpp"

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, wxString::FromUTF8("Csőd értesítő"), wxDefaultPosition, wxSize(400, 300))
{

    wxPanel *panel = new wxPanel(this);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    m_field1 = new wxFilePickerCtrl(panel, wxID_ANY, wxEmptyString, wxString::FromUTF8("TM.dbf fájl kiválasztása"),
                                    wxString::FromUTF8("Minden Fájl (*.*)|*.*"), wxDefaultPosition, wxDefaultSize,
                                    wxFLP_USE_TEXTCTRL | wxFLP_OPEN | wxFLP_FILE_MUST_EXIST, wxDefaultValidator);
    m_field1->GetPickerCtrl()->SetLabel(wxString::FromUTF8("Tallózás..."));
    m_field2 = new wxFilePickerCtrl(panel, wxID_ANY, wxEmptyString, wxString::FromUTF8("UJ.dbf fájl kiválasztása"),
                                    wxString::FromUTF8("Minden Fájl (*.*)|*.*"), wxDefaultPosition, wxDefaultSize,
                                    wxFLP_USE_TEXTCTRL | wxFLP_OPEN | wxFLP_FILE_MUST_EXIST, wxDefaultValidator);
    m_field2->GetPickerCtrl()->SetLabel(wxString::FromUTF8("Tallózás..."));
    m_field3 = new wxFilePickerCtrl(panel, wxID_ANY, wxEmptyString, wxString::FromUTF8("XLSX fájl kiválasztása"),
                                    wxString::FromUTF8("Minden Fájl (*.*)|*.*"), wxDefaultPosition, wxDefaultSize,
                                    wxFLP_USE_TEXTCTRL | wxFLP_OPEN | wxFLP_FILE_MUST_EXIST, wxDefaultValidator);
    m_field3->GetPickerCtrl()->SetLabel(wxString::FromUTF8("Tallózás..."));

    wxButton *submit = new wxButton(panel, wxID_ANY, wxString::FromUTF8("Generálás"));

    sizer->Add(new wxStaticText(panel, wxID_ANY, wxString::FromUTF8("TM.dbf fájl:")), 0, wxLEFT | wxTOP, 10);
    sizer->Add(m_field1, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
    sizer->Add(new wxStaticText(panel, wxID_ANY, wxString::FromUTF8("UJ.dbf fájl:")), 0, wxLEFT | wxTOP, 10);
    sizer->Add(m_field2, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
    sizer->Add(new wxStaticText(panel, wxID_ANY, wxString::FromUTF8("XLSX fájl:")), 0, wxLEFT | wxTOP, 10);
    sizer->Add(m_field3, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);

    sizer->Add(submit, 0, wxALIGN_RIGHT | wxALL, 10);

    panel->SetSizer(sizer);

    submit->Bind(wxEVT_BUTTON, &MyFrame::OnSubmit, this);
}

void MyFrame::OnExit([[maybe_unused]] wxCommandEvent &event)
{
    Close(true);
}

void MyFrame::OnAbout([[maybe_unused]] wxCommandEvent &event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello([[maybe_unused]] wxCommandEvent &event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

void MyFrame::OnSubmit([[maybe_unused]] wxCommandEvent &event)
{
    wxString a = m_field1->GetPath();
    wxString b = m_field2->GetPath();
    wxString c = m_field3->GetPath();

    if (a.empty() || b.empty() || c.empty())
    {
        wxMessageBox("Please select all three files.", "Missing input",
                     wxOK | wxICON_WARNING);
        return;
    }

    auto tm_records = read_dbf(a.utf8_string(), dbf_tipus::TM);
    auto uj_records = read_dbf(b.utf8_string(), dbf_tipus::UJ);
    auto xlsx_records = read_xlsx(c.utf8_string());

    std::string output;

    output += "Cégnév;Adószám\n";

    compare_records(tm_records, dbf_tipus::TM, xlsx_records, &output);
    compare_records(uj_records, dbf_tipus::UJ, xlsx_records, &output);

    wxFileDialog saveDialog(this, "Save file", "", "",
                            "Comma separated values (*.csv)|*.csv|All files (*.*)|*.*",
                            wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveDialog.ShowModal() == wxID_CANCEL)
        return;

    wxFileOutputStream file(saveDialog.GetPath());
    if (!file.IsOk())
    {
        wxLogError("Cannot save to file '%s'.", saveDialog.GetPath());
        return;
    }

    file.Write(output.data(), output.size());
}