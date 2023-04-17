#include <tango/tango.h>

// Check if crash reporting is used.
#if defined(ENABLE_CRASH_REPORT)
#  include <crashreporting/crash_report.h>
#else
#  define DECLARE_CRASH_HANDLER
#  define INSTALL_CRASH_HANDLER
#endif

DECLARE_CRASH_HANDLER;

int main(int argc,char *argv[])
{
  INSTALL_CRASH_HANDLER

  try
  {
    Tango::Util *tg = Tango::Util::init(argc,argv);
    tg->server_init(false);
    cout << "Ready to accept request" << endl;
    tg->server_run();
  }
  catch (bad_alloc &)
  {
    cout << "Can't allocate memory to store device object !!!" << endl;
    cout << "Exiting" << endl;
  }
  catch (CORBA::Exception &e)
  {
    Tango::Except::print_exception(e);

    cout << "Received a CORBA_Exception" << endl;
    cout << "Exiting" << endl;
  }

  Tango::Util::instance()->server_cleanup();

  return(0);
}
