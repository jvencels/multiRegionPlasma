/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "dsmcCloud.H"

#include "regionProperties.H"
#include "PtrList.H"
#include "volFields.H"
#include "typeInfo.H"
#include "IOdictionary.H"
#include "autoPtr.H"
#include "runTimeSelectionTables.H"
#include "electromagneticConstants.H"
#include "AMixedFvPatchVectorField.H"
#include "IFstream.H"
#include "graph.H"
#include "interpolateXY.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "setRootCase.H"
    #include "createTime.H"

    regionProperties rp(runTime);

    #include "createEmptyMeshes.H"
    #include "createAirMeshes.H"
    #include "createLinearMeshes.H"
    #include "createNonlinearMeshes.H"

    #include "createAirFields.H"
    #include "createLinearFields.H"
    #include "createNonlinearFields.H"


    while (runTime.loop())
    {
	Info<< "Time = " << runTime.timeName() << nl << endl;

        forAll(linearRegions, i)
        {
            Info<< "\nSolving for linear region "
                << linearRegions[i].name() << endl;
            #include "setRegionLinearFields.H"
            #include "solveLinear.H"
        }

        forAll(nonlinearRegions, i)
        {
            Info<< "\nSolving for nonlinear region "
                << nonlinearRegions[i].name() << endl;
            #include "setRegionNonlinearFields.H"
            #include "interpolateProperties.H"
            #include "solveNonlinear.H"
        }

	forAll(airRegions, i)
        {
            Info<< "\nSolving for air region "
                << airRegions[i].name() << endl;
            #include "setRegionAirFields.H"
            #include "solveAir.H"
        }

        runTime.write();

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
