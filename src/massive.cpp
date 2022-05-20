#include "massive.hpp"

#include "../huerto/constants.hpp"

#include <schnek/parser.hpp>
#include <schnek/tools/fieldtools.hpp>
#include <schnek/tools/literature.hpp>
#include <schnek/util/logger.hpp>

#include <boost/make_shared.hpp>
#include <boost/optional.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>

#include <mpi.h>

#include <fstream>
#include <string>
#include <unistd.h>

#include "species/species.hpp"

boost::random::mt19937 rng;

double step(double x, double x0)
{
  return (x>=x0)?1.0:0.0;
}

double stepi(double x, double x0)
{
  return (x>=x0)?0.0:1.0;
}

double box(double x, double xmin, double xmax)
{
  return ((x>=xmin)&&(x<xmax))?1.0:0.0;
}

int print(std::string label, double value)
{
  std::cout << label << ": " << value << std::endl;
  return 0;
}

Massive::Massive()
{
}

void Massive::initParameters(schnek::BlockParameters &parameters)
{
  SimulationContext::initParameters(parameters);
  initConstantParameters(parameters);

  parameters.addArrayParameter("N", gridSize, 100);
  parameters.addArrayParameter("L", size);
  parameters.addParameter("tMax", &tMax);
  parameters.addParameter("cflFactor", &cflFactor, 0.5);
}

void Massive::registerData()
{
  subdivision = std::make_shared<schnek::MPICartSubdivision<Field> >();
  subdivision->init(gridSize, 2);
}

void Massive::init()
{
  double minDx = std::numeric_limits<double>::max();
  for (std::size_t i=0; i<DIMENSION; ++i) {
    dx[i] = size[i] / gridSize[i];
    minDx = std::min(dx[i], minDx);
  }

  dt = cflFactor*minDx/clight;
}

void Massive::execute()
{

  time = 0.0;
  timeStep = 0;

  schnek::DiagnosticManager::instance().setPhysicalTime(&time);
  schnek::DiagnosticManager::instance().execute();

  while (time<=tMax)
  {
    if (subdivision->master())
      schnek::Logger::instance().out() <<"Time "<< time << " - " << dt << std::endl;

    for(pSpecies f: schnek::BlockContainer<Species>::childBlocks())
    {
      f->advance(dt);
    }

    time += dt;
    ++timeStep;
    schnek::DiagnosticManager::instance().execute();
  }

  schnek::DiagnosticManager::instance().execute();
}

int runSimulation() {
  try
  {
    schnek::BlockClasses blocks;

    blocks.registerBlock("massive").setClass<Massive>();

    blocks("multiwave").addChildren("EMFields");

    std::ifstream in("multiwave.setup");
    if (!in) throw std::string("Could not open file 'multiwave.setup'");

    schnek::Parser P("multiwave", "multiwave", blocks);
    registerCMath(P.getFunctionRegistry());

    P.getFunctionRegistry().registerFunction("step",step);
    P.getFunctionRegistry().registerFunction("stepi",stepi);
    P.getFunctionRegistry().registerFunction("box",box);
    P.getFunctionRegistry().registerFunction("print",print);

    schnek::pBlock application = P.parse(in);

    Massive &massive = dynamic_cast<Massive&>(*application);
    massive.initAll();

    if (massive.getSubdivision().master())
    {
      std::ofstream referencesText("information.tex");
      std::ofstream referencesBib("references.bib");

      schnek::LiteratureManager::instance().writeInformation(referencesText,"references.bib");
      schnek::LiteratureManager::instance().writeBibTex(referencesBib);
      referencesText.close();
      referencesBib.close();
    }

    massive.execute();
  }
  catch (schnek::ParserError &e)
  {
    std::cerr << "Parse error in " << e.getFilename() << " at line "
        << e.getLine() << ": " << e.message << std::endl;
    return -1;
  }
  catch (schnek::VariableNotInitialisedException &e)
  {
    std::cerr << "Variable was not initialised: " << e.getVarName() << std::endl;
    return -1;
  }
  catch (schnek::EvaluationException &e)
  {
    std::cerr << "Error in evaluation: " << e.getMessage() << std::endl;
    return -1;
  }
  catch (schnek::VariableNotFoundException &e)
  {
    std::cerr << "Error: " << e.getMessage() << std::endl;
    return -1;
  }
  catch (SchnekException &e)
  {
    std::cerr << "An error occured" << std::endl;
    return -1;
  }
  catch (std::string &err)
  {
    std::cerr << "FATAL ERROR: " << err << std::endl;
    return -1;
  }


  return 0;
}

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);

  int returnCode = runSimulation();
  
  MPI_Finalize();
  
  return returnCode;
}
// end of main
