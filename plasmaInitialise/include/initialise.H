PtrList<IOdictionary> dsmcInitialiseDictAir(airRegions.size());
PtrList<dsmcCloud> plasmaAir(airRegions.size());
PtrList<label> totalMoleculesAir(airRegions.size());


// Populate air field pointer lists
forAll(airRegions, i)
{
        Info<< "*** Initialising plasa for region "
            << airRegions[i].name() << nl << endl;



	Info<< "    Adding dsmcInitialiseDictAir\n" << endl;
	dsmcInitialiseDictAir.set
	(
	    i,
	    new IOdictionary
	    (
		IOobject
		(
		    "dsmcInitialiseDict",
		    airRegions[i].time().system(), //bija runTime.timeName(),
		    airRegions[i],
                    IOobject::MUST_READ_IF_MODIFIED,
                    IOobject::NO_WRITE
		)
	    )
	);

    Info<< "Initialising plasma for Time = " << runTime.timeName() << nl << endl;

	plasmaAir.set
	(
	    i,
	    new dsmcCloud
	    (
		"dsmc",
		airRegions[i],
		dsmcInitialiseDictAir[i]//???
	    )
	);

	totalMoleculesAir.set
	(
	    i,
	    new label
	    (
		plasmaAir[i].size()
	    )
	);

    if (Pstream::parRun())
    {
        reduce(totalMoleculesAir[i], sumOp<label>());
    }

    Info<< nl << "Total number of molecules added: " << totalMoleculesAir[i]
        << nl << endl;

    IOstream::defaultPrecision(15);

    if (!airRegions[i].write())
    {
        FatalErrorIn(args.executable())
            << "Failed writing dsmcCloud."
            << nl << exit(FatalError);
    }

    Info<< nl << "ClockTime = " << runTime.elapsedClockTime() << " s"
        << nl << endl;

}



