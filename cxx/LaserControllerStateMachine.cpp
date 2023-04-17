/*----- PROTECTED REGION ID(LaserControllerStateMachine.cpp) ENABLED START -----*/
static const char *RcsId = "$Id:  $";


#include <LaserController.h>



namespace LaserController_ns
{

//--------------------------------------------------------
bool LaserController::is_dummy_allowed(TANGO_UNUSED(Tango::AttReqType type))
{
 
  return true;
}
//--------------------------------------------------------
bool LaserController::is_dummyCommand1_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
  return true;
}
//--------------------------------------------------------
bool LaserController::is_dummyCommand2_allowed(TANGO_UNUSED(const CORBA::Any &any))
{
  return true;
}

} //  End of namespace
