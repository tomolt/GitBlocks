#include "ConfigPanel.h"

BEGIN_EVENT_TABLE(ConfigPanel, cbConfigurationPanel)
END_EVENT_TABLE()

ConfigPanel::ConfigPanel(wxWindow *parent, GitBlocks *pgitBlocks)
{
	gitBlocks = pgitBlocks;
	
	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	
	wxBoxSizer *cfgSizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(cfgSizer);
	
	wxBoxSizer *gitSizer = new wxBoxSizer(wxHORIZONTAL);
	cfgSizer->Add(gitSizer, 0, wxEXPAND);
	
	wxStaticText *gitLabel = new wxStaticText(this, ID_CFG_GIT_LABEL, _T("Git command: "));
	gitSizer->Add(gitLabel, 0, wxALIGN_CENTER_VERTICAL);
	
	gitLine = new wxTextCtrl(this, ID_CFG_GIT_LINE, gitBlocks->GetGit());
	gitSizer->Add(gitLine, wxEXPAND, wxALIGN_CENTER_VERTICAL);
	
	wxButton *gitBrowse = new wxButton(this, ID_CFG_GIT_BROWSE, _T("Browse"));
	gitSizer->Add(gitBrowse, 0, wxALIGN_CENTER_VERTICAL);
	
	Connect(ID_CFG_GIT_BROWSE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ConfigPanel::GitBrowse));
}

ConfigPanel::~ConfigPanel()
{
	
}

wxString ConfigPanel::GetTitle() const
{
	return _T("GitBlocks");
}

wxString ConfigPanel::GetBitmapBaseName() const
{
	return _T("GitBlocks");
}

void ConfigPanel::OnApply()
{
	gitBlocks->SetGit(gitLine->GetValue());
}

void ConfigPanel::OnCancel()
{
	
}

void ConfigPanel::GitBrowse(wxCommandEvent &event)
{
#ifdef __WXMSW__ /// Fucking hipster Windows needs extra code
	gitLine->SetValue(wxFileSelector(_("Git command"), wxEmptyString, wxEmptyString, wxEmptyString, _("Executable Files (*.exe)|*.exe"), wxFD_OPEN | wxFD_FILE_MUST_EXIST, this));
#else
	gitLine->SetValue(wxFileSelector(_("Git command"), wxEmptyString, wxEmptyString, wxEmptyString, _("All Files (*.*)|*.*"), wxFD_OPEN | wxFD_FILE_MUST_EXIST, this));
#endif
}
