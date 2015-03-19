#include "CommitDialog.h"

#include <projectmanager.h>
#include <cbproject.h>
#include <projectfile.h>

CommitDialog::CommitDialog(wxWindow *parent) : wxDialog(parent, ID_COMD, _T("Commit"))
{
	ProjectManager *ProjMan = Manager::Get()->GetProjectManager();
	filenames.push_back(ProjMan->GetActiveProject()->GetFilename());
	for(unsigned int i=0;i<ProjMan->GetActiveProject()->GetFilesCount();i++)
		filenames.push_back(ProjMan->GetActiveProject()->GetFile(i)->relativeFilename);
	
	wxBoxSizer *comdSizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(comdSizer);
	
	filechoice = new wxCheckListBox(this, ID_COMD_FILE_CHOICE, wxDefaultPosition, wxDefaultSize, filenames);
	comdSizer->Add(filechoice, 1, wxALIGN_CENTER_HORIZONTAL | wxEXPAND);
	
	wxBoxSizer *comtSizer = new wxBoxSizer(wxHORIZONTAL);
	comdSizer->Add(comtSizer);
	
	wxStaticText *comtLabel = new wxStaticText(this, ID_COMD_COMT_LABEL, _T("Comment: "));
	comtSizer->Add(comtLabel);
	
	comtLine = new wxTextCtrl(this, ID_COMD_COMT_LINE);
	comtSizer->Add(comtLine, 1, wxALL);
	
	wxBoxSizer *ccSizer = new wxBoxSizer(wxHORIZONTAL);
	comdSizer->Add(ccSizer, 0);
	
	wxButton *ccCommit = new wxButton(this, ID_COMD_CC_COMMIT, _T("Commit"));
	ccSizer->Add(ccCommit, wxEXPAND);
	
	wxButton *ccCancel = new wxButton(this, ID_COMD_CC_CANCEL, _T("Cancel"));
	ccSizer->Add(ccCancel, wxEXPAND);
	
	Connect(ID_COMD_CC_COMMIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CommitDialog::OnCommit));
	Connect(ID_COMD_CC_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CommitDialog::OnCancel));
}
