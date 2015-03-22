#ifndef COMMITALLDIALOG_H
#define COMMITALLDIALOG_H

//(*Headers(CommitAllDialog)
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class CommitAllDialog: public wxDialog
{
	public:

		CommitAllDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~CommitAllDialog();

		//(*Declarations(CommitAllDialog)
		wxStaticText* StaticText1;
		wxTextCtrl* Comment;
		//*)

	protected:

		//(*Identifiers(CommitAllDialog)
		static const long ID_STATICTEXT1;
		static const long ID_COMMENT;
		//*)

	private:

		//(*Handlers(CommitAllDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
