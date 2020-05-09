#include "RayTracerResource.h"
#include "RayTracerGadget.h"

#include <ACGM_RayTracer_lib/SceneImporter.h>




RayTracerGadget::RayTracerGadget(const hiro::Resource *res)
  : hiro::Gadget(res)
{
}

void RayTracerGadget::Initialize()
{
  hiro::Gadget::Initialize();
  style_ = std::make_shared<hiro::draw::RasterStyle>();
  style_->use_nearest_filtering = true;
  auto renderer = GetResource<RayTracerResource>()->GetRenderer();
  AddRenderer(renderer, style_);


}

void RayTracerGadget::GenerateGui(hiro::GuiGenerator& gui)
{
    const std::vector<std::string> scenes = { "scene0", "scene1", "scene2", "scene3", "scene4", "scene5", "scene6", "scene7", "scene8" };
    sceneSelector_ = gui.AddDroplist("Scene")->AddItemsIndexed(scenes)->Set(0);
    renderButton_ = gui.AddButton("Render")->Subscribe([this](const hiro::gui::Button*) {RenderScene(); });
    maxReflectionDepthInput_ = gui.AddNumericInt("Max reflection depth")->Set(10);
    maxTransparencyDepthInput_ = gui.AddNumericInt("Max transparency depth")->Set(10);
}

void RayTracerGadget::RenderScene()
{
    auto selectedScene = sceneSelector_->GetText() + ".txt";
    acgm::SceneImporter importer;
    bool success = importer.Import(selectedScene);
    std::cout << "Import scene successful: " << std::boolalpha << success;

    if (!success) 
    {
        return;
    }

    auto renderer = GetResource<RayTracerResource>()->GetRenderer();
    renderer->SetResolution(importer.GetRenderOptions().resolution);

    int maxReflectionDepth = maxReflectionDepthInput_->Get();
    int maxTransparencyDepth = maxTransparencyDepthInput_->Get();

    auto scene = importer.GetScene();
    scene->SetMaxReflectionDepth(maxReflectionDepth);
    scene->SetMaxTransparencyDepth(maxTransparencyDepth);
    scene->Raytrace(renderer);
}
