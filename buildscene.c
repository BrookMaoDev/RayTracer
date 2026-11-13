 // Sets up all objects in the scene. This involves creating each object,
 // defining the transformations needed to shape and position it as
 // desired, specifying the reflectance properties (albedos and colours)
 // and setting up textures where needed.
 // Light sources must be defined, positioned, and their colour defined.
 // All objects must be inserted in the object_list. All light sources
 // must be inserted in the light_list.
 //
 // To create hierarchical objects:
 //    You must keep track of transformations carried out by parent objects
 //    as you move through the hierarchy. Declare and manipulate your own
 //    transformation matrices (use the provided functions in utils.c to
 //    compound transformations on these matrices). When declaring a new
 //    object within the hierarchy
 //    - Initialize the object
 //    - Apply any object-level transforms to shape/rotate/resize/move
 //      the object using regular object transformation functions
 //    - Apply the transformations passed on from the parent object
 //      by pre-multiplying the matrix containing the parent's transforms
 //      with the object's own transformation matrix.
 //    - Compute and store the object's inverse transform as usual.
 //
 // NOTE: After setting up the transformations for each object, don't
 //       forget to set up the inverse transform matrix!

 struct object3D *o;
 struct pointLS *l;
 struct point3D p;

 // Feature toggles: pick the scene and turn features on with -D when compiling (no flags = the
 // plain scene with no textures and a point light). demo/scripts/ has a script for each one.
 //   SCENE_REFRACTION  Use the refraction scene below instead (a marble inside a glass sphere)
 //   SCENE_FIBONACCI   Use the Fibonacci word fractal scene below instead
 //   TEXTURES          Texture map every object
 //   NORMALS           Add the matching normal map to every object
 //   ALS               Replace the point light with an area light (soft shadows)
 //   ALPHA             Put a lattice alpha map on both spheres

#if !defined(SCENE_REFRACTION) && !defined(SCENE_FIBONACCI)
 // Simple scene for Assignment 3:
 // Insert a couple of objects. A plane and two spheres
 // with some transformations.

 // Note the parameters: ra, rd, rs, rg, R, G, B, alpha, r_index, and shinyness)

 o=newSphere(.05,.95,.35,.35,1,.25,.25,1,1,6);		// Initialize a sphere
 Scale(o,1.5,.75,.75);					// Apply a few transforms (Translate * Rotate * Scale)
 RotateZ(o,PI/4);					
 Translate(o,2.0,2.5,1.5);
 invert(&o->T[0][0],&o->Tinv[0][0]);			// Compute the inverse transform * DON'T FORGET TO DO THIS! *

 // If needed, this is how you load a texture map
#ifdef TEXTURES
 loadTexture(o, "./textures/colors/Poliigon_WoodVeneerOak_7760_BaseColor.ppm", 1, &texture_list); // This loads a texture called 'Poliigon_WoodVeneerOak_7760_BaseColor.ppm'. The
																								   // texture gets added to the texture list, and a
																								   // pointer to it is stored within this object in the
																								   // corresponding place. The '1' indicates this image
																								   // will be used as a texture map. Use '2' to load
																								   // an image as a normal map, and '3' to load an
																								   // alpha map. Texture and normal maps are RGB .ppm
																								   // files, alpha maps are grayscale .pgm files.
																								   // * DO NOT * try to free image data loaded in this
																								   // way, the cleanup function already provided will do
																								   // this at the end.
#endif
#ifdef NORMALS
 loadTexture(o, "./textures/normals/Poliigon_WoodVeneerOak_7760_Normal.ppm", 2, &texture_list);
#endif
#ifdef ALPHA
 loadTexture(o, "./textures/alphas/lattice.pgm", 3, &texture_list);
#endif
 insertObject(o, &object_list); // <-- If you don't insert the object into the object list,
								//     nothing happens! your object won't be rendered.

 // That's it for defining a single sphere... let's add a couple more objects
 o=newSphere(.05,.95,.95,.75,.75,.95,.55,1,1,6);
 Scale(o,.95,1.65,.65);
 RotateZ(o,-PI/1.5);
 Translate(o,-2.2,1.75,1.35);
 invert(&o->T[0][0],&o->Tinv[0][0]);
#ifdef TEXTURES
 loadTexture(o, "./textures/colors/Poliigon_MetalGoldPaint_7253_BaseColor.ppm", 1, &texture_list);
#endif
#ifdef NORMALS
 loadTexture(o, "./textures/normals/Poliigon_MetalGoldPaint_7253_Normal.ppm", 2, &texture_list);
#endif
#ifdef ALPHA
 loadTexture(o, "./textures/alphas/lattice.pgm", 3, &texture_list);
#endif
 insertObject(o, &object_list);

 o=newPlane(.05,.75,.05,.05,.55,.8,.75,1,1,2);
 Scale(o,11,11,11);
 RotateZ(o,PI/4);
 RotateX(o, -PI / 2);
 Translate(o,0,-4,5);
 invert(&o->T[0][0],&o->Tinv[0][0]);
#ifdef TEXTURES
 loadTexture(o, "./textures/colors/Poliigon_StoneQuartzite_8060_BaseColor.ppm", 1, &texture_list);
#endif
#ifdef NORMALS
 loadTexture(o, "./textures/normals/Poliigon_StoneQuartzite_8060_Normal.ppm", 2, &texture_list);
#endif
 insertObject(o,&object_list);

 // Insert a single point light source. We set up its position as a point structure, and specify its
 // colour in terms of RGB (in [0,1]).
