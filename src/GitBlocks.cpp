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

#include "CommitDialog.h"
#include "CommitAllDialog.h"
#include "CloneDialog.h"
#include "NewBranchDialog.h"
#include "SwitchBranchDialog.h"

// Register the plugin with Code::Blocks.
// We are using an anonymous namespace so we don't litter the global one.
namespace
{
PluginRegistrant<GitBlocks> reg(_("GitBlocks"));
}


BEGIN_EVENT_TABLE(GitBlocks, cbPlugin)
END_EVENT_TABLE()

// constructor
GitBlocks::GitBlocks()
{
#if 0
	// Make sure our resources are available.
	if(!Manager::LoadResource(_("GitBlocks.zip")))
	{
		NotifyMissingFile(_("GitBlocks.zip"));
	}
#endif
}

// destructor
GitBlocks::~GitBlocks()
{
}

void GitBlocks::OnAttach()
{
	git = _("git");
	
	Logger *gitBlocksLogger = new TextCtrlLogger();
	logSlot = Manager::Get()->GetLogManager()->SetLog(gitBlocksLogger);
	Manager::Get()->GetLogManager()->Slot(logSlot).title = _("GitBlocks");
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
	RegisterFunction(wxCommandEventHandler(GitBlocks::NewBranch), _("Add new branch"));
	RegisterFunction(wxCommandEventHandler(GitBlocks::SwitchBranch), _("Switch branch"));
	menu->AppendSeparator();
	RegisterFunction(wxCommandEventHandler(GitBlocks::DiffToIndex), _("Diff to index"));
	RegisterFunction(wxCommandEventHandler(GitBlocks::Log), _("Show log"));
	RegisterFunction(wxCommandEventHandler(GitBlocks::Status), _("Show status"));
	
	menuBar->Insert(menuBar->FindMenu(_("&Tools")) + 1, menu, wxT("&GitBlocks"));
}

void GitBlocks::Execute(wxString command, const wxString comment, wxString dir)
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
	Execute(git + _(" init"), _("Creating an empty git repository ..."));
}

void GitBlocks::Clone(wxCommandEvent &event)
{
	CloneDialog dialog(Manager::Get()->GetAppWindow());
	if(dialog.ShowModal() == wxID_OK)
	{
		wxString command = git + _(" clone ") + dialog.Origin->GetValue();
		Execute(command, _("Cloning repository ..."), dialog.Directory->GetValue());
	}
}

void GitBlocks::Destroy(wxCommandEvent &event)
{
	if(wxMessageBox(_("Are you sure you want to destroy the repository?"), _("Destroy repository"), wxYES_NO) == wxYES)
	{
#ifdef __WXMSW__ // Fucking hipster Windows needs some extra code
		wxString command = _("RD /S .git");
#else
		wxString command = _("rm -r .git");
#endif
		Execute(command, _("Destroying the repository ..."));
	}
}

void GitBlocks::Commit(wxCommandEvent &event)
{
	CommitDialog dialog(Manager::Get()->GetAppWindow());
	if(dialog.ShowModal())
	{
		wxString command;
		
		command = git + _(" add");
		for(unsigned int i = 0; i < dialog.FileChoice->GetCount(); i++)
			if(dialog.FileChoice->IsChecked(i))
				command += _(" ") + dialog.FileChoice->GetString(i);
		Execute(command, _("Adding files ..."));
		
		command = git + _(" commit -m \"") + dialog.Comment->GetValue() + _("\"");
		Execute(command, _("Committing ..."));
	}
}

void GitBlocks::CommitAll(wxCommandEvent &event)
{
	CommitAllDialog dialog(Manager::Get()->GetAppWindow());
	if(dialog.ShowModal() == wxID_OK)
	{
		wxString command;
		cbProject *project = Manager::Get()->GetProjectManager()->GetActiveProject();
		
		command = git + _(" add");
		for(unsigned int i=0;i<project->GetFilesCount();i++)
			command += _(" ") + project->GetFile(i)->relativeFilename;
		Execute(command, _("Adding files ..."));
		
		command = git + _(" commit -m \"") + dialog.Comment->GetValue() + _("\"");
		Execute(command, _("Committing ..."));
	}
}

void GitBlocks::Push(wxCommandEvent &event)
{
#ifdef __WXMSW__ // Fucking hipster Windows needs some extra code
	wxString command = _("cmd.exe /C \"") + git + _(" push origin master\"");
#else
	wxString command = _("xterm -e \"") + git + _(" push origin HEAD\"");
#endif
	Execute(command, _("Pushing HEAD to origin ..."));
}

