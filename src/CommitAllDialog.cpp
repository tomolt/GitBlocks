#include "CommitAllDialog.h"

CommitAllDialog::CommitAllDialog(wxWindow *parent) : wxDialog(parent, ID_COAD, _T("Commit All"))
{
	wxBoxSizer *coadSizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(coadSizer);
	
	wxBoxSizer *comtSizer = new wxBoxSizer(wxHORIZONTAL);
	coadSizer->Add(comtSizer);
	
	wxStaticText *comtLabel = new wxStaticText(this, ID_COAD_COMT_LABEL, _T("Comment: "));
	comtSizer->Add(comtLabel);
	
	comtLine = new wxTextCtrl(this, ID_COAD_COMT_LINE);
	comtSizer->Add(comtLine, 1, wxALL);
	
	wxBoxSizer *ccSizer = new wxBoxSizer(wxHORIZONTAL);
	coadSizer->Add(ccSizer, 0);
	
	wxButton *ccCommitAll = new wxButton(this, ID_COAD_CC_COMMIT_ALL, _T("Commit All"));
	ccSizer->Add(ccCommitAll, wxEXPAND);
	
	wxButton *ccCancel = new wxButton(this, ID_COAD_CC_CANCEL, _T("Cancel"));
	ccSizer->Add(ccCancel, wxEXPAND);
	
	Connect(ID_COAD_CC_COMMIT_ALL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CommitAllDialog::OnCommitAll));
	Connect(ID_COAD_CC_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CommitAllDialog::OnCancel));
}
