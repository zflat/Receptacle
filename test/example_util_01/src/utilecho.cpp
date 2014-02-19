#include "utilecho.h"

QString UtilEcho::name() const{
  return tr("Util echo");
}


QString UtilEcho::description() const{
 return tr("Example printing text output");
}


QString UtilEcho::command() const{
  return tr("echo01");
}

void UtilEcho::run_util(){
}




