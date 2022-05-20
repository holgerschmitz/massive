#include "species.hpp"

void Species::initParameters(schnek::BlockParameters &blockPars) {
  blockPars.addParameter("charge", &charge, 1.0);
  blockPars.addParameter("mass", &mass, 1.0);

  blockPars.addArrayParameter("v_lo_", vDomain.getLo());
  blockPars.addArrayParameter("v_hi_", vDomain.getHi());
}