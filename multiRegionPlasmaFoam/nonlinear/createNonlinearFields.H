    // Initialise nonlinear field pointer lists

    PtrList<graph> muGraphNonlinear(nonlinearRegions.size());

    PtrList<volScalarField> phiNonlinear(nonlinearRegions.size());
    PtrList<volScalarField> sigmaNonlinear(nonlinearRegions.size());
    PtrList<volVectorField> JNonlinear(nonlinearRegions.size());

    PtrList<volScalarField> muNonlinear(nonlinearRegions.size());
    PtrList<volVectorField> HcNonlinear(nonlinearRegions.size());
    PtrList<volVectorField> ANonlinear(nonlinearRegions.size());
    PtrList<volVectorField> BNonlinear(nonlinearRegions.size());


    // Populate nonlinear field pointer lists
    forAll(nonlinearRegions, i)
    {
        Info<< "*** Reading nonlinear mesh magnetic properties for region "
            << nonlinearRegions[i].name() << nl << endl;


	Info << "Reading mu property file and interpolate" << endl; 
	IFstream file_mu("constant"/nonlinearRegions[i].name()/"muProperties"); 
	
        muGraphNonlinear.set
        (
            i,
            new graph
		(
		"mu_data_file",
		"B_data",
		"mu_data",
		file_mu
		)
        );

        Info<< "    Adding to phi\n" << endl;

        phiNonlinear.set
        (
            i,
            new volScalarField
            (
                IOobject
                (
                    "phi",
                    runTime.timeName(),
                    nonlinearRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                nonlinearRegions[i]
            )
        );

        Info<< "    Adding to sigma\n" << endl;

        sigmaNonlinear.set
        (
            i,
            new volScalarField
            (
                IOobject
                (
                    "sigma",
                    runTime.timeName(),
                    nonlinearRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                nonlinearRegions[i]
            )
        );

        Info<< "    Adding to J\n" << endl;
        JNonlinear.set
        (
            i,
            new volVectorField
            (
                IOobject
                (
                    "J",
                    runTime.timeName(),
                    nonlinearRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                nonlinearRegions[i]
            )
        );

        Info<< "    Adding to mu\n" << endl;

        muNonlinear.set
        (
            i,
            new volScalarField
            (
                IOobject
                (
                    "mu",
                    runTime.timeName(),
                    nonlinearRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                nonlinearRegions[i]
            )
        );

        Info<< "    Adding to Hc\n" << endl;
        HcNonlinear.set
        (
            i,
            new volVectorField
            (
                IOobject
                (
                    "Hc",
                    runTime.timeName(),
                    nonlinearRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                nonlinearRegions[i]
            )
        );

        Info<< "    Adding to A\n" << endl;
        ANonlinear.set
        (
            i,
            new volVectorField
            (
                IOobject
                (
                    "A",
                    runTime.timeName(),
                    nonlinearRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
                ),
                nonlinearRegions[i]
            )
        );

	Info<< "    Adding to B\n" << endl;
	BNonlinear.set
	(
	    i,
	    new volVectorField
	    (
		IOobject
		(
		    "B",
		    runTime.timeName(),
		    nonlinearRegions[i],
                    IOobject::MUST_READ,
                    IOobject::AUTO_WRITE
		),
                nonlinearRegions[i]
	    )
	);
    }



