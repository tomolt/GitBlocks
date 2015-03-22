#include "../include/CloneDialog.h"

#include <wx/dirdlg.h>

//(*InternalHeaders(CloneDialog)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(CloneDialog)
const long CloneDialog::ID_STATICTEXT1 = wxNewId();
const long CloneDialog::ID_TEXTCTRL1 = wxNewId();
const long CloneDialog::ID_STATICTEXT2 = wxNewId();
const long CloneDialog::ID_TEXTCTRL2 = wxNewId();
const long CloneDialog::ID_BROWSE = wxNewId();
//*)

BEGIN_EVENT_TABLE(CloneDialog,wxDialog)
	//(*EventTable(CloneDialog)
	//*)
END_EVENT_TABLE()

CloneDialog::CloneDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(CloneDialog)
	wxBoxSizer* BoxSizer3;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;

	Create(parent, wxID_ANY, _("Clone existing repository"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Origin: "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer2->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Origin = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	BoxSizer2->Add(Origin, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Directory: "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer3->Add(StaticText2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Directory = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	BoxSizer3->Add(Directory, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Browse = new wxButton(this, ID_BROWSE, _("Browse"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BROWSE"));
	BoxSizer3->Add(Browse, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer3, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	BoxSizer1->Add(StdDialogButtonSizer1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&CloneDialog::OnTextCtrl1Text);
	Connect(ID_BROWSE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CloneDialog::OnButton1Click);
	//*)
	
	
}

CloneDialog::~CloneDialog()
{
	//(*Destroy(CloneDialog)
	//*)
}


void CloneDialog::OnButton1Click(wxCommandEvent& event)
{
	wxDirDialog dialog(NULL, _("Choose clone directory ..."), wxEmptyString, wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
	if(dialog.ShowModal() == wxID_OK)
	{
		Directory->SetValue(dialog.GetPath());
	}
}

void CloneDialog::OnTextCtrl1Text(wxCommandEvent& event)
{
}
