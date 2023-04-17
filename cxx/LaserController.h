

#ifndef LaserController_H
#define LaserController_H

#include <tango/tango.h>

namespace LaserController_ns
{

class LaserController : public TANGO_BASE_CLASS
{
  public:
    Tango::DevDouble  *attr_dummy_read;
    LaserController(Tango::DeviceClass *cl,string &s);
    LaserController(Tango::DeviceClass *cl,const char *s);
    LaserController(Tango::DeviceClass *cl,const char *s,const char *d);
    ~LaserController()
    {
      delete_device();
    };

    void delete_device();
    virtual void init_device();
    virtual void always_executed_hook();

  public:
    virtual void read_attr_hardware(vector<long> &attr_list);
    virtual void write_attr_hardware(vector<long> &attr_list);
    virtual void read_dummy(Tango::Attribute &attr);
    virtual void write_dummy(Tango::WAttribute &attr);
    virtual bool is_dummy_allowed(Tango::AttReqType type);
    void add_dynamic_attributes();

  public:
    virtual void dummyCommand1();
    virtual void dummyCommand2(Tango::DevDouble argin);
    virtual bool is_dummyCommand1_allowed(const CORBA::Any &any);
    virtual bool is_dummyCommand2_allowed(const CORBA::Any &any);
    void add_dynamic_commands();
};

} //  End of namespace

#endif   // LaserController_H
