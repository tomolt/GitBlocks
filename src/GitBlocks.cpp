#include "GitBlocks.h"

#include <wx/utils.h>

#include <sdk.h> // Code::Blocks SDK
#include <configurationpanel.h>
#include <logmanager.h>
#include <loggers.h>
#include <projectmanager.h>
#include <cbproject.h>
#include <editormanager.h>
#include <cbeditor.h>
#include <cbstyledtextctrl.h>

#include "ConfigPanel.h"
#include "CommitDialog.h"
#include "CommitAllDialog.h"
#include "CloneDialog.h"

// Register the plugin with Code::Blocks.
// We are using an anonymous namespace so we don't litter the global one.
namespace
{
PluginRegistrant<GitBlocks> reg(_T("GitBlocks"));
}


BEGIN_EVENT_TABLE(GitBlocks, cbPlugin)
END_EVENT_TABLE()

// constructor
GitBlocks::GitBlocks()
{
#if 0
	// Make sure our resources are available.
	if(!Manager::LoadResource(_T("GitBlocks.zip")))
	{
		NotifyMissingFile(_T("GitBlocks.zip"));
	}
#endif
}

// destructor
GitBlocks::~GitBlocks()
{
}

void GitBlocks::OnAttach()
{
	git = _T("git");
	
	Logger *gitBlocksLogger = new TextCtrlLogger();
	logSlot = Manager::Get()->GetLogManager()->SetLog(gitBlocksLogger);
	Manager::Get()->GetLogManager()->Slot(logSlot).title = _T("GitBlocks");
	CodeBlocksLogEvent evtAdd1(cbEVT_ADD_LOG_WINDOW, gitBlocksLogger, Manager::Get()->GetLogManager()->Slot(logSlot).title);
	Manager::Get()->ProcessEvent(evtAdd1);
}

void GitBlocks::OnRelease(bool appShutDown)
{
	Manager::Get()->GetLogManager()->DeleteLog(logSlot);
}

int GitBlocks::Configure()
{
	
}

cbConfigurationPanel *GitBlocks::GetConfigurationPanel(wxWindow* parent)
{
	return NULL;
}

void GitBlocks::RegisterFunction(wxObjectEventFunction func, wxString label)
{
	wxMenuItem *item = new wxMenuItem(menu, wxID_ANY, label, label);
	menu->Append(item);
	Connect(item->GetId(), wxEVT_COMMAND_MENU_SELECTED, func);
}

void GitBlocks::BuildMenu(wxMenuBar* menuBar)
{
	menu = new wxMenu();
	
	RegisterFunction(wxCommandEventHandler(GitBlocks::Init), _("Create an empty repository"));
	RegisterFunction(wxCommandEventHandler(GitBlocks::Clone), _("Clone an existing repository"));
	RegisterFunction(wxCommandEventHandler(GitBlocks::Destroy), _("Destroy the local repository"));
	menu->AppendSeparator();
	RegisterFunction(wxCommandEventHandler(GitBlocks::Commit), _("Commit"));
	RegisterFunction(wxCommandEventHandler(GitBlocks::CommitAll), _("Commit all changes"));
	menu->AppendSeparator();
	RegisterFunction(wxCommandEventHandler(GitBlocks::Push), _("Push to origin"));
	RegisterFunction(wxCommandEventHandler(GitBlocks::Pull), _("Pull from origin"));
	RegisterFunction(wxCommandEventHandler(GitBlocks::Fetch), _("Fetch from origin"));
	menu->AppendSeparator();
	RegisterFunction(wxCommandEventHandler(GitBlocks::DiffToIndex), _("Diff to index"));
	RegisterFunction(wxCommandEventHandler(GitBlocks::Log), _("Show log"));
	RegisterFunction(wxCommandEventHandler(GitBlocks::Status), _("Show status"));
	
	menuBar->Insert(menuBar->FindMenu(_("&Tools")) + 1, menu, wxT("&GitBlocks"));
}

void GitBlocks::Execute(wxString &command, const wxString comment, wxString dir)
{
	if(dir.empty())
		dir = Manager::Get()->GetProjectManager()->GetActiveProject()->GetBasePath();
	
	wxArrayString output;
	
	Manager::Get()->GetLogManager()->Log(comment, logSlot);
	Manager::Get()->GetLogManager()->Log(command, logSlot);
	
	wxString ocwd = wxGetCwd();
	wxSetWorkingDirectory(dir);
	wxExecute(command, output);
	wxSetWorkingDirectory(ocwd);
	
	for(unsigned int i=0;i<output.size();i++)
		Manager::Get()->GetLogManager()->Log(output[i], logSlot);
}

void GitBlocks::Init(wxCommandEvent &event)
{
	wxString command = git + _T(" init");
	Execute(command, _T("Creating an empty git repository ..."));
}

void GitBlocks::Clone(wxCommandEvent &event)
{
	CloneDialog dialog(Manager::Get()->GetAppWindow());
	if(dialog.ShowModal() == wxID_OK)
	{
		wxString command = git + _T(" clone ") + dialog.Origin->GetValue();
		Execute(command, _T("Cloning repository ..."), dialog.Directory->GetValue());
	}
}

void GitBlocks::Destroy(wxCommandEvent &event)
{
	if(wxMessageBox(_T("Are you sure you want to destroy the repository?"), _T("Destroy repository"), wxYES_NO) == wxYES)
	{
#ifdef __WXMSW__ // Fucking hipster Windows needs some extra code
		wxString command = _T("RD /S .git");
#else
		wxString command = _T("rm -r .git");
#endif
		Execute(command, _T("Destroying the repository ..."));
	}
}

