/*
 * HMolPolMagFieldQuadrupole.hh
 *
 *  Created on: Jul 14, 2016
 *      Author: wdconinc
 */

#ifndef INCLUDE_HMOLPOLMAGFIELDQUADRUPOLE_HH_
#define INCLUDE_HMOLPOLMAGFIELDQUADRUPOLE_HH_

#include <G4QuadrupoleMagField.hh>
#include <G4UnitsTable.hh>

#include "HMolPolMagField.hh"

class HMolPolMagFieldQuadrupole: public HMolPolMagField {

  public:

    // Constructor with logical volume and gdml settings
    HMolPolMagFieldQuadrupole(G4LogicalVolume* volume, std::map<G4String,G4String> gdml)
    : HMolPolMagField(volume,gdml),
      fGradient(0.0),fPoleTipField(0.0),fApertureRadius(0.0)
    {
      // If no magnetic field gradient tag is found, just leave at zero field
      try {
        // Read the gradient value from the input string
        if (gdml.count("MagFieldGradient"))
          std::stringstream(gdml["MagFieldGradient"]) >> fGradient;
        else
          G4cout << "    Warning: Specify MagFieldGradient in units of Tesla/m" << G4endl;
        // Assume this is in units of Tesla/m
        fGradient *= CLHEP::tesla / CLHEP::m;
        G4cout << "    Field gradient " << fGradient / (CLHEP::tesla / CLHEP::m) << " T/m" << G4endl;
      } catch (const std::exception& ex) {
        G4cout << "    Could not parse " << gdml["MagFieldGradient"] << G4endl;
      }

      // If no pole tip magnetic field tag is found, just leave at zero
      try {
        // Read the gradient value from the input string
        if (gdml.count("MagFieldPoleTipField"))
          std::stringstream(gdml["MagFieldPoleTipField"]) >> fPoleTipField;
        else
          G4cout << "    Warning: Specify MagFieldPoleTipField in units of Tesla" << G4endl;
        // Assume this is in units of Tesla
        fPoleTipField *= CLHEP::tesla;
        G4cout << "    Field gradient " << fPoleTipField / CLHEP::tesla << " T" << G4endl;
      } catch (const std::exception& ex) {
        G4cout << "    Could not parse " << gdml["MagFieldPoleTipField"] << G4endl;
      }

      // If no aperture radius tag is found, just leave at zero
      try {
        // Read the gradient value from the input string
        if (gdml.count("MagFieldApertureRadius"))
          std::stringstream(gdml["MagFieldApertureRadius"]) >> fApertureRadius;
        else
          G4cout << "    Warning: Specify MagFieldApertureRadius in units of m" << G4endl;
        // Assume this is in units of m
        fApertureRadius *= CLHEP::m;
        G4cout << "    Aperture radius " << fApertureRadius / CLHEP::m << " m" << G4endl;
      } catch (const std::exception& ex) {
        G4cout << "    Could not parse " << gdml["MagFieldApertureRadius"] << G4endl;
      }

      // Create field
      CreateField();

      // Create print command
      fMessenger->DeclareMethod("print",&HMolPolMagFieldQuadrupole::Print,
          "Print information on the magnetic field " + volume->GetName());

      // Create field gradient commands
      new G4UnitDefinition("kilogauss/m", "kilogauss/m", "Gradient", CLHEP::kilogauss/CLHEP::m);
      new G4UnitDefinition("gauss/m", "gauss/m", "Gradient", CLHEP::gauss/CLHEP::m);
      new G4UnitDefinition("tesla/m", "tesla/m", "Gradient", CLHEP::tesla/CLHEP::m);
      fMessenger->DeclareMethodWithUnit("setGradient","tesla/m",&HMolPolMagFieldQuadrupole::SetGradient,
          "Set the gradient of quadrupole magnetic field " + volume->GetName());
      fMessenger->DeclareMethodWithUnit("setPoleTipField","tesla",&HMolPolMagFieldQuadrupole::SetPoleTipField,
          "Set the pole tip field of quadrupole magnetic field " + volume->GetName());
      fMessenger->DeclareMethodWithUnit("setApertureRadius","m",&HMolPolMagFieldQuadrupole::SetApertureRadius,
          "Set the aperture radius of quadrupole magnetic field " + volume->GetName());
    }

    /// Destructor for the HMolPolMagFieldQuadrupole
    virtual ~HMolPolMagFieldQuadrupole() {
      // Delete existing field
      if (fField) delete fField;
    };

    /// Print info
    void Print() {
      G4cout << "Quadrupole magnetic field " << fVolume->GetName() << G4endl;
      G4cout << "Field gradient " << fGradient / (CLHEP::tesla/CLHEP::m) << " T/m"<< G4endl;
      HMolPolMagField::Print();
    }

    // Change the gradient and recreate the field
    void SetGradient(const G4double gradient) { fGradient = gradient; CreateField(); }
    void SetPoleTipField(const G4double field) { fPoleTipField = field; CreateField(); }
    void SetApertureRadius(const G4double radius) { fApertureRadius = radius; CreateField(); }

  private:

    // Create or recreate the field
    void CreateField() {
      // Override gradient if specified as pole tip field and aperture radius
      if (fPoleTipField * fApertureRadius != 0.0) {
        fGradient = fPoleTipField / fApertureRadius;
      }

      // Delete existing field
      if (fField) delete fField;

      // Create uniform magnetic field with the given field vector
      fField = new G4QuadrupoleMagField(fGradient);
    }

  private:

    // Field gradient
    G4double fGradient;

    // Pole tip field
    G4double fPoleTipField;
    // Aperture radius
    G4double fApertureRadius;

};

#endif /* INCLUDE_HMOLPOLMAGFIELDQUADRUPOLE_HH_ */
