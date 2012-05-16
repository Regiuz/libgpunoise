#include <iostream>

#include "BaseApplication.h"

#include <OGRE/OgreException.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreManualObject.h>
#include <OGRE/OgreGpuProgramManager.h>
#include <OGRE/OgreHighLevelGpuProgramManager.h>

#include <boost/format.hpp>
#include <boost/foreach.hpp>
#include <boost/range/adaptor/map.hpp>

#include "gpunoise/Module3D.h"
#include "gpunoise/MPPerlin3D.h"
#include <gpunoise/Voronoi3D.h>
#include <gpunoise/Add3D.h>
#include <gpunoise/Multiply3D.h>
#include <gpunoise/Min3D.h>




struct GPUNoiseDemo : BaseApplication
{
  virtual void createScene();
  
  Ogre::ManualObject* generateNoiseQuad();
};


Ogre::ManualObject* GPUNoiseDemo::generateNoiseQuad()
{
  using namespace Ogre;
  
  ManualObject* noise_quad = mSceneMgr->createManualObject();
  
  noise_quad->begin("BaseWhite", RenderOperation::OT_TRIANGLE_LIST);
  {
    Vector3 min(-1,-1,0);
    Vector3 max( 1, 1,0);
    
    Vector3 v00(min);
    Vector3 v11(max);
    Vector3 v01(min.x, max.y, 0);
    Vector3 v10(max.x, min.y, 0);
    
    noise_quad->position(v00);
    noise_quad->textureCoord(v00);
    noise_quad->position(v01);
    noise_quad->textureCoord(v01);
    noise_quad->position(v10);
    noise_quad->textureCoord(v10);
    noise_quad->position(v11);
    noise_quad->textureCoord(v11);
    
    std::size_t i00 = 0;
    std::size_t i01 = 1;
    std::size_t i10 = 2;
    std::size_t i11 = 3;
    
    noise_quad->index(i00);
    noise_quad->index(i11);
    noise_quad->index(i01);
    
    noise_quad->index(i00);
    noise_quad->index(i10);
    noise_quad->index(i11);
  }
  noise_quad->end();

  return noise_quad;
}


