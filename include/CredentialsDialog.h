#ifndef CREDENTIALSDIALOG_H
#define CREDENTIALSDIALOG_H

//(*Headers(CredentialsDialog)
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class CredentialsDialog: public wxDialog
{
	public:

		CredentialsDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~CredentialsDialog();

		//(*Declarations(CredentialsDialog)
		wxTextCtrl* Username;
		wxStaticText* StaticText1;
		wxTextCtrl* Password;
		wxStaticText* StaticText2;
		//*)

	protected:

		//(*Identifiers(CredentialsDialog)
		static const long ID_STATICTEXT1;
		static const long ID_TEXTCTRL1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL2;
		//*)

	private:

		//(*Handlers(CredentialsDialog)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
