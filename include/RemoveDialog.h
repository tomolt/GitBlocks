#ifndef REMOVEDIALOG_H
#define REMOVEDIALOG_H

//(*Headers(RemoveDialog)
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/choice.h>
//*)

class RemoveDialog: public wxDialog
{
	public:

		RemoveDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~RemoveDialog();

		//(*Declarations(RemoveDialog)
		wxStaticText* StaticText1;
		wxChoice* FileChoice;
		//*)

	protected:

		//(*Identifiers(RemoveDialog)
		static const long ID_STATICTEXT1;
		static const long ID_CHOICE1;
		//*)

	private:

		//(*Handlers(RemoveDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
