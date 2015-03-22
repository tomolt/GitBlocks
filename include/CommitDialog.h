#ifndef COMMITDIALOG_H
#define COMMITDIALOG_H

#define wxUSE_CHECKLISTBOX 1

//(*Headers(CommitDialog)
#include <wx/checklst.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class CommitDialog: public wxDialog
{
	public:

		CommitDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~CommitDialog();

		//(*Declarations(CommitDialog)
		wxStaticText* StaticText1;
		wxCheckListBox* FileChoice;
		wxTextCtrl* Comment;
		//*)

	protected:

		//(*Identifiers(CommitDialog)
		static const long ID_FILECHOICE;
		static const long ID_STATICTEXT1;
		static const long ID_COMMENT;
		//*)

	private:

		//(*Handlers(CommitDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
