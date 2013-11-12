    PtrList<fvMesh> nonlinearRegions(rp.nonlinearRegionNames().size());

    forAll(rp.nonlinearRegionNames(), i)
    {
        Info<< "Create nonlinear mesh for region " << rp.nonlinearRegionNames()[i]
            << " for time = " << runTime.timeName() << nl << endl;

        nonlinearRegions.set
        (
            i,
            new fvMesh
            (
                IOobject
                (
                    rp.nonlinearRegionNames()[i],
                    runTime.timeName(),
                    runTime,
                    IOobject::MUST_READ
                )
            )
        );
    }
