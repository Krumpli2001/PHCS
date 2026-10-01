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

MyFrame::MyFrame() : wxFrame(nullptr, wxID_ANY, "Hello World", wxDefaultPosition, wxSize(400, 300))
{

    wxPanel *panel = new wxPanel(this);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    m_field1 = new wxFilePickerCtrl(panel, wxID_ANY, wxEmptyString, "TM.dbf fájl kiválasztása",
                                    "All files (*.*)|*.*", wxDefaultPosition, wxDefaultSize,
                                    wxFLP_USE_TEXTCTRL | wxFLP_OPEN | wxFLP_FILE_MUST_EXIST);
    m_field2 = new wxFilePickerCtrl(panel, wxID_ANY, wxEmptyString, "UJ.dbf fájl kiválasztása",
                                    "All files (*.*)|*.*", wxDefaultPosition, wxDefaultSize,
                                    wxFLP_USE_TEXTCTRL | wxFLP_OPEN | wxFLP_FILE_MUST_EXIST);
    m_field3 = new wxFilePickerCtrl(panel, wxID_ANY, wxEmptyString, "XLSX fájl kiválasztása",
                                    "All files (*.*)|*.*", wxDefaultPosition, wxDefaultSize,
                                    wxFLP_USE_TEXTCTRL | wxFLP_OPEN | wxFLP_FILE_MUST_EXIST);
    wxButton *submit = new wxButton(panel, wxID_ANY, "Submit");

    sizer->Add(new wxStaticText(panel, wxID_ANY, "TM.dbf file:"), 0, wxLEFT | wxTOP, 10);
    sizer->Add(m_field1, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "UJ.dbf file:"), 0, wxLEFT | wxTOP, 10);
    sizer->Add(m_field2, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
    sizer->Add(new wxStaticText(panel, wxID_ANY, "XLSX file:"), 0, wxLEFT | wxTOP, 10);
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

    // std::println("Selected files:");
    // std::println("1: {}", a.utf8_string());
    // std::println("2: {}", b.utf8_string());
    // std::println("3: {}", c.utf8_string());

    wxMessageBox(wxString::Format("1: %s\n2: %s\n3: %s", a, b, c),
                 "Selected files", wxOK | wxICON_INFORMATION);

    // auto tm_records = read_dbf(argv[1], dbf_tipus::TM);
    // auto uj_records = read_dbf(argv[2], dbf_tipus::UJ);
    // auto tszem_records = read_dbf(argv[3], dbf_tipus::TSZEM);
    // auto xlsx_records = read_xlsx(argv[4]);

    // std::println("Szia világ2!");

    compare_records(tm_records, dbf_tipus::TM, xlsx_records);
    compare_records(uj_records, dbf_tipus::UJ, xlsx_records);
}