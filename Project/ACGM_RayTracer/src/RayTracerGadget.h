#pragma once

#include <HIRO/Gadget.h>

#include <HIRO_DRAW/renderers/RasterRenderer.h>



//! Visual part of the RayTracer HIRO module.
class RayTracerGadget
  : public hiro::Gadget
{
public:
  //! Construct with a HIRO resource.
  explicit RayTracerGadget(const hiro::Resource *res);

  void Initialize() override;

  void GenerateGui(hiro::GuiGenerator& gui);

private:
  //! Structure specifying how the raster should be rendered.
  void RenderScene();

  hiro::draw::PRasterStyle style_;
  hiro::gui::Droplist* sceneSelector_;
  hiro::gui::Button* renderButton_;
  hiro::gui::NumericInt* maxReflectionDepthInput_;
  hiro::gui::NumericInt* maxTransparencyDepthInput_;
};