void GitBlocks::Pull(wxCommandEvent &event)
{
#ifdef __WXMSW__ // Fucking hipster Windows needs some extra code
	wxString command = _("cmd.exe /C \"") + git + _(" pull origin\"");
#else
	wxString command = _("xterm -e \"") + git + _(" pull origin\"");
#endif
	Execute(command, _("Pulling from origin ..."));
}

void GitBlocks::Fetch(wxCommandEvent &event)
{
#ifdef __WXMSW__ // Fucking hipster Windows needs some extra code
	wxString command = _("cmd.exe /C \"") + git + _(" fetch origin\"");
#else
	wxString command = _("xterm -e \"") + git + _(" fetch origin\"");
#endif
	Execute(command, _("Fetching from origin ..."));
}

void GitBlocks::NewBranch(wxCommandEvent &event)
{
	NewBranchDialog dialog(Manager::Get()->GetAppWindow());
	if(dialog.ShowModal() == wxID_OK)
	{
		Execute(git + _(" branch ") + dialog.Name->GetValue(), _("Adding new branch ..."));
		if(dialog.Switch->IsChecked())
			Execute(git + _(" checkout ") + dialog.Name->GetValue(), _("Switching to new branch ..."));
	}
}

void GitBlocks::SwitchBranch(wxCommandEvent &event)
{
	SwitchBranchDialog dialog(Manager::Get()->GetAppWindow());
	if(dialog.ShowModal() == wxID_OK)
		Execute(git + _(" checkout ") + dialog.Name->GetValue(), _("Switching branch ..."));
}

void GitBlocks::DiffToIndex(wxCommandEvent &event)
{
	wxString command = git + _(" diff");
	wxString comment = _("Fetching diff to index ...");
	wxString dir = Manager::Get()->GetProjectManager()->GetActiveProject()->GetBasePath();
	
	wxArrayString output;
	
	Manager::Get()->GetLogManager()->Log(comment, logSlot);
	Manager::Get()->GetLogManager()->Log(command, logSlot);
	
	wxString ocwd = wxGetCwd();
	wxSetWorkingDirectory(dir);
	wxExecute(command, output);
	wxSetWorkingDirectory(ocwd);
	
	cbEditor *editor = Manager::Get()->GetEditorManager()->New(_("GitBlocks: Diff to index"));
	cbStyledTextCtrl *ctrl = editor->GetControl();
	
	for(unsigned int i=0;i<output.size();i++)
		ctrl->AppendText(output[i] + _("\n"));
	
	editor->SetModified(false);
}

void GitBlocks::Log(wxCommandEvent &event)
{
	wxString command = git + _(" log --pretty=format:%h%x09%an%x09%ad%x09%s");
	wxString comment = _("Fetching log ...");
	wxString dir = Manager::Get()->GetProjectManager()->GetActiveProject()->GetBasePath();
	
	wxArrayString output;
	
	Manager::Get()->GetLogManager()->Log(comment, logSlot);
	Manager::Get()->GetLogManager()->Log(command, logSlot);
	
	wxString ocwd = wxGetCwd();
	wxSetWorkingDirectory(dir);
	wxExecute(command, output);
	wxSetWorkingDirectory(ocwd);
	
	cbEditor *editor = Manager::Get()->GetEditorManager()->New(_("GitBlocks: Log"));
	cbStyledTextCtrl *ctrl = editor->GetControl();
	
	for(unsigned int i=0;i<output.size();i++)
		ctrl->AppendText(output[i] + _("\n"));
	
	editor->SetModified(false);
}

void GitBlocks::Status(wxCommandEvent &event)
{
	wxString command = git + _(" status");
	wxString comment = _("Fetching status ...");
	wxString dir = Manager::Get()->GetProjectManager()->GetActiveProject()->GetBasePath();
	
	wxArrayString output;
	
	Manager::Get()->GetLogManager()->Log(comment, logSlot);
	Manager::Get()->GetLogManager()->Log(command, logSlot);
	
	wxString ocwd = wxGetCwd();
	wxSetWorkingDirectory(dir);
	wxExecute(command, output);
	wxSetWorkingDirectory(ocwd);
	
	cbEditor *editor = Manager::Get()->GetEditorManager()->New(_("GitBlocks: Status"));
	cbStyledTextCtrl *ctrl = editor->GetControl();
	
	for(unsigned int i=0;i<output.size();i++)
		ctrl->AppendText(output[i] + _("\n"));
	
	editor->SetModified(false);
}
