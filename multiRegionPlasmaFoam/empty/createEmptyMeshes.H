    PtrList<fvMesh> emptyRegions(rp.emptyRegionNames().size());

    forAll(rp.emptyRegionNames(), i)
    {
        Info<< "Create empty mesh for region " << rp.emptyRegionNames()[i]
            << " for time = " << runTime.timeName() << nl << endl;

        emptyRegions.set
        (
            i,
            new fvMesh
            (
                IOobject
                (
                    rp.emptyRegionNames()[i],
                    runTime.timeName(),
                    runTime,
                    IOobject::MUST_READ
                )
            )
        );
    }
