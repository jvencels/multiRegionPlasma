solve
(
	fvm::laplacian(phi)
);

/*J=-sigma*fvc::grad(phi) + fvc::curl(Hc)*mu;
J.correctBoundaryConditions();

solve
(
	- fvm::laplacian(A) == J*mu*constant::electromagnetic::mu0/mu
);*/




/*J=-sigma*fvc::grad(phi);

solve
(
	- fvm::laplacian(A) == (J+fvc::curl(Hc))*constant::electromagnetic::mu0*mu
);*/



J=-sigma*fvc::grad(phi)+fvc::curl(Hc);
J.correctBoundaryConditions();

solve
(
    - fvm::laplacian(A) == J*constant::electromagnetic::mu0*mu
);


B=fvc::curl(A);

//H=B/constant::electromagnetic::mu0/mu;

