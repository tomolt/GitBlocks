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
#include "CredentialsDialog.h"
#include "RemoveDialog.h"
#include "NewBranchDialog.h"
#include "SwitchBranchDialog.h"

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
	// Make sure our resources are available.
	if(!Manager::LoadResource(_T("GitBlocks.zip")))
	{
		NotifyMissingFile(_T("GitBlocks.zip"));
	}
}

// destructor
GitBlocks::~GitBlocks()
{
}

void GitBlocks::OnAttach()
{
	Logger *gitBlocksLogger = new TextCtrlLogger();
	logSlot = Manager::Get()->GetLogManager()->SetLog(gitBlocksLogger);
	Manager::Get()->GetLogManager()->Slot(logSlot).title = _T("GitBlocks");
	CodeBlocksLogEvent evtAdd1(cbEVT_ADD_LOG_WINDOW, gitBlocksLogger, Manager::Get()->GetLogManager()->Slot(logSlot).title);
	Manager::Get()->ProcessEvent(evtAdd1);
	
	git_libgit2_init();
}

void GitBlocks::OnRelease(bool appShutDown)
{
	git_libgit2_shutdown();
	
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
	RegisterFunction(wxCommandEventHandler(GitBlocks::Remove), _("Remove file"));
	menu->AppendSeparator();
	RegisterFunction(wxCommandEventHandler(GitBlocks::NewBranch), _("Add new branch"));
	RegisterFunction(wxCommandEventHandler(GitBlocks::SwitchBranch), _("Switch branch"));
	menu->AppendSeparator();
	RegisterFunction(wxCommandEventHandler(GitBlocks::DiffToIndex), _("Diff to index"));
	RegisterFunction(wxCommandEventHandler(GitBlocks::Log), _("Show log"));
	RegisterFunction(wxCommandEventHandler(GitBlocks::Status), _("Show status"));
	
	menuBar->Insert(menuBar->FindMenu(_("&Tools")) + 1, menu, wxT("&GitBlocks"));
}

wxString GitBlocks::GetCPD()
{
	return Manager::Get()->GetProjectManager()->GetActiveProject()->GetBasePath();
}

int AcquireCredentials(git_cred **cred, const char *url, const char *username_from_url, unsigned int allowed_types, void *payload)
{
	if(allowed_types & GIT_CREDTYPE_USERPASS_PLAINTEXT)
	{
		CredentialsDialog dialog(Manager::Get()->GetAppWindow());
		if(dialog.ShowModal() == wxID_OK)
		{
			git_cred_userpass_plaintext_new(cred, dialog.Username->GetValue().ToUTF8().data(), dialog.Password->GetValue().ToUTF8().data());
			return 0;
		}
		else
			return 1;
	}
	else
		return -1;
}

wxArrayString GitBlocks::ListBranches()
{
	wxArrayString output;
	// Currently broken.
	return output;
}

void GitBlocks::Init(wxCommandEvent &event)
{
	git_repository *repo = NULL;
	git_repository_init(&repo, GetCPD().ToUTF8().data(), 0);
	repos.insert(std::pair<wxString, git_repository*>(GetCPD(), repo));
}

void GitBlocks::Clone(wxCommandEvent &event)
{
	CloneDialog dialog(Manager::Get()->GetAppWindow());
	if(dialog.ShowModal() == wxID_OK)
	{
		git_repository *repo = NULL;
		git_clone_options options = GIT_CLONE_OPTIONS_INIT;
		options.remote_callbacks.credentials = AcquireCredentials;
		git_clone(&repo, dialog.Origin->GetValue().ToUTF8().data(), dialog.Directory->GetValue().ToUTF8().data(), &options);
		
		wxFileDialog pdialog(Manager::Get()->GetAppWindow(), _("Open cloned project ..."), dialog.Directory->GetValue(), wxEmptyString, _("*.cbp;*.workspace"), wxFD_OPEN);
		if(pdialog.ShowModal() == wxID_OK)
		{
			if(pdialog.GetPath().EndsWith(_(".cbp")))
			{
				Manager::Get()->GetProjectManager()->LoadProject(pdialog.GetPath(), true);
			}
			else if(pdialog.GetPath().EndsWith(_(".workspace")))
			{
				Manager::Get()->GetProjectManager()->LoadWorkspace(pdialog.GetPath());
			}
		}
	}
}

