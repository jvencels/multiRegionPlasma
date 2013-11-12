// Code based on the cfd-online forum article http://www.cfd-online.com/Forums/openfoam-programming-development/103774-read-temperature-dependent-thermophysical-properties-file-boundaries-false.html

//Interpolation
mu.field() = interpolateXY
(
	mag(B.field()),
	muGraph.x(),
	muGraph.y()
);


//Interpolation boundary field
forAll(mu.boundaryField(), patchi)
{
	mu.boundaryField()[patchi] = interpolateXY
	(
		mag(B.boundaryField()[patchi]),
		muGraph.x(),
		muGraph.y()
	);
}
