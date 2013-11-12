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

#include "phiOpenFvPatchScalarField.H"
#include "volFields.H"

#include "addToRunTimeSelectionTable.H"
#include "fvPatchFieldMapper.H"

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

namespace Foam
{

phiOpenFvPatchScalarField::phiOpenFvPatchScalarField
(
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF
)
:
    fixedValueFvPatchScalarField(p, iF),
    radius_(p.size())
{}

phiOpenFvPatchScalarField::phiOpenFvPatchScalarField
(
    const phiOpenFvPatchScalarField& ptf,
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    fixedValueFvPatchScalarField(ptf, p, iF, mapper),
    radius_(ptf.radius_, mapper)
{}


phiOpenFvPatchScalarField::phiOpenFvPatchScalarField
(
    const fvPatch& p,
    const DimensionedField<scalar, volMesh>& iF,
    const dictionary& dict
)
:
    fixedValueFvPatchScalarField(p, iF),
    radius_("radius", dict, p.size())
{
    fvPatchScalarField::operator=(scalarField("value", dict, p.size()));
}


phiOpenFvPatchScalarField::phiOpenFvPatchScalarField
(
    const phiOpenFvPatchScalarField& ptf
)
:
    fixedValueFvPatchScalarField(ptf),
    radius_(ptf.radius_)
{}


phiOpenFvPatchScalarField::phiOpenFvPatchScalarField
(
    const phiOpenFvPatchScalarField& ptf,
    const DimensionedField<scalar, volMesh>& iF
)
:
    fixedValueFvPatchScalarField(ptf, iF),
    radius_(ptf.radius_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void phiOpenFvPatchScalarField::updateCoeffs()
{
    if (this->updated())
    {
        return;
    }

    tmp<scalarField> intFld = patchInternalField();

    vectorField n = patch().nf();

    operator==
    (
        transform(I - n*n, intFld)/(1/(patch().deltaCoeffs()*radius_)+1)
    );

    fixedValueFvPatchScalarField::updateCoeffs();
}


void phiOpenFvPatchScalarField::write(Ostream& os) const
{
    fixedValueFvPatchScalarField::write(os);
    os.writeKeyword("radius")<< radius_
        << token::END_STATEMENT << nl;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

makePatchTypeField
(
    fvPatchScalarField,
    phiOpenFvPatchScalarField
);

} // End namespace Foam
// ************************************************************************* //
