solve
(
    fvm::laplacian(phi)
);



/*J=-sigma*fvc::grad(phi) + fvc::curl(Hc)*mu;
J.correctBoundaryConditions();

solve
(
    fvc::curl(fvc::curl(A)/mu) - fvm::laplacian(1/mu, A) == J*constant::electromagnetic::mu0/mu
);*/




/*J=-sigma*fvc::grad(phi);

solve
(
    fvc::curl(fvc::curl(A)/mu) - fvm::laplacian(1/mu, A) == (J+fvc::curl(Hc)) *constant::electromagnetic::mu0
);*/



J=-sigma*fvc::grad(phi)+fvc::curl(Hc);
J.correctBoundaryConditions();

solve
(
    - fvm::laplacian(A) == J*constant::electromagnetic::mu0*mu
);




B=fvc::curl(A);

//H=B/constant::electromagnetic::mu0/mu;

