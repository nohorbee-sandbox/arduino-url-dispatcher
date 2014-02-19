#ifndef RESOURCE_H
#define RESOURCE_H

#include <Arduino.h>

  //typedef void Handler(WebServer &server, ConnectionType type,
//                       char *url_tail, bool tail_complete);
   typedef void Handler(String param1, String param2);

struct Resource
  {
    char * uri;
    Handler *handler;
  };


 #endif