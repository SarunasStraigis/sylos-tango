/*----- PROTECTED REGION ID(LaserControllerClass.cpp) ENABLED START -----*/
static const char *RcsId      = "$Id:  $";
static const char *TagName    = "$Name:  $";
static const char *CvsPath    = "$Source:  $";
static const char *SvnPath    = "$HeadURL:  $";
static const char *HttpServer = "http://www.esrf.eu/computing/cs/tango/tango_doc/ds_doc/";


#include <LaserControllerClass.h>

extern "C" {
#ifdef _TG_WINDOWS_

  __declspec(dllexport)

#endif

  Tango::DeviceClass *_create_LaserController_class(const char *name)
  {
    return LaserController_ns::LaserControllerClass::init(name);
  }
}

namespace LaserController_ns
{

LaserControllerClass *LaserControllerClass::_instance = NULL;

//--------------------------------------------------------
CORBA::Any *dummyCommand1Class::execute(Tango::DeviceImpl *device, const CORBA::Any &in_any)
{
  cout2 << "dummyCommand1Class::execute(): arrived" << endl;
  ((static_cast<LaserController *>(device))->dummyCommand1());
  return new CORBA::Any();
}
//--------------------------------------------------------
CORBA::Any *dummyCommand2Class::execute(Tango::DeviceImpl *device, const CORBA::Any &in_any)
{
  cout2 << "dummyCommand1Class::execute(): arrived" << endl;
  Tango::DevDouble argin;
  extract(in_any, argin);
  ((static_cast<LaserController *>(device))->dummyCommand2(argin));
  return new CORBA::Any();
}
//--------------------------------------------------------
LaserControllerClass::LaserControllerClass(string &s):Tango::DeviceClass(s)
{
  cout2 << "Entering LaserControllerClass constructor" << endl;
  set_default_property();
  write_class_property();

  cout2 << "Leaving LaserControllerClass constructor" << endl;
}

//--------------------------------------------------------
LaserControllerClass::~LaserControllerClass()
{
  _instance = NULL;
}
//--------------------------------------------------------
LaserControllerClass *LaserControllerClass::init(const char *name)
{
  if (_instance == NULL)
  {
    try
    {
      string s(name);
      _instance = new LaserControllerClass(s);
    }
    catch (bad_alloc &)
    {
      throw;
    }
  }
  return _instance;
}
//--------------------------------------------------------
LaserControllerClass *LaserControllerClass::instance()
{
  if (_instance == NULL)
  {
    cerr << "Class is not initialised !!" << endl;
    exit(-1);
  }
  return _instance;
}
//--------------------------------------------------------
Tango::DbDatum LaserControllerClass::get_class_property(string &prop_name)
{
  for (unsigned int i=0 ; i<cl_prop.size() ; i++)
    if (cl_prop[i].name == prop_name)
      return cl_prop[i];
  //  if not found, returns  an empty DbDatum
  return Tango::DbDatum(prop_name);
}
//--------------------------------------------------------
Tango::DbDatum LaserControllerClass::get_default_device_property(string &prop_name)
{
  for (unsigned int i=0 ; i<dev_def_prop.size() ; i++)
    if (dev_def_prop[i].name == prop_name)
      return dev_def_prop[i];
  //  if not found, return  an empty DbDatum
  return Tango::DbDatum(prop_name);
}
//--------------------------------------------------------
Tango::DbDatum LaserControllerClass::get_default_class_property(string &prop_name)
{
  for (unsigned int i=0 ; i<cl_def_prop.size() ; i++)
    if (cl_def_prop[i].name == prop_name)
      return cl_def_prop[i];
  //  if not found, return  an empty DbDatum
  return Tango::DbDatum(prop_name);
}
//--------------------------------------------------------
void LaserControllerClass::set_default_property()
{
  string  prop_name;
  string  prop_desc;
  string  prop_def;
  vector<string>  vect_data;
}
//--------------------------------------------------------
void LaserControllerClass::write_class_property()
{
}
//--------------------------------------------------------
void LaserControllerClass::device_factory(const Tango::DevVarStringArray *devlist_ptr)
{
//  This class is not concrete and cannot implement devices
}
//--------------------------------------------------------
void LaserControllerClass::attribute_factory(vector<Tango::Attr *> &att_list)
{
  dummyAttrib  *dummy = new dummyAttrib();
  Tango::UserDefaultAttrProp  dummy_prop;
  dummy_prop.set_label("Dummy");
  dummy->set_default_properties(dummy_prop);
  dummy->set_polling_period(3000);
  dummy->set_disp_level(Tango::OPERATOR);
  att_list.push_back(dummy);
}
//--------------------------------------------------------
void LaserControllerClass::command_factory()
{
}
} //  namespace
