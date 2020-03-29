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
    scene_selector_ = gui.AddDroplist("Scene")->AddItemsIndexed({ "scene0", "scene1", "scene2" })->Set(0);
    render_button_ = gui.AddButton("Render")->Subscribe([this](const hiro::gui::Button*) {RenderScene(); });
}

void RayTracerGadget::RenderScene()
{
    auto selectedScene = scene_selector_->GetText() + ".txt";
    acgm::SceneImporter importer;
    bool success = importer.Import(selectedScene);
    std::cout << "Import scene successful: " << std::boolalpha << success;

    if (!success) 
    {
        return;
    }

    auto renderer = GetResource<RayTracerResource>()->GetRenderer();
    renderer->SetResolution(importer.GetRenderOptions().resolution);

    auto scene = importer.GetScene();
    scene->Raytrace(renderer);
}
