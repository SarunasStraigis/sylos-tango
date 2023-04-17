
#ifndef LaserControllerClass_H
#define LaserControllerClass_H

#include <tango/tango.h>
#include <LaserController.h>


namespace LaserController_ns
{

class dummyAttrib: public Tango::Attr
{
  public:
    dummyAttrib():Attr("dummy", Tango::DEV_DOUBLE, Tango::READ_WRITE) {}
    ~dummyAttrib() {}

    virtual void read(Tango::DeviceImpl *dev,Tango::Attribute &att)
    {
      (static_cast<LaserController *>(dev))->read_dummy(att);
    }
    virtual void write(Tango::DeviceImpl *dev,Tango::WAttribute &att)
    {
      (static_cast<LaserController *>(dev))->write_dummy(att);
    }
    virtual bool is_allowed(Tango::DeviceImpl *dev,Tango::AttReqType ty)
    {
      return (static_cast<LaserController *>(dev))->is_dummy_allowed(ty);
    }
};

//  Command dummyCommand1 class definition
class dummyCommand1Class : public Tango::Command
{
  public:
    dummyCommand1Class(const char   *name,
              Tango::CmdArgType in,
              Tango::CmdArgType out,
              const char        *in_desc,
              const char        *out_desc,
              Tango::DispLevel  level)
      :Command(name,in,out,in_desc,out_desc, level) {}

    dummyCommand1Class(const char   *name,
              Tango::CmdArgType in,
              Tango::CmdArgType out)
      :Command(name,in,out) {}

    ~dummyCommand1Class() {}

    virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
    virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
    {
      return (static_cast<LaserController*>(dev))->is_dummyCommand1_allowed(any);
    }
};


//  Command dummyCommand2 class definition
class dummyCommand2Class : public Tango::Command
{
  public:
    dummyCommand2Class(const char   *name,
              Tango::CmdArgType in,
              Tango::CmdArgType out,
              const char        *in_desc,
              const char        *out_desc,
              Tango::DispLevel  level)
      :Command(name,in,out,in_desc,out_desc, level) {}

    dummyCommand2Class(const char   *name,
              Tango::CmdArgType in,
              Tango::CmdArgType out)
      :Command(name,in,out) {}

    ~dummyCommand2Class() {}

    virtual CORBA::Any *execute (Tango::DeviceImpl *dev, const CORBA::Any &any);
    virtual bool is_allowed (Tango::DeviceImpl *dev, const CORBA::Any &any)
    {
      return (static_cast<LaserController*>(dev))->is_dummyCommand2_allowed(any);
    }
};


#ifdef _TG_WINDOWS_
class __declspec(dllexport)  LaserControllerClass : public Tango::DeviceClass
#else
class LaserControllerClass : public Tango::DeviceClass
#endif
{
  public:
    //  write class properties data members
    Tango::DbData cl_prop;
    Tango::DbData cl_def_prop;
    Tango::DbData dev_def_prop;

    //  Method prototypes
    static LaserControllerClass *init(const char *);
    static LaserControllerClass *instance();
    ~LaserControllerClass();
    Tango::DbDatum  get_class_property(string &);
    Tango::DbDatum  get_default_device_property(string &);
    Tango::DbDatum  get_default_class_property(string &);

  protected:
    LaserControllerClass(string &);
    static LaserControllerClass *_instance;
    void command_factory();
    void attribute_factory(vector<Tango::Attr *> &);
    void write_class_property();
    void set_default_property();
    void get_class_property();
    string get_cvstag();
    string get_cvsroot();

  private:
    void device_factory(const Tango::DevVarStringArray *);
};

} //  End of namespace

#endif   // LaserController_H
