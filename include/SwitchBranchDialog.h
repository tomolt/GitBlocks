#ifndef SWITCHBRANCHDIALOG_H
#define SWITCHBRANCHDIALOG_H

//(*Headers(SwitchBranchDialog)
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class SwitchBranchDialog: public wxDialog
{
	public:

		SwitchBranchDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~SwitchBranchDialog();

		//(*Declarations(SwitchBranchDialog)
		wxStaticText* StaticText1;
		wxTextCtrl* Name;
		//*)

	protected:

		//(*Identifiers(SwitchBranchDialog)
		static const long ID_STATICTEXT1;
		static const long ID_NAME;
		//*)

	private:

		//(*Handlers(SwitchBranchDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
