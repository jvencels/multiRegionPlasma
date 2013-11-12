  //  const fvMesh& nonlinearMesh = nonlinearRegions[i];

    graph& muGraph = muGraphNonlinear[i];

    volScalarField& phi = phiNonlinear[i];
    volScalarField& sigma = sigmaNonlinear[i];
    volVectorField& J = JNonlinear[i];

    volScalarField& mu = muNonlinear[i];
    volVectorField& Hc = HcNonlinear[i];
    volVectorField& A = ANonlinear[i];
    volVectorField& B = BNonlinear[i];

