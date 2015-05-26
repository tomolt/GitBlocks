#ifndef RENAMEDIALOG_H
#define RENAMEDIALOG_H

//(*Headers(RenameDialog)
#include <wx/dialog.h>
//*)

class RenameDialog: public wxDialog
{
	public:

		RenameDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~RenameDialog();

		//(*Declarations(RenameDialog)
		//*)

	protected:

		//(*Identifiers(RenameDialog)
		//*)

	private:

		//(*Handlers(RenameDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
