   // const fvMesh& airMesh = airRegions[i];

    volScalarField& phi = phiAir[i];
    volScalarField& mu = muAir[i];
    volVectorField& A = AAir[i];
    volVectorField& B = BAir[i];

    dsmcCloud& plasma = plasmaAir[i];
    const volScalarField& rhoQ = airRegions[i].lookupObject<volScalarField>("rhoQ");
    volVectorField& E = EAir[i];

