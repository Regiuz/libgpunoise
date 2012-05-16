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
    
    std::list< Module3D* > modules;
    
    MPPerlin3D source1;
    
    
    
    modules.push_back(&source1);
    
    ///{name => module}, to make sure the modules are unique
    std::map<std::string, Module3D*> unique_modules;
    
    BOOST_FOREACH(Module3D* module_ptr, modules)
      unique_modules[module_ptr->getName()] = module_ptr;
    
    using boost::adaptors::map_values;
    
    BOOST_FOREACH(Module3D* module_ptr, unique_modules | map_values)
      noise_functions += module_ptr->generate();
  }
  
  
  
  std::string shader_string =
    boost::str(boost::format(
      "%1%"
      "void fp_entry("
        "in float2 uv : TEXCOORD0,\n"
        "out float4 oColour : COLOR)\n"
      "{ oColour = %2%(uv.u, uv.v, 0); }") % noise_functions % noise_name);

  
  HighLevelGpuProgramPtr gpu_program = 
    HighLevelGpuProgramManager::getSingleton().createProgram("demo shader",
                                                             ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                             "cg",
                                                             GPT_FRAGMENT_PROGRAM);
  
  gpu_program->setSource(shader_string);
  //gpu_program->setSourceFile("demo_shader.cg");
  
  gpu_program->setParameter("profiles", "ps_3_0 fp40");
  gpu_program->setParameter("entry_point", "fp_entry");

  
  gpu_program->load();
  
  
  
  MaterialPtr material = MaterialManager::getSingleton().create("RTTMat", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  
  BOOST_ASSERT(material->getNumTechniques() > 0);
  
  Technique* technique = material->getTechnique(0);
  
  BOOST_ASSERT(technique->getNumPasses() > 0);
  
  Pass* pass = technique->getPass(0);
  pass->setFragmentProgram(gpu_program->getName());
  
  
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
