//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// TETActionInitialization.cc
// 
// Author: Haegin Han
// Reference: ICRP Publication 145. Ann. ICRP 49(3), 2020.
// Geant4 Contributors: J. Allison and S. Guatelli
//

#include "TETActionInitialization.hh"

//#include "doiPETActionInitialization.hh"
#include "doiPETRunAction.hh"
#include "doiPETEventAction.hh"
#include "doiPETPrimaryGeneratorAction.hh"
#include "doiPETSteppingAction.hh"

TETActionInitialization::TETActionInitialization(TETModelImport* _tetData, G4String _output, doiPETAnalysis* analysisMan)
 : G4VUserActionInitialization(), fTetData(_tetData), fOutput(_output)
{
    	analysis = analysisMan;
}

void TETActionInitialization::BuildForMaster() const
{
 SetUserAction(new TETRunAction(fTetData, fOutput));

#ifdef ANALYSIS_USE
	 doiPETRunAction* runAction = new doiPETRunAction(analysis);
#else
 	doiPETRunAction* runAction = new doiPETRunAction();
#endif
	SetUserAction(runAction);
}

void TETActionInitialization::Build() const
{
	// initialise UserAction classes
	SetUserAction(new TETPrimaryGeneratorAction());

 	doiPETPrimaryGeneratorAction* primary = new doiPETPrimaryGeneratorAction();
	SetUserAction(primary);

	SetUserAction(new TETRunAction(fTetData, fOutput));

#ifdef ANALYSIS_USE
	 doiPETRunAction* runAction = new doiPETRunAction(analysis);
#else
 	doiPETRunAction* runAction = new doiPETRunAction();
#endif
	SetUserAction(runAction);

	SetUserAction(new doiPETEventAction());

	SetUserAction(new TETSteppingAction());
	SetUserAction(new doiPETSteppingAction());
}  






//doiPETActionInitialization::~doiPETActionInitialization()
//{}

