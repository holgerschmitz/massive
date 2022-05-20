#ifndef MASSIVE_SPECIES_SPECIES_HPP
#define MASSIVE_SPECIES_SPECIES_HPP

#include <schnek/variables.hpp>

#include "../types.hpp"

/** 
 * @brief Base class for a particle species
 * 
 * Species contains the fundamental properties of a particle species from the
 * setup file. It needs to be extended to store the distribution functions \f$f\f$ 
 * and implement the algorithm to advance \f$f\f$.
 */
class Species : public schnek::Block {
  protected:
    /**
     * @brief single particle charge
     */ 
    double charge;

    /**
     * @brief particle mass
     */
    double mass;

    /**
     * @brief the physocal extent of the velocity grid
     */
    VDomain vDomain;

    /**
     * @brief total density, used to enforce density conservation
     */
    double densityGoal;

  protected:
    void initParameters(schnek::BlockParameters &blockPars) override;
  public:
    virtual void advance(double dt) = 0;
};

typedef boost::shared_ptr<Species> pSpecies;

#endif // MASSIVE_SPECIES_SPECIES_HPP