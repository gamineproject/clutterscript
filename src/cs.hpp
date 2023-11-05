#include "cs_basic.hpp"
#include "cs_runtime.hpp"
/*
      /@@@  /@@@@
     /@     /@_
    //@      //"@ - Copyright Gamine 2023.
     //@@@ //@@@
      /// ////

    Possibly a fast runtime without any libraries or binaries.

    
*/
#pragma once

/* The ClutterScript engine */
namespace cs{
    using cs::newContext;
    using cs::deleteContext;
    using cs::lex;
}