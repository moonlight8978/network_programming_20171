#include "stdafx.h"

void define_routes() {
  ROUTES[0].path = "/idols";
  ROUTES[0].get = true;
  ROUTES[0].post = true;

  ROUTES[1].path = "/";
  ROUTES[1].get = true;


  TOTAL_ROUTES = 2;
}
