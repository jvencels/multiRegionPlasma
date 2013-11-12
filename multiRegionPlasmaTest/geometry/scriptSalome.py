# Script for computational geometry processing in the programme Salome
# Open file "geometrySalome.hdf", then "File->Load Script"

import geompy
import salome
import smesh

gg = salome.ImportComponentGUI("GEOM")
box = salome.myStudy.FindObjectByPath("/Geometry/box_tmp").GetObject()
air = salome.myStudy.FindObjectByPath("/Geometry/air_tmp").GetObject()

# cuts "air" from "box"
box = geompy.MakeCut(box, air)

# add objects in the study
id_box = geompy.addToStudy(box, "box")

# display the results
gg.createAndDisplayGO(id_box)
gg.setDisplayMode(id_box,2) 

solids = ['substrate', 'container', 'target', 'wire', 'space', 'magnet1', 'magnet2', 'ring']
# function cuts all objects from from "air"
for solid in solids:
    object0 = salome.myStudy.FindObjectByPath("/Geometry/"+solid).GetObject()
    air = geompy.MakeCut(air, object0)
    
id_air = geompy.addToStudy(air, "air")

# display the results
gg.createAndDisplayGO(id_air)
gg.setDisplayMode(id_air,2)

# ====================================================================================

# ===== Creates outer mesh of the "box" =====
objectBox = salome.myStudy.FindObjectByPath("/Geometry/box").GetObject()
listBox = geompy.ExtractShapes(objectBox, geompy.ShapeType["SHELL"], True)
Box = geompy.ExtractShapes(listBox[1], geompy.ShapeType["FACE"], True)
boxNames = ['minX', 'minY', 'minZ', 'maxZ', 'maxY', 'maxX']
for i, v in enumerate(Box):
  id_temp_common = geompy.addToStudy(v, boxNames[i])
  gg.createAndDisplayGO(id_temp_common)
  gg.setDisplayMode(id_temp_common,2)
  triaN = smesh.Mesh(v, boxNames[i])
  algo2D = triaN.Triangle(smesh.NETGEN_1D2D)
  n12_params = algo2D.Parameters()

  # decrease parameter if during computation files "domain*" are produced,
  # it means that two region surfaces intersect and more fine .stl mesh is needed
  n12_params.SetMaxSize(0.03)

  triaN.Compute()

  # command saves all surfaces of "box" region in separate files
  # !!! change "/home/juris/Desktop" to appropriate location
  triaN.ExportSTL("/home/juris/Desktop/multiRegionPlasma/multiRegionPlasmaTest/geometry/draft/"+boxNames[i]+".stl", 1)

# ===== Creates surface mesh for all regions =====
solids[0:0] = ['box', 'air']
# function finds common surfaces for each two regions, then renames them and makes surface mesh
for solid1 in solids:
  for solid2 in solids:
    if solid1 != solid2:
      object1 = salome.myStudy.FindObjectByPath("/Geometry/"+solid1).GetObject()
      list1 = geompy.ExtractShapes(object1, geompy.ShapeType["SHELL"])
      object2 = salome.myStudy.FindObjectByPath("/Geometry/"+solid2).GetObject()
      list2 = geompy.ExtractShapes(object2, geompy.ShapeType["SHELL"])
      for i in list1:
        for j in list2:
          temp_common = geompy.MakeCommon(i, j)
          prop = geompy.BasicProperties(temp_common)
          if prop[1]>0: # if common surface exist
            id_temp_common = geompy.addToStudy(temp_common, solid1+'_to_'+solid2)

            # display the results
            gg.createAndDisplayGO(id_temp_common)
            gg.setDisplayMode(id_temp_common,2)

             # "box" and "air" do not need very fine surface mesh, these are processed separately
            if (solid1=='box' and solid2=='air') or (solid1=='air' and solid2=='box'):
              meshBox = smesh.Mesh(temp_common, solid1+'_to_'+solid2)
              algoBox = meshBox.Segment()

              # decrease parameter if during computation files "domain*" are produced
              algoBox.MaxSize(0.005)

              algoBox = meshBox.Triangle(smesh.MEFISTO)
              meshBox.Compute()

              # !!! change "/home/juris/Desktop" to appropriate location
              meshBox.ExportSTL("/home/juris/Desktop/multiRegionPlasma/multiRegionPlasmaTest/geometry/draft/"+solid1+'_to_'+solid2+".stl", 1)

            else:
              meshOther = smesh.Mesh(temp_common, solid1+'_to_'+solid2)
              algoOther = meshOther.Segment()

              # decrease parameter if during computation files "domain*" are produced
              algoOther.MaxSize(0.001)

              algoOther = meshOther.Triangle(smesh.MEFISTO)
              meshOther.Compute()
              # !!! change "/home/juris/Desktop" to appropriate location
              meshOther.ExportSTL("/home/juris/Desktop/multiRegionPlasma/multiRegionPlasmaTest/geometry/draft/"+solid1+'_to_'+solid2+".stl", 1)






