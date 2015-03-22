# ---------- Declarations ---------- #

cb_plugin_lib_LTLIBRARIES = GitBlocks.la
cb_plugin_data_DATA = GitBlocks.zip
CLEANFILES = GitBlocks.zip


# ---------- GitBlocks.so ---------- #

GitBlocks_la_SOURCES = src/CloneDialog.cpp \
						src/CommitAllDialog.cpp \
						src/CommitDialog.cpp \
						src/ConfigPanel.cpp \
						src/GitBlocks.cpp \
						src/NewBranchDialog.cpp \
						src/SwitchBranchDialog.cpp

noinst_HEADERS = include/CloneDialog.h \
					include/CommitAllDialog.h \
					include/CommitDialog.h \
					include/ConfigPanel.h \
					include/GitBlocks.h \
					include/NewBranchDialog.h \
					incldue/SwitchBranchDialog.h

GitBlocks_la_CPPFLAGS = -ansi $(WX_CFLAGS) $(CB_CFLAGS) -Iinclude

GitBlocks_la_LDFLAGS = -shared -module -avoid-version -no-undefined $(WX_LIBS) $(CB_LIBS)

# ---------- GitBlocks.zip ---------- #

GitBlocks_zip_RESOURCES = manifest.xml

GitBlocks.zip: $(GitBlocks_zip_RESOURCES)
	PWD=`pwd` cd $(srcdir) && zip -R $(PWD)/GitBlocks.zip manifest.xml
