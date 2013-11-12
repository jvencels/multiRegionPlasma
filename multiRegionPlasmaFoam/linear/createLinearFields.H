    // Initialise linear field pointer lists

    PtrList<volScalarField> phiLinear(linearRegions.size());
    PtrList<volScalarField> sigmaLinear(linearRegions.size());
    PtrList<volVectorField> JLinear(linearRegions.size());

    PtrList<volScalarField> muLinear(linearRegions.size());
    PtrList<volVectorField> HcLinear(linearRegions.size());
    PtrList<volVectorField> ALinear(linearRegions.size());
    PtrList<volVectorField> BLinear(linearRegions.size());
    PtrList<volVectorField> JHcLinear(linearRegions.size());


    // Populate linear field pointer lists
    forAll(linearRegions, i)
    {
        Info<< "*** Reading linear mesh magnetic properties for region "
            << linearRegions[i].name() << nl << endl;


        Info<< "    Adding to phi\n" << endl;

        phiLinear.set
        (
            i,
            new volScalarField
            (
                IOobject
                (
                    "phi",
                    runTime.timeName(),
                    linearRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                linearRegions[i]
            )
        );

        Info<< "    Adding to sigma\n" << endl;

        sigmaLinear.set
        (
            i,
            new volScalarField
            (
                IOobject
                (
                    "sigma",
                    runTime.timeName(),
                    linearRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                linearRegions[i]
            )
        );

        Info<< "    Adding to J\n" << endl;
        JLinear.set
        (
            i,
            new volVectorField
            (
                IOobject
                (
                    "J",
                    runTime.timeName(),
                    linearRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                linearRegions[i]
            )
        );

        Info<< "    Adding to sigma\n" << endl;

        muLinear.set
        (
            i,
            new volScalarField
            (
                IOobject
                (
                    "mu",
                    runTime.timeName(),
                    linearRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                linearRegions[i]
            )
        );

        Info<< "    Adding to Hc\n" << endl;
        HcLinear.set
        (
            i,
            new volVectorField
            (
                IOobject
                (
                    "Hc",
                    runTime.timeName(),
                    linearRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                linearRegions[i]
            )
        );

        Info<< "    Adding to A\n" << endl;
        ALinear.set
        (
            i,
            new volVectorField
            (
                IOobject
                (
                    "A",
                    runTime.timeName(),
                    linearRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                linearRegions[i]
            )
        );

	Info<< "    Adding to B\n" << endl;
	BLinear.set
	(
	    i,
	    new volVectorField
	    (
		IOobject
		(
		    "B",
		    runTime.timeName(),
		    linearRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
		),
                linearRegions[i]
	    )
	);
    }



