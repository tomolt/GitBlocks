#ifndef NEWBRANCHDIALOG_H
#define NEWBRANCHDIALOG_H

//(*Headers(NewBranchDialog)
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class NewBranchDialog: public wxDialog
{
	public:

		NewBranchDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~NewBranchDialog();

		//(*Declarations(NewBranchDialog)
		wxStaticText* StaticText1;
		wxCheckBox* Switch;
		wxTextCtrl* Name;
		//*)

	protected:

		//(*Identifiers(NewBranchDialog)
		static const long ID_STATICTEXT1;
		static const long ID_NAME;
		static const long ID_SWITCH;
		//*)

	private:

		//(*Handlers(NewBranchDialog)
		void OnCheckBox1Click(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