void GitBlocks::Destroy(wxCommandEvent &event)
{
	if(wxMessageBox(_("Are you sure you want to destroy the local repository?"), _("Destroy local repository"), wxYES_NO) == wxYES)
	{
		Manager::Get()->GetLogManager()->Log(_("Destroying the local repository ..."), logSlot);
		Manager::Get()->GetLogManager()->Log(_T("<rmdir> .git"), logSlot);
		wxRmdir(wxGetCwd() + _T("/.git"));
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
		Execute(command, _("Adding files ..."));
		
		command = git + _T(" commit -m \"") + dialog.Comment->GetValue() + _T("\"");
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
		
		command = git + _T(" add");
		command += _T(" ") + project->GetFilename();
		for(unsigned int i=0;i<project->GetFilesCount();i++)
			command += _T(" ") + project->GetFile(i)->relativeFilename;
		Execute(command, _("Adding files ..."));
		
		command = git + _T(" commit -m \"") + dialog.Comment->GetValue() + _T("\"");
		Execute(command, _("Committing ..."));
	}
}

void GitBlocks::Push(wxCommandEvent &event)
{
	ExecuteInTerminal(git + _T(" push origin HEAD"), _("Pushing HEAD to origin ..."));
}

void GitBlocks::Pull(wxCommandEvent &event)
{
	ExecuteInTerminal(git + _T(" pull origin"), _("Pulling from origin ..."));
}

void GitBlocks::Fetch(wxCommandEvent &event)
{
	ExecuteInTerminal(git + _T(" fetch origin"), _("Fetching from origin ..."));
}

void GitBlocks::Remove(wxCommandEvent &event)
{
	RemoveDialog dialog(Manager::Get()->GetAppWindow());
	if(dialog.ShowModal() == wxID_OK)
	{
		wxString filename = dialog.FileChoice->GetString(dialog.FileChoice->GetCurrentSelection());
		cbProject *project = Manager::Get()->GetProjectManager()->GetActiveProject();
		ProjectFile *file = project->GetFile(dialog.FileChoice->GetCurrentSelection());
		if(file == NULL)
			return;
		project->BeginRemoveFiles();
		project->RemoveFile(file);
		project->EndRemoveFiles();
		if(filename.empty())
			return;
		Execute(git + _T(" rm ") + filename, _("Removing file ..."));
		Manager::Get()->GetProjectManager()->GetUI().RebuildTree();
	}
}

void GitBlocks::NewBranch(wxCommandEvent &event)
{
	NewBranchDialog dialog(Manager::Get()->GetAppWindow());
	if(dialog.ShowModal() == wxID_OK)
	{
		Execute(git + _T(" branch ") + dialog.Name->GetValue(), _("Adding new branch ..."));
		if(dialog.Switch->IsChecked())
			Execute(git + _T(" checkout ") + dialog.Name->GetValue(), _("Switching to new branch ..."));
	}
}

void GitBlocks::SwitchBranch(wxCommandEvent &event)
{
	SwitchBranchDialog dialog(Manager::Get()->GetAppWindow());
	
	wxArrayString branches = ListBranches();
	for(unsigned int i=0; i<branches.size(); i++)
		dialog.BranchChoice->Append(branches[i]);
	
	if(dialog.ShowModal() == wxID_OK)
		Execute(git + _T(" checkout ") + branches[dialog.BranchChoice->GetSelection()], _("Switching branch ..."));
}

void GitBlocks::DiffToIndex(wxCommandEvent &event)
{
	wxString command = git + _T(" diff");
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
		ctrl->AppendText(output[i] + _T("\n"));
	
	editor->SetModified(false);
}

void GitBlocks::Log(wxCommandEvent &event)
{
	wxString command = git + _T(" log --pretty=format:%h%x09%an%x09%ad%x09%s");
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
		ctrl->AppendText(output[i] + _T("\n"));
	
	editor->SetModified(false);
}

void GitBlocks::Status(wxCommandEvent &event)
{
	wxString command = git + _T(" status");
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
		ctrl->AppendText(output[i] + _T("\n"));
	
	editor->SetModified(false);
}
