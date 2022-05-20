#ifndef MASSIVE_MASSIVE_HPP_
#define MASSIVE_MASSIVE_HPP_


#include <schnek/grid.hpp>
#include <schnek/variables.hpp>
#include <schnek/diagnostic/diagnostic.hpp>
#include <schnek/diagnostic/hdfdiagnostic.hpp>

#include <boost/ref.hpp>

#include <set>

#include "../huerto/simulation/simulation_context.hpp"
#include "types.hpp"
#include "../huerto/constants.hpp"

class Species;

class Massive: public schnek::Block, 
               public schnek::BlockContainer<Species>, 
               public SimulationContext
{
  private:
    double cflFactor;
  protected:
    void initParameters(schnek::BlockParameters &blockPars);
    void registerData();
  public:
    Massive();
    void init();
    void execute();
};

#endif /* MASSIVE_MASSIVE_HPP_ */
