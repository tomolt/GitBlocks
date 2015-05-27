# ---------- Declarations ---------- #

cb_plugin_lib_LTLIBRARIES = GitBlocks.la
cb_plugin_data_DATA = GitBlocks.zip GitBlocks.cbplugin
CLEANFILES = GitBlocks.zip GitBlocks.cbplugin


# ---------- GitBlocks.so ---------- #

GitBlocks_la_SOURCES = src/CloneDialog.cpp \
						src/CommitAllDialog.cpp \
						src/CommitDialog.cpp \
						src/GitBlocks.cpp \
						src/NewBranchDialog.cpp \
						src/RemoveDialog.cpp \
						src/SwitchBranchDialog.cpp

noinst_HEADERS = include/CloneDialog.h \
					include/CommitAllDialog.h \
					include/CommitDialog.h \
					include/GitBlocks.h \
					include/NewBranchDialog.h \
					include/RemoveDialog.h \
					include/SwitchBranchDialog.h

GitBlocks_la_CPPFLAGS = -ansi $(WX_CFLAGS) $(CB_CFLAGS) -Iinclude

GitBlocks_la_LDFLAGS = -shared -module -avoid-version -no-undefined $(WX_LIBS) $(CB_LIBS) -lgit2

# ---------- GitBlocks.zip ---------- #

GitBlocks_zip_RESOURCES = manifest.xml

GitBlocks.zip: $(GitBlocks_zip_RESOURCES)
	cd $(srcdir)
	zip -j9 GitBlocks.zip manifest.xml

# ---------- GitBlocks.cbplugin ---------- #

GitBlocks_cbplugin_RESOURCES = $(cb_plugin_lib_LTLIBRARIES) GitBlocks.zip

GitBlocks.cbplugin: $(GitBlocks_cbplugin_RESOURCES)
	cd $(srcdir)
	zip -j9 GitBlocks.cbplugin .libs/GitBlocks.so GitBlocks.zip

