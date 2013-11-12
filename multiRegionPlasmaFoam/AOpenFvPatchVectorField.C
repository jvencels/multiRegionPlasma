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

#include "AOpenFvPatchVectorField.H"
#include "volFields.H"

#include "addToRunTimeSelectionTable.H"
#include "fvPatchFieldMapper.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

namespace Foam
{

AOpenFvPatchVectorField::AOpenFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF
)
:
    fixedValueFvPatchVectorField(p, iF),
    radius_(p.size())
{}

AOpenFvPatchVectorField::AOpenFvPatchVectorField
(
    const AOpenFvPatchVectorField& ptf,
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    fixedValueFvPatchVectorField(ptf, p, iF, mapper),
    radius_(ptf.radius_, mapper)
{}


AOpenFvPatchVectorField::AOpenFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const dictionary& dict
)
:
    fixedValueFvPatchVectorField(p, iF),
    radius_("radius", dict, p.size())
{
    fvPatchVectorField::operator=(vectorField("value", dict, p.size()));
}


AOpenFvPatchVectorField::AOpenFvPatchVectorField
(
    const AOpenFvPatchVectorField& ptf
)
:
    fixedValueFvPatchVectorField(ptf),
    radius_(ptf.radius_)
{}


AOpenFvPatchVectorField::AOpenFvPatchVectorField
(
    const AOpenFvPatchVectorField& ptf,
    const DimensionedField<vector, volMesh>& iF
)
:
    fixedValueFvPatchVectorField(ptf, iF),
    radius_(ptf.radius_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void AOpenFvPatchVectorField::updateCoeffs()
{
    if (this->updated())
    {
        return;
    }

    tmp<vectorField> intFld = patchInternalField();

    vectorField n = patch().nf();

    operator==
    (
        transform(I - n*n, intFld)/(1/(patch().deltaCoeffs()*radius_)+1)
    );

    fixedValueFvPatchVectorField::updateCoeffs();
}


void AOpenFvPatchVectorField::write(Ostream& os) const
{
    fixedValueFvPatchVectorField::write(os);
    os.writeKeyword("radius")<< radius_
        << token::END_STATEMENT << nl;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

makePatchTypeField
(
    fvPatchVectorField,
    AOpenFvPatchVectorField
);

} // End namespace Foam
// ************************************************************************* //