void GitBlocks::Commit(wxCommandEvent &event)
{
	CommitDialog dialog(Manager::Get()->GetAppWindow());
	if(dialog.ShowModal())
	{
		wxString command;
		
		command = git + _T(" add");
		for(unsigned int i = 0; i < dialog.FileChoice->GetCount(); i++)
			if(dialog.FileChoice->IsChecked(i))
				command += _T(" ") + dialog.FileChoice->GetString(i);
		Execute(command, _T("Adding files ..."));
		
		command = git + _T(" commit -m \"") + dialog.Comment->GetValue() + _T("\"");
		Execute(command, _T("Committing ..."));
	}
}

void GitBlocks::CommitAll(wxCommandEvent &event)
{
	CommitAllDialog dialog(Manager::Get()->GetAppWindow());
	if(dialog.ShowModal() == wxID_OK)
	{
		wxString command;
		cbProject *project = Manager::Get()->GetProjectManager()->GetActiveProject();
		
		command = git + _T(" add");
		for(unsigned int i=0;i<project->GetFilesCount();i++)
			command += _T(" ") + project->GetFile(i)->relativeFilename;
		Execute(command, _T("Adding files ..."));
		
		command = git + _T(" commit -m \"") + dialog.Comment->GetValue() + _T("\"");
		Execute(command, _T("Committing ..."));
	}
}

void GitBlocks::Push(wxCommandEvent &event)
{
#ifdef __WXMSW__ // Fucking hipster Windows needs some extra code
	wxString command = _T("cmd.exe /C \"") + git + _T(" push origin master\"");
#else
	wxString command = _T("xterm -e \"") + git + _T(" push origin master\"");
#endif
	Execute(command, _T("Pushing master to origin ..."));
}

void GitBlocks::Pull(wxCommandEvent &event)
{
#ifdef __WXMSW__ // Fucking hipster Windows needs some extra code
	wxString command = _T("cmd.exe /C \"") + git + _T(" pull origin\"");
#else
	wxString command = _T("xterm -e \"") + git + _T(" pull origin\"");
#endif
	Execute(command, _T("Pulling from origin ..."));
}

void GitBlocks::Fetch(wxCommandEvent &event)
{
#ifdef __WXMSW__ // Fucking hipster Windows needs some extra code
	wxString command = _T("cmd.exe /C \"") + git + _T(" fetch origin\"");
#else
	wxString command = _T("xterm -e \"") + git + _T(" fetch origin\"");
#endif
	Execute(command, _T("Fetching from origin ..."));
}

void GitBlocks::DiffToIndex(wxCommandEvent &event)
{
	wxString command = git + _T(" diff");
	wxString comment = _T("Fetching diff to index ...");
	wxString dir = Manager::Get()->GetProjectManager()->GetActiveProject()->GetBasePath();
	
	wxArrayString output;
	
	Manager::Get()->GetLogManager()->Log(comment, logSlot);
	Manager::Get()->GetLogManager()->Log(command, logSlot);
	
	wxString ocwd = wxGetCwd();
	wxSetWorkingDirectory(dir);
	wxExecute(command, output);
	wxSetWorkingDirectory(ocwd);
	
	cbEditor *editor = Manager::Get()->GetEditorManager()->New(_T("GitBlocks: Diff to index"));
	cbStyledTextCtrl *ctrl = editor->GetControl();
	
	for(unsigned int i=0;i<output.size();i++)
		ctrl->AppendText(output[i] + _T("\n"));
	
	editor->SetModified(false);
}

void GitBlocks::Log(wxCommandEvent &event)
{
	wxString command = git + _T(" log --pretty=format:%h%x09%an%x09%ad%x09%s");
	wxString comment = _T("Fetching log ...");
	wxString dir = Manager::Get()->GetProjectManager()->GetActiveProject()->GetBasePath();
	
	wxArrayString output;
	
	Manager::Get()->GetLogManager()->Log(comment, logSlot);
	Manager::Get()->GetLogManager()->Log(command, logSlot);
	
	wxString ocwd = wxGetCwd();
	wxSetWorkingDirectory(dir);
	wxExecute(command, output);
	wxSetWorkingDirectory(ocwd);
	
	cbEditor *editor = Manager::Get()->GetEditorManager()->New(_T("GitBlocks: Log"));
	cbStyledTextCtrl *ctrl = editor->GetControl();
	
	for(unsigned int i=0;i<output.size();i++)
		ctrl->AppendText(output[i] + _T("\n"));
	
	editor->SetModified(false);
}

void GitBlocks::Status(wxCommandEvent &event)
{
	wxString command = git + _T(" status");
	wxString comment = _T("Fetching status ...");
	wxString dir = Manager::Get()->GetProjectManager()->GetActiveProject()->GetBasePath();
	
	wxArrayString output;
	
	Manager::Get()->GetLogManager()->Log(comment, logSlot);
	Manager::Get()->GetLogManager()->Log(command, logSlot);
	
	wxString ocwd = wxGetCwd();
	wxSetWorkingDirectory(dir);
	wxExecute(command, output);
	wxSetWorkingDirectory(ocwd);
	
	cbEditor *editor = Manager::Get()->GetEditorManager()->New(_T("GitBlocks: Status"));
	cbStyledTextCtrl *ctrl = editor->GetControl();
	
	for(unsigned int i=0;i<output.size();i++)
		ctrl->AppendText(output[i] + _T("\n"));
	
	editor->SetModified(false);
}
