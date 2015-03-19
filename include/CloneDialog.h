#ifndef CLONEDIALOG_H
#define CLONEDIALOG_H

#include "Common.h"

class CloneDialog : public wxDialog
{
public:
	CloneDialog(wxWindow *parent);
	
	wxString GetOrigin() { return originLine->GetValue(); }
	wxString GetDirectory() { return directoryLine->GetValue(); }
	
private:
	wxTextCtrl *originLine;
	wxTextCtrl *directoryLine;
	
	void OnCommit(wxCommandEvent &event);
	void OnCancel(wxCommandEvent &event);
};

#endif // CLONEDIALOG_H
