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

#include "AMixedFvPatchVectorField.H"
#include "addToRunTimeSelectionTable.H"
#include "fvPatchFieldMapper.H"
#include "volFields.H"
#include "mappedPatchBase.H"
#include "surfaceFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

AMixedFvPatchVectorField::
AMixedFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF
)
:
    fixedValueFvPatchVectorField(p, iF)
{}


AMixedFvPatchVectorField::
AMixedFvPatchVectorField
(
    const AMixedFvPatchVectorField& ptf,
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    fixedValueFvPatchVectorField(ptf, p, iF, mapper)
{}


AMixedFvPatchVectorField::
AMixedFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const dictionary& dict
)
:
    fixedValueFvPatchVectorField(p, iF)
{
    if (!isA<mappedPatchBase>(this->patch().patch()))
    {
        FatalErrorIn
        (
            "AMixedFvPatchVectorField::"
            "AMixedFvPatchVectorField\n"
            "(\n"
            "    const fvPatch& p,\n"
            "    const DimensionedField<vector, volMesh>& iF,\n"
            "    const dictionary& dict\n"
            ")\n"
        )   << "\n    patch type '" << p.type()
            << "' not type '" << mappedPatchBase::typeName << "'"
            << "\n    for patch " << p.name()
            << " of field " << dimensionedInternalField().name()
            << " in file " << dimensionedInternalField().objectPath()
            << exit(FatalError);
    }

    fvPatchVectorField::operator=(vectorField("value", dict, p.size()));
}


AMixedFvPatchVectorField::
AMixedFvPatchVectorField
(
    const AMixedFvPatchVectorField& wtcsf,
    const DimensionedField<vector, volMesh>& iF
)
:
    fixedValueFvPatchVectorField(wtcsf, iF)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void AMixedFvPatchVectorField::updateCoeffs()
{
    if (updated())
    {
        return;
    }

    // Since we're inside initEvaluate/evaluate there might be processor
    // comms underway. Change the tag we use.
    int oldTag = UPstream::msgType();
    UPstream::msgType() = oldTag+1;

    // Get the coupling information from the mappedPatchBase
    const mappedPatchBase& mpp = refCast<const mappedPatchBase>
    (
        patch().patch()
    );
    const polyMesh& nbrMesh = mpp.sampleMesh();
    const fvPatch& nbrPatch = refCast<const fvMesh>
    (
        nbrMesh
    ).boundary()[mpp.samplePolyPatch().index()];

    // Force recalculation of mapping and schedule
    const mapDistribute& distMap = mpp.map();

    const AMixedFvPatchVectorField& nbrField =
    refCast
    <
        const AMixedFvPatchVectorField
    >
    (
        nbrPatch.lookupPatchField<volVectorField, vector>("A")
    );

    // Swap to obtain full local values of neighbour internal field
    vectorField nbrIntFld(nbrField.patchInternalField());
    distMap.distribute(nbrIntFld);

    const scalarField& nbrMu =
    refCast
    <
        const scalarField
    >
    (
        nbrPatch.lookupPatchField<volScalarField, scalar>("mu")
    );

    scalarField muNbr(nbrMu);
    distMap.distribute(muNbr);




    /*const vectorField& nbrField =
    refCast
    <
        const vectorField
    >
    (
        nbrPatch.lookupPatchField<volVectorField, vector>("A")
    );

    vectorField nbrIntFld(nbrField);
    distMap.distribute(nbrIntFld);*/




    scalarField mu = patch().lookupPatchField<volScalarField, scalar>("mu");

tmp<scalarField> K(mu/muNbr);

    forAll(K(), patchi)
    {
	if (K()[patchi]>1)
    	{
	    K()[patchi]=1;
	}
    }

    vectorField n = patch().nf();

    operator==
    (
	K()*nbrIntFld + (1.0 - K())*this->patchInternalField()

    );

    fixedValueFvPatchVectorField::updateCoeffs();


    // Restore tag
    UPstream::msgType() = oldTag;
}


void AMixedFvPatchVectorField::write
(
    Ostream& os
) const
{
    fixedValueFvPatchVectorField::write(os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makePatchTypeField
(
    fvPatchVectorField,
    AMixedFvPatchVectorField
);


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam


// ************************************************************************* //
