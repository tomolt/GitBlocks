#ifndef COMMITDIALOG_H
#define COMMITDIALOG_H

#include "Common.h"
#include "GitBlocks.h"

class CommitDialog : public wxDialog
{
public:
	CommitDialog(wxWindow *parent);
	
	unsigned int GetNumFiles() { return filenames.size(); }
	wxString GetFileName(unsigned int i) { return filenames[i]; }
	bool IsFileChecked(unsigned int i) { return filechoice->IsChecked(i); }
	
	wxString GetComment() { return comtLine->GetValue(); }
	
private:
	wxArrayString filenames;
	wxCheckListBox *filechoice;
	wxTextCtrl *comtLine;
	
	void OnCommit(wxCommandEvent &event) { EndModal(1); }
	void OnCancel(wxCommandEvent &event) { EndModal(0); }
};

#endif // COMMITDIALOG_H
