#include "CloneDialog.h"

CloneDialog::CloneDialog(wxWindow *parent) : wxDialog(parent, ID_CLOD, _T("Clone repository"))
{
	wxBoxSizer *clodSizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(clodSizer);
	
	// clodSizer->AddSpacer(2);
	
	wxBoxSizer *originSizer = new wxBoxSizer(wxHORIZONTAL);
	clodSizer->Add(originSizer);
	
	wxStaticText *originLabel = new wxStaticText(this, ID_CLOD_ORIGIN_LABEL, _T("Origin repository: "));
	originSizer->Add(originLabel, wxALIGN_CENTER_VERTICAL);
	
	originLine = new wxTextCtrl(this, ID_CLOD_ORIGIN_LINE);
	originSizer->Add(originLine, wxEXPAND | wxALIGN_CENTER_VERTICAL);
	
	wxBoxSizer *directorySizer = new wxBoxSizer(wxHORIZONTAL);
	clodSizer->Add(directorySizer);
	
	wxStaticText *directoryLabel = new wxStaticText(this, ID_CLOD_DIRECTORY_LABEL, _T("Directory: "));
	directorySizer->Add(directoryLabel, wxALIGN_CENTER_VERTICAL);
	
	directoryLine = new wxTextCtrl(this, ID_CLOD_DIRECTORY_LINE);
	directorySizer->Add(directoryLine, wxEXPAND | wxALIGN_CENTER_VERTICAL);
	
	wxButton *directoryBrowse = new wxButton(this, ID_CLOD_DIRECTORY_BUTTON, _T("Browse"));
	directorySizer->Add(directoryBrowse, wxALIGN_CENTER_VERTICAL);
	
	wxBoxSizer *ccSizer = new wxBoxSizer(wxHORIZONTAL);
	clodSizer->Add(ccSizer, 0);
	
	wxButton *ccClone = new wxButton(this, ID_CLOD_CC_CLONE, _T("Clone"));
	ccSizer->Add(ccClone, wxEXPAND);
	
	wxButton *ccCancel = new wxButton(this, ID_CLOD_CC_CANCEL, _T("Cancel"));
	ccSizer->Add(ccCancel, wxEXPAND);
	
	Connect(ID_CLOD_CC_CLONE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CloneDialog::OnCommit));
	Connect(ID_CLOD_CC_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CloneDialog::OnCancel));
}

void CloneDialog::OnCommit(wxCommandEvent& event)
{
	EndModal(1);
}

void CloneDialog::OnCancel(wxCommandEvent& event)
{
	EndModal(0);
}
