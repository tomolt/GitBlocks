#ifndef COMMITALLDIALOG_H
#define COMMITALLDIALOG_H

#include "Common.h"
#include "GitBlocks.h"

class CommitAllDialog : public wxDialog
{
public:
	CommitAllDialog(wxWindow *parent);
	
	wxString GetComment() { return comtLine->GetValue(); }
	
private:
	wxTextCtrl *comtLine;
	
	void OnCommitAll(wxCommandEvent &event) { EndModal(1); }
	void OnCancel(wxCommandEvent &event) { EndModal(0); }
};

#endif // COMMITALLDIALOG_H
