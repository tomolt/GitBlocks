#include "../include/RemoveDialog.h"

#include <projectmanager.h>
#include <cbproject.h>

//(*InternalHeaders(RemoveDialog)
#include <wx/button.h>
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(RemoveDialog)
const long RemoveDialog::ID_STATICTEXT1 = wxNewId();
const long RemoveDialog::ID_CHOICE1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(RemoveDialog,wxDialog)
	//(*EventTable(RemoveDialog)
	//*)
END_EVENT_TABLE()

RemoveDialog::RemoveDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(RemoveDialog)
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;

	Create(parent, id, _("Remove file"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("File to remove: "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FileChoice = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
	BoxSizer2->Add(FileChoice, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	BoxSizer1->Add(StdDialogButtonSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	//*)
	
	cbProject *project = Manager::Get()->GetProjectManager()->GetActiveProject();
	for(unsigned int i=0;i<project->GetFilesCount();i++)
		FileChoice->Append(project->GetFile(i)->relativeFilename);
}

RemoveDialog::~RemoveDialog()
{
	//(*Destroy(RemoveDialog)
	//*)
}

