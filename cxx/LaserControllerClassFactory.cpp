/*----- PROTECTED REGION ID(LaserController::ClassFactory.cpp) ENABLED START -----*/
static const char *RcsId = "$Id:  $";

#include <tango/tango.h>
#include <LaserControllerClass.h>


void Tango::DServer::class_factory()
{
  add_class(LaserController_ns::LaserControllerClass::init("LaserController"));
}
