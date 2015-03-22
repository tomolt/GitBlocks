#include "../include/CommitDialog.h"

#include <projectmanager.h>
#include <cbproject.h>

//(*InternalHeaders(CommitDialog)
#include <wx/button.h>
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(CommitDialog)
const long CommitDialog::ID_FILECHOICE = wxNewId();
const long CommitDialog::ID_STATICTEXT1 = wxNewId();
const long CommitDialog::ID_COMMENT = wxNewId();
//*)

BEGIN_EVENT_TABLE(CommitDialog,wxDialog)
	//(*EventTable(CommitDialog)
	//*)
END_EVENT_TABLE()

CommitDialog::CommitDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(CommitDialog)
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxStdDialogButtonSizer* StdDialogButtonSizer1;

	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	FileChoice = new wxCheckListBox(this, ID_FILECHOICE, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_FILECHOICE"));
	BoxSizer1->Add(FileChoice, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Comment: "), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer2->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Comment = new wxTextCtrl(this, ID_COMMENT, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_COMMENT"));
	BoxSizer2->Add(Comment, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StdDialogButtonSizer1 = new wxStdDialogButtonSizer();
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_OK, wxEmptyString));
	StdDialogButtonSizer1->AddButton(new wxButton(this, wxID_CANCEL, wxEmptyString));
	StdDialogButtonSizer1->Realize();
	BoxSizer1->Add(StdDialogButtonSizer1, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);
	//*)
	
	cbProject *project = Manager::Get()->GetProjectManager()->GetActiveProject();
	FileChoice->Append(project->GetFilename());
	for(unsigned int i=0;i<project->GetFilesCount();i++)
		FileChoice->Append(project->GetFile(i)->relativeFilename);
}

CommitDialog::~CommitDialog()
{
	//(*Destroy(CommitDialog)
	//*)
}

