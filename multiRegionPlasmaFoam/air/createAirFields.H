    // Initialise air field pointer lists

    PtrList<volScalarField> phiAir(airRegions.size());
    PtrList<volScalarField> muAir(airRegions.size());
    PtrList<volVectorField> AAir(airRegions.size());
    PtrList<volVectorField> BAir(airRegions.size());
    PtrList<dsmcCloud> plasmaAir(airRegions.size());
    PtrList<volVectorField> EAir(airRegions.size());

    // Populate air field pointer lists
    forAll(airRegions, i)
    {
        Info<< "*** Reading air mesh magnetic properties for region "
            << airRegions[i].name() << nl << endl;

        Info<< "    Adding to phi\n" << endl;

        phiAir.set
        (
            i,
            new volScalarField
            (
                IOobject
                (
                    "phi",
                    runTime.timeName(),
                    airRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                airRegions[i]
            )
        );

        Info<< "    Adding to mu\n" << endl;

	muAir.set
        (
            i,
            new volScalarField
            (
                IOobject
                (
                    "mu",
                    runTime.timeName(),
                    airRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                airRegions[i]
            )
        );

        Info<< "    Adding to A\n" << endl;
        AAir.set
        (
            i,
            new volVectorField
            (
                IOobject
                (
                    "A",
                    runTime.timeName(),
                    airRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                airRegions[i]
            )
        );

	Info<< "    Adding to B\n" << endl;
	BAir.set
	(
	    i,
	    new volVectorField
	    (
		IOobject
		(
		    "B",
		    runTime.timeName(),
		    airRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
		),
		airRegions[i]
	    )
	);

	Info<< "    Adding to E\n" << endl;
	EAir.set
	(
	    i,
	    new volVectorField
	    (
		IOobject
		(
		    "E",
		    runTime.timeName(),
		    airRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
		),
		airRegions[i]
	    )
	);

    Info<< nl << "Constructing plasmaCloud " << endl;

	plasmaAir.set
	(
	    i,
	    new dsmcCloud
	    (
		"dsmc",
		airRegions[i]
	    )
	);
    }



