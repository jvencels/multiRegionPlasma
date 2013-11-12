    PtrList<fvMesh> linearRegions(rp.linearRegionNames().size());

    forAll(rp.linearRegionNames(), i)
    {
        Info<< "Create linear mesh for region " << rp.linearRegionNames()[i]
            << " for time = " << runTime.timeName() << nl << endl;

        linearRegions.set
        (
            i,
            new fvMesh
            (
                IOobject
                (
                    rp.linearRegionNames()[i],
                    runTime.timeName(),
                    runTime,
                    IOobject::MUST_READ
                )
            )
        );
    }
