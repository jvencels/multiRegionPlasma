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

Class
    regionProperties

Description
    Simple class to hold region information for coupled region simulations

SourceFiles
    regionProperties.C

\*---------------------------------------------------------------------------*/

#ifndef regionProperties_H
#define regionProperties_H

#include "IOdictionary.H"
#include "Time.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                       Class regionProperties Declaration
\*---------------------------------------------------------------------------*/

class regionProperties
:
    public IOdictionary
{
    // Private data

        //- List of the empty region names
        List<word> emptyRegionNames_;

        //- List of the air region names
        List<word> airRegionNames_;

        //- List of the linear region names
        List<word> linearRegionNames_;

        //- List of the nonlinear region names
        List<word> nonlinearRegionNames_;


    // Private Member Functions

        //- Disallow default bitwise copy construct
        regionProperties(const regionProperties&);

        //- Disallow default bitwise assignment
        void operator=(const regionProperties&);


public:

    // Constructors

        //- Construct from components
        regionProperties(const Time& runTime);


    //- Destructor
    ~regionProperties();


    // Member Functions

        // Access

            //- Return const reference to the list of empty region names
            const List<word>& emptyRegionNames() const;

            //- Return const reference to the list of air region names
            const List<word>& airRegionNames() const;

            //- Return const reference to the list of linear region names
            const List<word>& linearRegionNames() const;

            //- Return const reference to the list of nonlinear region names
            const List<word>& nonlinearRegionNames() const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
