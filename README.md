# multiRegionPlasma

**multiRegionPlasma** is a program to model electromagnetic field and
trajectories of charged particles. It contains five parts:
* *multiRegionPlasmaFoam* - does computations of fields and particles;
* *multiRegionPlasmaTest* - demonstration example to model electric and
magnetic fields and electron trajectories in simple circular magnetron
sputtering system;
* *plasmaInitialise* - initializes charged particles.
* *basic* and *dsmc* are modified OpenFOAM libraries.


## License
The program is licensed under GNU General Public License, for details
see `LICENSE.md`.


## Running
The program tested on **OpenFOAM 2.2.2**. If you are using version **2.1.x or older**
then probably you need to delete file *system/surfaceFeatureExtractDict* and
instead write few lines in the file *multiRegionPlasmaTest/Allrun*.
For example look [here.](https://github.com/OpenFOAM/OpenFOAM-2.1.x/blob/master/tutorials/heatTransfer/chtMultiRegionFoam/snappyMultiRegionHeater/Allrun)

To begin, copy *multiRegionPlasma* folder to your working directory.
No changes will be made to your original OpenFOAM program.


### Program compiling
Make appropriate changes in addresses that contains */home/juris/Desktop/* in
such files:
* *dsmc/Make/options*
* *multiRegionPlasmaFoam/Make/options*

To compile:
> cd basic
> wmake libso
> cd ../dsmc
> wmake libso
> cd ../plasmaInitialise
> chmod +x Allrun
> ./Allrun
> cd ../multiRegionPlasmaFoam
> chmod +x Allrun
> ./Allrun

Now in the folder */home/juris/OpenFOAM/juris-2.2.0/platforms/* you will find
compiled libraries and program.


### Demonstrational example
The example *multiRegionPlasmaTest* uses around 1.5 GB of RAM, its execution
takes around one hour (around half is used for the mesh generation).


#### Geometry processing
If you want just to try the program, you can skip this step.

Geometry and .stl file generation files are located in
*multiRegionPlasmaTest/geometry*.
1. Make appropriate changes to adresses that contains */home/juris/Desktop/* in
the file *scriptSalome.py*.
2. Open Salome and open *geometrySalome.hdf*. In *Geometry* module you can see
geometry of regions. Note that some flat surfaces are splitted. 
3. To cut *air* region from *box* and to find surface pairs between two
neighbouring regions use script. Do "File->Load Script", then choose
*scriptSalome.py*. This script finds surface pairs, renames them and makes .stl
surface mesh (it is not computational mesh). Surface mesh will be saved in the
*draft* folder.
4. To merge these .stl files together use bash script *mergeFiles*.
> cd multiRegionPlasmaTest/geometry
> chmod +x mergeFiles
> ./mergeFiles
This script will merge all appropriate files together and result will be copied
to the folder *final*. Here you will find surface files that correspond to each
region.
5. Copy these region surface meshes to folder *constant/triSurface*.

#### Running the example
> cd multiRegionPlasmaTest
> chmod +x Allrun
> ./Allrun

#### Possible problems during a run

If during test example execution the program produces *domain* * folders then
it means that .stl surface meshes intersect and *splitMeshRegions* interprets
intersections as a separate regions. To solve it try increase change .stl mesh
refinement, look *scriptSalome.py* for
details.

If *splitMeshRegions* produces error then most probably you must increase
refinement of *blockMesh* mesh. Look *constant/polyMesh/blockMeshDict*.

#### Changes to make
Particle initialization can be specified in the *constant/air/dsmcProperties*.
Here you can add other species, set superparticles etc.
Magnetic permiability dependence can be specified in the
*constant/wire/muProperties*.

### Post processing
Open ParaView and open appropriate region file, for example 
*multiRegionPlasmaTest{air}.OpenFOAM*. Do not use the command *paraFoam*,
because it will not be able to handle multi-region case.
To see particles, open the *air* region, change time step to bigger value,
because initially there are no particles initialized. Then choose lagrangian
fields. 


## Purpose of the program
Program was designed as a part of Bachelor's thesis. The purpose was to
create a tool to optimize magnetron sputtering process. OpenFOAM was
chosen as a basis because of free availability, open source code and large
community. Bachelor's thesis can be found in the 
[cfd-online forum.](http://www.cfd-online.com/Forums/openfoam-solving/)
The work is written in Latvian because of compulsory requirement. 


### What is done
You can use program *Kompare* to see the changes made.

#### General
Pre-processing:
* Geometry export from Salome, .stl file processing.

Electric and magnetic fields:
* Electric field calculation via electric scalar potential.
* Magnetic field calculation via vectorial magnetic potential.
* Hybrid boundary conditions for magnetic vector potential on boundaries
between two regions.
* Magnetic permeability dependence on magnetic field strength.
* Open boundary conditions (infinite space) [see 4.2.1].

Particles:
* Particles can be initialized in one or many separate regions. 
* Particles of different species (charges, masses etc.).
* Particles can be initialized from any specific boundary (inlet).

#### Specific
* In *basic* library added possibility for particle to hit mappedPatch.
See *basic/particle/particleTemplates.C*.
* In *dsmc*  library added fields *rhoQ* - charge density.
See *DsmcCloud.C*, *DsmcCloud.H*, *DsmcCloudI.H*.

PIC is realized in the file *DsmcParcel.C*. Here the program reads the electric
field and uses RK4 to compute particle velocity. Then collects charge from all
particles in the cell.

Charge defined in *DsmcParcel.H* and *DsmcParcelI.H*

Particles can be initialized from mapped patch, see *FreeStream.C*.

* *plasmaInitialise* is based on *dsmcInitialise*.
* *multiRegionPlasmaFoam* is based on *chtMultiRegionFoam* and *dsmcFoam*.
I used ideas of Zhe Huang [master thesis](http://webfiles.portal.chalmers.se/et/MSc/ZheHuangMSc.pdf) to compute 
magnetic field via magnetic vectorpotential. Idea how to make magnetic
permiability dependent from strenght of magnetic field comes from Anja Miehe
post in the [cfd-online forum](http://www.cfd-online.com/Forums/openfoam-programming-development/103774-read-temperature-dependent-thermophysical-properties-file-boundaries-false.html).


* *multiRegionPlasmaTest* is based on *snappyMultiRegionHeater* and
*freeSpaceStream*.


### OpenFOAM additional benefits
* You can run the program in parallel. Modify all *decomposeParDict* files,
these you can find in the folders *system* and also *system/'regionName'*. 


### Magnetron sputtering
To answer the question about handling such problem in OpenFOAM, I will note
some unsolved problems in the work.

Appropriate boundary conditions for magnetic vector potential are quite
difficult to realize properly. There are some cases when magnetic field vectors
are parallel to ferromagnetic surface, in this case boundary conditions are 
calculated quite wrongly [see page 32].
I came with mixed boundary conditions [see 4.2.4], but even these BC do not
solve the problem stated before.
I tried other formulations, but solutions diverged.

Magnetic field have gradient on magnet surfaces [compare Fig. 4.25 and 4.26].
I think it is because of curl scheme that is used to compute magnetization
currents around magnets.

Simple interpolation scheme was used for PIC (Particle In Cell). OpenFOAM
is FVM program that stores fields in cell centers, consequently all charged 
particles belongs to the total charge in the center of cell. I have not done
further studies, but seems that energy is not conserved. Try to avoid large
charge gradients in the simulation. I did two and one electron beam
simulations and compared  results with self-written program in C++ [see 5.3.2].
Red particles are from OpenFOAM, blue - from C++ program that uses
particle-particle interaction model.


### Possible applications
* Salome script `scriptSalome.py` and Bash script `mergeFiles` can be used
to generate complicated geometries and export them to the OpenFOAM.
* Heat and mass transfer equations can be added to **multiRegionFOAM** and
rarefied gas dynamics can be studied in complicated geometry cases.


## Contact information
Private email:
juris.vencels@gmail.com

For general questions:
http://www.cfd-online.com/Forums/openfoam-solving/
