    PtrList<fvMesh> airRegions(rp.airRegionNames().size());

    forAll(rp.airRegionNames(), i)
    {
        Info<< "Create air mesh for region " << rp.airRegionNames()[i]
            << " for time = " << runTime.timeName() << nl << endl;

        airRegions.set
        (
            i,
            new fvMesh
            (
                IOobject
                (
                    rp.airRegionNames()[i],
                    runTime.timeName(),
                    runTime,
                    IOobject::MUST_READ
                )
            )
        );
    }