void GPUNoiseDemo::createScene()
{
  using namespace Ogre;
  
  
  std::string noise_functions;
  std::string noise_name;
  
  {
    using namespace gpunoise;
    
    std::list< Module* > modules;
    
    Voronoi3DHelperModule voronoi_helper_module;
      modules.push_back(&voronoi_helper_module);
    
    Voronoi3D source1(&voronoi_helper_module);
      modules.push_back(&source1);
    Voronoi3D source2(&voronoi_helper_module);
      modules.push_back(&source2);
    
    
    source1.SetFrequency(50);
    source1.SetDisplacement(50);
    
    source2.SetSeed(3);
    source2.SetFrequency(2);
    source2.SetDisplacement(5);
    
    
    Add3D add_s12(&source1, &source2);
      modules.push_back(&add_s12);
    
    
    
    
    noise_name = add_s12.getName();
    
    ///{name => module}, to make sure the modules are unique
    std::map<std::string, Module*> unique_modules;
    
    BOOST_FOREACH(Module* module_ptr, modules)
      unique_modules[module_ptr->getName()] = module_ptr;
    
    using boost::adaptors::map_values;
    
    BOOST_FOREACH(Module* module_ptr, unique_modules | map_values)
      noise_functions += module_ptr->generate();
  }
  
  std::string vp_shader_string =
    "void vp_entry(\n"
    "  in float4 iPosition : POSITION,\n"
    "  in float2 iTexCoord0 : TEXCOORD0,\n"
    "  uniform float4x4 worldviewproj,\n"
    "\n"
    "  out float4 oViewPosition : POSITION,\n"
    "  out float2 oTexCoord0 : TEXCOORD0)\n"
    "{\n"
    "  oViewPosition = mul(worldviewproj, iPosition);\n"
    "  oTexCoord0 = iTexCoord0;\n"
    "}\n";
  
  std::string fp_shader_string =
    boost::str(boost::format(
      "%1%\n\n"
      "\n"
      "\n"
      "\n"
      "void fp_entry(\n"
      "  in float2 uv : TEXCOORD0,\n"
      "  uniform float Z,\n"
      "  out float4 oColour : COLOR)\n"
      "{\n"
      "  float noises = %2%(float3(uv.x, uv.y, Z));\n"
      //"  if (noises < 0)\n"
      //"    oColour.rgb = float3(0,1,0);\n"
      //"  else if(noises > 1)\n"
      //"    oColour.rbg = float3(1,0,0);\n"
      //"  else\n"
      "    oColour.rbg = abs(noises);\n"
      "  oColour.a = 1;\n"
      "}\n"
      ) % noise_functions % noise_name);

  std::cout << fp_shader_string << std::endl;
  
  HighLevelGpuProgramPtr fp_gpu_program = 
    HighLevelGpuProgramManager::getSingleton().createProgram("demo fp shader",
                                                             ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                             "cg",
                                                             GPT_FRAGMENT_PROGRAM);
  
  fp_gpu_program->setSource(fp_shader_string);
  //gpu_program->setSourceFile("demo_shader.cg");
  
  fp_gpu_program->setParameter("profiles", "fp40");
  fp_gpu_program->setParameter("entry_point", "fp_entry");

  fp_gpu_program->load();
  
  HighLevelGpuProgramPtr vp_gpu_program = 
    HighLevelGpuProgramManager::getSingleton().createProgram("demo vp shader",
                                                             ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                             "cg",
                                                             GPT_VERTEX_PROGRAM);
  
  vp_gpu_program->setSource(vp_shader_string);
  //gpu_program->setSourceFile("demo_shader.cg");
  
  vp_gpu_program->setParameter("profiles", "vs_1_1 arbvp1");
  vp_gpu_program->setParameter("entry_point", "vp_entry");
  vp_gpu_program->load();
  
  
  
  MaterialPtr material = MaterialManager::getSingleton().create("RTTMat", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  
  BOOST_ASSERT(material->getNumTechniques() > 0);
  
  Technique* technique = material->getTechnique(0);
  
  BOOST_ASSERT(technique->getNumPasses() > 0);
  
  Pass* pass = technique->getPass(0);
  pass->setFragmentProgram(fp_gpu_program->getName());
  pass->setVertexProgram(vp_gpu_program->getName());
  
  GpuProgramParametersSharedPtr vertexParams = pass->getVertexProgramParameters(); 
  vertexParams->setNamedAutoConstant("worldviewproj", GpuProgramParameters::ACT_WORLDVIEWPROJ_MATRIX);
  
  GpuProgramParametersSharedPtr fragmentParams = pass->getFragmentProgramParameters();
  //fragmentParams->setNamedConstant("Z", 1.0);
  fragmentParams->setNamedConstantFromTime("Z", .01);
  
  //pass->setFragmentProgramParameters();
  /*
  pass->createTextureUnitState();
  pass->createTextureUnitState();
  pass->createTextureUnitState();

  TextureUnitState *te = material->getTechnique(0)->getPass(0)->getTextureUnitState(0);
  te->setTextureName("grad4d.png");
  te->setTextureFiltering(Ogre::TFO_NONE);


  TextureUnitState *te0 = this->m_pRTTMat->getTechnique(0)->getPass(0)->getTextureUnitState(1);
  te0->setTextureName("perm.png");
  te0->setTextureFiltering(Ogre::TFO_NONE);
  */
  
  
  
  SceneNode* sn = mSceneMgr->getRootSceneNode()->createChildSceneNode();
  
  ManualObject* noise_quad = generateNoiseQuad();
  
  noise_quad->setMaterialName(0, material->getName(), material->getGroup());
  
  sn->attachObject(noise_quad);
}


int main(int argc, char **argv) {

  try {
    GPUNoiseDemo app;
    
    app.go();
  } catch( Ogre::Exception& e ) {
      std::cerr << "An exception has occured: " <<
          e.getFullDescription().c_str() << std::endl;
  }

  
  return 0;
}