#ifndef ALS
 p.px=0;
 p.py=25.5;
 p.pz=-3.5;
 p.pw=1;
 l=newPLS(&p,.95,.95,.95);
 insertPLS(l,&light_list);
#else
 // Area light in place of the point light above: a 4x4 rectangle at the same position, facing
 // down, sampled with 64 point lights per shading call. Render with antialiasing on so each
 // pixel averages 16 x 64 light samples and the penumbra is smooth.
 addAreaLight(4, 4, 0, -1, 0, 0, 25.5, -3.5, 64, .95, .95, .95, &object_list, &light_list);
#endif
#elif defined(SCENE_REFRACTION)
 // Refraction scene: a glass marble inside a larger glass sphere on a wooden table, in front of a marble wall
 // Note the parameters: ra, rd, rs, rg, R, G, B, alpha, r_index, and shinyness)

 // Table
 o=newPlane(.1,.8,.1,.05,1,1,1,1,1,4);
 Scale(o,10,10,10);
 RotateX(o,-PI/2);
 Translate(o,0,-1.5,6);
 invert(&o->T[0][0],&o->Tinv[0][0]);
 loadTexture(o, "./textures/colors/Poliigon_WoodVeneerOak_7760_BaseColor.ppm", 1, &texture_list);
 insertObject(o,&object_list);

 // Wall
 o=newPlane(.1,.8,.1,.05,1,1,1,1,1,4);
 Scale(o,10,10,10);
 Translate(o,0,7,8);
 invert(&o->T[0][0],&o->Tinv[0][0]);
 loadTexture(o, "./textures/colors/Poliigon_StoneQuartzite_8060_BaseColor.ppm", 1, &texture_list);
 insertObject(o,&object_list);

 // The rest of the room: walls behind and beside the camera and a ceiling above the light. The
 // camera never sees these directly, but without them the glass reflects the black background.
 o=newPlane(.3,.6,0,0,.85,.83,.8,1,1,1);	// Behind the camera
 Scale(o,10,10,10);
 Translate(o,0,7,-6);
 invert(&o->T[0][0],&o->Tinv[0][0]);
 insertObject(o,&object_list);

 o=newPlane(.3,.6,0,0,.85,.83,.8,1,1,1);	// Left
 Scale(o,10,10,10);
 RotateY(o,PI/2);
 Translate(o,-7,7,1);
 invert(&o->T[0][0],&o->Tinv[0][0]);
 insertObject(o,&object_list);

 o=newPlane(.3,.6,0,0,.85,.83,.8,1,1,1);	// Right
 Scale(o,10,10,10);
 RotateY(o,PI/2);
 Translate(o,7,7,1);
 invert(&o->T[0][0],&o->Tinv[0][0]);
 insertObject(o,&object_list);

 o=newPlane(.3,.6,0,0,.85,.83,.8,1,1,1);	// Ceiling
 Scale(o,10,10,10);
 RotateX(o,-PI/2);
 Translate(o,0,12,1);
 invert(&o->T[0][0],&o->Tinv[0][0]);
 insertObject(o,&object_list);

 // Two nested objects: a clear glass sphere (n = 1.5) with a blue marble of denser glass
 // (n = 1.9) inside it. Each ray keeps a stack of the objects it is inside, so every surface it
 // crosses uses the right indices on both sides (air -> glass -> marble -> glass -> air). The
 // marble sits strictly inside the outer sphere so their surfaces never touch.

 // Outer sphere: radius 1.2, resting on the table (y = -1.5)
 o=newSphere(.02,.1,.6,.3,.9,.95,1,.1,1.5,80);
 Scale(o,1.2,1.2,1.2);
 Translate(o,0,-.299,1.8);
 invert(&o->T[0][0],&o->Tinv[0][0]);
 insertObject(o,&object_list);

 // Inner marble: blue glass, at the centre of the outer sphere
 o=newSphere(.1,.7,.8,.3,.1,.35,.95,.5,1.9,100);
 Scale(o,.35,.35,.35);
 Translate(o,0,-.299,1.8);
 invert(&o->T[0][0],&o->Tinv[0][0]);
 insertObject(o,&object_list);

 // Key light up and to the left, behind the camera
 p.px=-4;
 p.py=10;
 p.pz=-2;
 p.pw=1;
 l=newPLS(&p,.95,.95,.95);
 insertPLS(l,&light_list);
#else
 // Fibonacci word fractal scene. The word starts as "0", and each generation replaces every 0
 // with 01 and every 1 with 0 (0, 01, 010, 01001, ...). The fractal is drawn by walking the word:
 // take a step forward on every digit, and on a 0 also turn left if the step is even and right
 // if it is odd.
 // TODO: generate the word with fibonacci() and fibonacciWord() (utils.c) and place objects
 //       along the path.
#endif

 // End of simple scene for Assignment 2
 // Keep in mind that you can define new types of objects such as cylinders and parametric surfaces,
 // or, you can create code to handle arbitrary triangles and then define objects as surface meshes.
 //
 // Remember: A lot of the quality of your scene will depend on how much care you have put into defining
 //           the relflectance properties of your objects, and the number and type of light sources
 //           in the scene.
 
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////
 // TO DO: For Assignment 3 you *MUST* define your own cool scene.
 //	   We will be looking for the quality of your scene setup, the use of hierarchical or composite
 //	   objects that are more interesting than the simple primitives from A2, the use of textures
 //        and other maps, illumination and illumination effects such as soft shadows, reflections and
 //        transparency, and the overall visual quality of your result. Put some work into thinking
 //        about these elements when designing your scene.
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////
