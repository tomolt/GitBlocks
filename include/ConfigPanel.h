#ifndef CONFIGPANEL_H
#define CONFIGPANEL_H

#include <configurationpanel.h>

#include "Common.h"
#include "GitBlocks.h"

class ConfigPanel : public cbConfigurationPanel
{
public:
	ConfigPanel(wxWindow *parent, GitBlocks *pgitBlocks);
	virtual ~ConfigPanel();
	
	virtual wxString GetTitle() const;
	virtual wxString GetBitmapBaseName() const;
	virtual void OnApply();
	virtual void OnCancel();
	
private:
	GitBlocks *gitBlocks;
	wxTextCtrl *gitLine;
	
	void GitBrowse(wxCommandEvent &event);
	
	DECLARE_EVENT_TABLE()
};

#endif // CONFIGPANEL_H
