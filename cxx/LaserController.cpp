
static const char *RcsId = "$Id:  $";


#include <LaserController.h>
#include <LaserControllerClass.h>


namespace LaserController_ns
{
//--------------------------------------------------------
LaserController::LaserController(Tango::DeviceClass *cl, string &s)
  : TANGO_BASE_CLASS(cl, s.c_str())
{
  init_device();
}
//--------------------------------------------------------
LaserController::LaserController(Tango::DeviceClass *cl, const char *s)
  : TANGO_BASE_CLASS(cl, s)
{
  init_device();
}
//--------------------------------------------------------
LaserController::LaserController(Tango::DeviceClass *cl, const char *s, const char *d)
  : TANGO_BASE_CLASS(cl, s, d)
{
  
  init_device();
}

//--------------------------------------------------------
void LaserController::delete_device()
{
  DEBUG_STREAM << "LaserController::delete_device() " << device_name << endl;
  
  delete[] attr_dummy_read;
}
//--------------------------------------------------------
void LaserController::init_device()
{
  DEBUG_STREAM << "LaserController::init_device() create device " << device_name << endl;

  attr_dummy_read = new Tango::DevDouble[1];
}
//--------------------------------------------------------
void LaserController::always_executed_hook()
{
  INFO_STREAM << "LaserController::always_executed_hook()  " << device_name << endl;
}
//--------------------------------------------------------
void LaserController::read_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
  DEBUG_STREAM << "LaserController::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
}
//--------------------------------------------------------
void LaserController::write_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
  DEBUG_STREAM << "LaserController::write_attr_hardware(vector<long> &attr_list) entering... " << endl;
}
//--------------------------------------------------------
void LaserController::read_dummy(Tango::Attribute &attr)
{
  DEBUG_STREAM << "LaserController::read_dummy(Tango::Attribute &attr) entering... " << endl;
  
  //  Set the attribute value
  attr.set_value(attr_dummy_read);
}
//--------------------------------------------------------
void LaserController::write_dummy(Tango::WAttribute &attr)
{
  DEBUG_STREAM << "LaserController::write_dummy(Tango::WAttribute &attr) entering... " << endl;
  //  Retrieve write value
  Tango::DevDouble  w_val;
  attr.get_write_value(w_val);
}
//--------------------------------------------------------
void LaserController::add_dynamic_attributes()
{
}
//--------------------------------------------------------
void LaserController::dummyCommand1()
{
}
//--------------------------------------------------------
void LaserController::dummyCommand2(Tango::DevDouble argin)
{
}
} //  namespace
//--------------------------------------------------------

