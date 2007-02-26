kritarcdir = $(kde_datadir)/krita/kritaplugins

kde_services_DATA = kritaImageComplete.desktop

SUBDIRS = Poisson

INCLUDES  =  -I$(srcdir)/../../../sdk \
	-I$(srcdir)/../../../core \
	-I$(srcdir)/../../../kritacolor/ \
	-I$(srcdir)/../../../ui \
	$(KOFFICE_INCLUDES) \
	$(all_includes)

kritaImageComplete_la_SOURCES = ImageComplete.cc

kde_module_LTLIBRARIES = kritaImageComplete.la
noinst_HEADERS = ImageComplete.h

kritaImageComplete_la_LDFLAGS = $(all_libraries) -module $(KDE_PLUGIN)
kritaImageComplete_la_LIBADD =  -lkritacommon -LPoisson -lPoisson

kritaImageComplete_la_METASOURCES = AUTO
