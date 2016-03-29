/********************************************
 * \author <b>Programmer:<\b> Valerie Gray
 * \author <b>Assisted By:<\b> Wouter Deconinck
 *
 * \brief <b>Purpose:</b> This is header file which for the primary action generator.
 * Or the generator of the primary particle
 *
 * \date <b>Date:</b> 06-25-2013
 * \date <b>Modified:</b> 07-14-2015
 *
 * \note <b>Entry Conditions:</b> none
 *
********************************************/

#ifndef HMolPolPrimaryGeneratorAction_h
#define HMolPolPrimaryGeneratorAction_h 1

//Geant4 includes
#include <G4ParticleTable.hh>
#include <G4VUserPrimaryGeneratorAction.hh>

// HMolPol classes
class HMolPolAnalysis;

//Geant4 classes
class G4ParticleGun;

class HMolPolPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{

  public:
    //create the constructor and destructor for the primary particle generator
    HMolPolPrimaryGeneratorAction(HMolPolAnalysis* AN); ///< The constructor
    // for the HMolPolPrimaryGeneratorAction class - it gets passed the
    // HMolPolAnalysis class so that the histogram will get filled
    virtual ~HMolPolPrimaryGeneratorAction();   ///< The destructor
    // for the HMolPolPrimaryGeneratorAction class

    //function to generate the primary electrons
    void GeneratePrimaries(G4Event* anEvent);  ///< function to generate
    // primary electrons

    ///<  Set Raster size
    void SetRasterX(const G4double& XRaster) { fRasterX = XRaster; }  ///< set
      /// the XRaster size of beam
    void SetRasterY(const G4double& YRaster) { fRasterY = YRaster; }  ///< set
    /// the YRaster size of beam
    void SetBeamE(const G4double& BeamE) { fBeamE = BeamE; }   ///< set
    /// the Energy of the beam

    ///<  Set Theta CM range size
    void SetThetaComMax(const G4double& ThetaComMax) { fTheta_com_max = ThetaComMax; }  ///< set
      /// the max Theta CM value
    void SetThetaComMin(const G4double& ThetaComMin) { fTheta_com_min = ThetaComMin; }  ///< set
    /// the min Theta CM value

    ///<  Set phi CM range size
    void SetPhiComMax(const G4double& PhiComMax) { fPhi_com_max = PhiComMax; }  ///< set
      /// the max Phi CM value
    void SetPhiComMin(const G4double& PhiComMin) { fPhi_com_min = PhiComMin; }  ///< set
    /// the min Phi CM value

  private:

    HMolPolAnalysis* fAnalysis;  ///< the analysis class

    G4double fRasterX;  ///< the total raster size in X
    G4double fRasterY;  ///< the total raser size in Y
    G4double fBeamE;    ///< the incoming electron beam energy

    // Center of mass angles to generate particles between
    G4double fTheta_com_min; /// < this is the minimum Theta that electrons
    /// will be generated over
    G4double fTheta_com_max; /// < this is the minimum Theta that electrons
    /// will be generated over
    G4double fPhi_com_min; /// < this is the minimum Theta that electrons
    /// will be generated over
    G4double fPhi_com_max; /// < this is the minimum Theta that electrons
    /// will be generated over

    //the primary generation of the primary electrons
    /// \todo why does doxygen not want this documented?? and are these right?
    G4ParticleGun* fParticleGun; ///< the ParticleGun class
};

#endif
