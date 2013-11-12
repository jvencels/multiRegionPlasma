solve( fvm::laplacian(phi) + rhoQ/constant::electromagnetic::epsilon0 );	

E=-fvc::grad(phi);

solve (fvm::laplacian(A));

B=fvc::curl(A);

plasma.evolve();

plasma.info();
